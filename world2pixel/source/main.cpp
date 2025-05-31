#include "mainheader.h"
#include "latlonfunctions.h"
#include "mapqueryfunctions.h"
#include "renderfunctions.h"
#include "xmlcheckpixelclass.h"


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
    std::string xmlfilename = "1.xml";

    if(argc>3)
    {
        tilesperside = std::stod(argv[3]);
        side = std::stod(argv[4]);
    }

    if(argc>5)
    {
        xmlfilename = argv[5];
    }

    std::string filename = "gol";
    if(argc>6) 
    {
        filename = argv[6];
    }

    double tileside = side/tilesperside;

    std::vector<CheckPixel> checkpixelqueue;
    {
        file<> xmlFile(xmlfilename.c_str());
        xml_document<> doc;
        doc.parse<0>(xmlFile.data());
        xml_node<> *root = doc.first_node();

        //                    std::cout << "Name of one of my nodes is: " << secchildname<<" "<<secchildvalue << "\n";

        xml_node<> *node = root;
        for (xml_node<> *child = node->first_node(); child; child = child->next_sibling())
        {
            std::string childname = child->name();
            if(childname=="pixel")
            {
                CheckPixel tempobject;
                for (xml_node<> *secchild = child->first_node(); secchild; secchild = secchild->next_sibling())
                {
                    std::string name = secchild->name();
                    std::string val = secchild->value();
                    if(name == "type")
                    {
                        int tempint = 0;
                        if(val == "simple")  tempint = 1;
                        else if(val == "else")  tempint = 0;
                        else if(val == "road")  tempint = 2;
                        else if(val == "prob")  tempint = 3;
                        tempobject.type = tempint;
                    }
                    if(val!="")
                    {
                        //i dunno if its possible to make this cleaner
                        //maybe define a map or something? for now this works well enough. maybe move it to a different file as a seperate function so int main() is cleaner
                        if(name == "positivefilter")
                        {
                            tempobject.filterpositive = val;
                        }
                        else if(name == "negativefilter")
                        {
                            tempobject.filternegative = val;
                        }
                        else if(name == "radiusmultiplier")
                        {
                            tempobject.radiusmultiplier = std::stod(val);
                        }
                        else if(name == "radiusmodifier")
                        {
                            tempobject.radiusmodifier = std::stod(val);
                        }
                        else if(name == "rendercharint")
                        {
                            tempobject.rendercharint = std::stoi(val);
                        }
                        else if(name == "rendercolor")
                        {
                            tempobject.rendercolor = std::stoi(val);
                        }
                        else if(name == "hitrendercharint")
                        {
                            tempobject.hitrendercharint = std::stoi(val);
                        }
                        else if(name == "hitrendercolor")
                        {
                            tempobject.hitrendercolor = std::stoi(val);
                        }
                        else if(name == "lanestosearch")
                        {
                            tempobject.lanestosearch = std::stoi(val);
                        }
                        else if(name == "lanewidth")
                        {
                            tempobject.lanewidth = std::stod(val);
                        }
                        else if(name == "lanekey")
                        {
                            tempobject.lanekey = val;
                        }
                        else if(name == "defaultamountoflanes")
                        {
                            tempobject.defaultamountoflanes = std::stoi(val);
                        }
                    }
                }
                checkpixelqueue.push_back(tempobject);
            }
        }
    } 

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
    
    std::cout<<"Map of: "<<targetlatlon.first<<"N "<<targetlatlon.second<<"E. "<<side<<"m by "<<side<<"m @ "<<tilesperside*tilesperside<<" tiles ("<<tilesperside<<" tiles per side).\n";\
    std::cout<<"Meters per one tile: "<<tileside<<"\n";
    for(int y = 0; y < tilesperside; y++)
    {
        for(int x = 0; x < tilesperside; x++)
        {
            std::pair<double,double> searchlatlon = movelatlon_m(targetlatlon,-y*tileside-0.5*tileside,x*tileside+0.5*tileside);
            for(int i = 0; i < checkpixelqueue.size(); i++)
            {
                int retint = -1;
                if(checkpixelqueue[i].type == 1)
                {
                    retint = checkpixelqueue[i].checksimple(features,searchlatlon,tileside);
                }
                else if(checkpixelqueue[i].type == 3)
                {
                    retint = checkpixelqueue[i].checkprob(features,searchlatlon,tileside);
                }
                else if(checkpixelqueue[i].type == 2)
                {
                    retint = checkpixelqueue[i].checkroad(features,searchlatlon,tileside);
                }
                else if(checkpixelqueue[i].type == 0)
                {
                    retint = checkpixelqueue[i].checkelse();
                }
                if(retint == 0) break;
            }
            if(x<tilesperside-1) std::cout<<" ";
        }
        std::cout<<"\n";
    }
}