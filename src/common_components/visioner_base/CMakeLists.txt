cmake_minimum_required(VERSION 3.5)
project(visioner_base)

include($ENV{ABCMAKE_PATH})
add_component(visioner_base)
target_link_components(visioner_base NAME microlog visioner_interfaces object_finder)
