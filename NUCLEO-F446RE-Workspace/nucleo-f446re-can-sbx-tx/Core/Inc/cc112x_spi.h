/*
 * cc112x_spi.h
 *
 *  Created on: May 16, 2021
 *      Author: seant
 */

#ifndef INC_CC112X_SPI_H_
#define INC_CC112X_SPI_H_

#include <stdint.h>
#include "stm32f4xx_hal.h"
#include "cc_definitions.h"
#include "cc_commands.h"
#include "cw.h"

#define CC_EXT_ADD 0x2F00

/*****************************************************************************
 *********************  TX related functions  ********************************
 ****************************************************************************/

uint8_t
cc_tx_rd_reg(uint16_t addr, uint8_t *data);

uint8_t
cc_tx_wr_reg(uint16_t addr, uint8_t data);

HAL_StatusTypeDef
cc_tx_spi_write_fifo(const uint8_t *data, uint8_t *spi_rx_data, size_t len);

int32_t
cc_tx_data_continuous(const uint8_t *data, size_t size, uint8_t *rec_data, size_t timeout_ms);

int32_t
cc_tx_cw(const cw_pulse_t *in, size_t len);

uint8_t
cc_tx_cmd(uint8_t CMDStrobe);

void
set_tx_fsk_regs();

/*****************************************************************************
 *********************  TX related functions  ********************************
 ****************************************************************************/

HAL_StatusTypeDef
cc_rx_spi_read_fifo(uint8_t *out, size_t len);

HAL_StatusTypeDef
cc_rx_spi_write_fifo(uint8_t *data, uint8_t *spi_rx_data, size_t len);

uint8_t
cc_rx_rd_reg(uint16_t addr, uint8_t *data);

uint8_t
cc_rx_wr_reg(uint16_t addr, uint8_t data);

int32_t
cc_rx_data_packet(uint8_t *out, size_t len, size_t timeout_ms);

uint8_t
cc_rx_cmd(uint8_t CMDStrobe);

uint8_t
cc_rx_check_fifo_status();


#endif /* INC_CC112X_SPI_H_ */
