// FUNC_NAME: ObjectContainer::ClearList
// Address: 0x0092faf0
// Clears two parallel dynamic arrays of items, optionally deleting each item via a destructor function pointer stored in the item structure.
// Global index stored to DAT_0112ebb4 + 0x160 from this + 0x50 (first array count) is likely for debugging or reference.

typedef void (*ItemDestructor)(void*);

struct ListItem {
    void* object;          // +0x00
    int field04;           // +0x04 (unused in this function)
    int field08;           // +0x08 (unused in this function)
    ItemDestructor destructor; // +0x0C
};

void __thiscall ObjectContainer::ClearList(ObjectContainer* this, bool bDeleteItems)
{
    ListItem** pArray;
    ListItem* pItem;
    uint i;

    // Store first array count into global (maybe for debug log)
    *(uint*)(DAT_0112ebb4 + 0x160) = this->firstArrayCount; // this->firstArrayCount at +0x50

    DebugPrint("ClearList", 0, &DAT_00d88e88, 0); // DAT_00d88e88 is likely a string or format

    if (bDeleteItems) {
        // Delete all items in first array
        if (this->firstArrayCount != 0) {
            pArray = (ListItem**)this->firstArrayPtr; // +0x4C
            for (i = 0; i < this->firstArrayCount; i++) {
                pItem = pArray[i];
                if (pItem != nullptr) {
                    if (pItem->object != nullptr) {
                        pItem->destructor(pItem->object);
                    }
                    FreeListItem(pItem); // FUN_009c8eb0
                }
            }
        }
        this->firstArrayCount = 0;
        FreeArray(this->firstArrayPtr); // FUN_009c8f10
        this->firstArrayPtr = nullptr;
        this->firstArrayCapacity = 0; // +0x54

        // Delete all items in second array
        if (this->secondArrayCount != 0) {
            pArray = (ListItem**)this->secondArrayPtr; // +0x58
            for (i = 0; i < this->secondArrayCount; i++) {
                pItem = pArray[i];
                if (pItem != nullptr) {
                    if (pItem->object != nullptr) {
                        pItem->destructor(pItem->object);
                    }
                    FreeListItem(pItem);
                }
            }
        }
        this->secondArrayCount = 0;
        FreeArray(this->secondArrayPtr);
        this->secondArrayPtr = nullptr;
        this->secondArrayCapacity = 0; // +0x60
    }
}