// FUNC_NAME: SweepQuery::sphereSweep
int SweepQuery::sphereSweep(float* startPos, float* endPos, float* outPos, float* outNormal) {
    float interpFactor = DAT_00e2b1a4;  // Global interpolation factor (time step?)
    // Temporary structure for collision query
    struct SweepTemp {
        float start[4];
        float end[4];
        byte flags;                 // +0x20
        uint handle;                // +0x24
        void** vtable;              // +0x28
        float factor;               // +0x2C
        // ... other unknown fields
        float outputPos[4];         // +0x30?
        uint outExtra;              // +0x40?
    } temp;

    // Initialize sweep structure
    temp.start[0] = startPos[0];
    temp.start[1] = startPos[1];
    temp.start[2] = startPos[2];
    temp.start[3] = startPos[3];
    temp.end[0] = endPos[0];
    temp.end[1] = endPos[1];
    temp.end[2] = endPos[2];
    temp.end[3] = endPos[3];
    temp.handle = ((uint)&temp.start) >> 2 | 0x40000000;  // Constructed handle
    temp.flags = 1;
    temp.vtable = &PTR_FUN_00e32a8c;  // vtable for sweep object
    temp.factor = DAT_00e2b1a4;

    // Perform collision sweep check (fills temp.outputPos and more)
    int hit = FUN_009e5ed0(&temp.start, &temp.vtable);  // This function checks sweep

    if (hit != 0) {
        // Linear interpolation between start and end by global factor
        outPos[0] = (endPos[0] - startPos[0]) * interpFactor + startPos[0];
        outPos[1] = (endPos[1] - startPos[1]) * interpFactor + startPos[1];
        outPos[2] = (endPos[2] - startPos[2]) * interpFactor + startPos[2];
        outPos[3] = (endPos[3] - startPos[3]) * interpFactor + startPos[3];

        // Copy output normal (or other data) from sweep result
        outNormal[0] = temp.outputPos[0];
        outNormal[1] = temp.outputPos[1];  // Actually these are likely at +0x30 from temp base
        outNormal[2] = temp.outputPos[2];
        outNormal[3] = temp.outputPos[3];

        return 1;  // Success
    }

    return 0;  // No collision
}