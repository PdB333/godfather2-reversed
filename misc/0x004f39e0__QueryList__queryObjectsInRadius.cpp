// FUNC_NAME: QueryList::queryObjectsInRadius
void __vectorcall QueryList::queryObjectsInRadius(const float* queryPoint, float extraRadius)
{
    // +0x04: pointer to first node in the query list
    // +0x08: pointer to result list head (will be populated)
    Node* currentNode = *(Node**)(this + 4);
    *(uint32_t*)(this + 8) = 0; // Clear result list head

    while (currentNode)
    {
        // Each node contains:
        // +0x10: pointer to an object with 3D position at offsets (0x80, 0x84, 0x88)
        // +0x24: pointer to a structure containing radius at +0x0C
        // +0x2C: next node pointer
        // +0x34: link for result list (will be set)
        void* object = *(void**)(currentNode + 0x10);
        // Access thread-local storage to get dynamic position offset (likely 0 in practice)
        // FS:[0x2C] gives TLS array; offset at TLS base +8 provides the actual offset.
        uint32_t* tlsBase = *(uint32_t**)(*(uint32_t*)(__readfsdword(0x2C)) + 8);
        int32_t posOffset = *tlsBase; // This may be zero, simplifying to fixed offsets
        float dx = queryPoint[0] - *(float*)(object + 0x80 + posOffset);
        float dy = queryPoint[1] - *(float*)(object + 0x84 + posOffset);
        float dz = queryPoint[2] - *(float*)(object + 0x88 + posOffset);
        float nodeRadius = *(float*)(*(uint32_t*)(currentNode + 0x24) + 0xC);
        float combinedRadius = nodeRadius + extraRadius;
        if (dx*dx + dy*dy + dz*dz < combinedRadius * combinedRadius)
        {
            // Link node into result list (singly-linked via +0x34)
            *(uint32_t*)(currentNode + 0x34) = *(uint32_t*)(this + 8);
            *(uint32_t*)(this + 8) = (uint32_t)currentNode;
        }
        currentNode = *(Node**)(currentNode + 0x2C);
    }
}