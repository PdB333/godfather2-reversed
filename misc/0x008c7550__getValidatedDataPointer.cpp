// FUNC_NAME: getValidatedDataPointer
// Function: 0x008c7550 - Returns a pointer to data at offset 0x8c from a validated object base,
// or a global default if the object is not valid.
// Called from multiple locations, likely a helper for accessing a component or sub-object.

// Forward declaration of the validation function
int* __cdecl getValidDataBase(void* pObject);

// Global default pointer (0x01218244 in image)
extern int g_defaultData;

int* __cdecl getValidatedDataPointer(void* pObject)
{
    int* pBase;
    
    pBase = getValidDataBase(pObject);
    if (pBase != (int*)0x0) {
        // Return pointer at offset 0x8c from the validated base
        return (int*)((unsigned char*)pBase + 0x8c);
    }
    // Object validation failed, return the global default
    return &g_defaultData;
}