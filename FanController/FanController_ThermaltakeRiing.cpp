/*-----------------------------------------*\
|  FanController_ThermaltakeRiing.cpp       |
|                                           |
|  Generic Fan Interface for Thermaltake    |
|  Riing controller                         |
|                                           |
|  Adam Honse (CalcProgrammer1) 6/5/2020    |
\*-----------------------------------------*/

#include "FanController_ThermaltakeRiing.h"

FanController_ThermaltakeRiing::FanController_ThermaltakeRiing(ThermaltakeRiingController* riing_ptr)
{
    riing = riing_ptr;

    name        = "Thermaltake Riing";
    description = "Thermaltake Riing Device";

    for(std::size_t fan_index = 0; fan_index < THERMALTAKE_NUM_CHANNELS; fan_index++)
    {
        fan new_fan;

        new_fan.name        = "Thermaltake Riing Fan ";
        new_fan.name.append(std::to_string(fan_index + 1));
        new_fan.speed_min   = THERMALTAKE_FAN_SPEED_MIN;
        new_fan.speed_max   = THERMALTAKE_FAN_SPEED_MAX;
        new_fan.speed_cmd   = 50;

        fans.push_back(new_fan);
    }

    UpdateControl();
}

void FanController_ThermaltakeRiing::UpdateControl()
{
    for(std::size_t fan_index = 0; fan_index < fans.size(); fan_index++)
    {
        riing->SendFan(fan_index + 1, THERMALTAKE_FAN_MODE_FIXED, fans[fan_index].speed_cmd);
    }
}

void FanController_ThermaltakeRiing::UpdateReading()
{

}