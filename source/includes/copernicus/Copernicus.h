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
#ifndef COPERNICUS_H
#define COPERNICUS_H

#include <iostream>
#include <sstream>
#include <memory>
#include <cstdint>
#include <chrono>
#include <thread>
#include <functional>

#include "json/json.h"
#include "copernicus/MyNetwork.h"

// For convenience
using namespace std;
using json = nlohmann::json;

/**
 * Main class that handles all the details of getting
 * stats and also handling events
 */
class Copernicus {
  public:

    // Public constructor
    Copernicus();

    // Starts a separate thread
    void timer_start(std::function<void()> func, unsigned int interval);

    // This will poll the API can get new stats
    void update_stats();

    // Get if polling is enabled or not
    bool is_enabled();

    // Set the polling status (false = disabled)
    void set_enabled(bool status);

    // Gets the current URL (hard coded)
    string get_url();

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
    string stat_dns;
    string stat_ads_total;
    string stat_ads_percent;


    // Curl callback function
    std::size_t callback( const char* in, std::size_t size, std::size_t num, std::string* out) {
        const std::size_t totalBytes(size * num);
        out->append(in, totalBytes);
        return totalBytes;
    }

};

#endif /* COPERNICUS_H */