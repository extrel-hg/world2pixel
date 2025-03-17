#include "mainheader.h"

bool isroad(Features infeatures, std::pair<double,double> searchlatlon, double radius)
{
    infeatures = infeatures("w");
    Features inradius = infeatures.maxMetersFromLonLat(radius, searchlatlon.second, searchlatlon.first);
    for (Feature curitem: inradius)
    {
        Tags tags = curitem.tags();
        bool highway = false;
        bool asphalt = false;
        for(Tag curtag: tags)
        {
            if(curtag.key() == "highway")
            {
                highway = true;
            }
            if(curtag.key() == "surface" && curtag.value() == "asphalt")
            {
                asphalt = true;
            }
        }
        if(highway && asphalt)
        {
            return true;
        }
    }
    return false;
}