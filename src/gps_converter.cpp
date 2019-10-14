#include <tas_proj/gps_converter.h>

namespace tas
{
namespace proj
{
GpsConverter::GpsConverter(const std::string& proj_string) : CoordinateSystemConverter()
{
    is_gps_ = false;
    proj_init_string_first_ = "+proj=longlat +ellps=WGS84 +datum=WGS84 +no_defs";
    if (!proj_string.empty())
        init(proj_string);
}

bool GpsConverter::init(const std::string& proj_string)
{
    bool success = CoordinateSystemConverter::init(proj_init_string_first_, proj_string);

    // Check if REF system is also latlong,
    // this will skip all transformations lateron
    is_gps_ = findString(proj_string, "longlat");

    return success;
}

bool GpsConverter::toGps(GpsCoord& to, const Eigen::Vector2d& from)
{
    if (!initialized_)
    {
        return false;
    }

    if (!is_gps_)
    {
        Eigen::Vector2d gps;
        toFirst(gps, from);
        to.lon = gps.x() * RAD_TO_DEG;
        to.lat = gps.y() * RAD_TO_DEG;
    }
    else
    {
        to.lon = from.x();
        to.lat = from.y();
    }
    return true;
}

bool GpsConverter::toGps(GpsCoord& to, const Eigen::Vector3d& from)
{
    if (!initialized_)
    {
        return false;
    }

    if (!is_gps_)
    {
        Eigen::Vector3d gps;
        toFirst(gps, from);
        to.lon = gps.x() * RAD_TO_DEG;
        to.lat = gps.y() * RAD_TO_DEG;
        to.altitude = gps.z();
    }
    else
    {
        to.lon = from.x();
        to.lat = from.y();
        to.altitude = from.z();
    }
    return true;
}

bool GpsConverter::fromGps(Eigen::Vector2d& to, const GpsCoord& from)
{
    if (!initialized_)
    {
        return false;
    }

    if (!is_gps_)
    {
        Eigen::Vector2d gps(from.lon * DEG_TO_RAD, from.lat * DEG_TO_RAD);
        toSecond(to, gps);
    }
    else
    {
        to.x() = from.lon;
        to.y() = from.lat;
    }
    return true;
}

bool GpsConverter::fromGps(Eigen::Vector3d& to, const GpsCoord& from)
{
    if (!initialized_)
    {
        return false;
    }

    if (!is_gps_)
    {
        Eigen::Vector3d gps(from.lon * DEG_TO_RAD, from.lat * DEG_TO_RAD, from.altitude);
        toSecond(to, gps);
    }
    else
    {
        to.x() = from.lon;
        to.y() = from.lat;
        to.z() = from.altitude;
    }
    return true;
}

bool GpsConverter::findString(const std::string& strHaystack, const std::string& strNeedle)
{
    auto it =
        std::search(strHaystack.begin(), strHaystack.end(), strNeedle.begin(), strNeedle.end(), [](char ch1, char ch2) {
            return std::toupper(ch1) == std::toupper(ch2);
        });
    return (it != strHaystack.end());
}
} // namespace proj
} // namespace tas
