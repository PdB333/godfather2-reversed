// FUNC_NAME: UIRenderer::renderTextOverlay
void UIRenderer::renderTextOverlay(void)
{
    // +0x2c: TLS pointer to check main thread
    uint* tlsPtr = *(uint**)(*(uint*)(__readfsdword(0x2c)) + 0x34);
    if (tlsPtr == 0) {
        // Initialize vtable for global singleton
        int* vtablePtr = (int*)(DAT_01206880 + 0x14);
        *(void**)(DAT_01206880 + 0x14) = &PTR_LAB_0110b134;
        *vtablePtr = *vtablePtr + 4;
        return;
    }

    uint colorValues[2] = { DAT_012052f0, DAT_012052f4 }; // Two color constants (e.g., white, yellow)
    uint lineIndex = 0;
    do {
        uint currentColor = colorValues[lineIndex];
        uint digitIndex = 0;
        do {
            // Save old glyph lookup state
            uint oldGlyphID1 = DAT_011f38f0;
            uint oldGlyphID2 = DAT_011f38f4;

            // Set current glyph lookup parameters
            DAT_011f38f0 = currentColor;
            DAT_011f38f4 = digitIndex;

            // Restore? Actually called with previous state
            FUN_00609340(0, oldGlyphID1, oldGlyphID2);
            FUN_0060db60(0, 0, 0, 0x3f800000, 0x3f800000); // Set scale to (1.0, 1.0)

            // Draw call via virtual function (offset 0xac in vtable)
            (**(code**)(*DAT_01205750 + 0xac))
                (DAT_01205750, 1, &DAT_011d91d8, 1, DAT_01205748, _DAT_00f15a68, DAT_0120574c);

            // Process glyph handles (skip index 4)
            for (int i = 0; i < 5; i++) {
                if (i == 4) continue;
                uint handle = (&DAT_011f38f0)[i * 2];
                if (handle != 0) {
                    // Resolve glyph pointer from handle table
                    void* glyphPtr;
                    if (handle < 0x1000) {
                        glyphPtr = &DAT_011a0f28 + handle * 0x38;
                    } else {
                        glyphPtr = 0;
                    }
                    FUN_00606830(handle, glyphPtr);
                }
            }

            digitIndex++;
        } while (digitIndex < 6);
        lineIndex++;
    } while (lineIndex < 2);

    FUN_0060dcb0(); // End draw or flush
    FUN_00609730(0, 0, 0, 0, 0x3f800000, 0); // Reset state
}