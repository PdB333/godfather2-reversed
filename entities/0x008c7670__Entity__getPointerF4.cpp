// FUNC_NAME: Entity::getPointerF4
// Function address: 0x008c7670
// Returns a pointer stored at offset 0xf4 from the object returned by an internal method
void* Entity::getPointerF4() {
    // Call internal helper to obtain a sub-object (likely a component or derived object)
    void* subObj = (void*)FUN_008c7490(this);
    if (subObj != nullptr) {
        // Read pointer at offset 0xf4 from that sub-object
        return *(void**)((uint8_t*)subObj + 0xf4);
    }
    return nullptr;
}