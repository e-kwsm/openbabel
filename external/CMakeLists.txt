include(ExternalProject)
ExternalProject_Add(inchi
  URL https://github.com/IUPAC-InChI/InChI/archive/refs/tags/v1.07.5.tar.gz
  URL_HASH SHA256=9a8af985295c47bfaf424ad8386b1597da515589665ec71908dae1bd2b67ac96
  SOURCE_SUBDIR INCHI-1-SRC/INCHI_API/libinchi/src
  PATCH_COMMAND "${CMAKE_COMMAND}"
    "-DPROJECT_BINARY_DIR=${PROJECT_BINARY_DIR}"
    "-DORIG=INCHI-1-SRC/INCHI_API/libinchi/src/CMakeLists.txt"
    "-DLIB_INSTALL_DIR=${LIB_INSTALL_DIR}"
    -P "${CMAKE_CURRENT_SOURCE_DIR}/inchi-patch.cmake"
  CMAKE_CACHE_ARGS
    "-DCMAKE_INSTALL_PREFIX:PATH=${PROJECT_BINARY_DIR}"
)
