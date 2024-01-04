cmake_minimum_required(VERSION 3.25.1)

project(nes_emulator)

add_compile_options(-ggdb)
add_compile_options(-W -Wall)

file(GLOB CORE_SRC lib/core/*.c)
add_library(core STATIC ${CORE_SRC})
target_include_directories(core PUBLIC include)
target_link_libraries(core PUBLIC inst)

file(GLOB INST_SRC lib/instructions/*.c)
add_library(inst STATIC ${INST_SRC})
target_include_directories(inst PUBLIC include)

add_library(cartridge STATIC lib/cartridge.c)
target_include_directories(cartridge PUBLIC include)

file(GLOB MAPPER_SRC lib/mappers/*.c)
add_library(mapper STATIC lib/mapper.c ${MAPPER_SRC})
target_include_directories(mapper PUBLIC include)
target_link_libraries(mapper PUBLIC core)

add_library(emulator STATIC lib/emulator.c)
target_include_directories(emulator PUBLIC include)
target_link_libraries(emulator PUBLIC core mapper cartridge)

add_executable(nes_emulator main.c)
target_include_directories(nes_emulator PUBLIC include)
target_link_libraries(nes_emulator PRIVATE emulator)

# # Build test
# file(GLOB TEST_SRCS test/*.test.cpp)

# add_executable(test.nes_emulator ${TEST_SRCS})
# target_include_directories(test.nes_emulator
#     PUBLIC
#     include
#     /opt/external_libs/include
#     test
# )

# find_library(gtest_main gtest_main /opt/external_libs/lib)
# find_library(gtest gtest /opt/external_libs/lib)

# add_library(test_common STATIC ${PROJECT_SOURCE_DIR}/test/test.common.cpp)
# target_include_directories(test_common PUBLIC 
#     ${PROJECT_SOURCE_DIR}/test
#     ${PROJECT_SOURCE_DIR}/include    
# )
# target_link_libraries(test_common PUBLIC core inst)

# target_link_libraries(test.nes_emulator PRIVATE ${gtest_main} ${gtest} test_common core inst cartridge)
