if(ESP_PLATFORM)
   idf_component_register(SRC_DIRS src INCLUDE_DIRS src)
   return()
endif()

cmake_minimum_required(VERSION 3.28)
cmake_policy(SET CMP0092 NEW)
project(dlms_parser)
include(FetchContent)

## mbedtls
#FetchContent_Populate(
#  mded_tls
#  URL https://github.com/Mbed-TLS/mbedtls/releases/download/mbedtls-4.0.0/mbedtls-4.0.0.tar.bz2
#  URL_HASH SHA512=cc62c99a82f2f85ee4caa6488804648e81358e59f1498b6a97b034114e531bf44b05ae3d50db797ada939b6d4ac90bde29cd2363a36631af9e5fdfef57bfb267)
#set(ENABLE_PROGRAMS OFF CACHE INTERNAL "")
#set(ENABLE_TESTING OFF CACHE INTERNAL "")
#add_subdirectory(${mded_tls_SOURCE_DIR})
#
## bearssl
#FetchContent_Populate(
#  bearsll
#  URL https://bearssl.org/bearssl-0.6.tar.gz
#  URL_HASH SHA512=f9ed25683cfc6c4abe7f1203a2b82ed101ee4c9e0f9ab60755b6a09c8d1e8e4f64d413624e7bb9c4b0033f909a2e4568a1d916cc6ce4736222900691e1f8359a)
#file(GLOB_RECURSE bearssl_sources CONFIGURE_DEPENDS "${bearsll_SOURCE_DIR}/src/*.c")
#add_library(bearssl STATIC ${bearssl_sources})
#target_include_directories(bearssl SYSTEM PUBLIC "${bearsll_SOURCE_DIR}/inc" PRIVATE "${bearsll_SOURCE_DIR}/src")

# cmake_template for warnings and sanitizers
FetchContent_Populate(
  cmake_template
  URL https://github.com/cpp-best-practices/cmake_template/archive/0a32e3ff530534f04d7a73817d563bb26eea1b5a.zip
  URL_HASH SHA512=4cab8e5f75054b46c131447e0b9b4f36239eed7c8e5c3a01a09f1454126ea4fc24a5426a4662966cd925673f25383220a56644cab7551cb70aa40870e4577c0b)
include(${cmake_template_SOURCE_DIR}/cmake/CompilerWarnings.cmake)
include(${cmake_template_SOURCE_DIR}/cmake/Sanitizers.cmake)

# Core library
file(GLOB_RECURSE dlms_parser_src_files CONFIGURE_DEPENDS "src/*.h" "src/*.cpp")
add_library(dlms_parser ${dlms_parser_src_files})
target_include_directories(dlms_parser PUBLIC src)
target_compile_features(dlms_parser PUBLIC cxx_std_20)

# Enable testing and add tests subdirectory
enable_testing()
add_subdirectory(tests)