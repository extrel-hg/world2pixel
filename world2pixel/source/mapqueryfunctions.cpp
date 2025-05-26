#include "mainheader.h"

bool islowgreenarea(Features infeatures, std::pair<double,double> searchlatlon, double tileside)
{
    infeatures = infeatures("*[landuse=grass,farmland,farmyard,flowerbed,meadow,plant_nursery,vineyard,greenery],*[leisure=park,dogpark,garden,nature_reserve]");

    double radius = tileside*0.5;

    double inlon = searchlatlon.second;
    double inlat = searchlatlon.first;

    Features inradius = infeatures.maxMetersFromLonLat(radius, inlon, inlat);
    if(inradius) return true;
    return false;
}

bool isbuilding(Features infeatures, std::pair<double,double> searchlatlon, double tileside)
{
    infeatures = infeatures("a[building]");

    double radius = tileside*0.5;

    double inlon = searchlatlon.second;
    double inlat = searchlatlon.first;

    Features inradius = infeatures.maxMetersFromLonLat(radius, inlon, inlat);
    if(inradius) return true;
    return false;
}

bool iswater(Features infeatures, std::pair<double,double> searchlatlon, double tileside)
{
    infeatures = infeatures("*[water]");

    double radius = tileside*0.5;

    double inlon = searchlatlon.second;
    double inlat = searchlatlon.first;

    Features inradius = infeatures.maxMetersFromLonLat(radius, inlon, inlat);
    if(inradius) return true;
    return false;
}

bool israilroad(Features infeatures, std::pair<double,double> searchlatlon, double tileside, int lanestosearch = 2, double lanewidth = 3.5)
{
    infeatures = infeatures("*[railway=rail]");

    double inlon = searchlatlon.second;
    double inlat = searchlatlon.first;

    double radius = lanewidth*0.5;

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

bool isroad(Features infeatures, std::pair<double,double> searchlatlon, double tileside, int lanestosearch = 10, double lanewidth = 3.5)
{
    infeatures = infeatures("*[highway]");
    infeatures = infeatures("*[!footway]");
    infeatures = infeatures("*[highway!=track,cycleway]");

    double inlon = searchlatlon.second;
    double inlat = searchlatlon.first;

    double radius = lanewidth*0.5;

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