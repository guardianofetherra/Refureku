cmake_minimum_required(VERSION 3.13.5)

project(RefurekuGenerator)

# Build dependencies
add_subdirectory(Submodules/Kodgen)

# Add Refureku generator executable
set(RefurekuGeneratorLibTarget RefurekuGeneratorLib)
add_library(${RefurekuGeneratorLibTarget}
				STATIC
					Source/FileParser.cpp
					Source/GeneratedEntityCodeTemplate.cpp
					Source/GeneratedClassCodeTemplate.cpp
					Source/GeneratedEnumCodeTemplate.cpp
					Source/FileGenerator.cpp)

# Warning level
if (MSVC)
	string(REGEX REPLACE " /W3" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")	# Remove the default flag /W3 - get /W4 propagated from Kodgen
endif()

# Setup compilation definitions
if (RFK_DEV)
	target_compile_definitions(${RefurekuGeneratorLibTarget} PUBLIC RFK_DEV=1)
endif()

target_include_directories(${RefurekuGeneratorLibTarget} PUBLIC Include)

# Link to Kodgen library
target_link_libraries(${RefurekuGeneratorLibTarget} PUBLIC Kodgen)

set(RefurekuGeneratorExeTarget RefurekuGenerator)
add_executable(${RefurekuGeneratorExeTarget} Source/main.cpp)

target_link_libraries(${RefurekuGeneratorExeTarget} PRIVATE ${RefurekuGeneratorLibTarget})

# Copy the RefurekuSettings template file next to the generated binary
add_custom_command(	TARGET ${RefurekuGeneratorExeTarget} PRE_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy
					${PROJECT_SOURCE_DIR}/RefurekuSettings.toml
					$<IF:$<BOOL:${MSVC}>,${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE}/RefurekuSettings.toml,${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/RefurekuSettings.toml>)