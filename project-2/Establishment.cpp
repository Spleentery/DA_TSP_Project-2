//
// Created by david on 5/8/23.
//


#include "Establishment.h"

Establishment::Establishment(string id_, double longitude_, double latitude_) {
    id=id_;
    longitude=longitude_;
    latitude=latitude_;

}

string Establishment::get_id() {
    return id;
}

double Establishment::get_longitude() {
    return longitude;
}

double Establishment::get_latitude() {
    return latitude;
}



Establishment::Establishment() {

}

