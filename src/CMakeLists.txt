# src/CmakeLists.txt
add_library(monitor_core
  core/LogListParser.cpp
  core/LogParser.cpp
  utils/StringUtils.cpp
  utils/DateUtils.cpp
)

target_include_directories(monitor_core PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
)

target_include_directories(monitor_core PRIVATE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include_internal> 
)

add_executable(log_app main.cpp)
target_link_libraries(log_app PRIVATE monitor_core)
