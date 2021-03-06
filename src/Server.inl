
/*
	Copyright (C) 2019 Marek Zalewski aka Drwalin - All Rights Reserved
	
	Any one is authorized to copy, use or modify this file,
	but only when this file is marked as written by Marek Zalewski.
	
	No one can claim this file is originally written by them.
	
	No one can modify or remove this Copyright notice from this file.
*/

#ifndef SERVER_INL
#define SERVER_INL

namespace ICon
{
	template < typename CallBackType, typename... Args >
	void _Server_AcceptNoLock_ThreadFunction_OneAccept( std::shared_ptr<Server> server, std::shared_ptr<HighLayerSocket> con, CallBackType callBackFunction, Args... args )
	{
		server->AcceptNoLockRunned( con, callBackFunction, args... );
	}
	
	template < typename CallBackType, typename... Args >
	void _Server_AcceptNoLock_ThreadFunction_OneAccept( std::shared_ptr<Server> server, CallBackType callBackFunction, Args... args )
	{
		server->AcceptNoLockRunned( callBackFunction, args... );
	}
	
	
	template < typename CallBackType, typename... Args >
	void Server::AcceptNoLockRunned( std::shared_ptr<HighLayerSocket> con, CallBackType callBackFunction, Args... args )
	{
		while( this->Accept( con ) != ICon::Error::none ){}
		this->isAcceptNoLockRunning.store( false );
		callBackFunction( con, args... );
	}
	
	template < typename CallBackType, typename... Args >
	void Server::AcceptNoLockRunned( CallBackType callBackFunction, Args... args )
	{
		while( this->keepAcceptNoLockRunning.load() == true )
		{
			std::shared_ptr<HighLayerSocket> con( new HighLayerSocket );
			if( this->Accept( con ) == ICon::Error::none )
			{
				if( con->IsValid() )
				{
					std::thread( callBackFunction, con, args... ).detach();
				}
			}
		}
		this->isAcceptNoLockRunning.store( false );
	}
	
	
	template < typename CallBackType, typename... Args >
	void Server::AcceptNoLock( std::shared_ptr<HighLayerSocket> con, CallBackType callBackFunction, Args... args )
	{
		if( this->opened )
		{
			if( this->isAcceptNoLockRunning.load() == false )
			{
				if( con )
				{
					this->isAcceptNoLockRunning.store( true );
					std::thread( _Server_AcceptNoLock_ThreadFunction_OneAccept, self, con, callBackFunction, args... ).detach();
				}
				else
				{
					ICon::Error::Push( ICon::Error::tryingToAcceptToUnallocatedHighSocketLayer, __LINE__, __FILE__ );
				}
			}
			else
			{
				ICon::Error::Push( ICon::Error::tryingToRunSecondInstancOfAcceptNoLock, __LINE__, __FILE__ );
			}
		}
		else
		{
			ICon::Error::Push( ICon::Error::tryingToAcceptUsingClosedServer, __LINE__, __FILE__ );
		}
	}
	
	template < typename CallBackType, typename... Args >
	void Server::AcceptNoLock( CallBackType callBackFunction, Args... args )
	{
		if( this->opened )
		{
			if( this->isAcceptNoLockRunning.load() == false )
			{
				this->keepAcceptNoLockRunning.store( true );
				this->isAcceptNoLockRunning.store( true );
				std::thread( _Server_AcceptNoLock_ThreadFunction_OneAccept, self, callBackFunction, args... ).detach();
			}
			else
			{
				ICon::Error::Push( ICon::Error::tryingToRunSecondInstancOfAcceptNoLock, __LINE__, __FILE__ );
			}
		}
		else
		{
			ICon::Error::Push( ICon::Error::tryingToAcceptUsingClosedServer, __LINE__, __FILE__ );
		}
	}
};

#endif

