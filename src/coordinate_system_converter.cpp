#include <iostream>
#include <tas_proj/coordinate_system_converter.h>

namespace tas::proj
{
CoordinateSystemConverter::CoordinateSystemConverter(const std::string& first_proj_string,
                                                     const std::string& second_proj_string)
{
  initialized_ = false;
  if (!first_proj_string.empty() && !second_proj_string.empty())
    init(first_proj_string, second_proj_string);
}

CoordinateSystemConverter::~CoordinateSystemConverter()
{
  proj_destroy(P);
}

bool CoordinateSystemConverter::init(const std::string& first_proj_string, const std::string& second_proj_string)
{
  std::string filepath = "/usr/share/proj";
  const char* c_filepath = filepath.c_str();
  proj_context_set_search_paths(PJ_DEFAULT_CTX, 1, &c_filepath);

  proj_init_string_first_ = first_proj_string;
  proj_init_string_second_ = second_proj_string;

  P = proj_create_crs_to_crs(PJ_DEFAULT_CTX, first_proj_string.c_str(), second_proj_string.c_str(), nullptr);
  initialized_ = P != nullptr;
  return initialized_;
}

bool CoordinateSystemConverter::toSecond(PJ_COORD& to, const PJ_COORD& from)
{
  if (!initialized_)
  {
    return false;
  }

  to = proj_trans(P, PJ_FWD, from);

  return true;
}

bool CoordinateSystemConverter::toFirst(PJ_COORD& to, const PJ_COORD& from)
{
  if (!initialized_)
  {
    return false;
  }

  to = proj_trans(P, PJ_INV, from);

  return true;
}

bool CoordinateSystemConverter::initialized() const
{
  return initialized_;
}

}  // namespace tas::proj
