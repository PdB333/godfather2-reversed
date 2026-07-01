// FUNC_NAME: InputSettings::setMouseInvert
// Address: 0x0090ce50
// Role: Sets the mouse invert flag in the settings object and persists to config.

// Global variable storing the current invert mouse state (0 or 1)
extern char g_mouseInvertEnabled; // DAT_0112a7a4

// Forward declaration of config write function
void setConfigString(const char* key, int value); // FUN_0069bf00

void __thiscall InputSettings::setMouseInvert(int thisPtr, int enable)
{
    g_mouseInvertEnabled = (char)enable;
    if (g_mouseInvertEnabled != 0) {
        // Set bit 3 (0x8) in flags at offset 0x14
        *(uint*)(thisPtr + 0x14) |= 8;
        setConfigString("Mouse.Invert", enable);
    } else {
        // Clear bit 3 (0x8) in flags at offset 0x14
        *(uint*)(thisPtr + 0x14) &= 0xFFFFFFF7;
        setConfigString("Mouse.Invert", enable);
    }
}