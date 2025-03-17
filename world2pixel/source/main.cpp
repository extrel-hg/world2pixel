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
    
    std::pair<double,double> targetlatlon = {std::stod(argv[1]),std::stod(argv[2])};

    std::string filename = "gol";
    if(argc>3) 
    {
        filename = argv[3];
    }

    Features rootfeatures(filename.c_str());

    //filter out features that arent needed, to speed up a little the queries
    Features features = rootfeatures("*[!admin_level]");
    features = features("*[!region_category]");

    //test code, check if any of the features that were supposed to be filtered out, were.
    for (Feature testf : features)
    {
        Tags tags = testf.tags();
        for(Tag tag: tags)
        {
            if(tag.key() == "admin_level") std::cout<<"endl\n";
            if(tag.key() == "region_category") std::cout<<"ada\n";
        }
    }

    for(int y = 0; y < 100; y++)
    {
        for(int x = 0; x < 100; x++)
        {
            std::pair<double,double> searchlatlon = movelatlon_m(targetlatlon,-y*10,x*10);
            if(isroad(features,searchlatlon,10))
            {
                std::cout<<"X";
            } else {
                std::cout<<"-";
            }
        }
        std::cout<<"\n";
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