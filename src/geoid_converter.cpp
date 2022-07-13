#include <tas_proj/geoid_converter.h>

namespace tas::proj
{
bool GeoidConverter::init()
{
  // in newer ubuntu versions egm96_15.gtx file already pre-installed in /usr/share/proj
  // std::string filepath = ament_index_cpp::get_package_share_directory("tas_proj") + "/media";
  // const char* c_filepath = filepath.c_str();
  // proj_context_set_search_paths(PJ_DEFAULT_CTX, 1, &c_filepath);
  return CoordinateSystemConverter::init("+proj=longlat +datum=WGS84 +no_defs",
                                         "+proj=longlat +datum=WGS84 +geoidgrids=egm96_15.gtx +no_defs");
}

double GeoidConverter::ellipsoidalHeight(double lon, double lat, double geoidal_height)
{
  if (!initialized_)
  {
    init();
  }

  PJ_COORD out;
  out.lpz.lam = lon;
  out.lpz.phi = lat;
  out.lpz.z = geoidal_height;
  toFirst(out, out);
  return out.lpz.z;
}

double GeoidConverter::geoidalHeight(double lon, double lat, double ellipsoidal_height)
{
  if (!initialized_)
  {
    init();
  }

  PJ_COORD out;
  out.lpz.lam = lon;
  out.lpz.phi = lat;
  out.lpz.z = ellipsoidal_height;
  toSecond(out, out);
  return out.lpz.z;
}

}  // namespace tas::proj
