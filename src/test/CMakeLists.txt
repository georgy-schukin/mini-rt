add_executable(minirt_test minirt_test.cpp)

target_link_libraries(minirt_test PUBLIC minirt)

#install(TARGETS minirt_test DESTINATION bin/minirt)
