// FUNC_NAME: ListContainer::setHeadObject
void __thiscall ListContainer::setHeadObject(void* this, ListableObject* obj) {
    int** headPtrSlot = (int**)((char*)this + 0x1e90); // pointer to head pointer
    int* newHead = nullptr;
    if (obj != nullptr) {
        newHead = (int*)((char*)obj + 0x48); // embedded link node offset in ListableObject
    }

    int** currentHead = (int**)*headPtrSlot; // current head pointer
    if (currentHead != newHead) {
        if (currentHead != nullptr) {
            FUN_004daf90(headPtrSlot); // remove current head from list (pop)
        }
        *headPtrSlot = newHead; // set new head
        if (newHead != nullptr) {
            // Save old backlink of new head (pointer to previous location)
            *(int**)((char*)this + 0x1e94) = *(int**)(newHead + 1); // offset 0x4 within link node
            // Set new head's backlink to point to the head pointer slot
            *(newHead + 1) = headPtrSlot;
        }
    }
}