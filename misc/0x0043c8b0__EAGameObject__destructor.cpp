// FUNC_NAME: EAGameObject::destructor
void __thiscall EAGameObject::destructor(EAGameObject* this) {
    // +0x00: pointer to first child in singly linked list
    EAGameObject* child = this->childList;
    while (child != nullptr) {
        // +0x04: next child in the list (singly linked)
        EAGameObject* nextChild = child->next;
        // vtable slot 1 (offset +0x04 from vtable pointer) – "release" with flag=0
        typedef void (__thiscall *ReleaseFunc)(EAGameObject*, int);
        ReleaseFunc release = (ReleaseFunc)(child->vtable[1]);
        release(child, 0);
        child = nextChild;
    }

    // +0x0C: another child pointer (e.g., exclusive child, parent, or alternate)
    if (this->otherObject != nullptr) {
        typedef void (__thiscall *ReleaseFunc)(EAGameObject*, int);
        ReleaseFunc release = (ReleaseFunc)(this->otherObject->vtable[1]);
        release(this->otherObject, 0);
    }

    // +0x10: vtable pointer
    // vtable slot 3 (offset +0x0C from vtable pointer) – final cleanup
    typedef void (__thiscall *FinalizeFunc)(EAGameObject*);
    FinalizeFunc finalize = (FinalizeFunc)(this->vtable[3]);
    finalize(this);
}