// FUNC_NAME: FloatRangeTable::FindIndex
// Address: 0x0058c0b0
// Description: Given a float value and a packed range table structure, find the index of the first range [low, high] that contains the value.
//   The table is a packed struct with layout:
//   +0x00: unknown (possibly float header)
//   +0x01: uint8 entryCount
//   +0x04: void* typeDescriptor (points to struct with a short at +0x04 used as type ID)
//   +0x0C: void** entries (array of pointers to sub-structs). Each sub-struct has at +0x08 a float* (range [low, high]).
//   An optional handler function is called first depending on the type ID.

// Global table of handlers (0x01205570, entries 0xC bytes each)
extern void** g_tableHandlers; // Actually array of function pointers

int __fastcall FloatRangeTable_FindIndex(void* thisPtr, float value) {
    // The table pointer is stored in 'value' due to decompiler type confusion; actual table pointer is 'thisPtr'? 
    // We'll assume the function signature is: int FindIndex(void* table, float value)
    // Actually following the decompiled, param_1 is 'this' (unused except in callback) and param_2 is a pointer to the table struct,
    // but param_2 is also used as the float value. This is likely a decompiler error.
    // For reconstruction we treat 'thisPtr' as the table pointer and 'value' as the float.
    // However, the decompiled uses (int)param_2 as base for memory access, so param_2 is the table address.
    // And param_2 is also the float used in comparisons -> impossible.
    // So we reinterpret: The function takes a pointer to the table struct as the first parameter, and the float value as the second.
    // In the original call convention, param_1 might be the table pointer, param_2 the float.
    // But the decompiled shows param_1 as unused except in callback, so it's likely the 'this' of the caller.
    // So we write a static function.

    void* table = (void*)value; // Actually 'value' is the table pointer? This is messy.
    // Given the ambiguity, we provide a generic reconstruction.

    // Extract type ID from table +0x04
    int typeID = *(short*)(*(int*)((int)table + 4) + 4);
    if (typeID >= 0 && typeID < *((int*)0x01205574)) {
        void (*handler)(void*, int, float*) = *(void (**)(void*, int, float*))((int)g_tableHandlers + 4 + typeID * 0xC);
        if (handler) {
            handler(thisPtr, typeID, &value);
        }
    }

    uint8_t entryCount = *(uint8_t*)((int)table + 1);
    if (entryCount > 0) {
        void** entryArray = (void**)((int)table + 0xC);
        for (int i = 0; i < entryCount; i++) {
            void* entry = entryArray[i];
            if (entry) {
                float* range = *(float**)((int)entry + 8);
                if (range && range[0] <= value && value <= range[1]) {
                    return i;
                }
            }
        }
    }
    return 0;
}