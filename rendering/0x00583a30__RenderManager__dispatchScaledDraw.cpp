// FUNC_NAME: RenderManager::dispatchScaledDraw
// Address: 0x00583a30
// Dispatches drawing to a handler based on a mode byte, scaling coordinates by a global factor.

typedef void (__thiscall *ShapeDrawFunc)(void* param2, void* param1, void* param3, float scaledX, float scaledY, void* param6, float scaledZ);

// Global scaling factor (e.g., screen width or resolution reference)
extern float g_screenWidth; // DAT_00e2b1a4

// Dispatch table for shape drawing functions, indexed by mode (0..0x22)
extern ShapeDrawFunc g_shapeDrawTable[0x23]; // DAT_0103afc0

void __thiscall RenderManager::dispatchScaledDraw(byte* thisPtr, 
                                                  void* param2, 
                                                  void* param3, 
                                                  float x, 
                                                  float y, 
                                                  void* param6, 
                                                  float z)
{
    // Extract mode from first byte (lower 6 bits)
    byte mode = *thisPtr & 0x3F;

    if (mode < 0x23) {
        // Compute scale factor: screenWidth / given z? Actually param_7 is used as divisor.
        // In the original code, param_7 is the z parameter, so scale = g_screenWidth / z.
        float scale = g_screenWidth / z;

        // Dispatch to appropriate handler with scaled coordinates
        g_shapeDrawTable[mode](param2, thisPtr, param3, 
                               scale * x, scale * y, 
                               param6, scale * z);
    }
    // If mode >= 0x23, do nothing (return 0)
}