#include <tas_proj/gps_converter.h>

namespace tas::proj
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

bool GpsConverter::toGps(GpsCoord& to, const PJ_COORD& from)
{
  if (!initialized_)
  {
    return false;
  }

  PJ_COORD gps;
  toFirst(gps, from);
  to.lon = gps.lpz.lam;
  to.lat = gps.lpz.phi;
  to.altitude = gps.lpz.z;

  return true;
}

bool GpsConverter::fromGps(PJ_COORD& to, const GpsCoord& from)
{
  if (!initialized_)
  {
    return false;
  }

  PJ_COORD gps;
  gps.lpz.lam = from.lon;
  gps.lpz.phi = from.lat;
  gps.lpz.z = from.altitude;
  toSecond(to, gps);

  return true;
}
}  // namespace tas::proj
