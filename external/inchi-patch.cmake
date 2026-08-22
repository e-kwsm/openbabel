#!/usr/bin/env cmake -P

# InChI does not have install target
file(APPEND "${ORIG}" "
### OPENBABEL PATCH ###
file(GLOB inchi_headers \"\${PROJECT_SOURCE_DIR}/../../../INCHI_BASE/src/*.h\")
install(FILES
# \"\${PROJECT_SOURCE_DIR}/../../../INCHI_BASE/src/inchi_api.h\"
# \"\${PROJECT_SOURCE_DIR}/../../../INCHI_BASE/src/bcf_s.h\"
\${inchi_headers}
DESTINATION include/inchi)
install(TARGETS libinchi LIBRARY DESTINATION ${LIB_INSTALL_DIR})")
