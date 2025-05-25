#include "mainheader.h"
#include "latlonfunctions.h"
#include "mapqueryfunctions.h"

//latitude - north south
//longitude - east west
//Yea its easy to mess it up sometimes

/*
TO DO:
* make documentation for devs and for users
* fill out README
* maybe dont use goto
*/

// latitude longitude tilesperside side radiusmodifier

int main(int argc, char* argv[])
{
    for(int i=0;i<argc;i++)
    {
        std::cout<<"Command parameter "<<i<<": "<<argv[i]<<"\n";
    }
    
    std::pair<double,double> targetlatlon = {std::stod(argv[1]),std::stod(argv[2])}; //north west corner
    int tilesperside = 100;
    double side = 100;

    if(argc>3)
    {
        tilesperside = std::stod(argv[3]);
        side = std::stod(argv[4]);
    }

    std::string filename = "gol";
    if(argc>5) 
    {
        filename = argv[6];
    }

    double tileside = side/tilesperside;

    Features rootfeatures(filename.c_str());
    Features features = rootfeatures;
    {
        double west, south, east, north, margin;
        margin = 100;
        west = targetlatlon.second - mtolon(margin,targetlatlon.first);
        east = targetlatlon.second + mtolon(side+margin,targetlatlon.first);
        north = targetlatlon.first + mtolat(margin);
        south = targetlatlon.first - mtolat(margin);

        Box mapbounds = Box::ofWSEN(west, south, east, north);
        features = features(mapbounds);
    }

    for(int y = 0; y < tilesperside; y++)
    {
        for(int x = 0; x < tilesperside; x++)
        {
            std::pair<double,double> searchlatlon = movelatlon_m(targetlatlon,-y*tileside-0.5*tileside,x*tileside+0.5*tileside);
            if(isroad(features,searchlatlon,tileside))
            {
                std::cout<<"X";
            } else {
                std::cout<<"-";
            }
            if(x<tilesperside-1) std::cout<<" ";
        }
        std::cout<<"\n";
    }
    std::cout<<"Meters per one tile: "<<tileside;
}