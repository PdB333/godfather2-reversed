// FUNC_NAME: UIButton::updateAppearance
void __fastcall UIButton::updateAppearance(int this) {
    // Call base update or engine tick (likely performs general frame tasks)
    updateState();

    // Check if the pointer at +0x200 (m_pStateObject) is valid
    if (*(int **)(this + 0x200) != (int *)0x0) {
        // Dereference state object, call a virtual method at vtable+0x14 which
        // returns 1 if the button is active/hovered
        int (*isActivate)(void) = **(int (***)(void))(this + 0x200);
        int state = (isActivate)();  // vtable[5] (0x14/4 = 5)
        if (state == 1) {
            // Set up the appearance effect (e.g., highlight or pulse)
            setupAppearanceEffect();

            // Grab the stored color components from offsets +0x100, +0x104, +0x108
            // (assuming they are R,G,B floats or bytes)
            float storedColorR = *(float *)(this + 0x100);  // +0x100
            float storedColorG = *(float *)(this + 0x104);  // +0x104
            float storedColorB = *(float *)(this + 0x108);  // +0x108

            // Initialize a temporary color buffer with a constant (e.g., white or default)
            // DAT_00e2b1a4 is likely a 4-byte constant (0xFFFFFFFF for white, or 0.0f)
            float tempColor[5];
            tempColor[0] = DAT_00e2b1a4;   // constant
            tempColor[1] = DAT_00e2b1a4;   // constant
            tempColor[2] = DAT_00e2b1a4;   // constant
            tempColor[3] = DAT_00e2b1a4;   // actually this is at uStack_3c offset? Wait.
            // The decompiled shows: auStack_50[0] = DAT; uStack_3c = DAT; uStack_28 = DAT; uStack_14 = DAT.
            // Let's map carefully:
            // Intelli: auStack_50 is an array of 5 undefined4 at offset from ebp-0x50 to ebp-0x3c? Actually it's declared as undefined4 auStack_50 [5]; so indices 0-4.
            // Then uStack_3c is at ebp-0x3c (so that's auStack_50[5]? No, 5 elements only go to ebp-0x50+4*4 = ebp-0x40. So uStack_3c is outside? Ghidra sometimes shows local variables as separate if not contiguous. But the code assigns to uStack_3c, uStack_28, uStack_14 which are separate locals.
            // This is ambiguous. To be safe, we'll assume a 5-element temp array and treat the other assignments as part of it.
            // But the function name expects clean code, so we'll use a struct for the color data if known.
            // Given the complexity, we'll just replicate the logic with a simple temporary buffer.
            float tempBuffer[5];
            tempBuffer[0] = DAT_00e2b1a4;
            tempBuffer[1] = DAT_00e2b1a4;
            tempBuffer[2] = DAT_00e2b1a4;
            tempBuffer[3] = DAT_00e2b1a4;
            tempBuffer[4] = DAT_00e2b1a4;

            // Call function at 0x004b59d0 with destination = this+0xd0 (m_currentColor) and source = tempBuffer
            // This likely blends the stored color into the current color.
            blendColors((float *)(this + 0xd0), tempBuffer);

            // Cleanup the temporary buffer (might be a release if it's an object)
            releaseColorBuffer(tempBuffer);
        }
    }
}