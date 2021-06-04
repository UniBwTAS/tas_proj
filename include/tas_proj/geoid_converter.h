#pragma once

#pragma once

#include <Eigen/Core>

#include <tas_proj/gps_coord.h>

#include <tas_proj/coordinate_system_converter.h>

namespace tas
{
namespace proj
{
/**
 * @class GeoidConverter.
 *
 * @author Andreas Reich
 * @author email: thorsten.luettel@unibw.de
 * @author Copyright (c) 2015
 * @author LRT 8 Autonomous Systems Technology
 * @author University of the Federal Armed Forces at Munich
 *
 * Converts from and to GPS coordinates, given a projection string
 */
class GeoidConverter : public CoordinateSystemConverter
{
public:
  /**
   * @brief Initializes the converter
   * @return True if successful, false otherwise
   */
  bool init();

  /**
   * @brief ellipsoidalHeight Converts geoidal height (w.r.t. EGM96 Geoid) to ellipsoidal height (w.r.t. WGS84
   * ellipsoid)
   * @param geoidal_height [m]
   * @param latitude [degree]
   * @param longitude [degree]
   * @return
   */
  double ellipsoidalHeight(double lon, double lat, double geoidal_height);

  /**
   * @brief geoidalHeight Converts ellipsoidal height (w.r.t. WGS84 ellipsoid) to geoidal height (w.r.t. EGM96 Geoid)
   * @param ellipsoidal_height [m]
   * @param latitude [degree]
   * @param longitude [degree]
   * @return
   */
  double geoidalHeight(double lon, double lat, double ellipsoidal_height);
};
}  // namespace proj
}  // namespace tas
