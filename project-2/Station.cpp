//
// Created by david on 5/8/23.
//


#include "Station.h"

Station::Station(string name_, string district_, string municipality_, string township_, string line_) {
    name=name_;
    municipality=municipality_;
    district=district_;
    township=township_;
    line=line_;
}

string Station::get_name() {
    return name;
}

string Station::get_district() {
    return district;
}

string Station::get_municipality() {
    return municipality;
}

string Station::get_township() {
    return township;
}

string Station::get_line() {
    return line;
}

Station::Station() {

}

