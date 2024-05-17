#ifndef CANFD2_H
#define CANFD2_H

#include <Arduino.h>
#include <SPI.h>
#include <TLE9255W.h>
extern "C" {
  #include <can2040.h>
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
    // Variables
    uint8_t tle9255w_tx;
    uint8_t tle9255w_rx;
    uint8_t spi_tx;
    uint8_t spi_rx;
    uint8_t spi_cs;
    uint8_t spi_sck;
    const SPISettings spi_settings = SPISettings(100000, MSBFIRST, SPI_MODE1);

    // Functions
    uint8_t canfd2_read_data(uint8_t reg_addr);
    void canfd2_write_data(uint8_t reg_addr, uint8_t write_data);
    uint8_t canfd2_get_mode();
};

#endif  // _CANFD2_H_