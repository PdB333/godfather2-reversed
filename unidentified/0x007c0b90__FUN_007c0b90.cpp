// FUNC_NAME: SomeManager::constructor
undefined4 * __thiscall SomeManager::constructor(undefined4 *this, undefined4 param2, undefined4 param3)
{
    int *piListEntry;
    int iSingletonResult;
    undefined4 uResourceHandle;

    // Base class initialization (likely a parent constructor)
    FUN_007ab5e0(param2, param3);

    // Set vtable pointer
    *this = &PTR_LAB_00d6e354;

    // Initialize fields at offsets
    this[0x23] = 0;          // +0x8C: some member
    *(undefined1 *)(this + 0x24) = 0;  // +0x90: byte
    *(undefined1 *)((int)this + 0x91) = 0; // +0x91: byte
    this[0x1f] = 0;          // +0x7C
    this[0x1e] = 0;          // +0x78
    this[0x1d] = 0;          // +0x74
    piListEntry = this + 0x26; // +0x98: linked list node pointer (this->listNode)
    this[0x22] = 0;          // +0x88
    this[0x21] = 0;          // +0x84
    this[0x20] = 0;          // +0x80
    *piListEntry = 0;        // clear list node
    this[0x27] = 0;          // +0x9C: next pointer in list?
    this[0x28] = 0;          // +0xA0: previous pointer?

    // Obtain singleton from global manager (e.g., StreamManager, ResourcePool)
    iSingletonResult = FUN_007ab710();
    if (iSingletonResult == 0) {
        iSingletonResult = 0;
    }
    else {
        iSingletonResult = iSingletonResult + 0x48; // offset to some sub-structure
    }

    // Insert this object into a linked list managed by the singleton
    if (*piListEntry != iSingletonResult) {
        if (*piListEntry != 0) {
            FUN_004daf90(piListEntry); // likely removes previous node
        }
        *piListEntry = iSingletonResult;
        if (iSingletonResult != 0) {
            this[0x27] = *(undefined4 *)(iSingletonResult + 4); // save old next
            *(int **)(iSingletonResult + 4) = piListEntry; // relink
        }
    }

    // Allocate actor/handle with size 0x20 (32 bytes)
    FUN_007f63e0(0x20); // e.g., allocate memory or grab a slot
    FUN_007ab120();     // another initialization step

    // Acquire resource handles by ID
    uResourceHandle = FUN_00896db0(0x1ff); // e.g., 511 = sound bank
    this[0x25] = uResourceHandle;   // +0x94

    FUN_00896e10(0x102); // e.g., 258 = other resource

    // Zero out more fields (indices 0x29 to 0x2f, offsets +0xA4 to +0xBC)
    this[0x29] = 0;
    this[0x2a] = 0;
    this[0x2b] = 0;
    this[0x2c] = 0;
    this[0x2d] = 0;
    this[0x2e] = 0;
    this[0x2f] = 0;

    return this;
}