# generated from rosidl_cmake/cmake/rosidl_cmake_aggregate_target-extras.cmake.in

# Create a convenience aggregate target more_interfaces::more_interfaces
# that links all generated interface targets, so downstream packages can use
# a single modern CMake target name instead of ${more_interfaces_TARGETS}.
if(more_interfaces_TARGETS AND NOT TARGET more_interfaces::more_interfaces)
  add_library(more_interfaces::more_interfaces INTERFACE IMPORTED)
  set_target_properties(more_interfaces::more_interfaces PROPERTIES
    INTERFACE_LINK_LIBRARIES "${more_interfaces_TARGETS}")
endif()
