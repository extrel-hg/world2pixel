#include "mainheader.h"

//latitude - north south
//longitude - east west

double mtolat(double meters)
{
    return meters/111.32/1000;
}

double mtolon(double meters, double lat)
{
    return meters/40075/1000/cos(lat)*360;
}

double lattom(double lat)
{
    return lat*111.32*1000;
}

double lontom(double lon, double lat)
{
    return 40075*1000*cos(lat)/360;
}

/*
mtolat - convert length of meters to amount of degrees of latitude
mtolon - convert length of meters to amount of degrees of longitute at a given latitude
lattom - convert amount of degrees of latitude to length of meters
lontom - convert amount of degrees of longitude to meters
*/

std::pair<double,double> movelatlon_m(std::pair<double,double> targetlaton, double NSmove, double EWmove) //returns latlon pair of coordinates, moved by meters. longitude is moved first.
{
    double movedlat = targetlaton.first + mtolat(NSmove);
    double movedlon = targetlaton.second + mtolon(EWmove, targetlaton.first);
    return {movedlat,movedlon};
}