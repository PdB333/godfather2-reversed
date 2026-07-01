// FUNC_NAME: EARS::Framework::Link::insertBefore
// Address: 0x00877d70
// Purpose: Inserts a node into a doubly linked list, using a temporary stack-based head to manage the insertion.
// The function manipulates intrusive list pointers at offsets +0x48 (next) and +0x4c (prev).

void __thiscall Link::insertBefore(int thisPtr, int nextNodePtr)
{
    int oldPrev;               // saved previous pointer
    int tempHead;              // temporary stack head for list manipulation
    int tempNext;              // temporary stack next pointer
    int local4;                // unused placeholder
    char local18;              // padding/zero
    undefined4 local20;        // temporary object for initialization
    undefined*** local1c;      // vtable pointer area
    undefined** local14;       // vtable pointer
    undefined4 localC;         // saved value for second node's prev
    
    tempHead = 0;
    localC = 0;
    tempNext = 0;
    local4 = 0;

    // If this node is valid and its 'next' pointer is non-null (list not empty)
    if ( (thisPtr != 0) && (*(int*)(thisPtr + 0x48) != 0) )
    {
        // Save the old prev pointer of this node
        oldPrev = *(int*)(thisPtr + 0x4c);
        // Write the address of the local stack variable tempHead into this node's prev field
        // This effectively makes the stack variable act as the list head for the duration
        *(int**)(thisPtr + 0x4c) = &tempHead;
        // Store the address of this node's next field into tempHead (used as reference)
        tempHead = thisPtr + 0x48;
    }

    // Process the 'nextNode' parameter: if non-null, offset it to point to its next field
    if (nextNodePtr == 0)
    {
        nextNodePtr = 0;
    }
    else
    {
        nextNodePtr = nextNodePtr + 0x48; // now points to the next field of nextNode
    }

    // If the offset pointer is non-null, link it to the stack-based list
    if ( (nextNodePtr != 0) && (tempNext = 0, tempHead = nextNodePtr, nextNodePtr != 0) )
    {
        // Save the old prev pointer of the nextNode's node (pointed to by nextNodePtr+4)
        localC = *(int*)(nextNodePtr + 4);
        // Write the address of the stack variable tempHead into that prev field
        *(int**)(nextNodePtr + 4) = &tempHead;
    }

    // Initialize a temporary object (likely an iterator or list controller) with a vtable and a global
    local14 = &PTR_FUN_00d7666c;        // vtable pointer (global constant)
    local1c = &local14;                 // secondary pointer to vtable
    local20 = DAT_0112e12c;             // some global data
    local18 = 0;                        // zero init
    FUN_00408a00(&local20, 0);           // constructor call (placement new or init)

    // Clean up: if tempHead was set (i.e., we linked something), call removal/detach function on it
    if (tempHead != 0)
    {
        FUN_004daf90(&tempHead);         // likely detaches or releases the node
    }
    if (tempNext != 0)
    {
        FUN_004daf90(&tempNext);         // same for the second temp pointer
    }

    return;
}