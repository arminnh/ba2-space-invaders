# get all *.cpp files recursively
file(GLOB_RECURSE SRC ${PROJECT_SOURCE_DIR}/src/*.cpp)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}" ${CMAKE_MODULE_PATH})
FIND_PACKAGE(SFML 2 COMPONENTS graphics window system REQUIRED)
ADD_EXECUTABLE(Space_Invaders ${SRC})
target_link_libraries(Space_Invaders ${SFML_LIBRARIES})

INSTALL(TARGETS Space_Invaders DESTINATION ${PROJECT_SOURCE_DIR}/bin)
