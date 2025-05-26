bool isroad(Features infeatures, std::pair<double,double> searchlatlon, double tileside, int lanestosearch = 10, double lanewidth = 3.5, double scanradiusmodifier = 1);
bool iswater(Features infeatures, std::pair<double,double> searchlatlon, double tileside);
bool isbuilding(Features infeatures, std::pair<double,double> searchlatlon, double tileside);
bool islowgreenarea(Features infeatures, std::pair<double,double> searchlatlon, double tileside);
bool israilroad(Features infeatures, std::pair<double,double> searchlatlon, double tileside , double lanewidth = 3.5, double scanradiusmodifier=1);
bool ispaved(Features infeatures, std::pair<double,double> searchlatlon, double tileside);
int istree_probability(Features infeatures, std::pair<double,double> searchlatlon, double tileside, double treespermetersquare = 0.05, double definitetreeminval = 50);