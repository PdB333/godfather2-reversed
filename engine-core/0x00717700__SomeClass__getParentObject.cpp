// FUNC_NAME: SomeClass::getParentObject
int SomeClass::getParentObject() {
    // Read pointer at offset 0x330 (likely a member pointer to a sub-object)
    int* subObjectPtr = *(int**)(this + 0x330);
    // If non-null, adjust back by 0x48 to get the containing object's base
    int base = 0;
    if (subObjectPtr != nullptr) {
        base = (int)subObjectPtr - 0x48; // container_of pattern
    }
    if (base != 0) {
        // Call internal processing function on the containing object
        return internalProcessParent(base);
    }
    return 0;
}