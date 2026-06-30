// FUNC_NAME: updateGlobalFloat4AndNotify

// Function at 0x006124c0
// Updates a global 4-float vector (position/direction/quaternion) and triggers
// a callback if the value changed and a specific object (with a callback slot) is active.
// Similar to a property change notification system.

// Global storage for the current float4 values (0x011f6890)
extern float gFloat4X;
extern float gFloat4Y;
extern float gFloat4Z;
extern float gFloat4W;

// Global pointer to an object that contains callback information (0x012058e8)
extern void* gCallbackObject; // Some engine object (e.g., RenderContext, CameraManager, etc.)

// Forward declaration of the callback function at 0x0060add0
void __fastcall callFloat4UpdateCallback(void* obj, void* callbackPtr, float* newValues);

void __fastcall updateGlobalFloat4AndNotify(uint unusedParam1, uint unusedParam2, float* newValues)
{
    float newX = newValues[0];
    float newY = newValues[1];
    float newZ = newValues[2];
    float newW = newValues[3];

    // Compare with current globals using SSE-style sign mask extraction.
    // Original: auVar1._0_4_ = -(uint)(fVar2 == _DAT_011f6890);
    // This produces 0xFFFFFFFF if equal, 0 if not.
    int cmpX = -(newX == gFloat4X);
    int cmpY = -(newY == gFloat4Y);
    int cmpZ = -(newZ == gFloat4Z);
    int cmpW = -(newW == gFloat4W);

    // Simulate _mm_movemask_ps: extract sign bits from the 4 float comparisons.
    // Since cmpX is all 1s when equal, its highest bit (sign bit) is set.
    int mask = ((cmpX >> 31) & 1) | ((cmpY >> 30) & 2) | ((cmpZ >> 29) & 4) | ((cmpW >> 28) & 8);

    // Store the new values into global storage
    gFloat4X = newX;
    gFloat4Y = newY;
    gFloat4Z = newZ;
    gFloat4W = newW;

    // If mask is not 0xF (meaning not all four components were equal), then something changed.
    // Equivalent to: if (newX != oldX || newY != oldY || newZ != oldZ || newW != oldW)
    if (mask != 0xF)
    {
        if (gCallbackObject != nullptr && *(void**)((int)gCallbackObject + 0x74) != nullptr)
        {
            // The callback object has fields at offsets +0x14 and +0x74
            // +0x14: some identifier or pointer
            // +0x74: function pointer to the update callback
            void* objArg = *(void**)((int)gCallbackObject + 0x14);
            void* callbackPtr = *(void**)((int)gCallbackObject + 0x74);
            callFloat4UpdateCallback(objArg, callbackPtr, &gFloat4X);
        }
    }
}