// FUNC_NAME: Variant::constructFromType

void __fastcall Variant::constructFromType(Variant* this) {
    // Call base class constructor or initializer
    BaseClass::constructor(this);

    // Get the data pointer stored at offset 0x08 (likely a pointer to a memory pool)
    uint8_t* dataPtr = *(uint8_t**)(this + 0x08);

    // Header is at dataPtr - 8 bytes: presumably contains a type ID (int) at -8 and a value (float?) at -4
    int* typeField = (int*)(dataPtr - 8);
    float* valueField = (float*)(dataPtr - 4);

    // Based on the type, initialize the variant to a default value
    if (*typeField == 3) {
        // For type 3: if the current float value is exactly an integer (e.g., uninitialized zeros),
        // set it to the default for type 3.
        if ((float)(int)(*valueField) == *valueField) {
            // Fetch static default tuple for type 3 (two 32-bit values)
            uint32_t* defaultData = (uint32_t*)getDefaultForType3();
            *typeField = defaultData[0];
            *(uint32_t*)(valueField) = defaultData[1];
            return;
        }
        // Otherwise fall through to the default case (sets different default)
    }
    else if (*typeField == 4) {
        // For type 4: always set to default for type 4
        uint32_t* defaultData = (uint32_t*)getDefaultForType4();
        *typeField = defaultData[0];
        *(uint32_t*)(valueField) = defaultData[1];
        return;
    }

    // Default case: type other than 3 or 4 (or type 3 with non-integer value)
    uint32_t* defaultData = (uint32_t*)getDefaultForOtherType();
    *typeField = defaultData[0];
    *(uint32_t*)(valueField) = defaultData[1];
}