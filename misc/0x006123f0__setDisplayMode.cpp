// FUNC_NAME: setDisplayMode
void __fastcall setDisplayMode(int mode)
{
    // g_pDisplayManager is a global singleton of the display/system manager (structure at 0x012058e8)
    if (g_pDisplayManager == 0) {
        return;
    }

    if (mode == 0) {
        // Reset to default mode
        // Check if the display manager's active flag (+0x9c) is set
        if (*(char *)(g_pDisplayManager + 0x9c) != '\0') {
            // Call virtual function at offset 0xc on the render device object (+0x98)
            // This likely ends/restores the current mode
            (**(code **)(**(int **)(g_pDisplayManager + 0x98) + 0xc))();
        }

        // Check if there is a camera/render target at offset +0x70
        if (*(int *)(g_pDisplayManager + 0x70) != 0) {
            // Set viewport/projection using scaled screen parameters
            // g_screenScale is a global multiplier (probably DPI or UI scale)
            // g_screenParams points to a structure containing floats at offsets 0x40/0x44/0x48/0x4c (left, top, right, bottom)
            FUN_006125c0(g_screenScale * *(float *)(g_screenParams + 0x40),
                         g_screenScale * *(float *)(g_screenParams + 0x44),
                         g_screenScale * *(float *)(g_screenParams + 0x48),
                         g_screenScale * *(float *)(g_screenParams + 0x4c));
        }
    }
    else if (mode != g_prevMode) {
        // Cache the new mode
        g_prevMode = mode;

        // Check if active flag is set
        if (*(char *)(g_pDisplayManager + 0x9c) != '\0') {
            // Call virtual function at offset 8 on the render device to set the new mode
            // Parameters: mode and a constant flag (4)
            (**(code **)(**(int **)(g_pDisplayManager + 0x98) + 8))(mode, 4);
        }

        // If a camera/render target exists, reset the device and update viewport
        if (*(int *)(g_pDisplayManager + 0x70) != 0) {
            FUN_0066d2e0(); // Reset/initialize device state
            FUN_006125c0(); // Apply viewport (using internally stored parameters)
        }
    }
}