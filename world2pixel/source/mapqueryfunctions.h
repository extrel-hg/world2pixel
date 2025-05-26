bool isroad(Features infeatures, std::pair<double,double> searchlatlon, double tileside, int lanestosearch = 10, double lanewidth = 3.5);
bool iswater(Features infeatures, std::pair<double,double> searchlatlon, double tileside);
bool isbuilding(Features infeatures, std::pair<double,double> searchlatlon, double tileside);
bool islowgreenarea(Features infeatures, std::pair<double,double> searchlatlon, double tileside);
bool israilroad(Features infeatures, std::pair<double,double> searchlatlon, double tileside, int lanestosearch = 2, double lanewidth = 3.5);