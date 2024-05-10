cmake_minimum_required(VERSION 3.5)
project(visioner_app)

include($ENV{ABCMAKE_PATH})
add_component(visioner_app)
target_link_components(visioner_app NAME microlog visioner_interfaces)
