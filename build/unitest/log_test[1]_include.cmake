if(EXISTS "/home/qrstu/yty_folder2/OBCompetition/build/unitest/log_test[1]_tests.cmake")
  include("/home/qrstu/yty_folder2/OBCompetition/build/unitest/log_test[1]_tests.cmake")
else()
  add_test(log_test_NOT_BUILT log_test_NOT_BUILT)
endif()
