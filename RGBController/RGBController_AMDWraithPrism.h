/*-----------------------------------------*\
|  RGBController_AMDWraithPrism.h           |
|                                           |
|  Generic RGB Interface for AMD Wraith     |
|  Prism                                    |
|                                           |
|  Adam Honse (CalcProgrammer1) 12/25/2019  |
\*-----------------------------------------*/

#pragma once
#include "RGBController.h"
#include "AMDWraithPrismController.h"

class RGBController_AMDWraithPrism : public RGBController
{
public:
    RGBController_AMDWraithPrism(AMDWraithPrismController* wraith_ptr);
    ~RGBController_AMDWraithPrism();
    void        UpdateLEDs();
    void        UpdateZoneLEDs(int zone);
    void        UpdateSingleLED(int led);

    void        SetCustomMode();
    void        UpdateMode();

private:
    AMDWraithPrismController*   wraith;
};
