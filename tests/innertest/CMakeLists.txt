set(INNER_TEST_NAME test_log_buffer)
set(INNER_TEST_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/test_log_buffer.cpp")

add_executable("${INNER_TEST_NAME}" "${INNER_TEST_SOURCE}")