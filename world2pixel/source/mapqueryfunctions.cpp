#include "mainheader.h"

bool isroad(Features infeatures, std::pair<double,double> searchlatlon, double radius)
{
    infeatures = infeatures("*[highway]");
    infeatures = infeatures("*[!footway]");
    infeatures = infeatures("*[highway!=track,cycleway]");
    Features inradius = infeatures.maxMetersFromLonLat(radius, searchlatlon.second, searchlatlon.first);
    for (Feature curitem: inradius)
    {
        Tags tags = curitem.tags();
        for(Tag curtag: tags)
        {
            if(curtag.key() == "highway")
            {
                return true;
            }
        }
    }
    return false;
}