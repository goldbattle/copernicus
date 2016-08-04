#include "copernicus/MyNetwork.h"
#include <iostream>
#include <istream>
#include <ostream>
#include <string>



std::string MyNetwork::Get(std::string host, std::string url) {

    // Open the happyhttp entry
    happyhttp::Connection conn(host.c_str(), 80 );
    conn.setcallbacks(OnBeginPtr, OnDataPtr, OnCompletePtr, (void*)this);

    // Get the request
    conn.request("GET", url.c_str(), 0, 0, 0 );

    while( conn.outstanding() )
        conn.pump();

    // Return the current data
    return dataReceived;
}


void MyNetwork::OnBegin( const happyhttp::Response* r) {
    dataReceived.clear();
}

void MyNetwork::OnData( const happyhttp::Response* r, const unsigned char* data, int n ) {
    dataReceived += std::string((const char*)data, n);
}

void MyNetwork::OnComplete( const happyhttp::Response* r) {
}

void MyNetwork::OnBeginPtr( const happyhttp::Response* r, void* userdata ) {
    ((MyNetwork*)userdata)->OnBegin(r);
}

void MyNetwork::OnDataPtr( const happyhttp::Response* r, void* userdata, const unsigned char* data, int n ) {
    ((MyNetwork*)userdata)->OnData(r, data, n);
}

void MyNetwork::OnCompletePtr( const happyhttp::Response* r, void* userdata ) {
    ((MyNetwork*)userdata)->OnComplete(r);
}