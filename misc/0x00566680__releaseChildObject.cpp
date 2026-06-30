// FUNC_NAME: releaseChildObject

// Address: 0x00566680
// Releases a child object at offset +0xC via its virtual destructor, then clears the pointer.

int __thiscall releaseChildObject(void* thisPtr) {
    // Pointer to child object stored at offset +0xC
    void** childObj = *(void***)((char*)thisPtr + 0xC);
    if (childObj != nullptr) {
        // Call the first virtual function (typically destructor) on child
        (*(void (__thiscall**)(void*))(*childObj))(childObj);
        // Clear the pointer to avoid dangling reference
        *(void***)((char*)thisPtr + 0xC) = nullptr;
    }
    return 1;
}