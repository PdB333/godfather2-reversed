// Xbox PDB: EARS_Modules_TOD_GlobalSHTODSequence_GlobalSHTODSequence
// FUNC_NAME: GlobalShutdownSequence::GlobalShutdownSequence

// 0x00830bf0 - Constructor for global shutdown sequence object
// This function initializes the vtable, sets a flag, registers the sequence,
// loads a resource (likely a script or sequence data), and installs a scope guard
// for cleanup.

// External function declarations (from Ghidra)
extern void FUN_0082f090();                          // Base class constructor?
extern void FUN_004d3bc0(const char* str);           // Debug/registration function
extern void FUN_004d3e20(int* guard);                // Scope guard constructor
extern int  FUN_004dafd0(void* data);                // Resource loader – returns handle

// External symbols
extern void* PTR_FUN_00d73994;        // Vtable for GlobalShutdownSequence
extern char DAT_0120546e[];           // Default raw data fallback

class GlobalShutdownSequence {
public:
    void** vtable;             // +0x00
    int    field_4;            // +0x04 (unused in this function)
    int    resourceHandle;      // +0x0C (offset 3)
    void*  rawDataPtr;         // +0x10 (offset 4)
    int    sequenceFlag;       // +0x24 (offset 9)
    // ... other members follow
};

// __thiscall (this in ecx)
GlobalShutdownSequence* __thiscall GlobalShutdownSequence_constructor(GlobalShutdownSequence* this)
{
    // Scope guard structure for automatic cleanup (unknown type)
    struct ScopeGuard {
        int dummy[3];
        void (*destructor)(int);  // Function pointer stored at offset 12?
    } guard;
    
    // Call base class constructor (if any)
    FUN_0082f090();
    
    // Set vtable pointer
    this->vtable = &PTR_FUN_00d73994;
    
    // Set the sequence flag to 1 (active)
    this->sequenceFlag = 1;
    
    // Register this sequence with a debug/global name
    FUN_004d3bc0("GlobalSHTODSequence");
    
    // Initialize scope guard (stores destructor pointer and cancellation flag)
    FUN_004d3e20((int*)&guard);
    
    // Determine raw data pointer – if null, use default
    void* data = this->rawDataPtr;
    if (data == nullptr) {
        data = &DAT_0120546e;
    }
    
    // Load the resource (e.g., a script or sequence definition) and store handle
    this->resourceHandle = FUN_004dafd0(data);
    
    // If scope guard's first field is non-zero, call its destructor immediately
    if (guard.dummy[0] != 0) {
        guard.destructor(guard.dummy[0]);
    }
    
    return this;
}