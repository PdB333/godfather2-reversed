// FUNC_NAME: ManagedList::clearLists
void __thiscall ManagedList::clearLists(ManagedList* this, ManagedList* otherList)
{
    // local variables used as temporary sentinels to detach list nodes
    int tempSentinel1 = 0; // local_8
    int tempSentinel2 = 0; // local_10
    undefined4 oldTailPrev = 0; // local_4
    undefined4 oldOtherTailPrev = 0; // local_c

    // Offset 0x48: node offset (list head sentinel)
    // Offset 0x4c: node + 4 (prev pointer of sentinel, points to last node)
    
    // Detach nodes from this list:
    if (this != nullptr && (this + 0x48) != nullptr) {
        oldTailPrev = *(undefined4*)((int)this + 0x4c); // save old tail pointer
        *(int**)((int)this + 0x4c) = &tempSentinel1;     // set tail to point to local stack sentinel
        tempSentinel1 = (int)this + 0x48;                // tempSentinel1 points to the head sentinel node
    }

    // Adjust otherList pointer to its sentinel node
    if (otherList == nullptr) {
        otherList = nullptr;
    } else {
        otherList = (ManagedList*)((int)otherList + 0x48); // point to sentinel node
    }

    // Detach nodes from other list (if non-null)
    if (otherList != nullptr) {
        oldOtherTailPrev = 0; // reset
        tempSentinel2 = (int)otherList; // tempSentinel2 points to other sentinel
        // The decompiler shows a conditional with nested assignments – effectively:
        // if (otherList != 0) { oldOtherTailPrev = *(int*)(otherList+4); *(int**)(otherList+4) = &tempSentinel2; }
        oldOtherTailPrev = *(undefined4*)((int)otherList + 4); // save old tail of other list
        *(int**)((int)otherList + 4) = &tempSentinel2;         // set its tail to point to local stack sentinel
    }

    // Stack-based cleanup object (likely a scoped destructor or list manager)
    undefined4 cleanupStruct[4]; // local_20 etc.
    cleanupStruct[0] = DAT_0112e05c;
    *(undefined4*)((int)cleanupStruct + 0xc) = 0;
    *(undefined**)((int)cleanupStruct + 4) = &PTR_FUN_00d7666c;
    *(undefined***)((int)cleanupStruct + 8) = (undefined***)&cleanupStruct[1];
    FUN_00408a00(cleanupStruct, 0); // likely destructor call (no effect here)

    // Delete all nodes from the detached lists
    if (tempSentinel1 != 0) {
        FUN_004daf90(&tempSentinel1); // deletes list starting from sentinel pointed by tempSentinel1
    }
    if (tempSentinel2 != 0) {
        FUN_004daf90(&tempSentinel2); // deletes list starting from sentinel pointed by tempSentinel2
    }

    return;
}