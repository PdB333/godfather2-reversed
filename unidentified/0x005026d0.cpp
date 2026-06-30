// FUN_NAME: EARSObject::EARSObject
void __fastcall EARSObject::EARSObject(EARSObject* this) {
    // Set base class vtable pointer (likely calls base class constructor)
    this->vtable = &PTR_FUN_00e37e18;
    FUN_004ebba0(); // Base class constructor (e.g., EARSBaseObject::EARSBaseObject)
    // Set derived class vtable
    this->vtable = &PTR_FUN_00e37110;

    // Add this object to global object list (likely a doubly-linked list)
    int* pNext = this->mNext; // +0x10: next pointer in object
    if (pNext != 0) {
        // Global object manager at DAT_01206880, list head pointer at offset 0x14
        ObjectManager* pMgr = (ObjectManager*)DAT_01206880;
        int** ppHead = (int**)((char*)pMgr + 0x14); // pointer to head node pointer
        // Insert at head: head->next = &sentinelNode
        *(void***)(*ppHead) = &PTR_LAB_01123be8; // sentinel node address
        *ppHead = *ppHead + 4; // move to next field? Possibly adjusting
        // Set sentinel's next to our object
        *((int*) *ppHead) = pNext; // our object's previous mNext value? Actually pNext is the original mNext from the object
        *ppHead = *ppHead + 4;
        // Clear the object's link fields
        this->mNext = 0;   // +0x10
        this->mPrev = 0;   // +0x14
    }
    return;
}