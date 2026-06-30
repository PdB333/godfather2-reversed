// FUNC_NAME: Entity::lerpVectorWithClamp
float Entity::lerpVectorWithClamp(const float* start, const float* end, float* out)
{
    float fVar1;
    float local_80[4];
    float local_70[4];
    float local_24;
    char local_48;
    float* local_50;
    // +0x84: pointer to a transform data (matrix)
    // +0x88: some float (unused in this function? maybe part of a struct)
    
    fVar1 = _DAT_00d5780c; // global max interpolation factor
    if (*(char*)(DAT_01223394 + 0x54) == '\0') { // check global pause flag
        local_80[0] = start[0];
        local_80[1] = start[1];
        local_80[2] = start[2];
        local_80[3] = 0.0f;
        FUN_009f1820(local_80, 0); // normalize or transform start vector
        
        local_70[0] = end[0];
        local_70[1] = end[1];
        local_70[2] = end[2];
        local_70[3] = 0.0f;
        local_50 = &PTR_LAB_00d5f038; // identity matrix pointer
        
        // local_20 from this+0x88 is set but not used later? Possibly part of struct
        // Actually the decompiler shows local_20 = *(undefined4 *)(param_1 + 0x88);
        // That may be unused because it's on stack but not read.
        
        // Transform end vector by the matrix at (this+0x84)+0x10
        FUN_009e7fd0(*(int*)(this + 0x84) + 0x10, local_70, &local_50, 0);
        
        fVar1 = _DAT_00d5780c;
        if (local_48 != '\0') { // if transformation succeeded
            if (0.0f < local_24) {
                fVar1 = local_24;
                if (_DAT_00d5780c <= local_24) {
                    fVar1 = _DAT_00d5780c;
                }
            } else {
                fVar1 = 0.0f;
            }
        }
    }
    
    // Linear interpolation from start to end with factor fVar1
    out[0] = (end[0] - start[0]) * fVar1 + start[0];
    out[1] = (end[1] - start[1]) * fVar1 + start[1];
    out[2] = (end[2] - start[2]) * fVar1 + start[2];
    
    return (float)fVar1;
}