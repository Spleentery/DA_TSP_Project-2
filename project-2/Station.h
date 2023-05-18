//
// Created by david on 5/8/23.
//

#ifndef PROJECT_2_STATION_H
#define PROJECT_2_STATION_H



#include <string>

using namespace std;

class Station {
    string id;
    double longitude;
    double latitude;

public:
    /**
     * Default constructor
     */
    Station();

    /**
     *  Constructor
     *  @param id_
     *  @param longitude_
     *  @param latitude_

     */
    Station(string id_, double longitude_, double latitude_);

    /**
     * Returns the station's name
     * @return id
     */
    string get_id();

    /**
     * Returns the station's district
     * @return longitude
     */
    double get_longitude();

    /**
     * Returns the station's municipality
     * @return latitude
     */
    double get_latitude();



};

#endif //PROJECT_2_STATION_H
