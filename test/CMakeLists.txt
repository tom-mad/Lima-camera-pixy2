add_executable(test_pixy2
    test_pixy2.cpp
)

target_link_libraries(test_pixy2 PUBLIC limacore pixy2)

add_test(
    NAME test_pixy2
    COMMAND test_pixy2
)
