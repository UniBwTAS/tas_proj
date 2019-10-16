#include <ros/package.h>

#include <tas_proj/geoid_converter.h>

namespace tas
{
namespace proj
{

bool GeoidConverter::init()
{
    std::string filepath = ros::package::getPath("tas_proj") + "/media";
    const char* c_filepath = filepath.c_str();
    pj_set_searchpath(1, &c_filepath);
    return CoordinateSystemConverter::init("+proj=longlat +datum=WGS84 +no_defs",
                                           "+proj=longlat +datum=WGS84 +geoidgrids=egm96_15.gtx +no_defs");
}

double GeoidConverter::ellipsoidalHeight(double lon, double lat, double geoidal_height)
{
    if (!initialized_)
    {
        init();
    }

    Eigen::Vector3d out;
    toFirst(out, {lon * DEG_TO_RAD, lat * DEG_TO_RAD, geoidal_height});
    return out.z();
}

double GeoidConverter::geoidalHeight(double lon, double lat, double ellipsoidal_height)
{
    if (!initialized_)
    {
        init();
    }

    Eigen::Vector3d out;
    toSecond(out, {lon * DEG_TO_RAD, lat * DEG_TO_RAD, ellipsoidal_height});
    return out.z();
}

} // namespace proj
} // namespace tas
