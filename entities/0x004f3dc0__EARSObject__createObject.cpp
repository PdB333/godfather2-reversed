// FUNC_NAME: EARSObject::createObject
// Function at 0x004f3dc0: Factory/constructor for an EARS game object.
// Parameters:
//   ownerOrContext - pointer to an owner/context object (offset +0xD used as flag)
//   object         - pointer to uninitialized memory (returns null if null, else constructed object)
// Returns the constructed object pointer.
EARSObject* EARSObject::createObject(int* ownerOrContext, EARSObject* object) {
    if (object != nullptr) {
        // Call base class initialization
        BaseClass::baseConstructor(); // e.g., memory zeroing, reference counting

        // Set vtable pointer (first 4 bytes)
        object->vtable = &EARSObject_vtable; // +0x00: vtable pointer

        // Check a flag at offset +0xD of the owner/context object
        if (*(char*)((int)ownerOrContext + 0xD) == '\0') {
            // Perform additional initialization (e.g., setup properties, bind to owner)
            extendedInit(ownerOrContext); // FUN_004f42f0
        }

        return object;
    }

    return nullptr;
}