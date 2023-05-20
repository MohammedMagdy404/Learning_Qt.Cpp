# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "02_QLayouts_autogen"
  "CMakeFiles\\02_QLayouts_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\02_QLayouts_autogen.dir\\ParseCache.txt"
  )
endif()
