#pragma once

#include <proj.h>
#include <string>

namespace tas::proj
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
  PJ *P{};

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
  bool toSecond(PJ_COORD& to, const PJ_COORD& from);

  /**
   * @brief Converts a given coordinate from "second" to "first" coordinate system
   * @param to Target coordinates
   * @param from Source coordinates
   * @return True if successful, false otherwise
   */
  bool toFirst(PJ_COORD& to, const PJ_COORD& from);

  bool initialized() const;
};
}  // namespace tas
