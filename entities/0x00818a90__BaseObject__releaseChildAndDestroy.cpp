//FUNC_NAME: BaseObject::releaseChildAndDestroy
void __fastcall BaseObject::releaseChildAndDestroy(BaseObject* this) {
    // If the child object pointer at offset +0x4 is non-null
    if (this->childObject != nullptr) {
        // Call virtual function at vtable offset +0x4 to release the child (passing 0 as a flag)
        (this->vtable->releaseChild)(this->childObject, 0);
        this->childObject = nullptr;
    }
    // Call virtual destructor at vtable offset +0xC
    (this->vtable->destructor)();
}