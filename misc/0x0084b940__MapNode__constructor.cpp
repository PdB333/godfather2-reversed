// FUNC_NAME: MapNode::constructor
void __thiscall MapNode::constructor(int* this, int containerPtr, KeyValueData* data, int extra1, int extra2, int extra3)
{
    // Set vtable pointer (class identification)
    this[0] = (int)&MapNode_vtable;

    // Adjust container pointer: if not null, advance by 0x48 to reach the list sentinel or bucket head
    int* adjustedContainer;
    if (containerPtr == 0) {
        adjustedContainer = (int*)0;
    } else {
        adjustedContainer = (int*)(containerPtr + 0x48);
    }

    // Store adjusted container pointer (likely a pointer to the list head's "prev" field or similar)
    this[1] = (int)adjustedContainer;

    // Initialize next pointer to null
    this[2] = 0;

    // If container is valid, insert this node into the linked list
    if (adjustedContainer != 0) {
        // Save the old "next" pointer from the container's sentinel (at offset +0x4 from adjustedContainer)
        this[2] = *(int*)((int)adjustedContainer + 4);
        // Update the sentinel's next to point to this node's "prev" field (offset +0x4 from this)
        *(int**)((int)adjustedContainer + 4) = (int*)((int)this + 4);
    }

    // Copy the 12‑byte key/value block (8 bytes key, 4 bytes value)
    *(uint64_t*)(this + 3) = *(uint64_t*)data;          // // +0x0C: key
    this[5] = *(int*)((char*)data + 8);                   // // +0x14: value

    // Store extra parameters
    this[6] = extra1;   // // +0x18
    this[7] = extra2;   // // +0x1C
    this[8] = extra3;   // // +0x20
}