#include <tas_proj/coordinate_system_converter.h>

namespace tas
{
namespace proj
{
CoordinateSystemConverter::CoordinateSystemConverter(const std::string& first_proj_string,
                                                     const std::string& second_proj_string)
{
  proj_first_ = nullptr;
  proj_second_ = nullptr;
  initialized_ = false;
  if (!first_proj_string.empty() && !second_proj_string.empty())
    init(first_proj_string, second_proj_string);
}

CoordinateSystemConverter::~CoordinateSystemConverter()
{
  if (proj_first_)
    pj_free(proj_first_);
  if (proj_second_)
    pj_free(proj_second_);
}

bool CoordinateSystemConverter::init(const std::string& first_proj_string, const std::string& second_proj_string)
{
  proj_init_string_first_ = first_proj_string;
  proj_init_string_second_ = second_proj_string;

  proj_first_ = pj_init_plus(first_proj_string.c_str());
  proj_second_ = pj_init_plus(second_proj_string.c_str());

  initialized_ = (proj_first_ && proj_second_);
  return initialized_;
}

bool CoordinateSystemConverter::toSecond(Eigen::Vector3d& to, const Eigen::Vector3d& from)
{
  if (!initialized_)
  {
    return false;
  }

  double x = from.x();
  double y = from.y();
  double z = from.z();
  bool success = !pj_transform(proj_first_, proj_second_, 1, 1, &x, &y, &z);
  to.x() = x;
  to.y() = y;
  to.z() = z;
  return success;
}

bool CoordinateSystemConverter::toSecond(Eigen::Vector2d& to, const Eigen::Vector2d& from)
{
  if (!initialized_)
  {
    return false;
  }

  double x = from.x();
  double y = from.y();
  bool success = !pj_transform(proj_first_, proj_second_, 1, 1, &x, &y, nullptr);
  to.x() = x;
  to.y() = y;
  return success;
}

bool CoordinateSystemConverter::toFirst(Eigen::Vector3d& to, const Eigen::Vector3d& from)
{
  if (!initialized_)
  {
    return false;
  }

  double x = from.x();
  double y = from.y();
  double z = from.z();
  bool success = !pj_transform(proj_second_, proj_first_, 1, 1, &x, &y, &z);
  to.x() = x;
  to.y() = y;
  to.z() = z;
  return success;
}

bool CoordinateSystemConverter::toFirst(Eigen::Vector2d& to, const Eigen::Vector2d& from)
{
  if (!initialized_)
  {
    return false;
  }

  double x = from.x();
  double y = from.y();
  bool success = !pj_transform(proj_second_, proj_first_, 1, 1, &x, &y, nullptr);
  to.x() = x;
  to.y() = y;
  return success;
}

bool CoordinateSystemConverter::initialized()
{
  return initialized_;
}

}  // namespace proj
}  // namespace tas
