// FUNC_NAME: releaseOwnedPointer

bool releaseOwnedPointer(void* container) {
    // container is a pointer to an object with a pointer at offset +0x08
    void* subObject = *(void**)((char*)container + 8);
    if (subObject != nullptr) {
        // Call virtual destructor via vtable
        (**(code**)subObject)();
        // Clear the pointer
        *(void**)((char*)container + 8) = nullptr;
        return true;
    }
    return false;
}