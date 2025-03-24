#include "mainheader.h"

bool isroad(Features infeatures, std::pair<double,double> searchlatlon, double radius, int lanestosearch = 4, double lanewidth = 1.5)
{
    infeatures = infeatures("*[highway]");
    infeatures = infeatures("*[!footway]");
    infeatures = infeatures("*[highway!=track,cycleway]");

    double inlon = searchlatlon.second;
    double inlat = searchlatlon.first;

    //Checks if current tile is a highway
    Features inradius = infeatures.maxMetersFromLonLat(radius, inlon, inlat);
    if(inradius) return true; //returns true when the Features inradius contains at least one feature
    return false;
}

/*
    for (Feature curitem: inradius)
    {
        Tags tags = curitem.tags();
        for(Tag curtag: tags)
        {
            std::string key = curtag.key();
            if(key == "highway")
            {
                return true;
            }
        }
    }
*/