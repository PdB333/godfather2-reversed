// FUNC_NAME: HUDText::setValue
// Address: 0x00603d30
// This function appears to update a HUD text element with a formatted numeric value.
// It checks a flag at offset +0x4c (bit 1) for initialization, and if not initialized,
// performs three reset calls and sets the flag. Then it formats a value using a global format string
// and calls an update method to display the text.

void __thiscall HUDText::setValue(int thisPtr, char* bufferOut, float value, bool showImmediate)
{
    // Check if initialization has been done (bit 1 of flags at +0x4c)
    if (!(*(uint*)(thisPtr + 0x4c) & 0x2))
    {
        // Triple reset or animation reset
        HUDText::reset(thisPtr);
        HUDText::reset(thisPtr);
        HUDText::reset(thisPtr);
        // Mark as initialized
        *(uint*)(thisPtr + 0x4c) |= 0x2;
    }

    // Play a UI sound or set a blending mode (ID 0xf)
    UI::setSoundOrBlend(0xf);

    // Format the value into the buffer using a global format string (e.g., "%.2f")
    HUDText::formatValue(value, &DAT_00e3266c, bufferOut);

    // Update the display with the new text and show/hide flag
    HUDText::updateDisplay(thisPtr, showImmediate);
}