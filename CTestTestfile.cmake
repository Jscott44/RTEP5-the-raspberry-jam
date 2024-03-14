# CMake generated Testfile for 
# Source directory: /home/user/repos/RTEP5-the-raspberry-jam
# Build directory: /home/user/repos/RTEP5-the-raspberry-jam
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(MyTest "/home/user/repos/RTEP5-the-raspberry-jam/test/Test")
set_tests_properties(MyTest PROPERTIES  _BACKTRACE_TRIPLES "/home/user/repos/RTEP5-the-raspberry-jam/CMakeLists.txt;19;add_test;/home/user/repos/RTEP5-the-raspberry-jam/CMakeLists.txt;0;")
subdirs("AlsaEffects")
subdirs("test")
