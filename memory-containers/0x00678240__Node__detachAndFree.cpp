// FUNC_NAME: Node::detachAndFree
// Function at 0x00678240: Detaches a node from multiple intrusive linked lists and frees its memory.
// The node (this) stores pointers to "link" structures (with headers containing index and data).
// Each link is checked against a sentinel (head of list) in the owning container.
// If not sentinel, the link is removed from the hash table (or array) and its memory is freed.
// Finally, the node itself is removed from an additional list and freed.

extern void DAT_01206694(void* ptr); // custom memory deallocation (pool allocator)

struct Node; // forward declaration
struct Container { // +0x00: vtable?; fields determined from usage
    int field_0x00;
    int count;         // +0x04
    int* hashTable;    // +0x0c
    int* headList1;    // +0x34
    int* headList2;    // +0x38
    int* headList3;    // +0x40
    int flagList1;     // +0x6c
    int flagList2;     // +0x70
    int flagList3;     // +0x78
};

struct Node { // size > 0x68
    Container* owner;       // +0x00
    int field_0x04;
    // ...
    // Each "link" is a structure with header: [-0x10] data?, [-0x08] index into hashTable
    // The field stores a pointer to the "link" data area (or to node itself?)
    int* linkData1;         // +0x3c (offset 0xf words)
    int* linkData2;         // +0x50 (offset 0x14 words)
    int* linkData3;         // +0x58 (offset 0x16 words)
    int* linkData4;         // +0x64 (offset 0x19 words)
    // ...
};

__thiscall void Node::detachAndFree(void)
{
    Container* container;
    int* linkPtr;
    int* linkData;
    int* thisData;

    // If this is null, return
    if (this == 0) {
        return;
    }

    container = this->owner;

    // --- Handle linkData2 (offset 0x50) ---
    linkData = this->linkData2;
    if (linkData == container->headList2) {
        // This link is the head of list2, just set flag
        container->flagList2 = 1;
    }
    else if (linkData != 0) {
        // Remove link from hash table using its index (stored at linkData[-2])
        container->hashTable[*(int*)(linkData - 2)] = 0;
        container->count--;
        DAT_01206694(linkData - 4); // free link structure (header at -0x10?)
    }

    // --- Handle linkData1 (offset 0x3c) ---
    linkPtr = this->linkData1;
    // Check if linkData1 is not the sentinel (this + 5 words = &this->linkData2? or special value)
    if ( (linkPtr != (int*)(this + 5)) && (container = this->owner, linkPtr != 0) ) {
        // Remove from hash table using index at linkPtr[-2]
        container->hashTable[*(int*)(linkPtr - 2)] = 0;
        container->count--;
        DAT_01206694(linkPtr - 4); // free
    }

    // --- Handle linkData4 (offset 0x64) ---
    container = this->owner;
    linkData = this->linkData4;
    if (linkData == container->headList3) {
        container->flagList3 = 1;
    }
    else if (linkData != 0) {
        container->hashTable[*(int*)(linkData - 2)] = 0;
        container->count--;
        DAT_01206694(linkData - 4);
    }

    // --- Handle linkData3 (offset 0x58) ---
    linkData = this->linkData3;
    container = this->owner;
    if (linkData != 0) {
        container->hashTable[*(int*)(linkData - 2)] = 0;
        container->count--;
        DAT_01206694(linkData - 4);
    }

    // --- Finally remove the node itself from list1 ---
    container = this->owner;
    if (this == container->headList1) {
        container->flagList1 = 1;
        return;
    }
    // Remove node from hash table using index stored at this[-2]
    container->hashTable[*(int*)(this - 2)] = 0;
    container->count--;
    DAT_01206694(this - 4); // free node itself
}