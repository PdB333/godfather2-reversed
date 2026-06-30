// FUNC_NAME: SimNpc::constructor
// Reconstructed constructor for a SimNpc object (Godfather 2, EARS engine).
// Initializes basic fields and allocates a unique handle.
// Address: 0x004ddbc0

void __thiscall SimNpc::constructor(void* this, int baseId) {
    // +0x00: Object ID (passed in EAX)
    *(int*)this = baseId;
    // +0x04: Flags (initialized to 0)
    *(int*)((char*)this + 4) = 0;
    // +0x08: Type (initialized to 0)
    *(int*)((char*)this + 8) = 0;
    // +0x0C: Subtype (16-bit, initialized to 0)
    *(short*)((char*)this + 12) = 0;
    // +0x10: Unique handle from manager
    unsigned int handle = FUN_004dd960();  // allocateHandle
    *(unsigned int*)((char*)this + 16) = handle;
}