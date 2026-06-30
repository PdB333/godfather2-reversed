// FUNC_NAME: UIRect::drawOffsetRects
// Function at 0x005cf730: Draws four copies of a rectangle offset by rotated vectors (dx, dy), (dy, -dx), (-dx, -dy), (-dy, dx).
// The rectangle is defined by this+0x04 (left), this+0x08 (top), this+0x0C (right), this+0x10 (bottom).
// this+0x18 contains flags (bitmask & 0x1E) passed to the inner render function.
// param_1, param_2, param_5, param_6, param_7 are forwarded to the render function (likely renderer, texture, color, etc.)
// param_3, param_4 define the offset vector (dx, dy).

void __thiscall UIRect::drawOffsetRects(void* this, void* param_1, void* param_2, float dx, float dy, void* param_5, void* param_6, void* param_7)
{
    // Offsets from this pointer:
    // +0x04: left (x1)
    // +0x08: top (y1)
    // +0x0C: right (x2)
    // +0x10: bottom (y2)
    // +0x18: flags (bitmask, only bits 1-4 used via & 0x1E)

    float left = *(float*)((int)this + 0x04);
    float top = *(float*)((int)this + 0x08);
    float right = *(float*)((int)this + 0x0C);
    float bottom = *(float*)((int)this + 0x10);
    uint flags = *(uint*)((int)this + 0x18) & 0x1E;

    // Global constants (likely render device and a color/flag)
    int renderDevice = DAT_01205668 + 0x10; // +0x10 offset into a renderer structure
    int someConstant = DAT_00e2b1a4;        // Possibly a color or render flag

    // Temporary rectangle corners for each offset
    float x1, y1, x2, y2;
    float dummy1 = 0, dummy2 = 0; // local_18 and local_28, always zero

    // First offset: (dx, dy)
    x1 = left + dx;
    y1 = top + dy;
    x2 = right + dx;
    y2 = bottom + dy;
    FUN_005ced60(renderDevice, param_1, &x1, &x2, param_5, param_2, flags, param_6, param_7, 0);

    // Second offset: (dy, -dx)
    x1 = left + dy;
    y1 = top - dx;
    x2 = right + dy;
    y2 = bottom - dx;
    FUN_005ced60(renderDevice, param_1, &x1, &x2, param_5, param_2, flags, param_6, param_7, 0);

    // Third offset: (-dx, -dy)
    x1 = left - dx;
    y1 = top - dy;
    x2 = right - dx;
    y2 = bottom - dy;
    FUN_005ced60(renderDevice, param_1, &x1, &x2, param_5, param_2, flags, param_6, param_7, 0);

    // Fourth offset: (-dy, dx)
    x1 = left - dy;
    y1 = top + dx;
    x2 = right - dy;
    y2 = bottom + dx;
    FUN_005ced60(renderDevice, param_1, &x1, &x2, param_5, param_2, flags, param_6, param_7, 0);
}