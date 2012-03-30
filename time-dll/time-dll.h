// time-dll.h

#pragma once

#using <mscorlib.dll>
#using <System.dll>

using namespace System;
using namespace System::Net;

#include <string>

namespace timedll 
{
	//Pretty much the most basic API ever.  Time API.
	public ref class Time
	{
	public:
		Time()
		{
		}

		// Parameters which can be accessed to get the time after calling UpdateTime.
		char* mData;
		int mDataSize;

		// Updates the time data stored in mData and mDataSize.
		void UpdateTime()
		{
			std::string returnString;

			System::Net::HttpWebRequest^ myRequest = dynamic_cast<HttpWebRequest^>(WebRequest::Create( "http://www.timeapi.org/utc/now?format=%25H%20%25M%20%25S" ));
			System::Net::WebResponse^ myResponse = myRequest->GetResponse();

			// Obtain a 'Stream' object associated with the response object.
			System::IO::Stream^ ReceiveStream = myResponse->GetResponseStream();

			System::Text::Encoding^ encode = System::Text::Encoding::GetEncoding( "utf-8" );

			// Pipe the stream to a higher level stream reader with the required encoding format.
			System::IO::StreamReader^ readStream = gcnew System::IO::StreamReader( ReceiveStream,encode );
			array<Char>^ read = gcnew array<Char>(256);

			// Read 256 charcters at a time.
			int count = readStream->Read( read, 0, 256 );

			while ( count > 0 )
			{
				// Dump the 256 characters on a string.
				String^ str = gcnew String( read,0,count );

				// Add the contents of the System::String to our std::string.
				array<Char>^ line = gcnew array<Char>(256);
				line = str->ToCharArray();
				for(int i = 0; i < count; i++)
				{
					returnString += line[i];
				}

				count = readStream->Read( read, 0, 256 );
			}

			// Set our object parameters based on what we got from the web.
			mDataSize = returnString.length();

			mData = new char[mDataSize];
			
			for(int i = 0; i < returnString.length(); i++)
			{
				mData[i] = returnString[i];
			}

			// Release the resources of stream object.
			readStream->Close();

			// Release the resources of response object.
			myResponse->Close();
		}
	};
}
