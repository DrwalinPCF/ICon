
/*
	Copyright (C) 2019 Marek Zalewski aka Drwalin - All Rights Reserved
	
	Any one is authorized to copy, use or modify this file,
	but only when this file is marked as written by Marek Zalewski.
	
	No one can claim this file is originally written by them.
	
	No one can modify or remove this Copyright notice from this file.
*/

#ifndef CONNECTION_H
#define CONNECTION_H

#include "HighLayerSocket.h"

#include <map>
#include <vector>
#include <set>

#include <memory>

namespace ICon
{
	class Connection
	{
	private:
		
		std::shared_ptr<HighLayerSocket> con;
		std::vector < unsigned char > buffer;
		
	public:
		
		bool IsValid();
		
		void WaitForAnythingToReceive();		// wait until con->buffer contain all message or is filled
		void UpdateReceive();
		bool IsAnythingToRecevie( bool updateReceive = true );		// return if part of message (at least its length) is to receive
		
		// stream output operator waits until full message arrive and is of correct type to argument (otherwise it throws an ICon::Error and returns without modifying argument and without poping an message) or connection is lost
		template < typename T >
		Connection & operator << ( const T & obj );
		
		template < typename T >
		Connection & operator >> ( T & obj );
		
		void SetHighLayerSocket( std::shared_ptr<HighLayerSocket> con );
		std::shared_ptr<HighLayerSocket> GetHighLayerSocket();
		
		void Close();
		
		Connection( std::shared_ptr<HighLayerSocket> con_ );
		Connection();
		~Connection();
	};
};

#include "Connection.inl"

#endif

