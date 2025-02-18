#include <geodesk/geodesk.h>

using namespace geodesk;

int main(int argc, char* argv[])
{
    //latitude - north south
    //longitude - east west
    Features features("gol");
    Coordinate myLocation = Coordinate::ofLonLat(17.225415,51.662171);
    Features inradius = features.maxMetersFrom(10, myLocation);
    for (Feature curitem: inradius)
    {
        std::cout << curitem["name"]<<" "<< curitem.id()<<" "<<curitem.typeName() << std::endl;
    }
}

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