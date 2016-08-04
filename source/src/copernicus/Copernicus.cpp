#include "copernicus/Copernicus.h"


using namespace std;
using json = nlohmann::json;


// Default constructor
Copernicus::Copernicus() {
  status = true;
  url_admin = "https://github.com/goldbattle/copernicus/";
  stat_dns = 0;
  stat_ads_total = 0;
  stat_ads_percent = 0;
}

// This will poll the API can get new stats
void Copernicus::update_stats() {

  // Check to make sure we are not disabled
  if(!status)
    return;

  // Create our response object
  MyNetwork network;
  std::string data_raw;

  // Grab api json using curl
  try {

    // Host and url
    std::string host("date.jsontest.com");
    std::string api_path("/");

    // Open the connection to the server
    data_raw = network.Get(host, api_path);

    // Data returned
    //std::cout << "[debug]: response data" << endl << data_raw << endl;

  }
  // Catch any problems with the http requests
  catch(const happyhttp::Wobbly& e) {
    // Error out
    std::cerr <<"[error]: HTTP Error \"" << e.what() << "\"" << std::endl;
    // Set to zero values
    stat_dns = 0;
    stat_ads_total = 0;
    stat_ads_percent = 0;
    // Return
    return;
  }

  // Master api json variable
  json data_json;

  // Parse the json
  try {
    
    // Convert string to json
    data_json = json::parse(data_raw);

    // Parse api response
    stat_dns = data_json["milliseconds_since_epoch"].get<int>();
    stat_ads_total = data_json["milliseconds_since_epoch"].get<int>();
    stat_ads_percent = data_json["milliseconds_since_epoch"].get<double>();

  }
  // Unable to parse json, reset values
  catch(...) {
    // Error out
    std::cerr <<"[error]: Unable to parse JSON" << std::endl;
    // Set to zero values
    stat_dns = 0;
    stat_ads_total = 0;
    stat_ads_percent = 0;
    // Return
    return;
  }

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