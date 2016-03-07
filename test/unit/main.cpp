/*
 * Copyright (c) 2016, ARM Limited, All Rights Reserved
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "mbed-drivers/mbed.h"
#include "wrd-gpio-expander/GPIOExpander.h"

/*****************************************************************************/
/* GPIOExpander                                                                    */
/*****************************************************************************/

GPIOExpander gpio0(YOTTA_CFG_HARDWARE_WEARABLE_REFERENCE_DESIGN_GPIO_EXPANDER_GPIO0_I2C_SDA,
                   YOTTA_CFG_HARDWARE_WEARABLE_REFERENCE_DESIGN_GPIO_EXPANDER_GPIO0_I2C_SCL,
                   YOTTA_CFG_HARDWARE_WEARABLE_REFERENCE_DESIGN_GPIO_EXPANDER_GPIO0_I2C_ADDRESS,
                   YOTTA_CFG_HARDWARE_WEARABLE_REFERENCE_DESIGN_GPIO_EXPANDER_GPIO0_IRQ_PIN);

GPIOExpander gpio1(YOTTA_CFG_HARDWARE_WEARABLE_REFERENCE_DESIGN_GPIO_EXPANDER_GPIO1_I2C_SDA,
                   YOTTA_CFG_HARDWARE_WEARABLE_REFERENCE_DESIGN_GPIO_EXPANDER_GPIO1_I2C_SCL,
                   YOTTA_CFG_HARDWARE_WEARABLE_REFERENCE_DESIGN_GPIO_EXPANDER_GPIO1_I2C_ADDRESS,
                   YOTTA_CFG_HARDWARE_WEARABLE_REFERENCE_DESIGN_GPIO_EXPANDER_GPIO1_IRQ_PIN);

#define TEST_PIN (1 << 6)
#define IRQ_PIN  (1 << 0)

void irqHandler(uint16_t address, uint32_t pins, uint32_t values)
{
    printf("%02X: %lu %lu\r\n", address, pins, values);
}

void writeDone(void)
{

}

void directionDone(void)
{
    gpio1.bulkWrite(TEST_PIN, TEST_PIN, writeDone);
}

void irqDone()
{
    gpio1.bulkSetDirection(TEST_PIN, TEST_PIN, directionDone);
}

/*****************************************************************************/
/* Debug                                                                     */
/*****************************************************************************/

// enable buttons to initiate transfer
static InterruptIn button1(YOTTA_CFG_HARDWARE_WEARABLE_REFERENCE_DESIGN_BUTTON_FORWARD_GPIO_PIN);

void readDone(uint32_t values)
{
    printf("%lu\r\n", values);
}

void toggleDone()
{
    printf("toggle done\r\n");

    gpio0.bulkRead(readDone);
}

void button1Task()
{
    gpio1.bulkToggle(TEST_PIN, toggleDone);
}

void button1ISR()
{
    minar::Scheduler::postCallback(button1Task);
}

/*****************************************************************************/
/* App start                                                                 */
/*****************************************************************************/

void app_start(int, char *[])
{
    // setup buttons
    button1.fall(button1ISR);

    gpio0.setInterruptHandler(irqHandler);
    gpio1.setInterruptHandler(irqHandler);

    gpio0.bulkSetInterrupt(IRQ_PIN, IRQ_PIN, irqDone);
}
