// FUNC_NAME: clampMouseToCenter
int64_t clampMouseToCenter(int32_t mouseX, int32_t mouseY)
{
    // Global flag indicating whether mouse clamping is enabled
    if (g_mouseClampEnabled != '\0') {
        // Compute delta from center
        int32_t deltaX = g_mouseCenterX - mouseX;
        int32_t deltaY = g_mouseCenterY - mouseY;

        // Check if the mouse has moved away from center (absolute delta > 0)
        // Using absolute value trick: ((x >> 31) + x) ^ (x >> 31) gives abs(x)
        if ((0 < ((deltaX >> 0x1f) + deltaX ^ deltaX >> 0x1f)) ||
            (0 < ((deltaY >> 0x1f) + deltaY ^ deltaY >> 0x1f))) {
            // Reset cursor to center plus offset
            SetCursorPos(g_mouseClampOffsetX + g_mouseCenterX,
                         g_mouseClampOffsetY + g_mouseCenterY);
            // Return the delta as a 64-bit value (high = deltaY, low = deltaX)
            return CONCAT44(deltaY, deltaX);
        }
    }
    return 0;
}