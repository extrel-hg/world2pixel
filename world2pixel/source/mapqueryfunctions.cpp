#include "mainheader.h"

bool isroad(Features infeatures, std::pair<double,double> searchlatlon, double radius)
{
    double inlon = searchlatlon.second;
    double inlat = searchlatlon.first;
    Features inradius = infeatures.maxMetersFromLonLat(radius, inlon, inlat);
    bool hasroad = false;
    for (Feature curitem: inradius)
    {
        Tags tags = curitem.tags();
        for(Tag curtag: tags)
        {
            std::string key = curtag.key();
            if(key == "highway")
            {
                hasroad = true;
            }
        }
    }
    return hasroad;
}