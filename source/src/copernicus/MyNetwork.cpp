/**
 * Copernicus a Windows Client for the Pi-Hole advertising-aware DNS/web server
 * Copyright (C) 2016  Patrick Geneva
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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