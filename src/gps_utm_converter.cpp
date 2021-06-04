#include <tas_proj/gps_utm_converter.h>

namespace tas
{
namespace proj
{
bool GpsUtmConverter::gpsToUtm(const GpsCoord& gps_point, UtmCoord& utm_point)
{
  return gpsToUtm(gps_point.lon, gps_point.lat, gps_point.heading, gps_point.altitude, gps_point.heading_valid,
                  utm_point.east, utm_point.north, utm_point.heading, utm_point.altitude, utm_point.zone,
                  utm_point.heading_valid, utm_point.subarea);
}

bool GpsUtmConverter::utmToGps(GpsCoord& gps_point, const UtmCoord& utm_point)
{
  return utmToGps(gps_point.lon, gps_point.lat, gps_point.heading, gps_point.altitude, gps_point.heading_valid,
                  utm_point.east, utm_point.north, utm_point.heading, utm_point.altitude, utm_point.zone,
                  utm_point.heading_valid);
}

bool GpsUtmConverter::gpsToUtm(double gps_lon, double gps_lat, double gps_heading, double gps_altitude,
                               bool gps_heading_valid, double& utm_east, double& utm_north, double& utm_heading,
                               double& utm_altitude, int& utm_zone, bool& utm_heading_valid, char& utm_subarea)
{
  if (!initialized_)
  {
    init(gps_lon, gps_lat);
  }

  if (initialized_)
  {
    Eigen::Vector2d utm;
    toSecond(utm, { gps_lon * DEG_TO_RAD, gps_lat * DEG_TO_RAD });
    utm_east = utm.x();
    utm_north = utm.y();
    utm_zone = utm_zone_;
    utm_subarea = utm_area_;
    utm_altitude = gps_altitude;

    if (gps_heading_valid)
    {
      double heading_offset = 0;
      calcHeadingOffset(gps_lon, gps_lat, heading_offset);
      utm_heading = gps_heading + heading_offset;
      utm_heading_valid = true;
    }
    else
    {
      utm_heading = 0.0;
      utm_heading_valid = false;
    }

    return true;
  }
  else
    return false;
}

bool GpsUtmConverter::utmToGps(double& gps_lon, double& gps_lat, double& gps_heading, double& gps_altitude,
                               bool& gps_heading_valid, double utm_east, double utm_north, double utm_heading,
                               double utm_altitude, int utm_zone, bool utm_heading_valid)
{
  if (!initialized_)
  {
    init(utm_zone);
  }

  if (initialized_)
  {
    Eigen::Vector2d gps;
    toFirst(gps, { utm_east, utm_north });

    gps_lon = gps.x() * RAD_TO_DEG;
    gps_lat = gps.y() * RAD_TO_DEG;
    gps_altitude = utm_altitude;

    if (utm_heading_valid)
    {
      double heading_offset = 0;
      calcHeadingOffset(gps_lon, gps_lat, heading_offset);
      gps_heading = utm_heading - heading_offset;
      gps_heading_valid = true;
    }
    else
    {
      gps_heading = 0.0;
      gps_heading_valid = false;
    }

    return true;
  }
  else
    return false;
}

int GpsUtmConverter::getUtmZone()
{
  if (initialized_)
    return utm_zone_;
  else
    return 0;
}

char GpsUtmConverter::getUtmArea()
{
  if (initialized_)
    return utm_area_;
  else
    return 0;
}

void GpsUtmConverter::calcHeadingOffset(double lon, double lat, double& heading_offset)
{
  Eigen::Vector2d utm;
  double utm_east1, utm_north1, utm_east2, utm_north2;

  // transform given point from GPS to UTM
  toSecond(utm, { lon * DEG_TO_RAD, lat * DEG_TO_RAD });
  utm_east1 = utm.x();
  utm_north1 = utm.y();

  // calculate a second point, moved a bit along the lon-axis.
  // transform this second point from GPS to UTM
  toSecond(utm, { 0.0001 + lon * DEG_TO_RAD, lat * DEG_TO_RAD });
  utm_east2 = utm.x();
  utm_north2 = utm.y();

  // calculate the angle between GPS and UTM coordinate system at this given coordinate
  heading_offset = atan((utm_north2 - utm_north1) / (utm_east2 - utm_east1));
}

bool GpsUtmConverter::init(double lon, double lat)
{
  if ((lon == 0.0 && lat == 0.0) || (fabs(lon) <= 0.01f && fabs(lat) <= 0.01f))
  {
    return false;
  }

  calcUtmZone(lon, lat, utm_zone_, utm_area_);
  init(utm_zone_);

  if (!initialized_)
  {
    utm_zone_ = 0;
    utm_area_ = 0;
  }

  return initialized_;
}

bool GpsUtmConverter::init(int utm_zone)
{
  std::string second_proj_string = "+proj=utm +ellps=WGS84 +zone=" + std::to_string(utm_zone);
  return CoordinateSystemConverter::init("+proj=longlat +ellps=WGS84 +datum=WGS84 +no_defs", second_proj_string);
}

void GpsUtmConverter::calcUtmZone(double lon, double lat, int& zone, char& area)
{
  double lon_grad = lon;
  double lat_grad = lat;

  // ensure longitude is in rage -180.0...179.9
  double lon_grad_temp = (lon_grad + 180) - int((lon_grad + 180) / 360) * 360 - 180;

  // each UTM zone has a width of 6 degree
  int utm_zone = int((lon_grad + 180) / 6) + 1;

  // take care of special zone "Norwegen"
  if (lat_grad >= 56.0 && lat_grad < 64.0 && lon_grad_temp >= 3.0 && lon_grad_temp < 12.0)
    utm_zone = 32;

  // take care of special zone "Spitzbergen"
  if (lat_grad >= 72.0 && lat_grad < 84.0)
  {
    if (lon_grad_temp >= 0.0 && lon_grad_temp < 9.0)
      utm_zone = 31;
    else if (lon_grad_temp >= 9.0 && lon_grad_temp < 21.0)
      utm_zone = 33;
    else if (lon_grad_temp >= 21.0 && lon_grad_temp < 33.0)
      utm_zone = 35;
    else if (lon_grad_temp >= 33.0 && lon_grad_temp < 42.0)
      utm_zone = 37;
  }

  // determine the UTM aera (the character after the number)
  char utm_area;

  if ((84 >= lat_grad) && (lat_grad >= 72))
    utm_area = 'X';
  else if ((72 > lat_grad) && (lat_grad >= 64))
    utm_area = 'W';
  else if ((64 > lat_grad) && (lat_grad >= 56))
    utm_area = 'V';
  else if ((56 > lat_grad) && (lat_grad >= 48))
    utm_area = 'U';
  else if ((48 > lat_grad) && (lat_grad >= 40))
    utm_area = 'T';
  else if ((40 > lat_grad) && (lat_grad >= 32))
    utm_area = 'S';
  else if ((32 > lat_grad) && (lat_grad >= 24))
    utm_area = 'R';
  else if ((24 > lat_grad) && (lat_grad >= 16))
    utm_area = 'Q';
  else if ((16 > lat_grad) && (lat_grad >= 8))
    utm_area = 'P';
  else if ((8 > lat_grad) && (lat_grad >= 0))
    utm_area = 'N';
  else if ((0 > lat_grad) && (lat_grad >= -8))
    utm_area = 'M';
  else if ((-8 > lat_grad) && (lat_grad >= -16))
    utm_area = 'L';
  else if ((-16 > lat_grad) && (lat_grad >= -24))
    utm_area = 'K';
  else if ((-24 > lat_grad) && (lat_grad >= -32))
    utm_area = 'J';
  else if ((-32 > lat_grad) && (lat_grad >= -40))
    utm_area = 'H';
  else if ((-40 > lat_grad) && (lat_grad >= -48))
    utm_area = 'G';
  else if ((-48 > lat_grad) && (lat_grad >= -56))
    utm_area = 'F';
  else if ((-56 > lat_grad) && (lat_grad >= -64))
    utm_area = 'E';
  else if ((-64 > lat_grad) && (lat_grad >= -72))
    utm_area = 'D';
  else if ((-72 > lat_grad) && (lat_grad >= -80))
    utm_area = 'C';
  else
    utm_area = 'Z';  // This is here as an error flag to show that the Latitude is outside the UTM limits

  zone = utm_zone;
  area = utm_area;
}

double GpsUtmConverter::getHeadingOffset(double lon, double lat)
{
  double heading_offset = 0;
  calcHeadingOffset(lon, lat, heading_offset);
  return heading_offset;
}

}  // namespace proj
}  // namespace tas
