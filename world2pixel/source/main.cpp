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

void cchange(int c) //Funkcja zmiany koloru tekstu!
{
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, c);
}

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
            if(israilroad(features,searchlatlon,tileside,railscanmodifier))
            {
                cchange(8);
                std::cout<<"X";
            } else if(int retval = isroad(features,searchlatlon,tileside,10,3.5,roadscanmodifier); retval>0)
            {
                if(retval==1) cchange(15);
                if(retval==2) cchange(6);
                std::cout<<"X";
            }  else if(isbuilding(features,searchlatlon,tileside))
            {
                cchange(12);
                std::cout<<char(254);
            } else if(iswater(features,searchlatlon,tileside))
            {
                cchange(9);
                std::cout<<"~";
            } else if(int retval = istree_probability(features,searchlatlon,tileside); retval>0)
            {
                if(retval==1)
                {
                    cchange(2);
                    std::cout<<".";
                }
                if(retval==2)
                {
                    cchange(2);
                    std::cout<<char(159);
                }
            } else if(ispaved(features,searchlatlon,tileside))
            {
                cchange(8);
                std::cout<<"-";
            }  else if(islowgreenarea(features,searchlatlon,tileside))
            {
                cchange(10);
                std::cout<<char(137);
            }
            else
            {
                cchange(10);
                std::cout<<char(137);
            }
            if(x<tilesperside-1) std::cout<<" ";
        }
        std::cout<<"\n";
    }
    std::cout<<"Meters per one tile: "<<tileside;
}