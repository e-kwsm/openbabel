#!/usr/bin/env cmake -P

# InChI does not have install target
file(APPEND "${ORIG}" "
### OPENBABEL PATCH ###
install(FILES \"\${PROJECT_SOURCE_DIR}/../../../INCHI_BASE/src/inchi_api.h\" DESTINATION include)
# target_sources(libinchi PUBLIC TYPE HEADERS FILES HEADERS INCHI-1-SRC/INCHI_BASE/src/inchi_api.h)
install(TARGETS libinchi LIBRARY DESTINATION ${LIB_INSTALL_DIR})")
