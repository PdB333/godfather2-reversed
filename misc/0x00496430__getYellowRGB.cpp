// FUNC_NAME: getYellowRGB
/* Function at 0x00496430
   Returns a constant yellow color value (0xFFFF00).
   Called repeatedly from FUN_006a0840 to set a default highlight color,
   likely for UI elements or character outlines.
   The return type is uint32_t representing an RGB color (0x00RRGGBB). */
#include <cstdint>

// Returns the yellow color code used for highlighting or team indicators.
uint32_t getYellowRGB(void)
{
    // Yellow in 0x00RRGGBB format: Red=0xFF, Green=0xFF, Blue=0x00
    return 0xFFFF00;
}