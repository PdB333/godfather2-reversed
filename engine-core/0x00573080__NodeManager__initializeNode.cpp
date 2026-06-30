//FUNC_NAME: NodeManager::initializeNode
void NodeManager::initializeNode(MemoryAllocator* allocator)
{
    // Local allocation info struct (size 0x10)
    AllocationInfo allocInfo;
    allocInfo.field0 = 0;
    allocInfo.field4 = 0;
    allocInfo.field8 = 0;
    allocInfo.fieldC = 0;

    // Allocate a 0x40-byte node from the allocator
    Node* node = (Node*)allocator->allocate(0x40, &allocInfo);
    if (node == nullptr) {
        m_nodePtr = nullptr; // +0x28
    } else {
        // Initialize node fields
        node->field0 = 0;
        node->field4 = 0;
        node->field8 = FUN_004265d0(&allocInfo.field4, allocator); // Some initialization
        node->fieldC = allocator;

        // Call allocator's second virtual function (e.g., addRef or lock)
        allocator->vtable->function2();

        m_nodePtr = node; // +0x28
    }

    // Set up secondary pointer at node+0x10
    NodeSub* subPtr = (NodeSub*)(node + 4); // +0x10 offset
    if (subPtr == nullptr) {
        m_subPtr1 = nullptr; // +0x30
    } else {
        FUN_00573720(); // Initialize sub-structure
        m_subPtr1 = subPtr; // +0x30
    }

    // Set up tertiary pointer at node+0x28
    NodeSub2* sub2Ptr = (NodeSub2*)(node + 10); // +0x28 offset
    if (sub2Ptr != nullptr) {
        sub2Ptr->allocator = allocator;
        sub2Ptr->field0 = 0;
        sub2Ptr->field4 = 0;
        sub2Ptr->field8 = 0;
        sub2Ptr->fieldC = 0; // only one byte? Actually *(undefined1 *)(puVar1 + 0xe) = 0; so byte at offset 0x38
        sub2Ptr->field10 = 0;

        // Call allocator's second virtual function again
        allocator->vtable->function2();

        m_subPtr2 = sub2Ptr; // +0x2c
    } else {
        m_subPtr2 = nullptr; // +0x2c
    }

    FUN_00572f30(); // Final initialization
    m_extraField = 0; // +0x34
}