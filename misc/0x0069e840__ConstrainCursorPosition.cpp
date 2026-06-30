// FUNC_NAME: ConstrainCursorPosition
// Function at 0x0069e840: Clamps cursor position to a central region when a constraint flag is set.
// If the cursor deviates from the center (DAT_0112a054, DAT_0112a058), it is reset to center plus offsets.
// Returns the deviation vector as a 64-bit value (X low, Y high).

#include <cstdint>

// External globals (likely defined elsewhere in the module)
extern char g_constraintEnabled;          // DAT_00e50b89: non-zero enables constraint
extern int g_centerX;                     // DAT_0112a054: center X coordinate
extern int g_centerY;                     // DAT_0112a058: center Y coordinate
extern int g_offsetX;                     // DAT_0112a05c: additional X offset when resetting
extern int g_offsetY;                     // DAT_0112a060: additional Y offset when resetting

// External Win32 function
extern "C" void SetCursorPos(int x, int y);

uint64_t ConstrainCursorPosition(int param1, int param2)
{
    if (g_constraintEnabled) {
        int dx = g_centerX - param1;
        int dy = g_centerY - param2;

        // Calculate absolute value using sign trick: abs(dx) = ((dx >> 31) + dx) ^ (dx >> 31)
        int absDx = ((dx >> 0x1f) + dx) ^ (dx >> 0x1f);
        int absDy = ((dy >> 0x1f) + dy) ^ (dy >> 0x1f);

        // If either absolute offset is non-zero, reset cursor to center + offsets
        if (absDx > 0 || absDy > 0) {
            int newX = g_offsetX + g_centerX;
            int newY = g_offsetY + g_centerY;
            SetCursorPos(newX, newY);
            // Return the original deviation vector (low dx, high dy)
            return ((uint64_t)(int32_t)dx) | ((uint64_t)(int32_t)dy << 32);
        }
    }
    return 0;
}