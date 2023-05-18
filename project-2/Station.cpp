//
// Created by david on 5/8/23.
//


#include "Station.h"

Station::Station(string id_, double longitude_, double latitude_) {
    id=id_;
    longitude=longitude_;
    latitude=latitude_;

}

string Station::get_id() {
    return id;
}

double Station::get_longitude() {
    return longitude;
}

double Station::get_latitude() {
    return latitude;
}



Station::Station() {

}

