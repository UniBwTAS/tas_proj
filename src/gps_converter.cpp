#include <tas_proj/gps_converter.h>

namespace tas
{
namespace proj
{
GpsConverter::GpsConverter(const std::string& proj_string) : CoordinateSystemConverter()
{
  proj_init_string_first_ = "+proj=longlat +ellps=WGS84 +datum=WGS84 +no_defs";
  if (!proj_string.empty())
    init(proj_string);
}

bool GpsConverter::init(const std::string& proj_string)
{
  return CoordinateSystemConverter::init(proj_init_string_first_, proj_string);
}

bool GpsConverter::toGps(GpsCoord& to, const Eigen::Vector2d& from)
{
  if (!initialized_)
  {
    return false;
  }

  Eigen::Vector2d gps;
  toFirst(gps, from);
  to.lon = gps.x() * RAD_TO_DEG;
  to.lat = gps.y() * RAD_TO_DEG;

  return true;
}

bool GpsConverter::toGps(GpsCoord& to, const Eigen::Vector3d& from)
{
  if (!initialized_)
  {
    return false;
  }

  Eigen::Vector3d gps;
  toFirst(gps, from);
  to.lon = gps.x() * RAD_TO_DEG;
  to.lat = gps.y() * RAD_TO_DEG;
  to.altitude = gps.z();

  return true;
}

bool GpsConverter::fromGps(Eigen::Vector2d& to, const GpsCoord& from)
{
  if (!initialized_)
  {
    return false;
  }

  Eigen::Vector2d gps(from.lon * DEG_TO_RAD, from.lat * DEG_TO_RAD);
  toSecond(to, gps);

  return true;
}

bool GpsConverter::fromGps(Eigen::Vector3d& to, const GpsCoord& from)
{
  if (!initialized_)
  {
    return false;
  }

  Eigen::Vector3d gps(from.lon * DEG_TO_RAD, from.lat * DEG_TO_RAD, from.altitude);
  toSecond(to, gps);

  return true;
}
}  // namespace proj
}  // namespace tas
