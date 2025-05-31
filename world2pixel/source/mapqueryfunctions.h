#pragma once

bool simplepixelcheck(Features infeatures, std::pair<double,double> searchlatlon, double tileside, std::string filterpositive, std::string filternegative = "", double radiusmultiplier = 1, double radiusmodifier = 0);

int probabilitypixelcheck(Features infeatures, std::pair<double,double> searchlatlon, double tileside, double densitypermetersquare, double tilesideresolutioncutoff, std::string filterpositive, std::string filternegative = "", double radiusmultiplier = 1, double radiusmodifier = 0);

bool roadlikepixelcheck(Features infeatures, std::pair<double,double> searchlatlon, double tileside, std::string filterpositive, std::string filternegative = "", int lanestosearch = 4, double lanewidth = 3.5, std::string lanekey = "lanes", int defaultamountoflanes = 2, double radiusmultiplier = 1, double radiusmodifier = 0);