#pragma once

#include <ostream>

namespace tas
{
namespace proj
{

/**
 * @brief The GPSCoord class
 */
class GpsCoord
{
  public:
    //! Geographic Longitude w.r.t. WGS84 ellipsoid [degree].
    double lon;

    //! Geographic Latitude w.r.t. WGS84 ellipsoid [degree].
    double lat;

    //! Altitude is given at TAS w.r.t. "normal sea level" [m].
    //! The EGM96 geoid represents our earth because its more
    //! precise than the WGS84 ellipsoid.
    //! @attention Some GPS receivers provide the altitude
    //! measurements w.r.t. the WGS84 ellipsoid, these values must
    //! be corrected in the sensor input.
    double altitude;

    //! Heading=0 points to GPS-East [rad].
    //! Heading=0 means the direction is parallel to a constant lat.
    //! @attention GPS-East is NOT parallel to UTM-East, thus a
    //! specific rotation is necessary (is performed by TAS
    //! GpsUtm-Convert functions).
    double heading;

    //! Flag that indicates if _heading is a valid value.
    bool heading_valid;

  public:
    GpsCoord();

    /**
     *
     * @param gps_lon
     * @param gps_lat
     * @param gps_heading
     * @param gps_altitude
     * @param gps_heading_valid
     * @return
     */
    GpsCoord(double gps_lon, double gps_lat, double gps_heading, double gps_altitude, bool gps_heading_valid = false);

    friend std::ostream& operator<<(std::ostream& os, const GpsCoord& c);
}; // GpsCoord

} // namespace proj
} // namespace tas
