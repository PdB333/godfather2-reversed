// FUNC_NAME: ReplicationLinkManager::~ReplicationLinkManager
// Function at 0x00476dd0: Destructor for a class managing 32 replication link slots
// Structure layout (offsets in bytes from this):
//   +0x00: vtable pointer
//   +0x3C: vtable entry (function pointer)
//   +0x48: vtable entry (function pointer)
//   +0x50: sub-object (may be a list, initialized/destroyed by init/release)
//   +0x60: pointer to separate object (released if non‑null)
//   +0x6C: first pointer (not freed by the loop)
//   +0x70: array of 32 pointers (freed by the loop, if non‑null)
void __fastcall ReplicationLinkManager::~ReplicationLinkManager(undefined4 *this)
{
    undefined4 *it;

    // Set vtable and vtable entries for destruction
    *this = &PTR_FUN_00e32f00;
    this[0xf] = &PTR_LAB_00e32f1c;   // +0x3C
    this[0x12] = &PTR_LAB_00e32f2c;  // +0x48

    // Initialize and then release sub-object at +0x50
    FUN_004086d0(this + 0x14);        // initSubObject(&subObject)
    FUN_00408310(this + 0x14);        // releaseObject(&subObject)

    // Release separate pointer at +0x60 if non‑null
    if (this[0x18] != 0) {
        FUN_00408310(this + 0x18);    // releaseObject(ptr at +0x60)
    }

    // Loop over array of 32 pointers starting at +0x70
    // it starts at +0x6C, increments by 4, and checks the next word (it[1])
    // This checks every pointer from +0x70 to +0xEC inclusive
    for (it = this + 0x1b; it != this + 0x3b; it = it + 4) {
        if (it[1] != 0) {
            FUN_00408310(it + 1);      // releaseObject(pointer at next offset)
        }
    }

    // Global cleanup call
    FUN_0046c640();                    // globalCleanup()
}