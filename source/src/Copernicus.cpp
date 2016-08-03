#include "Copernicus.h"

using namespace std;

// Default constructor
Copernicus::Copernicus() {
  status = true;
  url_admin = "http://google.com/";
  stat_dns = 0;
  stat_ads_total = 0;
  stat_ads_percent = 0;
}

// Get if polling is enabled or not
bool Copernicus::is_enabled() {
  return status;
}

// Set the polling status (false = disabled)
void Copernicus::set_enabled(bool status) {
  this->status = status;
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
  ss << "Total: " << stat_ads_total;
  return ss.str();
}

// Accessors method to percentage of ads
string Copernicus::get_ads_blocked_percent() {
  stringstream ss;
  ss << "Percent: " << stat_ads_percent;
  return ss.str();
}