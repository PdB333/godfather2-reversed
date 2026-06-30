// FUNC_NAME: setMarkerColor
int __cdecl setMarkerColor(uint32_t* outBuffer, uint32_t unusedParam, uint32_t markerId) {
    // outBuffer[0] appears to be a 32-bit color with flags in the high byte.
    // outBuffer[1] is a secondary attribute (only low byte used here).
    // markerId is validated by a helper function at 0x00496710.

    if (FUN_00496710(markerId)) {
        uint32_t color = outBuffer[0];
        uint8_t attrByte = (uint8_t)outBuffer[1];

        // If the current low byte of color is not 1 or 3, reset to a default yellow (0x00FFFF00)
        // and clear the attribute byte.
        if ((color & 0xFF) != 1 && (color & 0xFF) != 3) {
            color = 0x00FFFF00;
            attrByte = 0;
        }

        // Force the top byte (alpha or flags) to 3.
        color = (color & 0x00FFFFFF) | (3 << 24);

        // Note: The original decompilation shows a confusing CONCAT22 operation on the second field.
        // It likely set outBuffer[1] to a combination of attrByte and some other constant bytes.
        // Here we assume it merely retains the low byte (attrByte) and zeros the rest,
        // which matches the typical pattern for a simple attribute field.
        outBuffer[0] = color;
        outBuffer[1] = attrByte & 0xFF;  // keep only the low byte, clear upper bytes

        return 1;
    }
    return 0;
}