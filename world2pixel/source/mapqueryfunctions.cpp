#include "mainheader.h"
#include <random>

bool simplepixelcheck(Features infeatures, std::pair<double,double> searchlatlon, double tileside, std::string filterpositive, std::string filternegative = "", double radiusmultiplier = 1, double radiusmodifier = 0)
{
    infeatures = infeatures(filterpositive.c_str());
    if(filternegative!="") infeatures = infeatures(filternegative.c_str());

    double radius = tileside*0.5*radiusmultiplier + radiusmodifier;

    double inlon = searchlatlon.second;
    double inlat = searchlatlon.first;

    Features inradius = infeatures.maxMetersFromLonLat(radius, inlon, inlat);
    if(inradius) return true;
    return false;
}

//0 for no feature, 1 for failed check, 2 for successful check
int probabilitypixelcheck(Features infeatures, std::pair<double,double> searchlatlon, double tileside, double densitypermetersquare, double tilesideresolutioncutoff, std::string filterpositive, std::string filternegative = "", double radiusmultiplier = 1, double radiusmodifier = 0)
{
    infeatures = infeatures(filterpositive.c_str());
    if(filternegative!="") infeatures = infeatures(filternegative.c_str());

    double radius = tileside*0.5*radiusmultiplier + radiusmodifier;

    double inlon = searchlatlon.second;
    double inlat = searchlatlon.first;

    int retval = 0;

    Features inradius = infeatures.maxMetersFromLonLat(radius, inlon, inlat);
    if(inradius && tileside > tilesideresolutioncutoff) return 2;
    if(inradius) 
    {
        retval = 1;
        int rollamount = tileside*tileside;
        double mod = 1;
        if(rollamount < 1)
        {
            rollamount++;
            mod = tileside*tileside;
        }
        for(int i = 0; i < rollamount;i++)
        {
            double roll = (double)std::rand()/(double)RAND_MAX;
            if(roll<densitypermetersquare*mod) return 2;
        }
    }
    return retval;
}

bool roadlikepixelcheck(Features infeatures, std::pair<double,double> searchlatlon, double tileside, std::string filterpositive, std::string filternegative = "", int lanestosearch = 4, double lanewidth = 3.5, double radiusmultiplier = 1, double radiusmodifier = 0)
{
    infeatures = infeatures(filterpositive.c_str());
    if(filternegative!="") infeatures = infeatures(filternegative.c_str());

    double inlon = searchlatlon.second;
    double inlat = searchlatlon.first;

    double radius = lanewidth*0.5*radiusmultiplier + radiusmodifier;

    for(int i = 1; i < lanestosearch+1; i++)
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
                        if(std::to_string(i+1) == value)
                        {
                            return true;
                        }
                    }
                }
                if(i == 2 && !lanespresent) return true;
            }
        }
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