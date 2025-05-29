#include "mainheader.h"
#include "latlonfunctions.h"
#include "mapqueryfunctions.h"
#include "renderfunctions.h"


#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
using namespace rapidxml;

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
/*
file<> xmlFile("test.xml");
    xml_document<> doc;
    doc.parse<0>(xmlFile.data());
    xml_node<> *root = doc.first_node();

    xml_node<> *node = root;
    for (xml_node<> *child = node->first_node(); child; child = child->next_sibling())
    {
        std::cout << "Name of checked node: " << child->name()<<" "<<child->value() << "\n";
        for (xml_node<> *secchild = child->first_node(); secchild; secchild = secchild->next_sibling())
        {
            std::cout << "Name of one of my nodes is: " << secchild->name()<<" "<<secchild->value() << "\n";
        }
    }
*/

int main(int argc, char* argv[])
{
    srand(time(NULL));
    for(int i=0;i<argc;i++)
    {
        std::cout<<"Command parameter "<<i<<": "<<argv[i]<<"\n";
    }
    
    std::pair<double,double> targetlatlon = {std::stod(argv[1]),std::stod(argv[2])}; //north west corner
    int tilesperside = 100;
    double side = 100;
    double roadscanmodifier = 1;
    double railscanmodifier = 2.5;

    if(argc>3)
    {
        tilesperside = std::stod(argv[3]);
        side = std::stod(argv[4]);
    }

    if(argc>5)
    {
        roadscanmodifier = std::stod(argv[5]);
    }

    if(argc>6)
    {
        railscanmodifier = std::stod(argv[6]);
    }

    std::string filename = "gol";
    if(argc>7) 
    {
        filename = argv[7];
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
            if(roadlikepixelcheck(features,searchlatlon,tileside,"*[railway=rail]","",3,5,"",1))
            {
                renderpixel((int)'X', 8);
            } else if(roadlikepixelcheck(features,searchlatlon,tileside,"*[highway]","*[highway!=sidewalk,cycleway,footway,pedestrian,path]"))
            {
                renderpixel((int)'X', 15);
            }  else if(simplepixelcheck(features,searchlatlon,tileside,"a[building]"))
            {
                renderpixel(254, 12);
            } else if(roadlikepixelcheck(features,searchlatlon,tileside,"*[water],*[natural=water],*[waterway]","",1,5,"",1))
            {
                renderpixel((int)'~', 9);
            } else if(int retval = probabilitypixelcheck(features,searchlatlon,tileside,0.05,10,"*[landuse=forest,orchard],*[natural=wood]"); retval>0)
            {
                renderpixel((int)'.', 2,retval,0,2);
                renderpixel(159, 2,retval,1,3);
            } else if(simplepixelcheck(features,searchlatlon,tileside,"*[landuse=commercial,construction,education,industrial,residential,retail,institutional,landfill,port,brownfield],*[area:highway]"))
            {
                renderpixel((int)'-', 8);
            }  else if(int retval = probabilitypixelcheck(features,searchlatlon,tileside,0.001,15,"*[landuse=grass,farmland,farmyard,flowerbed,meadow,plant_nursery,vineyard,greenery,allotments,recreation_ground],*[leisure=park,dogpark,garden,nature_reserve,playground],*[natural=grassland,scrub]");retval>0)
            {
                renderpixel(137, 10,retval,0,2);
                renderpixel(int('X'), 42,retval,1,3);
            }
            else
            {
                if(simplepixelcheck(features,searchlatlon,tileside,"*[admin_level=8]"))
                {
                    renderpixel(int('.'), 8);
                }
                else 
                {
                    renderpixel(137, 10);
                }
            }
            if(x<tilesperside-1) std::cout<<" ";
        }
        std::cout<<"\n";
    }
    std::cout<<"Meters per one tile: "<<tileside;
}