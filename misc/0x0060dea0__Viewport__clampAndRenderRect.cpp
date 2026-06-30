// FUNC_NAME: Viewport::clampAndRenderRect

// Function at 0x0060dea0: clamps a rectangle (x, y, width, height) to the active viewport,
// then renders the clamped rectangle using renderRect.

struct ViewportRect {
    int x;      // +0x00
    int y;      // +0x04
    int width;  // +0x08
    int height; // +0x0C
    // +0x10 to +0x17 unknown/padding
};

extern int gActiveViewportIndex; // DAT_012058b0, index into gViewports array
extern ViewportRect gViewports[]; // Base at DAT_011f3918, stride 0x18

extern void renderRect(int width, int height); // FUN_00609640

// This is __thiscall but the 'this' pointer is not used; maybe a static member.
void __thiscall Viewport::clampAndRenderRect(int x, int width, int y, int height) {
    // Equivalent to the four parameters: param_1 = x, param_2 = width,
    // param_3 = y, in_EAX = height.
    // The decompiler listed param_1, param_2, param_3 but missed the fourth register param.
    // We'll use a revised signature with four ints.

    // Actually the original signature might have been (int x, int y, int w, int h) but with
    // calling convention where first stack param is x, second is width, third is y,
    // and height passed in EAX. We'll stick with the four ints.

    int index = gActiveViewportIndex;
    int baseOffset = index * 0x18; // sizeof(ViewportRect) = 0x18

    int minX = gViewports[0].x; // Actually using base address directly: *(int*)(DAT_011f3918 + baseOffset)
    int minY = gViewports[0].y; // *(int*)(DAT_011f391c + baseOffset)
    int viewportWidth = gViewports[0].width; // *(int*)(DAT_011f3920 + baseOffset)
    int viewportHeight = gViewports[0].height; // *(int*)(DAT_011f3924 + baseOffset)

    int maxX = minX + viewportWidth;
    int maxY = minY + viewportHeight;

    // Clamp left edge
    if (x < minX) {
        width += (x - minX);
        x = minX;
    }

    // Clamp right edge
    if (x > maxX) {
        width = 0;
        x = maxX;
    }

    // Clamp top edge
    if (height < minY) { // Note: original code compares in_EAX (height) with iVar3 (minY)
        y += (height - minY); // param_3 = param_3 + (in_EAX - iVar3)
        height = minY;
    }

    // Clamp bottom edge
    if (height > maxY) {
        y = 0;
        height = maxY;
    }

    // Adjust width if rectangle extends beyond right edge
    if (x + width > maxX) {
        width = (minX - x) + viewportWidth;
    }

    // Adjust height if rectangle extends beyond bottom edge
    if (height + y > maxY) {
        y = (minY - height) + viewportHeight;
    }

    // Ensure non-negative dimensions
    if (width < 0) width = 0;
    if (y < 0) y = 0; // Note: original code clamps param_3 (y), not height

    // Call render function with clamped width and height
    renderRect(width, y); // Note: original calls FUN_00609640(param_2, param_3)
}