// FUNC_NAME: SceneCullingSystem::submitVisibleTriangles
uint* __thiscall SceneCullingSystem::submitVisibleTriangles(int* thisPtr, float someScale, float depthThreshold) {
    if (!func_0066def0()) {
        return nullptr;
    }

    ushort triangleCount = *(ushort*)(thisPtr + 0x12743);
    int currentTriangleIdx = 0;
    if (triangleCount != 0) {
        int* triangleData = thisPtr + 0x13f46; // pointer to triangle list
        
        // Some constant vector (probably one divided by something, like 1/256 or frustum planes)
        float constVec[4] = { DAT_00e44628, DAT_00e44628, DAT_00e44628, DAT_00e44628 };
        float faceOffset; // local_74
        float dirX, dirY, dirZ; // local_80, local_7c, local_78
        
        do {
            ushort vertexIndex = *(ushort*)(triangleData - 2);
            int vertexPtr = thisPtr[vertexIndex + 0x12944];
            int meshData = thisPtr[vertexIndex + 0x12744];
            int basePtr = *(int*)(meshData + 0x50);
            
            if (vertexPtr != currentTriangleIdx) {
                // Fetch transformed camera position? Or some global offset
                float tmp = DAT_00e44564;
                func_00417560(); // likely updates global camera position
                dirY = tmp - *(float*)(vertexPtr + 0x94);
                dirZ = tmp - *(float*)(vertexPtr + 0x98);
                dirX = tmp - *(float*)(vertexPtr + 0x90);
                
                // Compute a view-dependent offset (possibly using param_2 as a scaling factor)
                faceOffset = tmp - (
                    (someScale * *(float*)(vertexPtr + 0x98) + *(float*)(vertexPtr + 0x88)) * dirZ +
                    (someScale * *(float*)(vertexPtr + 0x94) + *(float*)(vertexPtr + 0x84)) * dirY +
                    (someScale * *(float*)(vertexPtr + 0x90) + *(float*)(vertexPtr + 0x80)) * dirX
                );
                currentTriangleIdx = vertexPtr;
                // Store view direction for later
                // (these are stored in local variables that survive loop)
            }
            
            // Read triangle vertices as 4D vectors (probably homogeneous)
            float* v0 = (float*)*(triangleData - 1);
            float triV0[4] = { v0[0], v0[1], v0[2], v0[3] };
            float* v1 = (float*)*triangleData;
            float triV1[4] = { v1[0], v1[1], v1[2], v1[3] };
            float* v2 = (float*)*(triangleData + 1);
            float triV2[4] = { v2[0], v2[1], v2[2], v2[3] };
            
            // Compute plane equation (components of cross product + dot with constVec)
            float planeA = ( (triV2[3] - triV1[1]) * (triV1[2] - triV1[1]) - (triV2[1] - triV1[1]) * (triV1[3] - triV1[1]) ) * constVec[0]; // Actually careful: need to interpret indices correctly. Ghidra uses stacks: local_60 is triV2[0]? etc.
            // The decompiled code is messy. We'll try to reconstruct the cross product correctly.
            float planeB = ( (triV2[4] - triV1[0]) * (triV1[2] - triV1[1]) - (triV2[1] - triV1[1]) * (triV1[4] - triV1[0]) ) * constVec[1]; // Off, let's use direct formula from decompiled:
            // local_30 = ((fStack_58 - fStack_38) * (fStack_4c - fStack_3c) - (fStack_5c - fStack_3c) * (fStack_48 - fStack_38)) * local_20;
            // But fStack_58 is triV2[1]? Actually local_60 = triV2[0], fStack_5c = triV2[1], fStack_58 = triV2[2], fStack_54 = triV2[3]. Similarly, local_50 = triV1[0], fStack_4c = triV1[1], fStack_48 = triV1[2], fStack_44 = triV1[3]. local_40 = triV0[0], fStack_3c = triV0[1], fStack_38 = triV0[2], fStack_34 = triV0[3].
            // So we have:
            // A = (triV2[2] - triV0[2]) * (triV1[1] - triV0[1]) - (triV2[1] - triV0[1]) * (triV1[2] - triV0[2])
            // B = (triV2[0] - triV0[0]) * (triV1[2] - triV0[2]) - (triV2[2] - triV0[2]) * (triV1[0] - triV0[0])
            // C = (triV2[1] - triV0[1]) * (triV1[0] - triV0[0]) - (triV2[0] - triV0[0]) * (triV1[1] - triV0[1])
            // And D = (triV2[3] - triV0[3]) * (triV1[3] - triV0[3]) - (triV2[3] - triV0[3]) * (triV1[3] - triV0[3]) (that's zero? Actually fStack_24 uses same terms, gives zero. Possibly it's the fourth component normalization.)
            // The code multiplies each by a component of constVec.
            float planeA = ((triV2[2] - triV0[2]) * (triV1[1] - triV0[1]) - (triV2[1] - triV0[1]) * (triV1[2] - triV0[2])) * constVec[0];
            float planeB = ((triV2[0] - triV0[0]) * (triV1[2] - triV0[2]) - (triV2[2] - triV0[2]) * (triV1[0] - triV0[0])) * constVec[1];
            float planeC = ((triV2[1] - triV0[1]) * (triV1[0] - triV0[0]) - (triV2[0] - triV0[0]) * (triV1[1] - triV0[1])) * constVec[2];
            float planeD = ((triV2[3] - triV0[3]) * (triV1[3] - triV0[3]) - (triV2[3] - triV0[3]) * (triV1[3] - triV0[3])) * constVec[3];
            // But the code only uses local_30, fStack_2c, fStack_28, and fStack_24. Then it squares and sums.
            
            // Compute squared magnitude
            float magSq = planeA*planeA + planeB*planeB + planeC*planeC;
            float invMag;
            if (magSq <= DAT_00e2cbe0) {
                invMag = 0.0f;
                magSq = 0.0f;
            } else {
                magSq = sqrtf(magSq);
                invMag = DAT_00e2b1a4 / magSq;
            }
            
            // Check if visible (dot with view direction > threshold)
            if (magSq > DAT_00e44598 && 
                depthThreshold <= (planeA * invMag * dirX + planeB * invMag * dirY + planeC * invMag * dirZ)) {
                // Compute depth value for sorting (bitwise truncation?)
                float depth0 = (float)((uint)(triV0[0] * dirX + triV0[1] * dirY + triV0[2] * dirZ + faceOffset) & DAT_00e44680);
                float depth1 = (float)((uint)(triV1[0] * dirX + triV1[1] * dirY + triV1[2] * dirZ + faceOffset) & DAT_00e44680);
                float depth2 = (float)((uint)(triV2[0] * dirX + triV2[1] * dirY + triV2[2] * dirZ + faceOffset) & DAT_00e44680);
                float minDepth = depth0;
                if (depth1 < minDepth) minDepth = depth1;
                if (depth2 < minDepth) minDepth = depth2;
                
                if (minDepth <= DAT_00e2fc48) {
                    // Submit triangle to render queue
                    undefined2* indices = (undefined2*)(*(int*)(meshData + 0x88) + (uint)*(ushort*)((int)triangleData - 6) * 6);
                    func_0066e060(
                        (meshData - *(int*)(basePtr + 0x50)) / 0xb0, // some index
                        *indices, indices[1], indices[2],
                        &triV0[0], &triV1[0], &triV2[0]
                    );
                    // Restore dir values (they were stored but may have been overwritten by func call)
                    dirX = /* local_80 */; dirY = /* local_7c */; dirZ = /* local_78 */;
                }
            }
            
            triangleData += 4; // advance to next triangle entry (4 ints per triangle)
            triangleCount--;
        } while (triangleCount != 0);
    }
    
    // Manage render command queue
    uint* queue = (uint*)thisPtr[4];
    uint* result = nullptr;
    if (queue != nullptr && queue[3] != 0) {
        *queue |= 1; // mark as pending?
        thisPtr[1] += queue[3]; // increment some counter
        (*thisPtr)++; // total count?
        result = queue;
    }
    thisPtr[4] = 0; // clear queue pointer
    return result;
}