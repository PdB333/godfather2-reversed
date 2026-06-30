// FUNC_NAME: UIRenderer::render
// Function address: 0x006cfdc0
// Role: Renders a UI element with a constant color from global constants.
// Checks if a condition pointer (this+0xd0) is non-null, then sets a color
// on a render state structure (this+0xd8) and calls sub-functions.

void __thiscall UIRenderer::render(int thisPtr, int param2) {
    // Global constants (likely RGBA color values)
    int g_constantA = _DAT_00d5f270;   // +0x00
    int g_constantB = _UNK_00d5f274;   // +0x04
    int g_constantC = _UNK_00d5f278;   // +0x08
    int g_constantD = _UNK_00d5f27c;   // +0x0c

    // Check if condition pointer at this+0xd0 is non-null
    if (*(int*)(thisPtr + 0xd0) != 0) {
        // Get render state structure pointer at this+0xd8
        int renderStatePtr = *(int*)(thisPtr + 0xd8);
        // Write the four global constants into the render state structure at offsets 0x10-0x1c
        *(int*)(renderStatePtr + 0x10) = g_constantA;
        *(int*)(renderStatePtr + 0x14) = g_constantB;
        *(int*)(renderStatePtr + 0x18) = g_constantC;
        *(int*)(renderStatePtr + 0x1c) = g_constantD;

        // Call sub-functions
        FUN_004ec1c0(param2);                          // Possibly sets a texture or shader
        FUN_004df830(*(int*)(thisPtr + 0xd8));         // Draws using the render state
        FUN_006cf860();                                // Resets or finalizes
    }
}