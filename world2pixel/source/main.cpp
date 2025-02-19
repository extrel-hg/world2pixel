#include <geodesk/geodesk.h>
#include <stdlib.h>

using namespace geodesk;

//latitude - north south
//longitude - east west
//Yea its easy to mess it up sometimes

/*
TO DO:
* make documentation for devs and for users
* fill out README
* maybe dont use goto
*/

int main(int argc, char* argv[])
{

    for(int i=0;i<argc;i++)
    {
        std::cout<<"Command parameter "<<i<<": "<<argv[i]<<"\n";
    }

    float targetlatitude,targetlongitude,targetradius;
    targetlatitude = atof(argv[1]);
    targetlongitude = atof(argv[2]);
    targetradius = atof(argv[3]);

    std::string filename = "gol";
    if(argc>4) 
    {
        filename = argv[4];
    }

    Features features(filename.c_str());
    Features inradius = features.maxMetersFromLonLat(targetradius, targetlongitude, targetlatitude);
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
}

/*
SONGS THAT YOUTUBE PLAYED WHILE DEVVING
2025.02.19
14:20
https://www.youtube.com/watch?v=Hd2-Akz6Ht4
14:30
https://www.youtube.com/watch?v=0JliRJNGwQU
*/

/*THE GRAVEYARD*/
/*Rest in peace code prototypes [*]*/

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