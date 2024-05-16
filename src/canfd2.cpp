#include "canfd2.h"

CANFD2::CANFD2(uint8_t tx, uint8_t rx, uint8_t spi_tx, uint8_t spi_rx, uint8_t spi_cs, uint8_t spi_sck) {
    this->spi_tx = spi_tx;
    this->spi_rx = spi_rx;
    this->spi_cs = spi_cs;
    this->spi_sck = spi_sck;
    this->tle9255w_tx = tx;
    this->tle9255w_rx = rx;
}

CANFD2::~CANFD2() {
    Serial1.end();
    SPI.end();
}


void CANFD2::begin(uint32_t baudrate, can2040_rx_cb callback) {
    Serial1.setTX(tle9255w_tx);
    Serial1.setRX(tle9255w_rx);
    Serial1.begin(9600);

    SPI.setTX(spi_tx); 
    SPI.setRX(spi_rx);
    SPI.setSCK(spi_sck);
    SPI.setCS(spi_cs);
    pinMode(spi_cs, OUTPUT);
    digitalWrite(cs, HIGH);
    this->cs = spi_cs;
    SPI.begin(false); // true means handle CS automatically

    uint32_t this_baudrate = baudrate;
    canfd2_write_data(CANFD2_REG_MODE_CTRL, CANFD2_CTRL_MODE_NORMAL_OP);
    canfd2_write_data(CANFD2_REG_SWK_CTRL_1, CANFD2_SWK_CTRL_1_CFG_VAL);
    switch(baudrate) {
        case 125000: {
            canfd2_write_data(CANFD2_REG_SWK_CTRL_2, CANFD2_SWK_CTRL_2_SWK_EN | CANFD2_SWK_CTRL_2_BR_125K);
            break;
        }
        case 250000: {
            canfd2_write_data(CANFD2_REG_SWK_CTRL_2, CANFD2_SWK_CTRL_2_SWK_EN | CANFD2_SWK_CTRL_2_BR_250K);
            break;
        }
        case 500000: {
            canfd2_write_data(CANFD2_REG_SWK_CTRL_2, CANFD2_SWK_CTRL_2_SWK_EN | CANFD2_SWK_CTRL_2_BR_500K);
            break;
        }
        case 1000000: {
            canfd2_write_data(CANFD2_REG_SWK_CTRL_2, CANFD2_SWK_CTRL_2_SWK_EN | CANFD2_SWK_CTRL_2_BR_1M);
            break;
        }
        default: {
            Serial.println("Invalid baudrate, setting to 500000");
            this_baudrate = 500000;
            canfd2_write_data(CANFD2_REG_SWK_CTRL_2, CANFD2_SWK_CTRL_2_SWK_EN | CANFD2_SWK_CTRL_2_BR_500K);
            break;
        }
    }

    // Setup canbus
    can2040_setup(&cbus, 0);
    can2040_callback_config(&cbus, callback);

    // Enable irqs
    irq_set_exclusive_handler(PIO0_IRQ_0_IRQn, PIOx_IRQHandler);
    NVIC_SetPriority(PIO0_IRQ_0_IRQn, 1);
    NVIC_EnableIRQ(PIO0_IRQ_0_IRQn);

    // Start canbus
    can2040_start(&cbus, rp2040.f_cpu(), this_baudrate, tle9255w_rx, tle9255w_tx);

    canfd2_write_data(CANFD2_REG_SWK_CTRL_2, CANFD2_SWK_CTRL_2_SWK_EN | CANFD2_SWK_CTRL_2_BR_500K );
    if(CANFD2_OP_MODE_NORMAL == canfd2_get_mode()) {
        if(Serial){
            Serial.println("CANFD Click 2 initialized");
        }
    } else {
        while(true) {
            if(Serial){
                Serial.println("CANFD Click 2 failed to initialize");
            }
        }
    }
}

uint8_t CANFD2::send_frame(struct can2040_msg *msg) {
    return can2040_transmit(&cbus, msg);
}

void CANFD2::canfd2_generic_write (uint8_t *data_buf, uint16_t len ) {
    Serial1.write( data_buf, len );
}

int32_t CANFD2::canfd2_generic_read (uint8_t *data_buf, uint16_t max_len ) {
    return Serial1.readBytes( data_buf, max_len );
}

void CANFD2::canfd2_generic_transfer (uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len ) {
    digitalWrite(cs, LOW);
    delay(1);
    SPI.beginTransaction(spi_settings);
    SPI.transfer(wr_buf, nullptr, wr_len);
    SPI.transfer(nullptr, rd_buf, rd_len);
    SPI.endTransaction();
    delay(1);
    digitalWrite(cs, HIGH);
}

uint8_t  CANFD2::canfd2_read_data (uint8_t reg_addr) {
    uint8_t write_tmp;
    uint8_t read_data;

    write_tmp = reg_addr & CANFD2_READ_CMD_MASK;

    digitalWrite(cs, LOW);
    delay(1);
    SPI.beginTransaction(spi_settings);
    SPI.transfer(&write_tmp, nullptr, 1);
    SPI.transfer(nullptr, &read_data, 1);
    SPI.endTransaction();
    delay(1);
    digitalWrite(cs, HIGH);

    return read_data;
}

void CANFD2::canfd2_write_data (uint8_t reg_addr, uint8_t write_data ) {
    uint8_t write_tmp;

    write_tmp = reg_addr | CANFD2_WRITE_CMD;

    digitalWrite(cs, LOW);
    delay(1);
    SPI.beginTransaction(spi_settings);
    SPI.transfer(&write_tmp, nullptr, 1);
    SPI.transfer(&write_data, nullptr, 1);
    SPI.endTransaction();
    delay(1);
    digitalWrite(cs, HIGH);

}

void CANFD2::canfd2_set_mode (uint8_t op_mode ) {
    switch ( op_mode ) {
        case CANFD2_OP_MODE_SLEEP: {
            canfd2_write_data(CANFD2_REG_MODE_CTRL, CANFD2_CTRL_MODE_SLEEP );
            break;
        }
        case CANFD2_OP_MODE_STANDBY: {
            canfd2_write_data(CANFD2_REG_MODE_CTRL, CANFD2_CTRL_MODE_STANDBY );
            break;
        }
        case CANFD2_OP_MODE_RECEIVE_ONLY: {
            canfd2_write_data(CANFD2_REG_MODE_CTRL, CANFD2_CTRL_MODE_REC_ONLY );
            break;
        }
        case CANFD2_OP_MODE_NORMAL: {
            canfd2_write_data(CANFD2_REG_MODE_CTRL, CANFD2_CTRL_MODE_NORMAL_OP );
            break;
        }
        default: {
            canfd2_write_data(CANFD2_REG_MODE_CTRL, CANFD2_CTRL_MODE_NORMAL_OP );
            break;
        }
    }
    
    canfd2_write_data(CANFD2_REG_SWK_CTRL_1, CANFD2_SWK_CTRL_1_CFG_VAL );
    canfd2_write_data(CANFD2_REG_SWK_CTRL_2, CANFD2_SWK_CTRL_2_SWK_EN |
                                                   CANFD2_SWK_CTRL_2_BR_1M );
}

uint8_t CANFD2::canfd2_get_mode () {
    uint8_t rx_buf;
    uint8_t o_mode;
    
    rx_buf = canfd2_read_data(CANFD2_REG_MODE_CTRL) & 0x0F;
    
    switch ( rx_buf ) {
        case CANFD2_CTRL_MODE_SLEEP: {
            o_mode = CANFD2_OP_MODE_SLEEP;
            break;
        }
        case CANFD2_CTRL_MODE_STANDBY: {
            o_mode = CANFD2_OP_MODE_STANDBY;
            break;
        }
        case CANFD2_CTRL_MODE_REC_ONLY: {
            o_mode = CANFD2_OP_MODE_RECEIVE_ONLY;
            break;
        }
        case CANFD2_CTRL_MODE_NORMAL_OP: {
            o_mode = CANFD2_OP_MODE_NORMAL;
            break;
        }
        default: {
            o_mode = CANFD2_OP_MODE_UNKNOWN;
            break;
        }
    }
    
    return o_mode;
}
