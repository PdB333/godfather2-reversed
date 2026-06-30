// FUNC_NAME: ResourceManager::registerResource
// At address 0x007651e0 – Registers a resource descriptor and returns a pointer to the created resource node.
// The descriptor is identified by a magic number (0x6862a74c). The node is linked into an intrusive list
// owned by 'this' (offset +0x64 stores the head pointer to the 'next' field of the first node).
// The node receives vtable-like function pointers and copies transform data from 'this'.

// Note: This function is part of the EARS asset management system.
// Caller provides a descriptor (param_2), the function initializes a node from it.

int __thiscall ResourceManager::registerResource(void* thisPtr, ResourceDescriptor* descriptor)
{
    int* ppListSlot;     // pointer to the "next" pointer slot in the manager (offset +0x64)
    ResourceDescriptor* descriptorNext; // descriptor->next (offset +0x14)
    ResourceNode* node;  // base of the created resource node

    // Validate descriptor type using a magic number from its vtable
    int descriptorType = descriptor->vtable->typeCheck();
    if (descriptorType != 0x6862a74c)
    {
        return 0; // invalid type
    }

    ppListSlot = (int*)((char*)thisPtr + 100); // +0x64: pointer to list head
    descriptorNext = descriptor + 0x14; // &descriptor->next

    // If the list head does not already point to this descriptor's 'next' field,
    // free the old node (if any) and link this descriptor into the list.
    if ((ResourceDescriptor*)*ppListSlot != descriptorNext)
    {
        if (*ppListSlot != 0)
        {
            // Free or detach previous node
            FUN_004daf90(ppListSlot);
        }
        *ppListSlot = (int)descriptorNext;
        if (descriptorNext != 0)
        {
            // Save the previous back pointer into thisPtr->prevNode (offset +0x68)
            *(int*)((char*)thisPtr + 0x68) = descriptor->backPointer;
            // Set the descriptor's back pointer to our list slot
            descriptor->backPointer = ppListSlot;
        }
    }

    // Compute base address of the resource node (subtract 0x50 from the next pointer)
    node = (*ppListSlot != 0) ? (ResourceNode*)(*ppListSlot - 0x50) : 0;
    if (node == 0)
        return 0;

    // Set up virtual function table entries (bound method pointers) at node+0x90
    node->funcTable[0] = ((long long)&LAB_00765050 << 32) | (unsigned int)thisPtr;
    node->funcTable[1] = ((long long)stackVar2 << 32) | (unsigned int)stackVar1; // stack locals (uninitialized? preserved)
    node->funcTable[2] = ((long long)&LAB_00765000 << 32) | (unsigned int)stackVar3;

    // Another vtable-like block at node+0x78
    node->funcTable2[0] = ((long long)FUN_007347e0 << 32) | *(unsigned int*)((char*)thisPtr + 0x50);
    node->funcTable2[1] = (unsigned long long)stackVar2 << 32;
    node->funcTable2[2] = ((long long)&LAB_007648f0 << 32) | (unsigned int)stackVar3;

    // Clear bit 0 of flag at node+0xa8
    node->flags &= ~1;

    // Initialize substructure at thisPtr+0x58
    FUN_0075cd50((char*)thisPtr + 0x58);

    // Copy three 8‑byte transform blocks from thisPtr to the node
    node->transform1[0] = *(long long*)((char*)thisPtr + 0x70);
    node->transform1[1] = *(long long*)((char*)thisPtr + 0x78);
    node->transform1[2] = *(long long*)((char*)thisPtr + 0x80);

    node->transform2[0] = *(long long*)((char*)thisPtr + 0xa0);
    node->transform2[1] = *(long long*)((char*)thisPtr + 0xa8);
    node->transform2[2] = *(long long*)((char*)thisPtr + 0xb0);

    // Optionally set a persistent flag on the node if bit 2 of thisPtr+0x6c is set
    if ((*(unsigned int*)((char*)thisPtr + 0x6c) >> 2) & 1)
    {
        node->persistentFlag = 1; // actually sets bit 24 (0x1000000) at node+0x58
    }

    return (int)node;
}

// Hypothetical structures (for readability)
struct ResourceDescriptor
{
    void* vtable; // first entry has function that returns magic
    int backPointer; // offset 0x15 (0x54)
    // ... other fields
    int next; // offset 0x14 (0x50)
};

struct ResourceNode
{
    // +0x58: flags
    int flags;
    // +0x78: funcTable2[3]
    long long funcTable2[3];
    // +0x90: funcTable[3]
    long long funcTable[3];
    // +0xa8: flags
    int flags2;
    // +0xd8: transform1[3]
    long long transform1[3];
    // +0x134: transform2[3]
    long long transform2[3];
    // +0x144: end
};