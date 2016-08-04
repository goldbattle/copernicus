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

#ifndef NETWORK_H
#define NETWORK_H

#include "happyhttp/happyhttp.h"

class MyNetwork {
    public:
        std::string Get(std::string host, std::string url);
    private:
        std::string dataReceived;
        std::map<std::string, std::string> conf;
        void OnBegin( const happyhttp::Response* r);
        void OnData( const happyhttp::Response* r, const unsigned char* data, int n );
        void OnComplete( const happyhttp::Response* r);
        static void OnBeginPtr( const happyhttp::Response* r, void* userdata);
        static void OnDataPtr( const happyhttp::Response* r, void* userdata, const unsigned char* data, int n );
        static void OnCompletePtr( const happyhttp::Response* r, void* userdata );
};

#endif // MYNETWORK_H