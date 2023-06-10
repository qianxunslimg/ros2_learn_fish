# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_example_parameters_rclcpp_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED example_parameters_rclcpp_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(example_parameters_rclcpp_FOUND FALSE)
  elseif(NOT example_parameters_rclcpp_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(example_parameters_rclcpp_FOUND FALSE)
  endif()
  return()
endif()
set(_example_parameters_rclcpp_CONFIG_INCLUDED TRUE)

# output package information
if(NOT example_parameters_rclcpp_FIND_QUIETLY)
  message(STATUS "Found example_parameters_rclcpp: 0.0.0 (${example_parameters_rclcpp_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'example_parameters_rclcpp' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  message(WARNING "${_msg}")
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(example_parameters_rclcpp_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${example_parameters_rclcpp_DIR}/${_extra}")
endforeach()
