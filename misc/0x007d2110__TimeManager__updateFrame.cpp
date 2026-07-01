// FUNC_NAME: TimeManager::updateFrame

// Reconstructed from 0x007d2110 - Appears to be a timing update function.
// Calls a virtual method (vtable+8) to get a float (likely current time step),
// then delegates to a global processing function with additional context.

class TimeManager {
public:
    // Virtual function at vtable+0x08 - gets some float value (e.g., timeStep)
    virtual float getTimeValue() = 0;
};

// Global constants (unknown purpose)
extern float DAT_00e5303c;          // +0x00e5303c
extern int* DAT_01206800;          // +0x01206800

// Global helper function (from FUN_007992a0)
void processTimeStep(float timeVal, float globalConst, int* objPtr, void** stackPtr, int extraParam);

void __thiscall TimeManager::updateFrame(int* thisPtr, int param_3) {
    // param_2 is overwritten by global, so ignore
    int* localStackPtr = thisPtr;

    // Call virtual function at vtable+8 (third entry in vtable)
    float timeVal = (float)(*(code **)(*thisPtr + 8))();

    // Call global processing function
    // Arguments: timeVal, global constant, global object pointer, address of this pointer, extra parameter
    processTimeStep(timeVal, DAT_00e5303c, DAT_01206800, &localStackPtr, param_3);
}