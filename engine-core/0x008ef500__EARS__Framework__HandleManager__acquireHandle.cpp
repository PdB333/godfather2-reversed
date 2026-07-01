// FUNC_NAME: EARS::Framework::HandleManager::acquireHandle
void __thiscall HandleManager::acquireHandle(int this, Handle* handle)
{
    void* nodePtr;          // +0x00 from handle extraction
    void* objPtr;           // +0x04 from handle extraction
    void* currentObject;    // this->currentObject (offset 0x3c)
    void** result;          // return value of clearHandle

    if (handle != nullptr) {
        // Extract node pointer and object pointer from the handle
        EARS::Framework::HandleManager::decomposeHandle(&nodePtr, &handle);
        currentObject = *(void**)(this + 0x3c); // this->currentObject

        // Validate that the node belongs to this container (head pointer at this+0x38)
        if (nodePtr == nullptr || nodePtr != (void*)(this + 0x38)) {
            EARS::Framework::debugAssert();
        }

        if (objPtr != currentObject) {
            // Acquiring reference to a different object
            if (nodePtr == nullptr) {
                EARS::Framework::debugAssert();
            }
            if (objPtr == *(void**)((int)nodePtr + 4)) {
                EARS::Framework::debugAssert();
            }
            // Increment reference count at offset 0x10 in the object
            (*(int*)((int)objPtr + 0x10))++;
            return;
        } else {
            // Object is already the current one – clear the handle
            result = (void**)EARS::Framework::HandleManager::clearHandle(&handle);
            *result = (void*)1; // Set success flag or indicate handled
        }
    }
}