// FUNC_NAME: CameraManager::getCameraPositionAndTarget
void __thiscall CameraManager::getCameraPositionAndTarget(CameraManager *this, float *outPosition, float *outTarget)
{
    // Local buffer (28 bytes): first 12 bytes -> position, next 4 bytes (unused), last 12 bytes -> target
    // Decompiler split this into three sections due to stack layout: position at uStack_3c..uStack_34,
    // gap at local_30, target at uStack_2c..uStack_24
    float position[3]; // offset -0x3c
    uint32_t gap;      // offset -0x30 (local_30) - unused
    float target[3];   // offset -0x2c

    // Retrieve camera object from this+0x2e8 (likely a CameraComponent pointer)
    void *cameraObject = *(void **)((char *)this + 0x2e8);
    // Access the camera's interface/component at cameraObject+0x10
    void *cameraInterface = *(void **)((char *)cameraObject + 0x10);
    // Vtable of cameraInterface, method at offset 0x1c (6th virtual function)
    void **vtable = *(void ***)cameraInterface;
    typedef void (__thiscall *CameraCalcFunc)(void *self, uint32_t param, float *buffer);
    CameraCalcFunc func = (CameraCalcFunc)vtable[0x1c / 4]; // index 7

    // Global dereference for second argument: DAT_01223480 + 0x24 -> +0x6c -> +4
    uint32_t global = *(uint32_t *)(DAT_01223480); // singleton pointer
    uint32_t arg2 = *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(global + 0x24) + 0x6c) + 4);

    // First argument: cameraObject + 0xe0 (likely a transform or parameter block)
    void *selfArg = (char *)cameraObject + 0xe0;

    // Call the virtual method, which fills the buffer starting at &gap (local_30)
    // The method writes 12 bytes before local_30 (to position) and 12 bytes after (to target)
    func(selfArg, arg2, (float *)&gap);

    // Copy results to outputs
    outPosition[0] = position[0];
    outPosition[1] = position[1];
    outPosition[2] = position[2];
    outTarget[0] = target[0];
    outTarget[1] = target[1];
    outTarget[2] = target[2];
}