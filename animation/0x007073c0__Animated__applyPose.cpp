// FUNC_NAME: Animated::applyPose
// Function address: 0x007073c0
// Role: Reads transform data from a global animation state and applies it to the animated object's component

void __fastcall Animated::applyPose(Animated* this)
{
    // +0x1e0: pointer to an animation component (e.g., bone controller) that has a vtable or data pointer at +0x00
    int* componentPtr = *(int**)((char*)this + 0x1e0);
    if (componentPtr != nullptr && *(void**)componentPtr != nullptr)
    {
        // Retrieve current animation frame data from a global function (likely returns a pose or skeleton)
        void* animData = (void*)FUN_00471610();

        // Extract position/rotation vector from animData at offsets +0x30, +0x34, +0x38
        // The fourth component (local_14) is set to zero, likely representing a rotation quaternion's w or a scaling factor
        float x = *(float*)((char*)animData + 0x30);
        float y = *(float*)((char*)animData + 0x34);
        float z = *(float*)((char*)animData + 0x38);
        float w = 0.0f;

        // Build a 4-component vector on the stack
        float transform[4] = { x, y, z, w };

        // Apply the transform to the component's internal state (second param=0 might be interpolation weight or flag)
        FUN_009f1820(transform, 0);
    }
}