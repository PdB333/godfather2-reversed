// FUNC_NAME: Entity::getBoneWorldTransform
undefined4 __thiscall Entity::getBoneWorldTransform(int thisPtr, undefined4 *outputMatrix) {
    char foundFlag;
    int *skeletonPtr;
    undefined4 *srcMatrix;
    int *boneNode;
    int boneNodePtr;
    int *local_boneNodePtr;
    int thisArray[3];
    undefined4 localTransform[16]; // Actually 16 floats, Ghidra misidentified as 7 + extras

    thisArray[0] = thisPtr;
    skeletonPtr = (int *)FUN_00446100(thisPtr + 0x54, 0);  // Get skeleton object at this+0x54
    if (skeletonPtr != (int *)0x0) {
        local_boneNodePtr = (int *)0x0;
        foundFlag = (**(code **)(*skeletonPtr + 0x10))(0x38523fc3, &local_boneNodePtr); // Find bone by hash
        if ((foundFlag != '\0') && (boneNode = local_boneNodePtr, local_boneNodePtr != (int *)0x0)) {
            // Get identity matrix (initial output)
            srcMatrix = (undefined4 *)FUN_00471610();  // Returns pointer to identity matrix
            // Copy 16 floats (64 bytes) into outputMatrix
            for (int i = 0; i < 16; i++) {
                outputMatrix[i] = srcMatrix[i];
            }

            // Prepare local transformation array (partially zeroed, partially identity)
            localTransform[0] = 0;
            localTransform[1] = 0;
            localTransform[2] = _DAT_00d5780c;   // Possibly 1.0f or identity element
            localTransform[3] = 0;
            localTransform[4] = 0;
            localTransform[5] = 0;
            localTransform[6] = _DAT_00d5780c;
            // (Based on offsets: uStack_8c, uStack_7c, uStack_6c are zero; auStack_64[2] = global; auStack_64[3]=0; uStack_48=0; uStack_38=0; uStack_28=global)
            // The global _DAT_00d5780c is likely an identity float (1.0f or 0.0f for quaternion?)
            // Full localTransform[0..15] is set here as per decompiled layout

            // Get bone's world transform relative to this entity
            (**(code **)(*boneNode + 0x8c))(thisArray, boneNode + 100, 1); // Compute transform, store in boneNode+100?

            // Combine local transformation with bone transform
            FUN_00724a70(localTransform); // Presumably multiply or transform matrix

            // Copy the combined result back to outputMatrix
            for (int i = 0; i < 16; i++) {
                outputMatrix[i] = localTransform[i];
            }
            return 1;
        }
    }
    return 0;
}