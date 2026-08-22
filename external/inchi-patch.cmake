# InChI does not have install target
file(APPEND "${ORIG}" "
### OPENBABEL PATCH ###
install(TARGETS libinchi LIBRARY DESTINATION ${LIB_INSTALL_DIR})")
