// FUNC_NAME: ResourceFactory::acquireInstance
// Address: 0x00633bc0
// Role: Retrieve or initialize a resource instance, handling lazy singleton creation and type dispatch.

// External declarations for helper functions (not recompiled here)
extern "C" uint64_t __fastcall getSingletonOrCreate(void); // Returns a 64-bit value: low dword = pointer to type field, high dword = pointer to flag byte
extern "C" void* __thiscall handleTypeSix(void* self, int* typeField, void* resourceInfo, uint32_t extra);
extern "C" void* __thiscall handleFallback(void* self, int* typeField, uint32_t param3, uint32_t param4);

// Global error sentinel (likely a zero/null address placeholder)
extern uint32_t g_nullSentinel; // DAT_00e2a93c

void* __thiscall ResourceFactory::acquireInstance(void* resourceInfo, uint32_t param3, uint32_t param4)
{
    // resourceInfo is a structure:
    // +0x04: pointer to a sub-structure
    //   +0x08: pointer to a byte flag field
    //     +0x06: flag byte (bit 0 = initialized?)
    int* typeField = nullptr;

    // Check if the initialization flag is clear (bit 0)
    uint8_t* flagByte = (uint8_t*)(*(int*)(*(int*)((uint8_t*)resourceInfo + 4) + 8) + 6);
    if ((*flagByte & 1) == 0)
    {
        uint64_t result = getSingletonOrCreate();
        // Low dword = pointer to an integer (type indicator)
        // High dword = pointer to a flag structure (maybe same as above)
        int* lowPtr = (int*)(uint32_t)result;
        if (*lowPtr != 0)
        {
            typeField = lowPtr;
        }
        else
        {
            // Set the flag bit on the high dword pointer (at offset 0x06)
            uint8_t* highFlag = (uint8_t*)(uint32_t)(result >> 32) + 6;
            *highFlag |= 1;
            typeField = nullptr; // implicit, already null
        }
    }
    // If typeField is null (either uninitialized or the singleton didn't exist)
    if (typeField == nullptr)
    {
        return (void*)&g_nullSentinel;
    }
    // Type dispatch based on the integer pointed to by typeField
    if (*typeField == 6)
    {
        handleTypeSix(this, typeField, resourceInfo, param3);
        return *(void**)((uint8_t*)this + 8); // Return member at +0x08
    }
    // Default case
    return handleFallback(this, typeField, param3, param4);
}