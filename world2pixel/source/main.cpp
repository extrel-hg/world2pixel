#include <geodesk/geodesk.h>

using namespace geodesk;

int main(int argc, char* argv[])
{
    // Open switzerland.gol
    Features features("gol");      

    // Get the feature that represents the area of the city of Zurich
    Feature zurich = features(
        "a[boundary=administrative][admin_level=8]"
        "[name:en=Zurich]").one();

    // Define a set that contains nodes and areas that are pubs
    Features pubs = features("na[amenity=pub]");

    // Iterate through the pubs that are contained 
    // in the area of Zurich and print their names
    for (Feature pub: pubs.within(zurich))
    {
        std::cout << pub["name"] << std::endl;
    }
}