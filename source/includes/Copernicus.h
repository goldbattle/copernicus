#ifndef COPERNICUS_H
#define COPERNICUS_H

#include <iostream>
#include <sstream>

using namespace std;

/**
 * Main class that handles all the details of getting
 * stats and also handling events
 */
class Copernicus {
  public:

    // Public constructor
    Copernicus();

    // Get if polling is enabled or not
    bool is_enabled();

    // Set the polling status (false = disabled)
    void set_enabled(bool status);

    // Accessors method to get the total DNS queries for today
    string get_dns_queries();
    
    // Accessors method to get number of ads blocked today
    string get_ads_blocked_total();

    // Accessors method to percentage of ads
    string get_ads_blocked_percent();

  private:

    // Current status if polling or not
    bool status;

    // Master url that the dashboard is at
    string url_admin;

    // Stats that we get from updating
    int stat_dns;
    int stat_ads_total;
    double stat_ads_percent;

};

#endif /* COPERNICUS_H */