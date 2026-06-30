// FUNC_NAME: EntityManager::createEntity
int __thiscall EntityManager::createEntity(
    int this,
    int* beforeIt,
    int* afterIt,
    uint initParam,
    int priority,
    uint data0,
    uint data1,
    uint data2
)
{
    int* piVar3;
    uint uVar5;
    int iVar6;
    int iVar7;
    uint localStack[3];
    undefined4* pNode;

    // Get the next iterator: if current node's data is 0, it's end (null),
    // otherwise advance to next node.
    if (*beforeIt == 0) {
        beforeIt = nullptr;
    } else {
        beforeIt = (int*)beforeIt[2];
    }

    // Same for after iterator
    if (*afterIt == 0) {
        iVar7 = 0;
    } else {
        iVar7 = afterIt[2];
    }

    // Access global game manager and its entity pool
    int* gameManager = *(int**)(DAT_01223520 + 0x2c); // GodfatherGameManager +0x2c
    // Pool free list count
    int* entityPool = *(int**)(gameManager + 0x14); // pool->count
    if (entityPool == nullptr) {
        return 0;
    }

    // Try to pop from free list (pool->freeListHead at +0x8)
    pNode = *(undefined4**)(gameManager + 8); // pool->freeList
    if (pNode == nullptr) {
        // If no free list, try to allocate via pool's allocator (vtable at +0x1c)
        int** allocatorVtable = *(int***)(gameManager + 0x1c);
        if (allocatorVtable != nullptr) {
            pNode = (undefined4*)
                    (**(code**)(*allocatorVtable + 4)) // allocator->allocate(size, data)
                    (*(undefined4*)(gameManager + 0xc), // unknown arg
                     *(undefined4*)(gameManager + 0x10)); // unknown arg
        }
        if (pNode == nullptr) {
            goto LAB_005f77a1;
        }
    } else {
        // Pop from free list
        uVar5 = *(int*)(gameManager + 0x14) - 1; // pool->count--
        *(undefined4*)(gameManager + 8) = *pNode; // pool->freeList = pNode->next
        *(uint*)(gameManager + 0x14) = uVar5;
        if (uVar5 < *(uint*)(gameManager + 0x18)) {
            *(uint*)(gameManager + 0x18) = uVar5; // update low watermark
        }
    }

    // Initialize the entity
    iVar6 = initializeEntity(piVar3, initParam); // FUN_005f6510
    if (iVar6 != 0 && priority >= 0) {
        *(int*)(iVar6 + 0x2c) = priority; // entity->priority
    }

LAB_005f77a1:
    // Set additional data fields
    *(uint*)(iVar6 + 0x44) = data0;  // entity +0x44
    *(uint*)(iVar6 + 0x4c) = data1;  // entity +0x4c (likely ID or pointer)
    *(uint*)(iVar6 + 0x48) = data2;  // entity +0x48

    if (beforeIt == (int*)iVar7) {
        // If both iterators point to the same element, set flags (bit0 and bit3)
        *(uint*)(iVar6 + 0x38) |= 9;
    } else {
        // Otherwise, add to spatial tree using parent from this+0x24
        addToSpatialTree(iVar6, *(undefined4*)(this + 0x24)); // FUN_005f8520
    }

    // Allocate a notification node (12 bytes) using a custom allocator from this+0x34
    uint someId = *(uint*)(this + 0x4c); // this->someId
    undefined4* context = *(undefined4**)(this + 0x38);
    if (context == nullptr) {
        localStack[0] = 0;
        localStack[1] = 0;
        localStack[2] = 0;
        context = localStack;
    }

    // vtable call at this+0x34: first method (alloc) takes size and context
    undefined4* allocVtable = *(undefined4**)(this + 0x34);
    pNode = (undefined4*)(**(code**)(*allocVtable))(0xc, context);

    if (pNode != nullptr) {
        *pNode = someId;                     // node->data0 = someId
        *(pNode + 1) = localStack[1];        // node->data1 = 0
        *(pNode + 2) = iVar6;                // node->data2 = created entity
    }

    // Notify that entity was created (FUN_005f9d10)
    notifyEntityCreated();

    // Insert node into a global list (head at unaff_EBX + 4)
    // unaff_EBX is likely a global pointer to a list head struct
    *(int**)(unaff_EBX + 4) = pNode;  // head->next = node
    *(int**)(*pNode[1]) = pNode;      // node->next->prev = node? (debug: pNode[1] was set to 0, this is problematic)

    return iVar6;
}