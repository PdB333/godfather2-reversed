// FUN_004f9480: EAObject::getHandleIfActive
// Function at 0x004f9480: Returns a handle if a flag is set, otherwise 0.
undefined4 EAObject::getHandleIfActive(EAObject* this, int isActive) {
    if (isActive != 0) {
        return this->getHandle(); // calls FUN_004f8e60(this)
    }
    return 0;
}