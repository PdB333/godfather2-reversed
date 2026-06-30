// FUNC_NAME: SomeClass::getProperty (likely getter for 12-byte property like color/vector)
// Address: 0x006c5740
// This function retrieves a 12-byte property from the object.
// If the object has a custom property (via a component with vtable), it queries it using a hash ID.
// Otherwise, it falls back to a default value (from a global singleton) or static defaults.

void __thiscall SomeClass::getProperty(SomeClass* this, /* out */ void* outputBuffer) {
    // +0x2BC: flag indicating whether to use default property
    if (*(char*)((uint8_t*)this + 0x2BC) != 0) {
        // Use default values from global singleton
        int* defaultValues = FUN_00471610(); // returns pointer to default data block
        // Copy 12 bytes: first 8 bytes at offset 0x10, next 4 bytes at offset 0x18
        *(uint64_t*)outputBuffer = *(uint64_t*)(defaultValues + 0x10);
        *(uint32_t*)((uint8_t*)outputBuffer + 8) = *(uint32_t*)(defaultValues + 0x18);
        return;
    }

    // Get component pointer from offset 0x1D (29) - likely vtable pointer
    int* componentPtr = nullptr;
    if (*(int*)((uint8_t*)this + 0x1D) != 0) {
        // The component object is at stored pointer - 0x48 (offset to base)
        componentPtr = (int*)(*(int*)((uint8_t*)this + 0x1D) - 0x48);
    }

    // Virtual call: method at vtable+0x10 takes a property hash and returns pointer to data
    // Hash used: 0xC476E9C5 (likely a CRC for the property name)
    void* propertyData = nullptr;
    bool found = (componentPtr != nullptr) &&
                 ((*(bool (__thiscall**)(int*, uint32_t, void**))(*componentPtr + 0x10))
                  (componentPtr, 0xC476E9C5, &propertyData) != 0);

    if (found) {
        // Copy 12 bytes from the returned property data at offsets 0x40, 0x44, 0x48
        // Note: The decompiler shows reading from a constant offset, likely misidentified.
        // We assume propertyData points to a structure with the desired data.
        uint32_t v0 = *(uint32_t*)((uint8_t*)propertyData + 0x40);
        uint32_t v1 = *(uint32_t*)((uint8_t*)propertyData + 0x44);
        uint32_t v2 = *(uint32_t*)((uint8_t*)propertyData + 0x48);
        *(uint32_t*)((uint8_t*)outputBuffer + 0) = v0;
        *(uint32_t*)((uint8_t*)outputBuffer + 4) = v1;
        *(uint32_t*)((uint8_t*)outputBuffer + 8) = v2;
        return;
    }

    // Fallback to static defaults (global data)
    // DAT_00d5ee68 and DAT_00d5ee70 are 8-byte and 4-byte constants
    *(uint64_t*)outputBuffer = DAT_00d5ee68;
    *(uint32_t*)((uint8_t*)outputBuffer + 8) = DAT_00d5ee70;
}