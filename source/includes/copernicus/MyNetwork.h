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