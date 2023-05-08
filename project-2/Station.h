//
// Created by david on 5/8/23.
//

#ifndef PROJECT_2_STATION_H
#define PROJECT_2_STATION_H



#include <string>

using namespace std;

class Station {
    string name;
    string district;
    string municipality;
    string township;
    string line;
public:
    /**
     * Default constructor
     */
    Station();

    /**
     *  Constructor
     *  @param name_
     *  @param district_
     *  @param municipality_
     *  @param township_
     *  @param line_
     */
    Station(string name_, string district_, string municipality_, string township_, string line_);

    /**
     * Returns the station's name
     * @return name
     */
    string get_name();

    /**
     * Returns the station's district
     * @return district
     */
    string get_district();

    /**
     * Returns the station's municipality
     * @return municipality
     */
    string get_municipality();

    /**
     * Returns the station's township
     * @return township
     */
    string get_township();

    /**
     * Returns the station's line
     * @return line
     */
    string get_line();
};

#endif //PROJECT_2_STATION_H
