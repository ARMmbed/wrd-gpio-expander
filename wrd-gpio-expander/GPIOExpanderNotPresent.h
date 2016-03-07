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

#ifndef __WRD_GPIO_EXPANDER_NOT_PRESENT_H__
#define __WRD_GPIO_EXPANDER_NOT_PRESENT_H__

#include "mbed-drivers/mbed.h"

using namespace mbed::util;

class GPIOExpanderNotPresent
{
public:
    GPIOExpanderNotPresent(PinName sda, PinName scl, uint16_t address, PinName irq = NC)
    {
        (void) sda;
        (void) scl;
        (void) address;
        (void) irq;
    }

    /**
     * @brief Read pin values.
     * @details The result is passed as a parameter in the callback function.
     *
     * @param callback Function with pin values as parameter.
     * @return Boolean result. True means command was accepted, False means it was not.
     */
    bool bulkRead(FunctionPointer1<void, uint32_t> callback)
    {
        minar::Scheduler::postCallback(callback.bind(0));

        return true;
    }

    /**
     * @brief Set values for at most 32 pins.
     * @details Pins are labeled LSB. For I/O expanders with less than 32 pins
     *          the higher bits are ignored. I/O expanders with more than 32 pins
     *          are not supported.
     *
     * @param pins The pins affected by this call are set high in bitmap (LSB).
     * @param values Pin values. 0 means low, 1 means high.
     * @param callback Function to call when I/O expander is ready for next command.
     * @return Boolean result. True means command was accepted, False means it was not.
     */
    bool bulkWrite(uint32_t pins, uint32_t values, FunctionPointer0<void> callback)
    {
        (void) pins;
        (void) values;

        minar::Scheduler::postCallback(callback);

        return true;
    }

    /**
     * @brief Set directions for at most 32 pins.
     * @details Pins are labeled LSB. For I/O expanders with less than 32 pins
     *          the higher bits are ignored. I/O expanders with more than 32 pins
     *          are not supported.
     *
     * @param pins The pins affected by this call are set high in bitmap (LSB).
     * @param directions Pin directions. 0 means input, 1 means output.
     * @param callback Function to call when I/O expander is ready for next command.
     * @return Boolean result. True means command was accepted, False means it was not.
     */
    bool bulkSetDirection(uint32_t pins, uint32_t directions, FunctionPointer0<void> callback)
    {
        (void) pins;
        (void) directions;

        minar::Scheduler::postCallback(callback);

        return true;
    }

    /**
     * @brief Toggles output on given pins.
     * @details Only affects pins that are already set to output.
     *
     * @param pins The pins affected by this call are set high in bitmap (LSB).
     * @param callback Function to call when I/O expander is ready for next command.
     * @return Boolean result. True means command was accepted, False means it was not.
     */
    bool bulkToggle(uint32_t pins, FunctionPointer0<void> callback)
    {
        (void) pins;

        minar::Scheduler::postCallback(callback);

        return true;
    }

    /**
     * @brief Set pins to trigger interrupts.
     * @details When interrupts are triggered the callback handler contains values.
     *
     * @param pins Pins affected by this call.
     * @param values Interrupt mask. 0 interrupt is disabled, 1 interrupt is enabled.
     * @param callback Function is called when next command can be send.
     * @return Boolean result. True means command was accepted, False means it was not.
     */
    bool bulkSetInterrupt(uint32_t pins, uint32_t values, FunctionPointer0<void> callback)
    {
        (void) pins;
        (void) values;

        minar::Scheduler::postCallback(callback);

        return true;
    }

    /**
     * @brief Interrupt callback function.
     * @details The callback function has the I2C address, fired pins, and pin values
     *          as parameters. The address is passed so a single callback function can
     *          handle multiple expanders. The pins and values are useful for determining
     *          which pins have fired and what edge triggered the interrupt.
     *
     * @param uint16_t address
     * @param uint32_t pins
     * @param uint32_t values
     */
    typedef FunctionPointer3<void, uint16_t, uint32_t, uint32_t> IRQCallback_t;

    /**
     * @brief Callback function for when interrupts have fired.
     * @details The fired pins and values are passes as arguments in callback function.
     *
     * @param callback Parameters: address, fired pins, and pin values.
     */
    void setInterruptHandler(IRQCallback_t callback)
    {
        (void) callback;
    }

    /**
     * @brief Clear handler set with setInterruptHandler.
     */
    void clearInterruptHandler(void) { }
};

#endif // __WRD_GPIO_EXPANDER_NOT_PRESENT_H__
