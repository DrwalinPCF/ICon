
#include "../../src/HighLayerSocket.h"
#include "../../src/Server.h"

#include <cstring>

int main()
{
	ICon::Init();
	ICon::Error::PrintWhenPushed();
	
	{
		std::shared_ptr<ICon::Server> server = ICon::Server::Make();
		std::shared_ptr<ICon::HighLayerSocket> con( new ICon::HighLayerSocket() );
		
		std::vector <int> tab;
		server->StartListening( 27000 );
		if( server->Accept( con ) == ICon::Error::Code::none )
		{
			printf( "\n Connected correctly! " );
			
			tab.resize( 10 );
			for( int i = 0; i < tab.size(); ++i )
				tab[i] = i + 10;
			con->Send( &(tab.front()), tab.size() * sizeof(int) );
			
			
			
			unsigned messageSize = con->GetNextMessageLengthLock();
			tab.resize( messageSize / sizeof(int) );
			unsigned recv = con->GetMessageLock( &(tab.front()), messageSize );
			con->PopMessage();
			for( int i = 0; i < tab.size(); ++i )
				printf( "\n tab[%i] = %i ", i, tab[i] );
			
			con->Close();
		}
		
		while( true )
		{
			ICon::Error err = ICon::Error::Pop();
			if( err == ICon::Error::Code::tryingToAccessEmptyErrorQueue )
				break;
			err.Print();
		}
		
		server->Close();
	}
	
	ICon::DeInit();
	
	return 0;
}



