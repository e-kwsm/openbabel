include(FetchContent)

if(NOT OPENBABEL_USE_SYSTEM_INCHI)
  FetchContent_Declare(inchi
    URL https://github.com/IUPAC-InChI/InChI/archive/refs/tags/v1.07.5.tar.gz
    URL_HASH SHA256=9a8af985295c47bfaf424ad8386b1597da515589665ec71908dae1bd2b67ac96
    SOURCE_SUBDIR INCHI-1-SRC/INCHI_API/libinchi/src
  )
  FetchContent_MakeAvailable(inchi)
endif()
