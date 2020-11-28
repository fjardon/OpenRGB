/*-------------------------------------------------------------------*\
|  QMKRGBMatrixController.h                                           |
|                                                                     |
|  Driver for QMK keybaords using RGB Matrix                          |
|                                                                     |
|  Kasper         10th Octobber 2020                                  |
|                                                                     |
\*-------------------------------------------------------------------*/

#include <string>
#include <array>
#include <map>  
#include <hidapi/hidapi.h>
#include "RGBController.h"
#include "hsv.h"

#pragma once

enum CommandsId
{
    QMK_RGBMATRIX_SET_SINGLE_LED = 3,
    QMK_RGBMATRIX_SET_LEDS,

    QMK_RGBMATRIX_SET_MODE,
    QMK_RGBMATRIX_SET_MODE_AND_SPEED,
    QMK_RGBMATRIX_SET_COLOR_MODE_AND_SPEED,

    QMK_RGBMATRIX_GET_QMK_VERSION,
    QMK_RGBMATRIX_GET_DEVICE_NAME,
    QMK_RGBMATRIX_GET_ZONES_COUNT,
    QMK_RGBMATRIX_GET_ZONE_NAME,
    QMK_RGBMATRIX_GET_ZONE_TYPE,
    QMK_RGBMATRIX_GET_ZONE_SIZE,
    QMK_RGBMATRIX_GET_LED_NAME,
    QMK_RGBMATRIX_GET_LED_MATRIX_COLUMNS,
    QMK_RGBMATRIX_GET_LED_MATRIX_ROWS,
    QMK_RGBMATRIX_GET_LED_VALUE_IN_MATRIX,
    QMK_RGBMATRIX_GET_LED_COLOR,
    QMK_RGBMATRIX_GET_HSV
};

enum ModeCommands
{
    QMK_RGBMATRIX_MODE_HID_DIRECT = 1,
    QMK_RGBMATRIX_MODE_STATIC,
    QMK_RGBMATRIX_MODE_ALPHA_MOD,
    QMK_RGBMATRIX_MODE_STATIC_GRADIENT_LEFT_RIGHT,
    QMK_RGBMATRIX_MODE_STATIC_GRADIENT_UP_DOWN,
    QMK_RGBMATRIX_MODE_BREATHING,
    QMK_RGBMATRIX_MODE_BAND_SAT,
    QMK_RGBMATRIX_MODE_BAND_VAL,
    QMK_RGBMATRIX_MODE_BAND_PINWHEEL_SAT,
    QMK_RGBMATRIX_MODE_BAND_PINWHEEL_VAL,
    QMK_RGBMATRIX_MODE_BAND_SPIRAL_SAT,
    QMK_RGBMATRIX_MODE_BAND_SPIRAL_VAL,
    QMK_RGBMATRIX_MODE_CYCLE_ALL,
    QMK_RGBMATRIX_MODE_CYCLE_LEFT_RIGHT,
    QMK_RGBMATRIX_MODE_CYCLE_UP_DOWN,
    QMK_RGBMATRIX_MODE_CYCLE_OUT_IN,
    QMK_RGBMATRIX_MODE_CYCLE_OUT_IN_DUAL,
    QMK_RGBMATRIX_MODE_RAINBOW_MOVING_CHEVRON,
    QMK_RGBMATRIX_MODE_DUAL_BEACON,
    QMK_RGBMATRIX_MODE_CYCLE_PINWHEEL,
    QMK_RGBMATRIX_MODE_CYCLE_SPIRAL,
    QMK_RGBMATRIX_MODE_RAINBOW_BEACON,
    QMK_RGBMATRIX_MODE_RAINBOW_PINWHEELS,
    QMK_RGBMATRIX_MODE_RAINDROPS,
    QMK_RGBMATRIX_MODE_JELLYBEAN_RAINDROPS,
    QMK_RGBMATRIX_MODE_TYPING_HEATMAP,
    QMK_RGBMATRIX_MODE_DIGITAL_RAIN,
    QMK_RGBMATRIX_MODE_SOLID_REACTIVE,
    QMK_RGBMATRIX_MODE_SOLID_REACTIVE_SIMPLE,
    QMK_RGBMATRIX_MODE_SOLID_REACTIVE_WIDE,
    QMK_RGBMATRIX_MODE_SOLID_REACTIVE_MULTIWIDE,
    QMK_RGBMATRIX_MODE_SOLID_REACTIVE_CROSS,
    QMK_RGBMATRIX_MODE_SOLID_REACTIVE_MULTICROSS,
    QMK_RGBMATRIX_MODE_SOLID_REACTIVE_NEXUS,
    QMK_RGBMATRIX_MODE_SOLID_REACTIVE_MULTINEXUS,
    QMK_RGBMATRIX_MODE_SPLASH,
    QMK_RGBMATRIX_MODE_MULTISPLASH,
    QMK_RGBMATRIX_MODE_SOLID_SPLASH,
    QMK_RGBMATRIX_MODE_SOLID_MULTISPLASH,
};

enum SpeedCommands
{
    QMK_RGBMATRIX_SPEED_SLOWEST          = 0x00,  /* Slowest speed                   */
    QMK_RGBMATRIX_SPEED_NORMAL           = 0x7F,  /* Normal speed                    */
    QMK_RGBMATRIX_SPEED_FASTEST          = 0xFF,  /* Fastest speed                   */
};

class QMKRGBMatrixController
{
public:
    QMKRGBMatrixController(hid_device* dev_handle, const char* path);
    ~QMKRGBMatrixController();

    void SetSingleLED(unsigned int led, unsigned char red, unsigned char green, unsigned char blue);
    void SetLEDs(std::vector<RGBColor> colors, unsigned int num_colors);

    void SetMode(unsigned char mode);
    void SetModeAndSpeed(unsigned char mode, unsigned char speed);
    void SetColorModeAndSpeed(hsv_t hsv_color, unsigned char mode, unsigned char speed);

    std::string GetLocation();

    std::string GetQMKVersion();
    std::string GetDeviceName();
    unsigned int GetZonesCount();
    std::string GetZoneName(int zone);
    unsigned int GetZoneType(int zone);
    unsigned int GetZoneSize(int zone);
    std::string GetLEDName(int led_column, int led_row);
    unsigned int GetLEDMatirxRows();
    unsigned int GetLEDMatirxColumns();
    unsigned int GetLEDValueInMatrix(int column, int row);
    RGBColor GetLEDColor(unsigned int led);
    unsigned int GetHSV();
    
protected:
    hid_device* dev;
private:
    std::string location;

    std::map<uint8_t, std::string> QMKKeycodeToKeyName
    {
        { 0, "" },
        { 1, "Menu" },
        { 2, "" },
        { 3, "" },
        { 4, "A" },
        { 5, "B" },
        { 6, "C" },
        { 7, "D" },
        { 8, "E" },
        { 9, "F" },
        { 10, "G" },
        { 11, "H" },
        { 12, "I" },
        { 13, "J" },
        { 14, "K" },
        { 15, "L" },
        { 16, "M" },
        { 17, "N" },
        { 18, "O" },
        { 19, "P" },
        { 20, "Q" },
        { 21, "R" },
        { 22, "S" },
        { 23, "T" },
        { 24, "U" },
        { 25, "V" },
        { 26, "W" },
        { 27, "X" },
        { 28, "Y" },
        { 29, "Z" },
        { 30, "1" },
        { 31, "2" },
        { 32, "3" },
        { 33, "4" },
        { 34, "5" },
        { 35, "6" },
        { 36, "7" },
        { 37, "8" },
        { 38, "9" },
        { 39, "0" },
        { 40, "Enter" },
        { 41, "Escape" },
        { 42, "Backspace" },
        { 43, "Tab" },
        { 44, "Space" },
        { 45, "-" },
        { 46, "=" },
        { 47, "[" },
        { 48, "]" },
        { 49, "/" },
        { 50, "" },
        { 51, ";" },
        { 52, "'" },
        { 53, "`" },
        { 54, "," },
        { 55, "." },
        { 56, "/" },
        { 57, "Caps Lock" },
        { 58, "F1" },
        { 59, "F2" },
        { 60, "F3" },
        { 61, "F4" },
        { 62, "F5" },
        { 63, "F6" },
        { 64, "F7" },
        { 65, "F8" },
        { 66, "F9" },
        { 67, "F10" },
        { 68, "F11" },
        { 69, "F12" },
        { 70, "Print Screen" },
        { 71, "Scroll Lock" },
        { 72, "Pause/Break" },
        { 73, "Insert" },
        { 74, "Home" },
        { 75, "Page Up" },
        { 76, "Delete" },
        { 77, "End" },
        { 78, "Page Down" },
        { 79, "Right Arrow" },
        { 80, "Left Arrow" },
        { 81, "Down Arrow" },
        { 82, "Up Arrow" },
        { 83, "Num Lock" },
        { 84, "Number Pad /" },
        { 85, "Number Pad *" },
        { 86, "Number Pad -" },
        { 87, "Number Pad +" },
        { 88, "Number Pad Enter" },
        { 89, "Number Pad 1" },
        { 90, "Number Pad 2" },
        { 91, "Number Pad 3" },
        { 92, "Number Pad 4" },
        { 93, "Number Pad 5" },
        { 94, "Number Pad 6" },
        { 95, "Number Pad 7" },
        { 96, "Number Pad 8" },
        { 97, "Number Pad 9" },
        { 98, "Number Pad 0" },
        { 99, "Number Pad ." },
        { 100, "" },
        { 101, "" },
        { 102, "" },
        { 103, "" },
        { 104, "" },
        { 105, "" },
        { 106, "" },
        { 107, "" },
        { 108, "" },
        { 109, "" },
        { 110, "" },
        { 111, "" },
        { 112, "" },
        { 113, "" },
        { 114, "" },
        { 115, "" },
        { 116, "" },
        { 117, "" },
        { 118, "" },
        { 119, "" },
        { 120, "" },
        { 121, "" },
        { 122, "" },
        { 123, "" },
        { 124, "" },
        { 125, "" },
        { 126, "" },
        { 127, "" },
        { 128, "" },
        { 129, "" },
        { 130, "" },
        { 131, "" },
        { 132, "" },
        { 133, "" },
        { 134, "" },
        { 135, "" },
        { 136, "" },
        { 137, "" },
        { 138, "" },
        { 139, "" },
        { 140, "" },
        { 141, "" },
        { 142, "" },
        { 143, "" },
        { 144, "" },
        { 145, "" },
        { 146, "" },
        { 147, "" },
        { 148, "" },
        { 149, "" },
        { 150, "" },
        { 151, "" },
        { 152, "" },
        { 153, "" },
        { 154, "" },
        { 155, "" },
        { 156, "" },
        { 157, "" },
        { 158, "" },
        { 159, "" },
        { 160, "" },
        { 161, "" },
        { 162, "" },
        { 163, "" },
        { 164, "" },
        { 224, "Left Control" },
        { 225, "Left Shift" },
        { 226, "Left Alt" },
        { 227, "Left Windows" },
        { 228, "Right Control" },
        { 229, "Right Shift" },
        { 230, "Right Alt" },
        { 231, "Right Windows" },
    };
};
