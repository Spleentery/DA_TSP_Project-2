//
// Created by david on 5/8/23.
//

#ifndef PROJECT_2_ESTABLISHMENT_H
#define PROJECT_2_ESTABLISHMENT_H



#include <string>

using namespace std;

class Establishment {
    string id;
    double longitude;
    double latitude;

public:

    Establishment();

    /**
     *  Constructor
     *  @param id_
     *  @param longitude_
     *  @param latitude_

     */
    Establishment(string id_, double longitude_, double latitude_);

    /**
     * Returns the id of the establishment
     * @return id
     */
    string get_id();

    /**
     * Returns the establishment's longitude
     * @return longitude
     */
    double get_longitude();

    /**
     * Returns the establishment's latitude
     * @return latitude
     */
    double get_latitude();



};

#endif //PROJECT_2_ESTABLISHMENT_H
