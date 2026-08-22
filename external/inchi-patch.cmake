#!/usr/bin/env cmake -P

# InChI does not have install target
file(APPEND "${ORIG}" "
### OPENBABEL PATCH ###
install(FILES \"\${PROJECT_SOURCE_DIR}/../../../INCHI_BASE/src/inchi_api.h\" DESTINATION include)
install(TARGETS libinchi LIBRARY DESTINATION ${LIB_INSTALL_DIR})")
