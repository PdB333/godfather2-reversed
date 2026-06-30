// FUNC_NAME: EARSObject::~EARSObject
void __fastcall EARSObject::~EARSObject(uint32_t *this)
{
    uint32_t *vtable4; // param_1 + 0x15 (offset 0x54)
    uint32_t *vtable5; // param_1 + 0x16 (offset 0x58)
    int temp;
    int *listEntry;

    // Save pointers to vtable slots (to be restored/cleaned later)
    vtable4 = this + 0x15;
    vtable5 = this + 0x16;

    // Set main vtable to destructor-safe stub
    *this = &PTR_FUN_00e32858;
    // Set other interface vtables to dtor stubs
    this[0xf] = &PTR_LAB_00e329a4;  // +0x3C
    this[0x12] = &PTR_LAB_00e329b4; // +0x48
    this[0x14] = &PTR_LAB_00e329b8; // +0x50
    *vtable4 = &PTR_LAB_00e329c0;   // +0x54
    *vtable5 = &PTR_LAB_00e32a20;   // +0x58

    // Check bit 13 of flags at +0x15E (ushort)
    if ((*(uint16_t *)((int)this + 0x15e) >> 0xd & 1) != 0) {
        // Deregister from two global lists (likely systems or managers)
        FUN_004086d0(&DAT_0120e944);
        FUN_004086d0(&DAT_0120e94c);
    }

    // Deregister from another global list
    FUN_004086d0(&DAT_0120e93c);

    // Generic cleanup (likely engine shutdown callbacks)
    FUN_0046ebb0();

    // Release global singleton (e.g., game state manager)
    FUN_0043c5d0(DAT_01223414);

    // Handle reference count at +0x164 (0x59*4)
    if (this[0x59] != 0) {
        this[0x59] = 1; // Force to 1 for final decrement
        if ((this[0x59] != 0) && (temp = this[0x59] - 1, this[0x59] = temp, temp == 0)) {
            // Reference reached zero: add this object to a global deletion queue
            listEntry = (int *)(DAT_01206880 + 0x14); // +0x14 offset from some manager
            **(uint32_t **)(DAT_01206880 + 0x14) = &PTR_LAB_0110ba58; // set head of queue?
            *listEntry = *listEntry + 4;              // advance end pointer
            *(uint32_t *)*listEntry = -(uint32_t)(this != NULL) & (uint32_t)vtable4; // store address
            *listEntry = *listEntry + 4;
        }

        // If this object holds another object at +0x68 (0x1a*4) and it's not a sentinel (0x48)
        if ((this[0x1a] != 0) && (this[0x1a] != 0x48)) {
            if (this[0x1a] == 0) {
                temp = 0;
            } else {
                temp = this[0x1a] - 0x48; // Subtract sentinel to get real pointer?
            }
            // Call a virtual method on the child object (vtable+0x54)
            (*(void (**)(void))(*(int *)(temp + 0x54) + 0x54))();
        }
    }

    // Free a memory block at +0x168 (0x5a*4) if present
    temp = this[0x5a];
    if (temp != 0) {
        listEntry = (int *)FUN_009c8f80(); // get allocator interface
        (*(void (**)(void))(*(int *)listEntry + 4))(temp, 0x70); // deallocate (size 0x70)
        this[0x5a] = 0;
    }

    // Unlink this object from an intrusive linked list whose head is at this[0x1a] (+0x68)
    temp = this[0x1a];
    if (temp != 0) {
        uint32_t *prev = *(uint32_t **)(temp + 4);
        if (prev == this + 0x1a) {
            // Head of list: update head to next
            *(uint32_t *)(temp + 4) = this[0x1b];
        } else {
            // Traverse to find predecessor then update its next
            uint32_t *walkerPrev = (uint32_t *)prev[1];
            while (walkerPrev != this + 0x1a) {
                prev = (uint32_t *)prev[1];
                walkerPrev = (uint32_t *)prev[1];
            }
            prev[1] = this[0x1b];
        }
    }

    // Final vtable setup and teardown
    *vtable5 = &PTR_FUN_00e33520;
    FUN_00454390(vtable5);  // likely finalize or unregister interface

    // Last vtable resets
    *vtable4 = &PTR_LAB_00e31528;
    this[0x14] = &PTR_LAB_00e32854;

    // Final engine cleanup (e.g., thread synchronization, stats)
    FUN_0046c640();
    return;
}