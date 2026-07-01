// FUNC_NAME: CameraInterpolator::update

// Function at 0x007f0860 - Updates camera interpolation using current time and two target objects.
// Uses global time variable at 0x00d5780c (likely gCurrentTime).
// Offsets:
//   this+0x04: pointer to source object (e.g., camera source)
//   this+0x08: pointer to target object (e.g., camera target)
//   this+0xf4: start time of interpolation (float)
// Each object at +0x134 contains a position/state used by the interpolation function.

extern float gCurrentTime; // 0x00d5780c

void __fastcall CameraInterpolator::update(void* thisPtr)
{
    float elapsed = gCurrentTime - *(float*)((char*)thisPtr + 0xf4);
    float timeParam = gCurrentTime - elapsed * elapsed; // Quadratic ease-out time

    // Get source and target objects
    void* sourceObj = *(void**)((char*)thisPtr + 0x04);
    void* targetObj = *(void**)((char*)thisPtr + 0x08);

    // Call interpolation function with position/state offsets at +0x134
    FUN_007f27a0(
        *(int*)((char*)sourceObj + 0x134),
        *(int*)((char*)targetObj + 0x134),
        timeParam
    );
}