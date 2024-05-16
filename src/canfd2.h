#ifndef CANFD2_H
#define CANFD2_H

#include <Arduino.h>
#include <SPI.h>
#include "stdint.h"
#include "TLE9255W.h"
extern "C" {
  #include "can2040.h"
}

static struct can2040 cbus;

static void PIOx_IRQHandler(void) {
    can2040_pio_irq_handler(&cbus);
}

class CANFD2 {
public:
    CANFD2(uint8_t tx, uint8_t rx, uint8_t spi_tx, uint8_t spi_rx, uint8_t spi_cs, uint8_t spi_sck);
    ~CANFD2();
    void begin(uint32_t baudrate, can2040_rx_cb callback);
    uint8_t send_frame(struct can2040_msg *msg);
private:
    // PIO stuff
    uint8_t tle9255w_tx;
    uint8_t tle9255w_rx;
    uint8_t spi_tx;
    uint8_t spi_rx;
    uint8_t spi_cs;
    uint8_t spi_sck;
    const SPISettings spi_settings = SPISettings(100000, MSBFIRST, SPI_MODE1);
    uint8_t cs;
    void canfd2_generic_write(uint8_t *data_buf, uint16_t len );
    int32_t canfd2_generic_read(uint8_t *data_buf, uint16_t max_len );
    void canfd2_generic_transfer(uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len );
    uint8_t canfd2_read_data(uint8_t reg_addr );
    void canfd2_write_data(uint8_t reg_addr, uint8_t write_data );
    void canfd2_set_mode(uint8_t op_mode );
    uint8_t canfd2_get_mode();
};

#endif  // _CANFD2_H_