project(CaelisChaos CXX)

set(PROJECT_NAME CaelisChaos)

################################################################################
# Source groups
################################################################################
set(no_group_source_files
    "src/CaelisEngine/Engine Changelog.txt"
    "src/CaelisEngine/Engine Dev-Changelog.txt"
)
source_group("" FILES ${no_group_source_files})

set(Header_Files
    "enet-1.3.17/include/enet/enet.h"
    "src/CaelisEngine/CaelisEngine.h"
    "src/CaelisEngine/GameStates/GameState.h"
    "src/CaelisEngine/GameStates/MainMenu.h"
    "src/CaelisEngine/GameStates/SingleplayerLobby.h"
    "src/CaelisEngine/GameStates/Match.h"
    "src/CaelisEngine/GUI/Button.h"
    "src/CaelisEngine/GUI/GUIComponent.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Source_Files
    "src/Caelis Chaos.cpp"
    "src/CaelisEngine/GameStates/GameState.cpp"
    "src/CaelisEngine/GameStates/MainMenu.cpp"
    "src/CaelisEngine/GameStates/SingleplayerLobby.cpp"
    "src/CaelisEngine/GameStates/Match.cpp"
    "src/CaelisEngine/GUI/Button.cpp"
)
source_group("Source Files" FILES ${Source_Files})

set(ALL_FILES
    ${no_group_source_files}
    ${Header_Files}
    ${Source_Files}
)

################################################################################
# Target
################################################################################
add_executable(${PROJECT_NAME} ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE CaelisChaos)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Linux")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
    )
endif()
################################################################################
# Include directories
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_include_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include;"
        "${CMAKE_CURRENT_SOURCE_DIR}/vendor/SDL3-3.2.12/include;"
        "${CMAKE_CURRENT_SOURCE_DIR}/vendor/SDL3_image-3.2.4/include;"
        "${CMAKE_CURRENT_SOURCE_DIR}/vendor/SDL3_ttf-3.2.2/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/CaelisEngine"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    target_include_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/enet-1.3.17/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/vendor/SDL3-3.2.12/include;"
        "${CMAKE_CURRENT_SOURCE_DIR}/vendor/SDL3_image-3.2.4/include;"
        "${CMAKE_CURRENT_SOURCE_DIR}/vendor/SDL3_ttf-3.2.2/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/CaelisEngine"
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Linux")
    target_include_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/enet-1.3.17/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/vendor/SDL3-3.2.12/include;"
        "${CMAKE_CURRENT_SOURCE_DIR}/vendor/SDL3_image-3.2.4/include;"
        "${CMAKE_CURRENT_SOURCE_DIR}/vendor/SDL3_ttf-3.2.2/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/CaelisEngine"
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
    )
endif()

################################################################################
# Compile definitions
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
            "_DEBUG"
        ">"
        "$<$<CONFIG:Release>:"
            "NDEBUG"
        ">"
        "_CONSOLE;"
        "UNICODE;"
        "_UNICODE"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
            "_DEBUG"
        ">"
        "$<$<CONFIG:Release>:"
            "NDEBUG"
        ">"
        "Win32;"
        "_CONSOLE;"
        "UNICODE;"
        "_UNICODE"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Linux")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
            "_DEBUG"
        ">"
        "$<$<CONFIG:Release>:"
            "NDEBUG"
        ">"
        "_CONSOLE;"
        "UNICODE;"
        "_UNICODE"
    )
endif()

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
                /Oi;
                /Gy
            >
            /permissive-;
            /sdl;
            /W3;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
                /Oi;
                /Gy
            >
            /permissive-;
            /sdl;
            /W3;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Linux")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
                /Oi;
                /Gy
            >
            /permissive-;
            /sdl;
            /W3;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        )
    endif()
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
        string(CONCAT FILE_CL_OPTIONS
            "$<$<CONFIG:Release>:"
                "/utf-8"
            ">"
        )
    endif()
    source_file_compile_options(src/Caelis Chaos.cpp ${FILE_CL_OPTIONS})
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
                /SAFESEH:NO;
                /OPT:REF;
                /OPT:ICF
            >
            /DEBUG;
            /SUBSYSTEM:CONSOLE
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
                /SAFESEH:NO;
                /OPT:REF;
                /OPT:ICF
            >
            /DEBUG;
            /SUBSYSTEM:CONSOLE
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Linux")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
                /SAFESEH:NO;
                /OPT:REF;
                /OPT:ICF
            >
            /DEBUG;
            /SUBSYSTEM:CONSOLE
        )
    endif()
endif()

################################################################################
# Dependencies
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set(ADDITIONAL_LIBRARY_DEPENDENCIES
        "user32;"
        "gdi32;"
        "shell32;"
        "enet64;"
        "ws2_32;"
        "winmm;"
        "SDL3;"
        "SDL3_test;"
        "SDL3_ttf;"
        "SDL3_image"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    set(ADDITIONAL_LIBRARY_DEPENDENCIES

        "SDL3;"
        "SDL3_test;"
        "SDL3_ttf;"
        "SDL3_image"

        "user32;"
        "gdi32;"
        "shell32;"
        "ws2_32;"
        "winmm"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Linux")
    set(ADDITIONAL_LIBRARY_DEPENDENCIES

        "SDL3;"
        "SDL3_test;"
        "SDL3_ttf;"
        "SDL3_image"

    )
endif()
target_link_libraries(${PROJECT_NAME} PRIVATE "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_link_directories(${PROJECT_NAME} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/lib-vc2022;"
        "${CMAKE_CURRENT_SOURCE_DIR}/enet-1.3.17;"
        "${CMAKE_CURRENT_SOURCE_DIR}/vendor/SDL3-3.2.12/lib/x64;"
        "${CMAKE_CURRENT_SOURCE_DIR}/vendor/SDL3_image-3.2.4/lib/x64;"
        "${CMAKE_CURRENT_SOURCE_DIR}/vendor/SDL3_ttf-3.2.2/lib/x64"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    target_link_directories(${PROJECT_NAME} PRIVATE

        "${CMAKE_CURRENT_SOURCE_DIR}/vendor/SDL3-3.2.12/lib/x86;"
        "${CMAKE_CURRENT_SOURCE_DIR}/vendor/SDL3_image-3.2.4/lib/x86;"
        "${CMAKE_CURRENT_SOURCE_DIR}/vendor/SDL3_ttf-3.2.2/lib/x86"
        "${CMAKE_CURRENT_SOURCE_DIR}/lib-vc2022;"
        "C:/Program Files (x86)/Microsoft SDKs/Windows/v7.1A/Lib"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Linux")
    target_link_directories(${PROJECT_NAME} PRIVATE

        "${CMAKE_CURRENT_SOURCE_DIR}/vendor/SDL3-3.2.12/lib/x86;"
        "${CMAKE_CURRENT_SOURCE_DIR}/vendor/SDL3_image-3.2.4/lib/x86;"
        "${CMAKE_CURRENT_SOURCE_DIR}/vendor/SDL3_ttf-3.2.2/lib/x86"
    )
endif()


