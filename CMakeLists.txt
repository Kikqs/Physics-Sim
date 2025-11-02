cmake_minimum_required(VERSION 3.20)
project(physics-sim VERSION 0.1 LANGUAGES C CXX)

# ── C++ standard ────────────────────────────────────────────────
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ── Options ─────────────────────────────────────────────────────
option(SIM_FETCH_DEPS "Fetch & build third-party dependencies" ON)
option(SIM_USE_IMGUI_DOCKING "Use Dear ImGui docking branch" ON)
set(SIM_GL_VERSION "4.6" CACHE STRING "OpenGL core version for the GLAD loader")

# ── FetchContent dependencies ───────────────────────────────────
if(SIM_FETCH_DEPS)
  include(FetchContent)
  
  set(IGG_GLFW_TAG "3.4")
  set(IGG_GLM_TAG  "1.0.1")
  if(SIM_USE_IMGUI_DOCKING)
    set(IGG_IMGUI_TAG "v1.92.2-docking")
  else()
    set(IGG_IMGUI_TAG "v1.92.2")
  endif()
  set(IGG_GLAD_GL_VERSION "${SIM_GL_VERSION}")
  set(IGG_GLAD_DOWNLOAD ON)
  
  FetchContent_Declare(
    imgui_glfw_glad_glm
    GIT_REPOSITORY https://github.com/cmmw/imgui-glfw-glad-glm.git
    GIT_TAG v4.2.0
  )
  FetchContent_MakeAvailable(imgui_glfw_glad_glm)
  
endif()

# ── System OpenGL ───────────────────────────────────────────────
find_package(OpenGL REQUIRED)

# ── App target ──────────────────────────────────────────────────
file(GLOB_RECURSE SIM_APP_SOURCES CONFIGURE_DEPENDS src/app/*.cpp)

if(SIM_APP_SOURCES)
  add_executable(sim_app ${SIM_APP_SOURCES})
  
  target_include_directories(sim_app PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
  )
  
  target_link_libraries(sim_app PRIVATE
    imgui
    glfw
    glm
    OpenGL::GL
  )
  
  target_compile_definitions(sim_app PRIVATE 
    IMGUI_IMPL_OPENGL_LOADER_GLAD
  )
  
  # Enable warnings
  target_compile_options(sim_app PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Wpedantic>
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
  )
endif()

# ── Tests ───────────────────────────────────────────────────────
option(SIM_BUILD_TESTS "Build unit tests" ON)

if(SIM_BUILD_TESTS)
  enable_testing()
  
  # Common test settings
  set(TEST_COMPILE_OPTS
    $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Wpedantic>
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
    $<$<CONFIG:Debug>:-g -O0>
    $<$<CONFIG:Release>:-O3>
  )
  
  # Helper function to create tests
  function(add_sim_test test_name test_source)
    add_executable(${test_name} ${test_source})
    target_include_directories(${test_name} PRIVATE ${CMAKE_SOURCE_DIR}/include)
    target_compile_options(${test_name} PRIVATE ${TEST_COMPILE_OPTS})
    add_test(NAME ${test_name} COMMAND ${test_name})
  endfunction()
  
  # Create tests
  add_sim_test(test_vec2 tests/test_vec2.cpp)
  
  # Custom target to run all tests
  add_custom_target(run_tests
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure --verbose
    DEPENDS test_vec2 test_mass test_particle test_units
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running all unit tests..."
  )
  
  message(STATUS "Unit tests enabled. Run 'make test' or 'make run_tests'")
endif()

# ── Install ─────────────────────────────────────────────────────
install(TARGETS sim_app RUNTIME DESTINATION bin)

# ── Summary ─────────────────────────────────────────────────────
message(STATUS "")
message(STATUS "=== Physics Simulation Configuration ===")
message(STATUS "Build type:       ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ standard:     ${CMAKE_CXX_STANDARD}")
message(STATUS "Fetch deps:       ${SIM_FETCH_DEPS}")
message(STATUS "Build tests:      ${SIM_BUILD_TESTS}")
message(STATUS "OpenGL version:   ${SIM_GL_VERSION}")
message(STATUS "ImGui docking:    ${SIM_USE_IMGUI_DOCKING}")
message(STATUS "========================================")
message(STATUS "")
