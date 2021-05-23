/*
 * cc_tx_init.h
 *
 *  Created on: May 16, 2021
 *      Author: seant
 */

#ifndef INC_CC_TX_INIT_H_
#define INC_CC_TX_INIT_H_

#include "cc_definitions.h"
#include "cc112x_spi.h"
#include <stdint.h>

void
tx_manualCalibration ();
void
tx_registerConfig ();
void
tx_cw_registerConfig ();


#endif /* INC_CC_TX_INIT_H_ */
