#include <cmath>

#include <tas_proj/gps_coord.h>

namespace tas
{
namespace proj
{
GpsCoord::GpsCoord() : lon(0), lat(0), altitude(0), heading(0), heading_valid(false)
{
}

GpsCoord::GpsCoord(double gps_lon, double gps_lat, double gps_heading, double gps_altitude, bool heading_valid)
  : lon(gps_lon), lat(gps_lat), altitude(gps_altitude), heading(gps_heading), heading_valid(heading_valid)
{
}

std::ostream& operator<<(std::ostream& os, const GpsCoord& c)
{
  os << " LON: " << c.lon;
  os << " LAT: " << c.lat;
  os << " HEAD: " << c.heading * M_PI / 180.;
  os << " ALT: " << c.altitude;
  os << " HEAD_VAL: " << c.heading_valid;
  return os;
}
}  // namespace proj
}  // namespace tas
