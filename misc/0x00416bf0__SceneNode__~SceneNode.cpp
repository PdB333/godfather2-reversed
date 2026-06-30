// FUNC_NAME: SceneNode::~SceneNode

// Destructor for a scene graph node in the EARS engine.
// Offset 0x00: vtable pointer
// Offset 0x08: m_pTransform (pointer to a transform component)
// Offset 0x0C: m_pAttachment (pointer to an attached object, e.g., child mesh or script)
// Offset 0x62: m_flags (bit 2 indicates the node is "live" in the scene manager's update stack)

void __thiscall SceneNode::~SceneNode(void *thisPtr) {
    SceneNode *node = (SceneNode *)thisPtr;

    // First vtable switch to a special destructor vtable (prevents further virtual dispatch on partially destroyed object)
    node->vtable = (VTable *)&PTR_FUN_00e2f858; // Destructor-in-progress vtable

    // Check if node is currently registered in the scene manager's update stack
    if ((node->m_flags & 0x4) != 0) {
        // Call virtual function at vtable+0x20 on the transform component's sub-object
        // The transform component (at +0x08) contains a nested object at offset +0x08 (its own subcomponent).
        // The call retrieves a 32-bit value (likely a tick count or accumulator).
        void *transform = node->m_pTransform;                         // +0x08
        void *subComponent = *(void **)((char *)transform + 8);      // transform->m_pSubComponent
        VTable *subVtable = *(VTable **)subComponent;                // subComponent->vtable
        uint32 tickValue = ((uint32 (__thiscall *)(void *))subVtable[8])(); // index 0x20 / 4 = 8

        // Stack-based notification to the scene manager (DAT_01206880)
        // The scene manager uses a custom stack pointer at offset +0x14.
        // We push a control label (PTR_LAB_01124668) followed by the node and the tick value.
        uint32 *stackPtr = (uint32 *)(*(uint32 *)(DAT_01206880 + 0x14)); // Global scene manager +0x14 (stack pointer)
        *stackPtr = (uint32)&PTR_LAB_01124668;                           // Write label
        stackPtr++;                                                       // Advance
        *stackPtr = (uint32)node;                                         // Push this node
        stackPtr++;                                                       // Advance
        *stackPtr = tickValue;                                            // Push tick value
        stackPtr++;                                                       // Advance
        // Update the scene manager's stack pointer (but the original code does not update it back? Actually it updates through piVar2 which is pointer to that offset)
        *(uint32 *)(DAT_01206880 + 0x14) = (uint32)stackPtr;             // Write back the new stack pointer
    }

    // Call virtual function at vtable+0x54 on the same subcomponent (deferred cleanup)
    void *transform = node->m_pTransform;
    void *subComponent = *(void **)((char *)transform + 8);
    VTable *subVtable = *(VTable **)subComponent;
    ((void (__thiscall *)(void *))subVtable[0x15])(); // index 0x54 / 4 = 0x15

    // Second vtable switch to "deleting" vtable (prepares for memory release)
    node->vtable = (VTable *)&PTR_FUN_00e353e0;

    // Free attached object if it exists (e.g., a child node or resource)
    if (node->m_pAttachment != NULL) {
        FUN_004a6400(); // Custom memory deallocation function (likely frees a buffer)
    }

    // Call the destructor of the attached object directly (with delete flag = 1)
    if (node->m_pAttachment != NULL) {
        VTable *attachVtable = *(VTable **)node->m_pAttachment;
        ((void (__thiscall *)(void *, int))attachVtable[0])(node->m_pAttachment, 1); // operator delete attached
    }

    // Final vtable switch to base class vtable (completes destruction)
    node->vtable = (VTable *)&PTR_LAB_00e2f638;

    return;
}