
/*
	Copyright (C) 2019 Marek Zalewski aka Drwalin - All Rights Reserved
	
	Any one is authorized to copy, use or modify this file,
	but only when this file is marked as written by Marek Zalewski.
	
	No one can claim this file is originally written by them.
	
	No one can modify or remove this Copyright notice from this file.
*/

#ifndef BINARY_TYPE_H
#define BINARY_TYPE_H

#include <vector>
#include <string>
#include <map>
#include <set>

#include <type_traits>
#include <algorithm>

#include <cstring>

namespace Binary
{
	namespace Type
	{
		typedef unsigned short NumberOfElements;
		
		enum
		{
			RAW = 0x00,
			
			BOOl = 0x01,
			
			INT_8 = 0x02,
			INT_16 = 0x03,
			INT_32 = 0x04,
			INT_64 = 0x05,
			UINT_8 = 0x06,
			UINT_16 = 0x07,
			UINT_32 = 0x08,
			UINT_64 = 0x09,
			
			FLOAT_32 = 0x0A,
			FLOAT_64 = 0x0B,
			FLOAT_80 = 0x0C,
			
			VECTOR = 0x20,
			MAP = 0x21,
			SET = 0x22,
			STRING = 0x23
		};
		
		unsigned long long GetOffset( const unsigned char * type, const unsigned long long length, unsigned long long offset = 0 );		// return 0 if too small array was given
		
		
		unsigned long long Get( std::vector < unsigned char > & type, const void * src, unsigned long long offset = 0 );
		
		unsigned long long Get( std::vector < unsigned char > & type, const float src, unsigned long long offset = 0 );
		unsigned long long Get( std::vector < unsigned char > & type, const double src, unsigned long long offset = 0 );
		unsigned long long Get( std::vector < unsigned char > & type, const long double src, unsigned long long offset = 0 );
		
		unsigned long long Get( std::vector < unsigned char > & type, const bool src, unsigned long long offset = 0 );
		unsigned long long Get( std::vector < unsigned char > & type, const char src, unsigned long long offset = 0 );
		unsigned long long Get( std::vector < unsigned char > & type, const short src, unsigned long long offset = 0 );
		unsigned long long Get( std::vector < unsigned char > & type, const int src, unsigned long long offset = 0 );
		unsigned long long Get( std::vector < unsigned char > & type, const long long src, unsigned long long offset = 0 );
		unsigned long long Get( std::vector < unsigned char > & type, const unsigned char src, unsigned long long offset = 0 );
		unsigned long long Get( std::vector < unsigned char > & type, const unsigned short src, unsigned long long offset = 0 );
		unsigned long long Get( std::vector < unsigned char > & type, const unsigned int src, unsigned long long offset = 0 );
		unsigned long long Get( std::vector < unsigned char > & type, const unsigned long long src, unsigned long long offset = 0 );
		
		
		unsigned long long Get( std::vector < unsigned char > & type, const std::string & src, unsigned long long offset = 0 );
		
		template < typename T1, typename T2  >
		unsigned long long Get( std::vector < unsigned char > & type, const std::map < T1, T2 > & src, unsigned long long offset = 0 );
		
		template < typename T >
		unsigned long long Get( std::vector < unsigned char > & type, const std::vector < T > & src, unsigned long long offset = 0 );
		
		template < typename T >
		unsigned long long Get( std::vector < unsigned char > & type, const std::set < T > & src, unsigned long long offset = 0 );
		
		
		
		template < typename T >
		bool IsValid( const std::vector < unsigned char > & type, const T & src, unsigned long long offset = 0 );
	};
	
	
	
	unsigned long long Store( std::vector < unsigned char > & dst, const float src, unsigned long long offset = 0 );
	unsigned long long Store( std::vector < unsigned char > & dst, const double src, unsigned long long offset = 0 );
	unsigned long long Store( std::vector < unsigned char > & dst, const long double src, unsigned long long offset = 0 );
	
	unsigned long long Store( std::vector < unsigned char > & dst, const char src, unsigned long long offset = 0 );
	unsigned long long Store( std::vector < unsigned char > & dst, const short src, unsigned long long offset = 0 );
	unsigned long long Store( std::vector < unsigned char > & dst, const int src, unsigned long long offset = 0 );
	unsigned long long Store( std::vector < unsigned char > & dst, const long long src, unsigned long long offset = 0 );
	unsigned long long Store( std::vector < unsigned char > & dst, const unsigned char src, unsigned long long offset = 0 );
	unsigned long long Store( std::vector < unsigned char > & dst, const unsigned short src, unsigned long long offset = 0 );
	unsigned long long Store( std::vector < unsigned char > & dst, const unsigned int src, unsigned long long offset = 0 );
	unsigned long long Store( std::vector < unsigned char > & dst, const unsigned long long src, unsigned long long offset = 0 );
	
	unsigned long long Store( std::vector < unsigned char > & dst, const bool src, unsigned long long offset = 0 );
	
	
	unsigned long long Store( std::vector < unsigned char > & dst, const std::string & src, unsigned long long offset = 0 );
	
	template < typename T >
	unsigned long long Store( std::vector < unsigned char > & dst, const std::vector < T > & src, unsigned long long offset = 0 );
	
	template < typename T1, typename T2  >
	unsigned long long Store( std::vector < unsigned char > & dst, const std::map < T1, T2 > & src, unsigned long long offset = 0 );
	
	template < typename T >
	unsigned long long Store( std::vector < unsigned char > & dst, const std::set < T > & src, unsigned long long offset = 0 );
	
	
	
	// when Binary::Restore returns 0, it means src is not valid
	
	unsigned long long Restore( const unsigned char * src, const unsigned long long length, float & dst, unsigned long long offset = 0 );
	unsigned long long Restore( const unsigned char * src, const unsigned long long length, double & dst, unsigned long long offset = 0 );
	unsigned long long Restore( const unsigned char * src, const unsigned long long length, long double & dst, unsigned long long offset = 0 );
	
	unsigned long long Restore( const unsigned char * src, const unsigned long long length, char & dst, unsigned long long offset = 0 );
	unsigned long long Restore( const unsigned char * src, const unsigned long long length, short & dst, unsigned long long offset = 0 );
	unsigned long long Restore( const unsigned char * src, const unsigned long long length, int & dst, unsigned long long offset = 0 );
	unsigned long long Restore( const unsigned char * src, const unsigned long long length, long long & dst, unsigned long long offset = 0 );
	unsigned long long Restore( const unsigned char * src, const unsigned long long length, unsigned char & dst, unsigned long long offset = 0 );
	unsigned long long Restore( const unsigned char * src, const unsigned long long length, unsigned short & dst, unsigned long long offset = 0 );
	unsigned long long Restore( const unsigned char * src, const unsigned long long length, unsigned int & dst, unsigned long long offset = 0 );
	unsigned long long Restore( const unsigned char * src, const unsigned long long length, unsigned long long & dst, unsigned long long offset = 0 );
	
	unsigned long long Restore( const unsigned char * src, const unsigned long long length, bool & dst, unsigned long long offset = 0 );
	
	unsigned long long Restore( const unsigned char * src, const unsigned long long length, std::vector<bool>::reference dst, unsigned long long offset = 0 );
	
	
	unsigned long long Restore( const unsigned char * src, const unsigned long long length, std::string & dst, unsigned long long offset = 0 );
	
	template < typename T >
	unsigned long long Restore( const unsigned char * src, const unsigned long long length, std::vector < T > & dst, unsigned long long offset = 0 );
	
	//only add new elements, without clearing dst
	template < typename T1, typename T2  >
	unsigned long long Restore( const unsigned char * src, const unsigned long long length, std::map < T1, T2 > & dst, unsigned long long offset = 0 );
	
	//only add new elements, without clearing dst
	template < typename T >
	unsigned long long Restore( const unsigned char * src, const unsigned long long length, std::set < T > & dst, unsigned long long offset = 0 );
};

#include "BinaryType.inl"

#endif

