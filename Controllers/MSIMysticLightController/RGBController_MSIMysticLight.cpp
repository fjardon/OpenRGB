/*-----------------------------------------*\
|  RGBController_MSIMysticLight.cpp         |
|                                           |
|  Generic RGB Interface for OpenRGB        |
|  MSI Mystic Light USB Driver              |
|                                           |
|  T-bond 3/4/2020                          |
\*-----------------------------------------*/

#include "RGBController_MSIMysticLight.h"
#include <array>

#define NUM_LED_ZONES (sizeof(led_zones) / sizeof(ZoneDescription))

static const ZoneDescription led_zones[] =
{
    ZoneDescription{"JRGB1",            MSI_ZONE_J_RGB_1},
    ZoneDescription{"JRGB2",            MSI_ZONE_J_RGB_2},
    ZoneDescription{"JRAINBOW1",        MSI_ZONE_J_RAINBOW_1},
    ZoneDescription{"JRAINBOW2",        MSI_ZONE_J_RAINBOW_2},
    ZoneDescription{"JCORSAIR",         MSI_ZONE_J_CORSAIR},
    ZoneDescription{"Onboard LED 0",    MSI_ZONE_ON_BOARD_LED},
    ZoneDescription{"Onboard LED 1",    MSI_ZONE_ON_BOARD_LED_1},
    ZoneDescription{"Onboard LED 2",    MSI_ZONE_ON_BOARD_LED_2},
    ZoneDescription{"Onboard LED 3",    MSI_ZONE_ON_BOARD_LED_3},
    ZoneDescription{"Onboard LED 4",    MSI_ZONE_ON_BOARD_LED_4},
    ZoneDescription{"Onboard LED 5",    MSI_ZONE_ON_BOARD_LED_5},
    ZoneDescription{"Onboard LED 6",    MSI_ZONE_ON_BOARD_LED_6},
    ZoneDescription{"Onboard LED 7",    MSI_ZONE_ON_BOARD_LED_7},
    ZoneDescription{"Onboard LED 8",    MSI_ZONE_ON_BOARD_LED_8},
    ZoneDescription{"Onboard LED 9",    MSI_ZONE_ON_BOARD_LED_9},
    ZoneDescription{"Onboard LED 10",   MSI_ZONE_ON_BOARD_LED_10},
};

RGBController_MSIMysticLight::RGBController_MSIMysticLight(MSIMysticLightController* controller_ptr)
{
    controller = controller_ptr;

    name        = "MSI Mystic Light Controller";
    vendor      = "MSI";
    type        = DEVICE_TYPE_MOTHERBOARD;
    description = controller->GetDeviceName();
    version     = controller->GetFWVersion();
    location    = controller->GetDeviceLocation();
    serial      = controller->GetSerial();

    SetupModes();
    SetupZones();
    SetupColors();
}

RGBController_MSIMysticLight::~RGBController_MSIMysticLight()
{
    delete controller;
}

void RGBController_MSIMysticLight::SetupZones()
{
    /*---------------------------------------------------------*\
    | Set up zones                                              |
    \*---------------------------------------------------------*/
    for(std::size_t zone_idx = 0; zone_idx < 16; zone_idx++)
    {
        ZoneDescription zd = led_zones[zone_idx];
        zone new_zone;
        new_zone.name           = zd.name;
        new_zone.type           = ZONE_TYPE_LINEAR;

        new_zone.leds_min       = 1;
        new_zone.leds_max       = 1;
        new_zone.leds_count     = 1;
        new_zone.matrix_map     = NULL;
        zones.push_back(new_zone);

        /*---------------------------------------------------------*\
        | Set up LEDs                                               |
        \*---------------------------------------------------------*/
        for(std::size_t led_idx = 0; led_idx < new_zone.leds_count; led_idx++)
        {
            led new_led;
            
            new_led.name = new_zone.name + " LED ";
            if(new_zone.leds_count > 1)
            {
                new_led.name.append(std::to_string(led_idx + 1));
            }

            new_led.value = zone_idx;

            leds.push_back(new_led);
        }
    }
}

void RGBController_MSIMysticLight::ResizeZone(int zone, int new_size)
{
}

void RGBController_MSIMysticLight::SetCustomMode()
{
    active_mode = 0;
}

void RGBController_MSIMysticLight::DeviceUpdateLEDs()
{
    for(size_t zone_idx = 0; zone_idx < zones.size(); zone_idx++)
    {
        for(int led_idx = zones[zone_idx].leds_count - 1; led_idx >= 0; led_idx--)
        {
            UpdateLed(zone_idx, led_idx);
        }
    }
    controller->Update();
}

void RGBController_MSIMysticLight::UpdateZoneLEDs(int zone)
{
    for(int led_idx = zones[zone].leds_count - 1; led_idx >= 0; led_idx--)
    {
        UpdateLed(zone, led_idx);
    }
    controller->Update();
}

void RGBController_MSIMysticLight::UpdateSingleLED(int led)
{
    UpdateLed(leds[led].value, led);
    controller->Update();
}

void RGBController_MSIMysticLight::DeviceUpdateMode()
{
}

void RGBController_MSIMysticLight::SetupModes()
{
    constexpr unsigned int RANDOM_ONLY  = MODE_FLAG_HAS_BRIGHTNESS | MODE_FLAG_HAS_SPEED | MODE_FLAG_HAS_RANDOM_COLOR;
    constexpr unsigned int COMMON       = RANDOM_ONLY | MODE_FLAG_HAS_PER_LED_COLOR;

    SetupMode("Static",                     MSI_MODE_STATIC,                        MODE_FLAG_HAS_BRIGHTNESS | MODE_FLAG_HAS_PER_LED_COLOR);
    SetupMode("Off",                        MSI_MODE_DISABLE,                       0);
    SetupMode("Breathing",                  MSI_MODE_BREATHING,                     COMMON);
    SetupMode("Flashing",                   MSI_MODE_FLASHING,                      COMMON);
    SetupMode("Double flashing",            MSI_MODE_DOUBLE_FLASHING,               COMMON);
    SetupMode("Lightning",                  MSI_MODE_LIGHTNING,                     COMMON);
    // SetupMode("MSI Marquee",                MSI_MODE_MSI_MARQUEE,                   COMMON);
    // SetupMode("Meteor",                     MSI_MODE_METEOR,                        COMMON);
    // SetupMode("Water drop",                 MSI_MODE_WATER_DROP,                    COMMON);
    // SetupMode("MSI Rainbow",                MSI_MODE_MSI_RAINBOW,                   RANDOM_ONLY);
    // SetupMode("Pop",                        MSI_MODE_POP,                           COMMON);
    // SetupMode("Rap",                        MSI_MODE_RAP,                           COMMON);
    // SetupMode("Jazz",                       MSI_MODE_JAZZ,                          COMMON);
    // SetupMode("Play",                       MSI_MODE_PLAY,                          COMMON);
    // SetupMode("Movie",                      MSI_MODE_MOVIE,                         COMMON);
    // SetupMode("Color ring",                 MSI_MODE_COLOR_RING,                    COMMON);
    // SetupMode("Planetary",                  MSI_MODE_PLANETARY,                     COMMON);
    // SetupMode("Double meteor",              MSI_MODE_DOUBLE_METEOR,                 COMMON);
    // SetupMode("Energy",                     MSI_MODE_ENERGY,                        COMMON);
    // SetupMode("Blink",                      MSI_MODE_BLINK,                         COMMON);
    // SetupMode("Clock",                      MSI_MODE_CLOCK,                         COMMON);
    // SetupMode("Color pulse",                MSI_MODE_COLOR_PULSE,                   COMMON);
    // SetupMode("Color shift",                MSI_MODE_COLOR_SHIFT,                   COMMON);
    // SetupMode("Color wave",                 MSI_MODE_COLOR_WAVE,                    COMMON);
    // SetupMode("Marquee",                    MSI_MODE_MARQUEE,                       COMMON);
    // SetupMode("Rainbow",                    MSI_MODE_RAINBOW,                       COMMON);
    // SetupMode("Rainbow wave",               MSI_MODE_RAINBOW_WAVE,                  COMMON);
    // SetupMode("Visor",                      MSI_MODE_VISOR,                         COMMON);
    // SetupMode("JRainbow",                   MSI_MODE_JRAINBOW,                      COMMON);
    // SetupMode("Rainbow flashing",           MSI_MODE_RAINBOW_FLASHING,              COMMON);
    // SetupMode("Rainbow double flashing",    MSI_MODE_RAINBOW_DOUBLE_FLASHING,       COMMON);
    // SetupMode("Random",                     MSI_MODE_RANDOM,                        COMMON);
    // SetupMode("Fan control",                MSI_MODE_FAN_CONTROL,                   COMMON);
    // SetupMode("Off 2",                      MSI_MODE_DISABLE_2,                     COMMON);
    // SetupMode("Color ring flashing",        MSI_MODE_COLOR_RING_FLASHING,           COMMON);
    // SetupMode("Color ring double flashing", MSI_MODE_COLOR_RING_DOUBLE_FLASHING,    COMMON);
    // SetupMode("Stack",                      MSI_MODE_STACK,                         COMMON);
    // SetupMode("Corsair Que",                MSI_MODE_CORSAIR_QUE,                   COMMON);
    // SetupMode("Fire",                       MSI_MODE_FIRE,                          COMMON);
    // SetupMode("Lava",                       MSI_MODE_LAVA,                          COMMON);
}

void RGBController_MSIMysticLight::UpdateLed(int zone, int led)
{
    bool random         = modes[active_mode].color_mode == MODE_COLORS_RANDOM;
    unsigned char red   = RGBGetRValue(zones[zone].colors[led]);
    unsigned char grn   = RGBGetGValue(zones[zone].colors[led]);
    unsigned char blu   = RGBGetBValue(zones[zone].colors[led]);
    MSI_MODE mode       = (MSI_MODE)(modes[active_mode].value);
    MSI_SPEED speed     = (MSI_SPEED)(modes[active_mode].speed);
    MSI_ZONE zon        = ZoneFromPos(zone);
    
    controller->SetMode(zon, mode, speed, MSI_BRIGHTNESS_LEVEL_100, random);
    controller->SetZoneColor(zon, red, grn, blu, red, grn, blu);
}

MSI_ZONE RGBController_MSIMysticLight::ZoneFromPos(int zone)
{
    return led_zones[zone].value;
}

void RGBController_MSIMysticLight::SetupMode(const char *name, MSI_MODE mod, unsigned int flags)
{
    mode Mode;
    Mode.name       = name;
    Mode.value      = mod;
    Mode.flags      = flags;
    if(flags & MODE_FLAG_HAS_PER_LED_COLOR)
    {
        Mode.color_mode = MODE_COLORS_PER_LED;
    }
    else
    {
        Mode.color_mode = MODE_COLORS_RANDOM;
    }

    if(flags & MODE_FLAG_HAS_SPEED)
    {
        Mode.speed      = MSI_SPEED_MEDIUM;
        Mode.speed_max  = MSI_SPEED_HIGH;
        Mode.speed_min  = MSI_SPEED_LOW;
    }

    modes.push_back(Mode);
}
