/*
 * led.cpp
 *
 *  Created on: Oct 12, 2020
 *      Author: imcha
 */
#include "led.hpp"
LedState LedRgb::LEDRGBTABLE[][3] = {
    [static_cast<uint32_t>(LedColor::OFF)] = {LedState::OFF, LedState::OFF,
                                              LedState::OFF},
    [static_cast<uint32_t>(LedColor::RED)] = {LedState::ON, LedState::OFF,
                                              LedState::OFF},
    [static_cast<uint32_t>(LedColor::GREEN)] = {LedState::OFF, LedState::ON,
                                                LedState::OFF},
    [static_cast<uint32_t>(LedColor::BLUE)] = {LedState::OFF, LedState::OFF,
                                               LedState::ON},
    [static_cast<uint32_t>(LedColor::YELLOW)] = {LedState::ON, LedState::ON,
                                                 LedState::OFF},
    [static_cast<uint32_t>(LedColor::CYAN)] = {LedState::OFF, LedState::ON,
                                               LedState::ON},
    [static_cast<uint32_t>(LedColor::MAGENTA)] = {LedState::ON, LedState::OFF,
                                                  LedState::ON},
    [static_cast<uint32_t>(LedColor::WHITE)] = {LedState::ON, LedState::ON,
                                                LedState::ON},
};
