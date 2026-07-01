// FUNC_NAME: setupDefaultControllerMappings
#include <cstdint>

// Forward declaration of the mapping function (defined elsewhere)
void setControllerButtonMapping(int slot, uint32_t flags);

// Global config byte (defined elsewhere)
extern uint8_t g_controllerConfigFlags;

void setupDefaultControllerMappings(void)
{
    uint32_t baseFlags = 0x100;

    if ((g_controllerConfigFlags & 8) != 0) {
        baseFlags = 0x200;
    }

    // Map controller slots 0-7 to specific XInput button masks.
    // The base flags (0x100 or 0x200) likely indicate primary vs. secondary function groups.
    setControllerButtonMapping(0, baseFlags | 1);   // Slot 0 -> A button
    setControllerButtonMapping(1, baseFlags | 1);   // Slot 1 -> A button (duplicate assignment)
    setControllerButtonMapping(2, baseFlags | 2);   // Slot 2 -> B button
    setControllerButtonMapping(3, baseFlags | 4);   // Slot 3 -> X button
    setControllerButtonMapping(4, baseFlags | 8);   // Slot 4 -> Y button
    setControllerButtonMapping(5, baseFlags | 0x10); // Slot 5 -> LB button
    setControllerButtonMapping(6, baseFlags | 4);   // Slot 6 -> X button (duplicate assignment)
    setControllerButtonMapping(7, baseFlags | 0x20); // Slot 7 -> RB button
}