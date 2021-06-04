#pragma once

#include <tas_proj/coordinate_system_converter.h>
#include <tas_proj/gps_coord.h>
#include <tas_proj/utm_coord.h>

namespace tas
{
namespace proj
{
class GpsUtmConverter : public CoordinateSystemConverter
{
public:
  /**
   * @brief Transform a GPS point from Lat/Lon to UTM system
   *
   * @param gps_point Source for point, in GPS coordinates
   * @param utm_point Destination for point, in UTM coordinates
   */
  bool gpsToUtm(const GpsCoord& gps_point, UtmCoord& utm_point);

  /**
   * @brief Transform a point from UTM system to GPS Lat/Lon
   *
   * @param gps_point Destination for point, in GPS coordinates
   * @param utm_point Source for point, in UTM coordinates
   */
  bool utmToGps(GpsCoord& gps_point, const UtmCoord& utm_point);

  /**
   * @brief Transform a GPS point from Lat/Lon to UTM system
   *
   * @param gps_lon           Source Point, GPS Longitude [degree]
   * @param gps_lat           Source Point, GPS Latitude [degree]
   * @param gps_heading       Source Point, GPS Heading, measured to Latitude-Axis (East=0) [rad]
   * @param gps_altitude      Source Point, GPS Altitude, measured to sea level
   * @param gps_heading_valid Source Point, notes if given GPS heading is valid or not
   * @param utm_east          Destination Point, UTM East Value [m]
   * @param utm_north         Destination Point, UTM North Value [m]
   * @param utm_heading       Destination Point, UTM Heading, measured to local (!) East Axis [rad]
   * @param utm_altitude      Destination Point, UTM Altitude, measured to sea level
   * @param utm_zone          Destination Point, UTM Zone (normally 32 in Munich)
   * @param utm_heading_valid Destination Point, notes if given UTM heading is valid or not
   * @param utm_subarea       Destination Point, UTM subarea (normally 'U' in Munich)
   */
  bool gpsToUtm(double gps_lon, double gps_lat, double gps_heading, double gps_altitude, bool gps_heading_valid,
                double& utm_east, double& utm_north, double& utm_heading, double& utm_altitude, int& utm_zone,
                bool& utm_heading_valid, char& utm_subarea);

  /**
   * @brief Transform a point from UTM system to GPS Lat/Lon
   *
   * @param gps_lon           Destination Point, GPS Longitude [degree]
   * @param gps_lat           Destination Point, GPS Latitude [degree]
   * @param gps_heading       Destination Point, GPS Heading, measured to Latitude-Axis (East=0) [rad]
   * @param gps_altitude      Destination Point, GPS Altitude, measured to sea level
   * @param gps_heading_valid Destination Point, notes if given GPS heading is valid or not
   * @param utm_east          Source Point, UTM East Value [m]
   * @param utm_north         Source Point, UTM North Value [m]
   * @param utm_heading       Source Point, UTM Heading, measured to local (!) East Axis [rad]
   * @param utm_altitude      Source Point, UTM Altitude, measured to sea level
   * @param utm_zone          Source Point, UTM Zone (normally 32 in Munich)
   * @param utm_heading_valid Source Point, notes if given UTM heading is valid or not
   */
  bool utmToGps(double& gps_lon, double& gps_lat, double& gps_heading, double& gps_altitude, bool& gps_heading_valid,
                double utm_east, double utm_north, double utm_heading, double utm_altitude, int utm_zone,
                bool utm_heading_valid);

  /**
   * @brief init Initialize the converter with given GPS coordinates
   * @param lon
   * @param lat
   * @return success
   */
  bool init(double lon, double lat);

  /**
   * @brief int Initialize the converter with given UTM zone
   * @param utm_zone
   * @return success
   */
  bool init(int utm_zone);

  /**
   * @brief getUtmZone Provides the current UTM zone.
   * @return
   */
  int getUtmZone();

  /**
   * @brief getUtmArea Provides the current UTM area as a char.
   * @return
   */
  char getUtmArea();

  /**
   * @brief getHeadingOffset provides the heading offset for given coordinate.
   *        Depeding on internal variable either the offset is calculated every time or
   *        one initial offset is returned.
   * @param lon
   * @param lat
   * @return
   */
  double getHeadingOffset(double lon, double lat);

  /**
   * @brief calcUtmZone Calculates the UTM zone and area info
   *        for the the given coordinate
   * @param lon
   * @param lat
   * @param zone is filled
   * @param area is filled
   */
  static void calcUtmZone(double lon, double lat, int& zone, char& area);

private:
  /**
   * @brief calcHeadingOffset Calculates the angle between GPS longitudinal(x) axis
   *        and UTM East(x) axis at the given coordinate
   * @param lon
   * @param lat
   * @param heading_offset is filled
   */
  void calcHeadingOffset(double lon, double lat, double& heading_offset);

private:
  int utm_zone_;
  char utm_area_;
};
}  // namespace proj
}  // namespace tas
