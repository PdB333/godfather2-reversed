// Xbox PDB: EARS_Modules_TOD_EARSLightTODSequence_EARSLightTODSequence
// FUNC_NAME: EARSLightTODSequence::constructor
EARSLightTODSequence* __fastcall EARSLightTODSequence::constructor(EARSLightTODSequence* this)
{
    // Initialization of fields at offsets 0x04 to 0x20
    this->field_4 = 0;
    this->field_8 = 0;
    this->field_C = 0;
    this->field_10 = 0;
    this->field_14 = 0;
    this->field_18 = 0;
    this->field_1C = 0;
    *(byte*)&this->field_20 = 1; // byte flag at +0x20

    // Set vtable pointer (0x00d733e0)
    this->vtable = &g_EARSLightTODSequence_vtable;

    // Local allocation info struct (type=2, size=0x10, flags=0)
    int allocInfo[3] = {2, 0x10, 0};

    // Initialize memory manager with this info
    int allocResult = memoryMgrInit(allocInfo);                // FUN_009c89c0
    memoryMgrReserve(8, allocResult, allocInfo);               // FUN_00821a60

    // Allocate 32-byte sub-object
    void* subObj = heapAlloc(0x20);                            // FUN_009c8e80
    this->subObject = subObj;                                  // +0x38
    this->subObjectLength = 0;                                 // +0x3C
    this->subObjectCapacity = 8;                               // +0x40

    // Debug log: class name
    debugLog("EARSLightTODSequence");                          // FUN_004d3bc0

    // Release temporary allocation info (destructor-like call)
    memoryMgrDestroy(allocInfo);                               // FUN_004d3e20

    // Set name field from input or default
    char* nameCandidate = (char*)this->field_10;               // +0x10
    if (nameCandidate == nullptr) {
        nameCandidate = &g_defaultName;                        // DAT_0120546e
    }
    this->namePtr = stringDup(nameCandidate);                  // FUN_004dafd0, stored at +0x0C

    // Inline destructor check for local allocInfo (not fully recovered by decompiler)
    // The original code likely had a stack-based object with a vtable destructor call.
    // The local_4 variable in the decompiled output is uninitialized, indicating a
    // missing vtable pointer. We omit the destructor call here for correctness.
    if (allocInfo[0] != 0) {
        // Hypothetical destructor: (*destructor)(allocInfo[0]);
    }

    return this;
}