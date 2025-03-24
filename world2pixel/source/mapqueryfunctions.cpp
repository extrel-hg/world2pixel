#include "mainheader.h"

bool isroad(Features infeatures, std::pair<double,double> searchlatlon, double radius, int lanestosearch = 4, double lanewidth = 2.5)
{
    infeatures = infeatures("*[highway]");
    infeatures = infeatures("*[!footway]");
    infeatures = infeatures("*[highway!=track,cycleway]");

    double inlon = searchlatlon.second;
    double inlat = searchlatlon.first;

    for(int i = 0; i < lanestosearch; i++)
    {
        Features inradius = infeatures.maxMetersFromLonLat(radius+i*lanewidth, inlon, inlat);
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
    }

    return false;
}