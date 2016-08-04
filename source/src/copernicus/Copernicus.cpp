#include "copernicus/Copernicus.h"

using namespace std;

// Default constructor
Copernicus::Copernicus() {
  status = true;
  url_admin = "https://github.com/goldbattle/copernicus/";
  stat_dns = 18108;
  stat_ads_total = 14648;
  stat_ads_percent = 80.89;
}

static int count=0;

// invoked when response headers have been received
void OnBegin( const happyhttp::Response* r, void* userdata )
{
  printf("BEGIN (%d %s)\n", r->getstatus(), r->getreason());
  count = 0;
}

// invoked to process response body data (may be called multiple times)
void OnData( const happyhttp::Response* r, void* userdata, const unsigned char* data, int n )
{
  fwrite(data, 1, n, stdout);
  count += n;
}

// invoked when response is complete
void OnComplete(const happyhttp::Response* r, void* userdata )
{
  printf( "COMPLETE (%d bytes)\n", count );
}


// This will poll the API can get new stats
void Copernicus::update_stats() {

  // Check to make sure we are not disabled
  if(!status)
    return;

  // Grab api json using curl
  try {
  const std::string url("date.jsontest.com");
  happyhttp::Connection conn(url.c_str(), 80);
  conn.setcallbacks(OnBegin, OnData, OnComplete, 0);

  // Do our request
  conn.request("GET", "/");

  // Wait for request
  while(conn.outstanding())
    conn.pump();

  }
  // Catch any problems with the http requests
  catch(const happyhttp::Wobbly& e) {
    std::cout <<"[error]: HTTP Error \"" << e.what() << "\"" << std::endl;
  }

  // TODO: Update main variables
  stat_dns += 1;
  stat_ads_total += 1;
  stat_ads_percent += 1;

}

// Get if polling is enabled or not
bool Copernicus::is_enabled() {
  return status;
}

// Set the polling status (false = disabled)
void Copernicus::set_enabled(bool status) {
  this->status = status;
}

// Gets the current URL (hard coded)
string Copernicus::get_url() {
  return url_admin;
}


// Accessors method to get the total DNS queries for today
string Copernicus::get_dns_queries() {
  stringstream ss;
  ss << "DNS: " << stat_dns;
  return ss.str();
}

// Accessors method to get number of ads blocked today
string Copernicus::get_ads_blocked_total() {
  stringstream ss;
  ss << "Ads Today: " << stat_ads_total;
  return ss.str();
}

// Accessors method to percentage of ads
string Copernicus::get_ads_blocked_percent() {
  stringstream ss;
  ss << "Traffic Percent: " << stat_ads_percent << "%";
  return ss.str();
}