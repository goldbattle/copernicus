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

#include "copernicus/Copernicus.h"


using namespace std;
using json = nlohmann::json;


// Default constructor
Copernicus::Copernicus() {
  status = true;
  url_admin = "http://pi.hole/admin/";
  stat_dns = "0";
  stat_ads_total = "0";
  stat_ads_percent = "0";
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
    std::string host("pi.hole");
    std::string api_path("/admin/api.php?summary");

    // Open the connection to the server
    data_raw = network.Get(host, api_path);

    // Data returned
    std::cout << "[debug]: response data" << endl << data_raw << endl;

  }
  // Catch any problems with the http requests
  catch(const happyhttp::Wobbly& e) {
    // Error out
    std::cerr <<"[error]: HTTP Error \"" << e.what() << "\"" << std::endl;
    // Set to zero values
    stat_dns = "Error";
    stat_ads_total = "Error";
    stat_ads_percent = "Error";
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
    stat_dns = data_json["dns_queries_today"].get<std::string>();
    stat_ads_total = data_json["ads_blocked_today"].get<std::string>();

    // Create a stream so we can add the percent
    stringstream ss;
    ss << data_json["ads_percentage_today"].get<std::string>() << "%";
    stat_ads_percent = ss.str();

  }
  // Unable to parse json, reset values
  catch(...) {
    // Error out
    std::cerr <<"[error]: Unable to parse JSON" << std::endl;
    // Set to zero values
    stat_dns = "Error";
    stat_ads_total = "Error";
    stat_ads_percent = "Error";
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
  ss << "Traffic Percent: " << stat_ads_percent;
  return ss.str();
}