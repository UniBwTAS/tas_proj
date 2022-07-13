#pragma once

#include <tas_proj/gps_coord.h>

#include <tas_proj/coordinate_system_converter.h>

namespace tas::proj
{
/**
 * @class GpsConverter.
 *
 * @author Thorsten Luettel
 * @author email: thorsten.luettel@unibw.de
 * @author Copyright (c) 2015
 * @author LRT 8 Autonomous Systems Technology
 * @author University of the Federal Armed Forces at Munich
 *
 * Converts from and to GPS coordinates, given a projection string
 */
class GpsConverter : public CoordinateSystemConverter
{
public:
  /**
   * @brief Constructor
   * @param proj_string The projection string
   */
  explicit GpsConverter(const std::string& proj_string = "");

  /**
   * @brief Initializes the converter
   * @param proj_string The projection string
   * @return True if successful, false otherwise
   */
  bool init(const std::string& proj_string);

  /**
   * @brief Converts a given coordinate into GPS
   * @param to Resulting GPS coordinate
   * @param from Source coordinate
   * @return True if successful, false otherwise
   */
  bool toGps(GpsCoord& to, const PJ_COORD& from);

  /**
   * @brief Converts a given GPS coordinate into another system
   * @param to The resulting coordinate
   * @param from The source GPS coordinate
   * @return True if successful, false otherwise
   */
  bool fromGps(PJ_COORD& to, const GpsCoord& from);
};
}  // namespace tas
