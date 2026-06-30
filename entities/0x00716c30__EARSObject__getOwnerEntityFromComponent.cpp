// FUNC_NAME: EARSObject::getOwnerEntityFromComponent
// Retrieves the owning container (e.g., Entity/GameObject) from a nested component pointer.
// The component pointer at offset +0x1c78 points to a field 0x48 bytes inside the container struct.
int __thiscall EARSObject::getOwnerEntityFromComponent() {
    // Dereference the pointer stored at this+0x1c78 (likely a component object reference)
    int* componentPtr = *(int**)(this + 0x1c78);
    if (componentPtr != nullptr) {
        // Subtract field offset (0x48) to get the base of the containing object
        return (int)(componentPtr - 0x48);
    }
    return 0;
}