#pragma once
#include "mapqueryfunctions.h"
#include "renderfunctions.h"

// 0 finished, -1 continue

/*
type:
0 - else
1 - simple
2 - road
3 - probability
*/

class CheckPixel {
    public:
        int type;
        std::string filterpositive = "";
        std::string filternegative = "";
        double radiusmultiplier = 1;
        double radiusmodifier = 0;
        int rendercharint = (int)'X';
        int rendercolor = 7;

        int hitrendercharint = (int)'.';
        int hitrendercolor = 8;
        
        int lanestosearch = 1;
        double lanewidth = 1;
        std::string lanekey = "lanes";
        int defaultamountoflanes = 1;

        double densitypermetersquare = 0.05;
        double tilesideresolutioncutoff = 10;

        int checkelse()
        {
            renderpixel(rendercharint,rendercolor);
            return 0;
        }
        int checksimple(Features infeatures, std::pair<double,double> searchlatlon, double tileside)
        {
           if(simplepixelcheck(infeatures,searchlatlon,tileside,filterpositive,filternegative,radiusmultiplier,radiusmodifier))
            {
                renderpixel(rendercharint,rendercolor);
                return 0;
            }
            else
            {
                return -1;
            }
        }
        int checkroad(Features infeatures, std::pair<double,double> searchlatlon, double tileside)
        {
            if(roadlikepixelcheck(infeatures,searchlatlon,tileside,filterpositive,filternegative,lanestosearch,lanewidth,lanekey,defaultamountoflanes,radiusmultiplier,radiusmodifier))
            {
                renderpixel(rendercharint,rendercolor);
                return 0;
            }
            else
            {
                return -1;
            }
        }
        int checkprob(Features infeatures, std::pair<double,double> searchlatlon, double tileside)
        {
            if(int retval = probabilitypixelcheck(infeatures,searchlatlon,tileside,densitypermetersquare,tilesideresolutioncutoff,filterpositive,filternegative,radiusmultiplier,radiusmodifier); retval>0)
            {
                renderpixel(rendercharint, rendercolor,retval,0,2);
                renderpixel(hitrendercharint, hitrendercolor,retval,1,3);
                return 0;
            }
            else
            {
                return -1;
            }
        }
};