// FUNC_NAME: UnknownClass::initializeComponent
void __thiscall UnknownClass::initializeComponent(void* this)
{
    // +0x0C: component type identifier (e.g., object class ID)
    *(int*)((int)this + 0x0C) = 0x3FF8;

    // Allocate a 12-byte internal structure
    int* internalStruct = (int*)AllocateMemory(12); // FUN_009c8e50
    if (internalStruct != (int*)0x0) {
        // Request a handle or resource for the type ID
        internalStruct[1] = CreateHandle(0x3FF8); // FUN_009c8e80
    }
    // +0x08: pointer to internal structure
    *(int**)((int)this + 0x08) = internalStruct;

    // Initialize the internal structure fields
    *internalStruct = 0;                               // field0 = 0
    if (internalStruct != (int*)0x0) {                 // always true if allocation succeeded
        internalStruct[2] = 0;                         // field8 = 0
    }

    // Perform additional initialization
    InitializeSubComponent(this); // FUN_0065c810
}