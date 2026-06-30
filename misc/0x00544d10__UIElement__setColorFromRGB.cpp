// FUNC_NAME: UIElement::setColorFromRGB
// Function address: 0x00544d10
// Sets a 4-component color from an RGB source with a global alpha (likely 0xFF).
// Uses virtual callbacks for visibility/update checks.

void __thiscall UIElement::setColorFromRGB(int* thisPtr, int* rgbSource) {
    int globalAlpha = DAT_00e2b1a4; // Constant opaque alpha (0xFFFFFFFF)
    int localColor[4];

    // Copy RGB from source
    localColor[0] = rgbSource[0];
    localColor[1] = rgbSource[1];
    localColor[2] = rgbSource[2];
    localColor[3] = globalAlpha;

    // Store color in object at offset 0x100 (RGBA)
    thisPtr[0x40] = localColor[0];  // +0x100
    thisPtr[0x41] = localColor[1];  // +0x104
    thisPtr[0x42] = localColor[2];  // +0x108
    thisPtr[0x43] = localColor[3];  // +0x10C

    // Call initialization / invalidation function
    FUN_006101b0();

    // Virtual call: onColorChanged() or update() (vtable + 0x68)
    (*(void (**)())(thisPtr[0] + 0x68))();

    int flag = thisPtr[0xba]; // Offset 0x2E8 – some state flag
    char visibleOrEnabled = (*(char (**)())(thisPtr[0] + 0x19c))(); // vtable + 0x19c

    if (visibleOrEnabled != 0) {
        // Re-set local color (likely due to optimization, same values)
        localColor[0] = rgbSource[0];
        localColor[1] = rgbSource[1];
        localColor[2] = rgbSource[2];
        localColor[3] = globalAlpha;

        // Check some sub-object state (offset chain: this->+0xD8 -> +0x18 -> +0xD8)
        if (*(char*)(*(int*)(thisPtr[0xd8] + 0x18) + 0xd8) == '\a') { // 0x07
            FUN_009f4240(1, 1, 0); // e.g., enableAlphaBlending(true, true, false)
        }
    } else {
        if (flag == 0) goto LAB_00544e1a;
        // Re-set local color again
        localColor[0] = rgbSource[0];
        localColor[1] = rgbSource[1];
        localColor[2] = rgbSource[2];
        localColor[3] = globalAlpha;
    }

    // Apply the color (e.g., push to rendering stack)
    FUN_009f4c40(&localColor);

LAB_00544e1a:
    // Virtual call: render() or draw() (vtable + 600 = 0x258)
    (*(void (**)())(thisPtr[0] + 600))();
}