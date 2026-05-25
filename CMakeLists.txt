cmake_minimum_required(VERSION 3.22)
project(EcotoneLabsUI VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ── Conditionally fetch JUCE ──────────────────────────────────────────────────
# When consumed via FetchContent by a parent project that already fetched JUCE,
# juce::juce_core is already a target — skip to avoid target redefinition errors.
if(NOT TARGET juce::juce_core)
    include(FetchContent)
    FetchContent_Declare(
        JUCE
        GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
        GIT_TAG        8.0.4
        GIT_SHALLOW    TRUE
    )
    FetchContent_MakeAvailable(JUCE)
endif()

# ── Embed fonts ───────────────────────────────────────────────────────────────
# NAMESPACE avoids BinaryData ODR collision with the parent app's own binary
# data targets. HEADER_NAME keeps the generated header filename distinct too.
juce_add_binary_data(EcotoneLabsUIFonts
    NAMESPACE   EcotoneLabsUIFonts
    HEADER_NAME EcotoneLabsUIFonts.h
    SOURCES
        fonts/JetBrainsMono-Regular.ttf
        fonts/JetBrainsMono-Medium.ttf
        fonts/InstrumentSerif-Italic.ttf
)

# ── Library target ────────────────────────────────────────────────────────────
add_library(EcotoneLabsUI STATIC)
add_library(EcotoneLabs::UI ALIAS EcotoneLabsUI)

target_sources(EcotoneLabsUI PRIVATE
    src/CordycepsLookAndFeel.cpp
)

# PUBLIC: consumers inherit the include path and find CordycepsLookAndFeel.h
# with no changes to their #include directives.
target_include_directories(EcotoneLabsUI
    PUBLIC  "${CMAKE_CURRENT_SOURCE_DIR}/include"
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_compile_features(EcotoneLabsUI PUBLIC cxx_std_17)

target_link_libraries(EcotoneLabsUI
    PUBLIC
        juce::juce_gui_basics
        juce::juce_graphics
        juce::juce_core
    PRIVATE
        EcotoneLabsUIFonts
        juce::juce_recommended_config_flags
        juce::juce_recommended_warning_flags
)
