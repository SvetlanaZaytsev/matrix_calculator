# CMake generated Testfile for 
# Source directory: /home/svetlanazay/laba3/matrix_calculator/tests
# Build directory: /home/svetlanazay/laba3/matrix_calculator/build/tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[matrix_tests]=] "/home/svetlanazay/laba3/matrix_calculator/build/tests/matrix_tests")
set_tests_properties([=[matrix_tests]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/svetlanazay/laba3/matrix_calculator/tests/CMakeLists.txt;14;add_test;/home/svetlanazay/laba3/matrix_calculator/tests/CMakeLists.txt;0;")
subdirs("../_deps/googletest-build")
