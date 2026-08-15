#!/usr/bin/env cmake -P

# InChI does not have install target
file(APPEND "${ORIG}" "
# add_custom_command(TARGET libinchi POST_BUILD
#   COMMAND \"\${CMAKE_COMMAND}\" -E copy \$<TARGET_FILE:libinchi> \"${PROJECT_BINARY_DIR}/${LIB_INSTALL_DIR}\"
# )
install(TARGETS libinchi LIBRARY DESTINATION ${LIB_INSTALL_DIR})")
