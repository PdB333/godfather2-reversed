// FUNC_NAME: EntityManager::createEntityNode
int __thiscall EntityManager::createEntityNode(EntityManager *this, int *pTransformData, int parentId) {
    bool bAllocatedNew;
    char cCanCreate;
    int *pEntity;
    undefined4 *pAllocVtable;
    int iAllocSize;

    // Check if creation is allowed (vtable[0x14] expects a pointer to transformData)
    cCanCreate = (**(code **)(*(int *)this + 0x14))(pTransformData);
    if (cCanCreate == '\0') {
        return 0;
    }

    bAllocatedNew = true;
    // Try to find an existing entity by its transform key
    pEntity = (int *)findEntityByTransform(pTransformData);
    if (pEntity == (int *)0x0) {
        bAllocatedNew = false;
        // Get allocator vtable from global memory manager
        pAllocVtable = (undefined4 *)getMemoryAllocator();
        // Allocate memory for new entity (size 0x70)
        iAllocSize = (**(code **)*pAllocVtable)(0x70, &stack0xfffffff0);
        if (iAllocSize != 0) {
            // Create default entity object (constructor-like call)
            pEntity = (int *)createDefaultEntity();
            if (pEntity != (int *)0x0) goto LAB_00832aed;
        }
        return 0;
    }

LAB_00832aed:
    // Copy transform data (4 ints) from input to entity at offset 0x1C (pEntity[7])
    pEntity[7] = *pTransformData;    // +0x1C: positionX or element0
    pEntity[8] = pTransformData[1];  // +0x20: positionY or element1
    pEntity[9] = pTransformData[2];  // +0x24: positionZ or element2
    pEntity[10] = pTransformData[3]; // +0x28: w or element3

    // If this has a parent entity (stored at this[2] i.e., offset 8)
    iAllocSize = this->parentEntity; // this+8
    if (iAllocSize != 0) {
        // Copy parent's world transform (at parent+0x24) into entity at offset 0x3C (pEntity[0xF])
        pEntity[0xF] = *(int *)(iAllocSize + 0x24);  // +0x3C: parentTransform0
        pEntity[0x10] = *(int *)(iAllocSize + 0x28); // +0x40: parentTransform1
        pEntity[0x11] = *(int *)(iAllocSize + 0x2C); // +0x44: parentTransform2
        pEntity[0x12] = *(int *)(iAllocSize + 0x30); // +0x48: parentTransform3
    }

    // If a parent id is provided, attach entity to that parent (vtable[4])
    if (parentId != 0) {
        (**(code **)(*pEntity + 4))(parentId);
    }

    // If we allocated a new entity now, register it in the manager's list
    if (!bAllocatedNew) {
        registerEntity((int)pEntity);
    }
    return 1;
}