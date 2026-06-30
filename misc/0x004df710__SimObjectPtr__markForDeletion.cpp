// FUNC_NAME: SimObjectPtr::markForDeletion
// Address: 0x004df710
// Sets a high flag (0x20000000) on the referenced SimObject at offset +0x0C (mFlags)
// Used to mark an object for deletion or disable further processing.
void __thiscall SimObjectPtr::markForDeletion() {
    // this->mPtr is at +0x0
    if (this->mPtr != nullptr) {
        // Set flag 0x20000000 on the target object's flags at +0x0C
        this->mPtr->mFlags |= 0x20000000;  // SimObject::mFlags +0x0C
    }
}