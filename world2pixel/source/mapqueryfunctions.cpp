#include "mainheader.h"

bool isroad(Features infeatures, std::pair<double,double> searchlatlon, double tileside, int lanestosearch = 10, double lanewidth = 3.5)
{
    infeatures = infeatures("*[highway]");
    infeatures = infeatures("*[!footway]");
    infeatures = infeatures("*[highway!=track,cycleway]");

    double inlon = searchlatlon.second;
    double inlat = searchlatlon.first;

    double radius = lanewidth*0.5;

    for(int i = 1; i < lanestosearch; i++)
    {
        Features inradius = infeatures.maxMetersFromLonLat(radius, inlon, inlat);
        if(inradius) {
            for (Feature curitem: inradius)
            {
                Tags tags = curitem.tags();
                bool lanespresent = false;
                for(Tag curtag: tags)
                {
                    std::string key = curtag.key();
                    std::string value = curtag.value();
                    if(key == "lanes")
                    {
                        lanespresent = true;
                        if(std::to_string(i) == value)
                        {
                            return true;
                        }
                    }
                }
                if(i == 1 && !lanespresent) return true;
            }
        } //returns true when the Features inradius contains at least one feature
        if(radius > tileside) return false;
        radius=radius+lanewidth*0.5;
    }
    
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