// FUNC_NAME: GameObject::~GameObject
void __fastcall GameObject::~GameObject(GameObject* this) {
    int* pChildList;       // derived from this[8] (offset +0x20) - linked list of child object IDs
    int childId;
    int* pWalk;            // walk pointer through child list

    pChildList = (int*)this[8];                       // +0x20: pointer to array of 2-int pairs (childId, nextPtr?)
    // Set vtable pointers to base class versions (destructor phase)
    *(int**)this = &PTR_FUN_00e30ff0;                 // +0x00: first vtable (class-specific)
    this[1] = (int)&PTR_LAB_00e31000;                 // +0x04: second vtable or data pointer
    this[2] = (int)&PTR_LAB_00e31004;                 // +0x08: third pointer

    // Traverse and destroy all children in the list
    childId = *pChildList;
    while (childId != 0) {
        FUN_004639e0(childId);                        // deallocate/remove child object (or reference)
        pWalk = pChildList + 2;                       // skip the childId and next pointer?
        pChildList = pChildList + 2;                  // advance to next 2-int node
        childId = *pWalk;                             // read next childId
    }

    // Call the actual base destructor chain
    FUN_0043cf50(this);                               // likely base class destructor (single inheritance)
    FUN_00446a10();                                   // global engine cleanup (e.g., release system handles)
    FUN_00408310(&DAT_0120e924);                       // remove from a global tracker list
    FUN_00408310(&DAT_0120e91c);                       // remove from another tracker list
    // Call virtual destructor from second base class via vtable at offset +0x0C
    (*(void (__thiscall**)(void))(*((int*)this[3]) + 0xC))();
    if (this[4] != 0) {                               // +0x10: pointer to addon data or resource
        FUN_009c8f10((void*)this[4]);                 // free that resource
    }
    // Final vtable adjustment to the most base class
    this[2] = (int)&PTR_LAB_00e31008;                 // +0x08: last vtable pointer
    DAT_01223418 = 0;                                 // clear global instance counter
    *(int**)this = &PTR_LAB_00e30fe0;                 // +0x00: base vtable (e.g., Object)
}