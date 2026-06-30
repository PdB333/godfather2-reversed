// FUNC_NAME: EARS::Framework::Object::~Object

void __fastcall EARS::Framework::Object::~Object(Object* this)
{
    uint* flagPtr;
    int nodeToRemove;
    undefined4* prevNext;
    undefined4* curNode;
    int* memManagerFreeSlots;

    // Step 1: Set vtable to base class vtable (calls base destructor chain)
    *(int*)this = (int)&PTR_FUN_00e37bf0;

    // Call destructor for embedded sub-object at offset 0x24 (this + 9 * 4)
    FUN_0043e500(this + 9);

    // Set destruction flag (bit 0) in a thread-local structure
    // this->field_4 (offset 0x10) is used as an offset into a per-thread memory state
    flagPtr = (uint*)(*(int*)(**(int**)(__readfsdword(0x2c) + 8) + this->field_4));
    *flagPtr |= 1;

    // Remove this object from a circular doubly-linked list
    // List head is stored at this + 0x3C (offset 0xF * 4)
    // The node being removed is this->listNode (value at offset 0x3C)
    nodeToRemove = this->listNode; // +0x3C
    if (nodeToRemove != 0)
    {
        // nodeToRemove->next is at node + 4
        if (*(undefined4**)(nodeToRemove + 4) == (undefined4*)(this + 0xF))
        {
            // If the next pointer points to the list head, update next to the previous node
            *(undefined4*)(nodeToRemove + 4) = this->prevNode; // +0x40 (offset 0x10 * 4)
        }
        else
        {
            // Otherwise, find the node whose next points to the list head
            curNode = *(undefined4**)(nodeToRemove + 4);
            while (curNode != (undefined4*)(this + 0xF))
            {
                prevNext = (undefined4*)curNode[1]; // node->next
                curNode = prevNext;
            }
            // Update that node's next to this->prevNode, effectively removing the head
            *(undefined4*)((int)prevNext + 4) = this->prevNode; // +0x40
        }
    }

    // Step 2: Set vtable to another base vtable (final destructor step)
    *(int*)this = (int)&PTR_FUN_00e37110;

    // If the object owns a memory block (offset 0x10), return it to the global free list
    if (this->memBlock != 0) // +0x10
    {
        // Global memory manager at DAT_01206880, free slots pointer at offset 0x14
        memManagerFreeSlots = (int*)(DAT_01206880 + 0x14);

        // Initialize a new free slot (pointer chain)
        **(undefined4**)(DAT_01206880 + 0x14) = (undefined4*)&PTR_LAB_01123be8;
        *memManagerFreeSlots = *memManagerFreeSlots + 4;
        *(int*)*memManagerFreeSlots = this->memBlock;
        *memManagerFreeSlots = *memManagerFreeSlots + 4;

        // Clear the memory block fields
        this->memBlock = 0;     // +0x10
        this->memBlockSize = 0; // +0x14 (offset 5 * 4)
    }
}