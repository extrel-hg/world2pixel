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

// latitude longitude radius NSmove EWmove

int main(int argc, char* argv[])
{
    for(int i=0;i<argc;i++)
    {
        std::cout<<"Command parameter "<<i<<": "<<argv[i]<<"\n";
    }
    
    std::pair<double,double> targetlatlon = {std::stod(argv[1]),std::stod(argv[2])}; //north west corner
    int tilesperside = 100;
    double side = 100;
    double radiusmodifier = 1;

    if(argc>3)
    {
        tilesperside = std::stod(argv[3]);
        side = std::stod(argv[4]);
        radiusmodifier = std::stod(argv[5]);
    }

    std::string filename = "gol";
    if(argc>6) 
    {
        filename = argv[6];
    }

    double tileside = side/tilesperside;
    double searchradius = (side/tilesperside)*radiusmodifier;

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

    {
        std::vector<std::string> finishedmap;
        for(int y = 0; y < tilesperside; y++)
        {
            std::cout<<y+1<<"/"<<tilesperside<<"\n";
            std::string line="";
            for(int x = 0; x < tilesperside; x++)
            {
                std::pair<double,double> searchlatlon = movelatlon_m(targetlatlon,-y*tileside-0.5*tileside,x*tileside+0.5*tileside);
                if(isroad(features,searchlatlon,searchradius))
                {
                    line = line + "X";
                } else {
                    line = line + "-";
                }
                if(x<tilesperside-1) line = line + " ";
            }
            finishedmap.push_back(line);
        }

        for(int y = 0; y < finishedmap.size(); y++)
        {
            std::cout<<finishedmap[y]<<"\n";
        }

    }
    
}

/*THE GRAVEYARD*/
/*Rest in peace code prototypes [*]*/

/*
    std::cout<<std::setprecision(8)<<targetlatlon.first<<","<<targetlatlon.second<<"\n";
    targetlatlon = movelatlon_m(targetlatlon.first,targetlatlon.second,movevector.first,movevector.second);
    std::cout<<targetlatlon.first<<","<<targetlatlon.second<<"\n";
    Features inradius = features.maxMetersFromLonLat(targetradius, targetlatlon.second, targetlatlon.first);
    for (Feature curitem: inradius)
    {
        Tags tags = curitem.tags();
        bool typeout = false;
        std::vector<std::string> allowedkeys = {"landuse","natural","building","railway","highway","power","waterway"};
        
        for(Tag curtag: tags)
        {
            for(int i = 0; i < allowedkeys.size(); i++)
            {
                if(curtag.key() == allowedkeys[i])
                {
                    typeout = true;
                    goto skiptags;
                }
            }
        }

        skiptags:

        if(typeout)
        {
            std::cout << curitem["name"]<<" "<< curitem.id()<<" "<<curitem.typeName() << std::endl;
            for(Tag curtag: tags)
            {
                std::string key = curtag.key();
                std::string value = curtag.value();
                std::string curtagstring = key + "=" + value;
                for(int i = 0; i < allowedkeys.size(); i++)
                {
                    if(curtag.key() == allowedkeys[i])
                    {
                        std::cout<<"        ## "<<curtagstring<<std::endl;  
                    }
                }
            }
        }
    }
    */

/*
    Box bounds = Box::ofWSEN(
    cords);
    Features featuresinbounds = inputgol(bounds);

    for (Feature curitem: featuresinbounds)
    {
        Tags tags = curitem.tags();

        std::string filterlist[11] = {"type=region", "boundary=administrative","route=hiking","route=train","type=route_master",
            "type=treaty","boundary=political","route=bicycle","type=network","type=group","boundary=statistical"};

        bool skipitem = false;

        for(Tag curtag: tags)
        {
            std::string key = curtag.key();
            std::string value = curtag.value();
            std::string curtagstring = key + "=" + value;
            for(int i = 0; i < std::size(filterlist); i++)
            {
                if(curtagstring == filterlist[i])
                {
                    skipitem = true;
                    break;
                }
            }
            if(skipitem)
            {
                break;
            }
        }
        if(skipitem)
        {
            continue;
        }

        std::cout << curitem["name"]<<" "<< curitem.id()<<" "<<curitem.typeName() << std::endl;
        for(Tag tag: tags)
        {
            std::cout <<"## "<< tag.key() << "=" << tag.value() << std::endl;
        }

    }*/

/*
if(curitem.lon() < bounds.minLon() || curitem.lon() > bounds.maxLon() || curitem.lat() < bounds.minLat() || curitem.lat() > bounds.maxLat())
{
    //continue;
}
*/


/*Features france("gol.gol");
    Box bounds = Box::ofWSEN(
    cords);
    Features thingsInParis = france(bounds);

    for (Feature curitem: thingsInParis)
    {
        std::cout << curitem["name"] << std::endl;
    }*/


/*
    // Open target .gol file
    Features features("gol");      

    // Define a set that contains nodes and areas that are pubs
    Features curquery = features("*[natural=water],""*[waterway]");

    // Iterate through the pubs that are contained 
    // in the area of Zurich and print their names
    for (Feature curitem: curquery)
    {
        if(curitem["name"] == "")
        {
            continue;
        }
        std::cout << curitem["name"] << std::endl;
    }
*/