cmake_minimum_required(VERSION 3.20)

project(physics-sim-nea VERSION 0.1 LANGUAGES C CXX)

# ── C++ standard ────────────────────────────────────────────────────────────────
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ── Options ────────────────────────────────────────────────────────────────────
option(SIM_FETCH_DEPS "Fetch & build third-party dependencies" ON)
option(SIM_USE_IMGUI_DOCKING "Use Dear ImGui docking branch" ON)
set(SIM_GL_VERSION "4.6" CACHE STRING "OpenGL core version for the GLAD loader")

# ── Dependencies (GLFW, GLM, ImGui, GLAD) ──────────────────────────────────────
if(SIM_FETCH_DEPS)
  include(FetchContent)

  # Pins to stable releases
  set(IGG_GLFW_TAG "3.4")                           # GLFW 3.4
  set(IGG_GLM_TAG  "1.0.1")                         # GLM 1.0.1
  if(SIM_USE_IMGUI_DOCKING)
    set(IGG_IMGUI_TAG "v1.92.2-docking")            # Dear ImGui docking
  else()
    set(IGG_IMGUI_TAG "v1.92.2")
  endif()
  set(IGG_GLAD_GL_VERSION "${SIM_GL_VERSION}")      # e.g. 4.6
  set(IGG_GLAD_DOWNLOAD ON)                         # download GLAD code during configure

  FetchContent_Declare(
    imgui_glfw_glad_glm
    GIT_REPOSITORY https://github.com/cmmw/imgui-glfw-glad-glm.git
    GIT_TAG v4.2.0
  )
  FetchContent_MakeAvailable(imgui_glfw_glad_glm)
endif()

# ── System OpenGL ──────────────────────────────────────────────────────────────
find_package(OpenGL REQUIRED)

# ── App target ─────────────────────────────────────────────────────────────────
file(GLOB_RECURSE SIM_APP_SOURCES
  CONFIGURE_DEPENDS
  src/app/*.cpp
)

if(SIM_APP_SOURCES)
  add_executable(sim_app ${SIM_APP_SOURCES})

  target_link_libraries(sim_app PRIVATE
    imgui
    glfw
    glm
    OpenGL::GL
  )

  target_compile_definitions(sim_app PRIVATE IMGUI_IMPL_OPENGL_LOADER_GLAD)
  target_include_directories(sim_app PRIVATE ${CMAKE_SOURCE_DIR}/src)
endif()

# ── (Optional) install step for the app ────────────────────────────────────────
install(TARGETS sim_app RUNTIME DESTINATION bin)
