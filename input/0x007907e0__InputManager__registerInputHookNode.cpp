// FUNC_NAME: InputManager::registerInputHookNode
// Address: 0x007907e0
// Registers an input hook node into a linked list of hooks and initializes it with a vtable pointer.
// The function takes a 'this' pointer (InputManager), an argument (likely controller slot or hook ID),
// and uses a global vtable table (PTR_FUN_00d5dbbc) and static data (DAT_01205228, DAT_0112ad8c).
// The stack is used as a temporary node structure which is passed to FUN_00408bf0 for final initialization.

void __thiscall InputManager::registerInputHookNode(void* thisPtr, uint32_t hookArg) {
    struct HookNode {
        uint32_t magic;               // +0x00: initialized from DAT_0112ad8c
        void* vtablePtr;              // +0x04: pointer to vtable (global PTR_FUN_00d5dbbc)
        uint8_t flags;                // +0x08: set to 0
        uint32_t nodeSpecificData;    // +0x0C: from param_2 (hookArg)
        int linkedListNode;           // +0x10: used for list insertion
        int* nextLink;                // +0x14: pointer to linked list next field
        // ... additional fields from stack
    };

    HookNode tempNode;
    memset(&tempNode, 0, sizeof(tempNode)); // implicit zeroing from locals

    // Initialize the temporary node structure
    tempNode.magic = DAT_0112ad8c;                    // static global
    tempNode.vtablePtr = (void*)&PTR_FUN_00d5dbbc;   // global vtable pointer
    tempNode.flags = 0;
    tempNode.nodeSpecificData = hookArg;

    // Linked list insertion (using in_EAX as current head of list)
    // in_EAX is the return value of a previously called function (likely allocator or creation)
    if (in_EAX != 0) {
        // Save the old "next" pointer from the node at in_EAX+0x4c
        tempNode.nextLink = *(int**)(in_EAX + 0x4c);
        // Set the node's next to point to the address of tempNode.linkedListNode (on stack)
        *(int**)(in_EAX + 0x4c) = &tempNode.linkedListNode;
        // Set the stack's linked list head to point to in_EAX+0x48 (the node's link field)
        tempNode.linkedListNode = (int)(in_EAX + 0x48);
    }

    // Adjust this pointer for the initialization call: if thisPtr is zero, keep zero; else add 0x3C
    uint32_t adjustedThis = (thisPtr == 0) ? 0 : ((uint32_t)thisPtr + 0x3C);

    // Call initialization routine with the temporary node and adjusted pointer
    FUN_00408bf0(&tempNode, adjustedThis, 0);

    // Clean up: if the stack linked list was modified, remove this node from the list
    if (tempNode.linkedListNode != 0) {
        FUN_004daf90(&tempNode.linkedListNode);
    }
}