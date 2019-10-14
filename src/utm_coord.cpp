#include <cmath>

#include <tas_proj/utm_coord.h>

namespace tas
{
namespace proj
{
UtmCoord::UtmCoord() : zone(0), subarea(' '), north(0), east(0), altitude(0), heading(0), heading_valid(false)
{
}

UtmCoord::UtmCoord(int utm_zone,
                   char utm_subarea,
                   double utm_north,
                   double utm_east,
                   double utm_heading,
                   double utm_altitude,
                   bool heading_valid)
    : zone(utm_zone),
      subarea(utm_subarea),
      north(utm_north),
      east(utm_east),
      altitude(utm_altitude),
      heading(utm_heading),
      heading_valid(heading_valid)
{
}

std::ostream& operator<<(std::ostream& os, const UtmCoord& c)
{
    os << " UTM ZONE: " << c.zone << c.subarea;
    os << " EAST: " << c.east;
    os << " NORTH: " << c.north;
    os << " HEAD: " << c.heading * M_PI / 180.;
    os << " ALT: " << c.altitude;
    os << " HEAD_VAL: " << c.heading_valid;
    return os;
}
} // namespace proj
} // namespace tas
