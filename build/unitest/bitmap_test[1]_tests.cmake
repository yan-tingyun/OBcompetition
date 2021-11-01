add_test( test_bitmap.test_bitmap /home/qrstu/yty_folder2/OBCompetition/build/bin/bitmap_test [==[--gtest_filter=test_bitmap.test_bitmap]==] --gtest_also_run_disabled_tests)
set_tests_properties( test_bitmap.test_bitmap PROPERTIES WORKING_DIRECTORY /home/qrstu/yty_folder2/OBCompetition/build/unitest)
set( bitmap_test_TESTS test_bitmap.test_bitmap)
