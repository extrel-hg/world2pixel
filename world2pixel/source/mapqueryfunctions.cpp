#include "mainheader.h"
#include <random>

bool ispaved(Features infeatures, std::pair<double,double> searchlatlon, double tileside)
{
    infeatures = infeatures("*[landuse=commercial,construction,education,industrial,residential,retail,institutional,landfill,port]");

    double radius = tileside*0.5;

    double inlon = searchlatlon.second;
    double inlat = searchlatlon.first;

    Features inradius = infeatures.maxMetersFromLonLat(radius, inlon, inlat);
    if(inradius) return true;
    return false;
}

bool islowgreenarea(Features infeatures, std::pair<double,double> searchlatlon, double tileside)
{
    infeatures = infeatures("*[landuse=grass,farmland,farmyard,flowerbed,meadow,plant_nursery,vineyard,greenery,allotments],*[leisure=park,dogpark,garden,nature_reserve,playground]");

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

//For Poland it is 1ha - 500 trees => 1m^2 - 0.05 trees
int istree_probability(Features infeatures, std::pair<double,double> searchlatlon, double tileside, double treespermetersquare = 0.05, double definitetreeminval = 10)
{
    if(definitetreeminval<tileside) return 2;
    infeatures = infeatures("*[landuse=forest,orchard]");

    double radius = tileside*0.5;

    double inlon = searchlatlon.second;
    double inlat = searchlatlon.first;

    int retval = 0;

    Features inradius = infeatures.maxMetersFromLonLat(radius, inlon, inlat);
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
            if(roll<treespermetersquare*mod) return 2;
        }
    }
    return retval;
}

bool israilroad(Features infeatures, std::pair<double,double> searchlatlon, double tileside , double lanewidth = 3.5, double scanradiusmodifier=1)
{
    infeatures = infeatures("*[railway=rail]");

    double inlon = searchlatlon.second;
    double inlat = searchlatlon.first;

    double radius = lanewidth*0.5;
    int lanestosearch = 10;

    for(int i = 1; i < lanestosearch+1; i++)
    {
        Features inradius = infeatures.maxMetersFromLonLat(radius*scanradiusmodifier, inlon, inlat);
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

bool isroad(Features infeatures, std::pair<double,double> searchlatlon, double tileside, int lanestosearch = 10, double lanewidth = 3.5, double scanradiusmodifier=1)
{
    infeatures = infeatures("*[highway]");
    infeatures = infeatures("*[!footway]");
    infeatures = infeatures("*[highway!=track,cycleway]");

    double inlon = searchlatlon.second;
    double inlat = searchlatlon.first;

    double radius = lanewidth*0.5;

    for(int i = 1; i < lanestosearch+1; i++)
    {
        Features inradius = infeatures.maxMetersFromLonLat(radius*scanradiusmodifier, inlon, inlat);
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