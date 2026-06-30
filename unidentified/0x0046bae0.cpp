// FUN_0046bae0: EARSObject::attachToParent
// Attaches this EARSObject as a child of the given parent.
// Parent's child list head is stored at offset 0x48.
// This object's first field (offset 0) stores a pointer to the parent's childListHead pointer location.
// Second field (offset 4) stores the next sibling pointer.
// The list is singly linked, inserting at the front.

class EARSObject {
public:
    int *m_ppParentList; // +0x00: pointer to parent's childListHead pointer
    EARSObject *m_pNext; // +0x04: next sibling
    // Parent has at +0x48: EARSObject* childListHead;
    // At +0x4C: unknown, used as next pointer for the first child?
};

int *__thiscall EARSObject::attachToParent(EARSObject *this, EARSObject *parent) {
    int *newListHeadPtr = (parent != nullptr) ? (int*)((char*)parent + 0x48) : nullptr;

    if (this->m_ppParentList != newListHeadPtr) {
        if (this->m_ppParentList != nullptr) {
            // Remove from current parent
            FUN_004daf90(this);
        }
        this->m_ppParentList = newListHeadPtr;
        if (newListHeadPtr != nullptr) {
            // Insert at front: current head's next (at newListHeadPtr+4) becomes this->m_pNext,
            // then set that to this.
            this->m_pNext = (EARSObject*)*(newListHeadPtr + 1); // newListHeadPtr+1 is offset 4
            *(EARSObject**)(newListHeadPtr + 1) = this;
        }
    }
    return (int*)this;
}