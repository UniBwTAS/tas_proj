#pragma once

#define ACCEPT_USE_OF_DEPRECATED_PROJ_API_H

#include <proj_api.h>
#include <string>
#include <Eigen/Core>

namespace tas
{
namespace proj
{
/**
 * @class CoordinateSystemConverter.
 *
 * @author Thorsten Luettel
 * @author email: thorsten.luettel@unibw.de
 * @author Copyright (c) 2015
 * @author LRT 8 Autonomous Systems Technology
 * @author University of the Federal Armed Forces at Munich
 *
 * Converts between different coordinate systems, given by two
 * projection strings. Also converts heights between different ellisoids.
 */

class CoordinateSystemConverter
{
protected:
  //! Flag that declares the converter as initialized.
  bool initialized_;

  //! The initialization string for first projection.
  std::string proj_init_string_first_;

  //! The initialization string for second projection.
  std::string proj_init_string_second_;

  //! The first projection.
  projPJ proj_first_;

  //! The second projection.
  projPJ proj_second_;

public:
  /**
   * @brief Constructor
   * @param first_proj_string The first projection string
   * @param second_proj_string The second projection string
   */
  explicit CoordinateSystemConverter(const std::string& first_proj_string = "",
                                     const std::string& second_proj_string = "");

  /**
   * @brief Destructor
   */
  virtual ~CoordinateSystemConverter();

  /**
   * @brief Initializes the converter
   * @param first_proj_string The first projection string
   * @param second_proj_string The second projection string
   * @return True if successful, false otherwise
   */
  bool init(const std::string& first_proj_string, const std::string& second_proj_string);

  /**
   * @brief Converts a given coordinate from "first" to "second" coordinate system
   * @param to Target coordinates
   * @param from Source coordinates
   * @return True if successful, false otherwise
   */
  bool toSecond(Eigen::Vector3d& to, const Eigen::Vector3d& from);

  bool toSecond(Eigen::Vector2d& to, const Eigen::Vector2d& from);

  /**
   * @brief Converts a given coordinate from "second" to "first" coordinate system
   * @param to Target coordinates
   * @param from Source coordinates
   * @return True if successful, false otherwise
   */
  bool toFirst(Eigen::Vector3d& to, const Eigen::Vector3d& from);

  bool toFirst(Eigen::Vector2d& to, const Eigen::Vector2d& from);

  bool initialized();
};
}  // namespace proj
}  // namespace tas
