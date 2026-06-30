// FUNC_NAME: LightManager::accumulateLighting
void __thiscall LightManager::accumulateLighting(void)
{
    // Iterate over a linked list starting at this->listHead (+0x10)
    // Each node has a next pointer at offset +0xA0
    int nodePtr = *(int *)((char *)this + 0x10);
    while (nodePtr != 0) {
        // Call per-node update function (e.g., updateShadowNode)
        FUN_0044f770(nodePtr, 0);
        nodePtr = *(int *)(nodePtr + 0xA0);   // next pointer
    }

    // Retrieve thread-local singleton (likely application or renderer)
    // Access through FS segment at offset 0x2c
    int *globalPtr = *(int **)(__readfsdword(0x2c) + 0x2c);
    int someOffset = *(int *)((char *)globalPtr + 8); // e.g., lightSourceCount or current frame index

    // Clear accumulated vector at this+0x40..0x4c (float4)
    *(float *)((char *)this + 0x40) = 0.0f;
    *(float *)((char *)this + 0x44) = 0.0f;
    *(float *)((char *)this + 0x48) = 0.0f;
    *(float *)((char *)this + 0x4c) = 0.0f;

    // Access an array of light source structures via this->lightSourceArray (+0x68)
    int lightArrayBase = *(int *)((char *)this + 0x68);
    // Each light source structure has fixed-size entries; someOffset selects a specific field
    int *current = (int *)(lightArrayBase + 0x8c + someOffset);
    // Count of entries to process is stored at lightArrayBase+0x10c+someOffset
    int count = *(int *)(lightArrayBase + 0x10c + someOffset);
    int *end = (int *)(lightArrayBase + 0x8c + someOffset + count * 4);

    // Accumulate light contributions (only x,y,z components; w unchanged)
    while (current != end) {
        // Each entry in the array is a pointer to a light source object
        int lightObj = *current;
        // The light object has a pointer to a vector at offset 0x18, then +0x40 + someOffset
        float *lightVec = (float *)(*(int *)(lightObj + 0x18) + 0x40 + someOffset);
        float x = lightVec[0];
        float y = lightVec[1];
        float z = lightVec[2];
        float w = lightVec[3];   // unused in accumulation (overwritten later)

        float oldW = *(float *)((char *)this + 0x4c);
        *(float *)((char *)this + 0x40) += x;
        *(float *)((char *)this + 0x44) += y;
        *(float *)((char *)this + 0x48) += z;
        *(float *)((char *)this + 0x4c) += w;
        *(float *)((char *)this + 0x4c) = oldW; // keep w unchanged (only accumulate x,y,z)

        current++;
    }
}