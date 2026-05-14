set(srcs "src/sscma_client_ops.c"
         "src/sscma_client_io.c"
         "src/sscma_client_io_i2c.c"
         "src/sscma_client_io_spi.c"
         "src/sscma_client_io_uart.c"
         "src/sscma_client_flasher.c"
         "src/sscma_client_flasher_we2_uart.c"
         "src/sscma_client_flasher_we2_spi.c"
         )
set(includes "include" "interface")
set(require "json" "mbedtls" "esp_timer")
set(priv_requires "driver")

idf_component_register(SRCS ${srcs}
                       INCLUDE_DIRS ${includes}
                       REQUIRES ${require}
                       PRIV_REQUIRES ${priv_requires}
                       )
