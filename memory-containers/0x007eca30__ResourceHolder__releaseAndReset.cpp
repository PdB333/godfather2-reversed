// FUNC_NAME: ResourceHolder::releaseAndReset
void __thiscall ResourceHolder::releaseAndReset() {
    // Check if child pointer (at offset +4) is non-null
    if (this->child != 0) {
        // Call virtual function at vtable offset +4 on child, passing 0 as argument
        // This likely releases or decrements reference count
        this->child->release(0); // child's vtable+4
        this->child = 0; // Set pointer to null
    }
    // Call virtual function at vtable offset +0xC on this object
    // Typically performs further cleanup or reset of the holder itself
    (*(void (__thiscall *)(ResourceHolder*))((int*)this->vtable + 3))(); // vtable+0xC = index 3
}