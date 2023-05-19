# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "01_firstSteps_autogen"
  "CMakeFiles\\01_firstSteps_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\01_firstSteps_autogen.dir\\ParseCache.txt"
  )
endif()
