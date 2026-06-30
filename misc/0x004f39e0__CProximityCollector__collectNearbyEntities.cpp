// FUNC_NAME: CProximityCollector::collectNearbyEntities
void __fastcall CProximityCollector::collectNearbyEntities(CProximityCollector* this, const Vector3* queryPoint, float extraRadius)
{
    CNode* current;

    // +0x04: pointer to head of source list (list of all candidate nodes)
    // +0x08: head of result list (initially set to NULL)
    this->mResultHead = NULL;

    current = this->mSourceHead;
    if (current == NULL) {
        return;
    }

    // TLS pointer at FS:[0x2C] points to a global game context
    // Dereference to get a pointer to a global structure
    // +0x08: offset within that structure used as a sub-offset into entity's position array
    uint32_t offsetBase = *reinterpret_cast<uint32_t*>(__readfsdword(0x2CU));
    uint32_t posOffset = *reinterpret_cast<uint32_t*>(offsetBase + 8);

    do {
        // Each node has a pointer to an entity at +0x10
        void* entity = *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(current) + 0x10);

        // Entity's position is at base + posOffset (floats at +0x80, +0x84, +0x88)
        float dx = queryPoint->x - *reinterpret_cast<float*>(reinterpret_cast<uintptr_t>(entity) + 0x80 + posOffset);
        float dy = queryPoint->y - *reinterpret_cast<float*>(reinterpret_cast<uintptr_t>(entity) + 0x84 + posOffset);
        float dz = queryPoint->z - *reinterpret_cast<float*>(reinterpret_cast<uintptr_t>(entity) + 0x88 + posOffset);

        // Node's detection radius derived from component at +0x24->+0x0C + extraRadius
        float nodeRadius = *reinterpret_cast<float*>(*reinterpret_cast<uintptr_t*>(reinterpret_cast<uintptr_t>(current) + 0x24) + 0x0C) + extraRadius;

        // Compare squared distance to squared radius
        if (dx*dx + dy*dy + dz*dz < nodeRadius * nodeRadius) {
            // Insert this node at the head of the result list
            // +0x34 is used to store the previous head (next pointer within new list)
            *reinterpret_cast<uintptr_t*>(reinterpret_cast<uintptr_t>(current) + 0x34) = reinterpret_cast<uintptr_t>(this->mResultHead);
            this->mResultHead = current;
        }

        // Move to next node via +0x2C link
        current = reinterpret_cast<CNode*>(*reinterpret_cast<uintptr_t*>(reinterpret_cast<uintptr_t>(current) + 0x2C));
    } while (current != NULL);
}