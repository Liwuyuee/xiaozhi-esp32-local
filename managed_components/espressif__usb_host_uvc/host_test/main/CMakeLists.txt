idf_component_register(SRC_DIRS . parsing streaming opening
                        REQUIRES cmock
                        INCLUDE_DIRS . parsing streaming opening
                        PRIV_INCLUDE_DIRS "../../private_include"
                        WHOLE_ARCHIVE)

# The following line would be needed to provide the 'main' function if this test used mocked FreeRTOS.
# As this test uses the real FreeRTOS implementation, we don't need Catch2 to provide 'main'.
# target_link_libraries(${COMPONENT_LIB} PRIVATE Catch2WithMain)
