#pragma once

#include <ostream>

namespace tas::proj
{
class UtmCoord
{
public:
  //! Zone the coordinate is given in.
  //! Each of the 60 longitude zones in the UTM system uses a
  //! transverse Mercator projection, which can map a region of
  //! large north-south extent with low distortion.
  //! Zone=1 covers longitude 180° to 174° W; zone numbering
  //! increases eastward to zone 60 that covers longitude 174°
  //! to 180° East.
  int zone;

  //! Subarea means one character naming the latitude band.
  char subarea;

  //! North coordinate value in the given zone [m].
  double north;

  //! East coordinate value in the given zone [m].
  double east;

  //! Altitude is given at TAS w.r.t. "normal sea level" [m].
  //! The EGM96 geoid represents our earth because its more
  //! precise than the WGS84 ellipsoid.
  //! @attention Some GPS receivers provide the altitude
  //! measurements w.r.t. the WGS84 ellipsoid, these values must
  //! be corrected in the sensor input.
  double altitude;

  //! Heading=0 points to East [rad].
  //! @attention UTM-East is NOT parallel to GPS-East, thus a
  //! specific rotation is necessary (is performed by TAS
  //! GpsUtm-Convert functions).
  double heading;

  //! Flag that indicates if _heading is a valid value.
  bool heading_valid;

public:
  UtmCoord();

  UtmCoord(int utm_zone, char utm_subarea, double utm_north, double utm_east, double utm_heading, double utm_altitude,
           bool heading_valid);

  friend std::ostream& operator<<(std::ostream& os, const UtmCoord& utm);
};
}  // namespace tas
