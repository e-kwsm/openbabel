# InChI does not have install target
file(APPEND "${ORIG}" "
### OPENBABEL PATCH ###
set(inchi_headers
  \"\${PROJECT_SOURCE_DIR}/../../../INCHI_BASE/src/bcf_s.h\"
  \"\${PROJECT_SOURCE_DIR}/../../../INCHI_BASE/src/inchi_api.h\"
  \"\${PROJECT_SOURCE_DIR}/../../../INCHI_BASE/src/ixa.h\"
)
install(FILES \${inchi_headers} DESTINATION include/inchi)
install(TARGETS libinchi LIBRARY DESTINATION ${LIB_INSTALL_DIR})")
