// FUNC_NAME: Animation::update
// Address: 0x00595e70
// Role: Updates animation state, processes transform flags, and calls virtual update functions.

void Animation::update(float deltaTime)
{
    // Flags field at offset +0x01 (byte) controls state:
    //   bit0 (0x01) - some flag affecting math
    //   bit1 (0x02) - transform dirty flag
    //   bit2 (0x04) - another transform flag
    //   bit3 (0x08) - animation complete flag
    uint* flagsPtr = reinterpret_cast<uint*>(reinterpret_cast<char*>(this) + 0x01);
    uint flags = *flagsPtr;

    // If transform dirty flag (bit1) is not set, update position transform
    if ((flags & 0x02) == 0)
    {
        float fVar = someFloatOperation(deltaTime); // FUN_00595490
        if ((flags & 0x01) != 0)
        {
            fVar = someFloatOperation(fVar);
            someFloatOperation(fVar);
        }
        // Build a 3D vector (likely position offset) from stack locals
        float vecLocal[3]; // local_20, local_1c, local_18
        buildVector3(vecLocal); // FUN_0059bb50
        // Call global transform function with vector and this+0x23 (position offset?)
        // gTransformSystem is DAT_012055a8 (global singleton)
        TransformSystem* transSys = *reinterpret_cast<TransformSystem**>(0x012055a8);
        transSys->vtable->func0x34(vecLocal[0], vecLocal[1], vecLocal[2], reinterpret_cast<float*>(this) + 0x23);
    }

    // If another transform flag (bit2) is not set, update rotation/matrix transform
    if ((flags & 0x04) == 0)
    {
        float fVar = someFloatOperation(deltaTime);
        if ((flags & 0x01) != 0)
        {
            fVar = someFloatOperation(fVar);
            someFloatOperation(fVar);
        }
        buildMatrix(flagsPtr); // FUN_0059bc30 - uses the flags pointer
    }

    // If animation complete flag (bit3) is set, call virtual update (vtable+0x10) and return
    if ((flags & 0x08) != 0)
    {
        (this->vtable->func0x10)(); // update callback
        return;
    }

    // Process delta for animation progress
    someFloatOperation(deltaTime);
    char animationDone = isAnimationComplete(); // FUN_00595610

    if (animationDone == 0)
    {
        // Not done: clear animation complete flag
        *flagsPtr = flags & 0xfffffff7; // clear bit3
    }
    else
    {
        // Done: set animation complete flag
        *flagsPtr = flags | 0x08;
    }

    // Call virtual function at vtable+0x0C to get some anim progress/value
    // Note: iStack_24 is uninitialized at this point; likely it's an output parameter from earlier transform calls
    // but due to decompiler artifacts we treat as local scratch.
    int scratch = 0; // placeholder for uninitialized stack variable (iStack_24)
    this->vtable->func0x0C(scratch, *(reinterpret_cast<int*>(this) + 0x2b)); // returns float
    *(reinterpret_cast<int*>(this) + 0x29) = static_cast<int>(scratch); // actually the return value is stored at +0x29

    // Finally call virtual update callback
    (this->vtable->func0x10)();
    return;
}