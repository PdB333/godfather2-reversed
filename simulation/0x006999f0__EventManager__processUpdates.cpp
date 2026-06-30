// FUNC_NAME: EventManager::processUpdates
// 0x006999f0
// Reconstructed from decompiled EA EARS engine code for The Godfather 2.
// This function iterates over a global array of event receivers (or handlers) and processes them.
// DAT_01129f8c and DAT_01129f90 are likely begin/end pointers of a list of structures (each 4 bytes?).
// FUN_004d3bc0 is likely a pre-processor for each receiver with the first parameter (this?).
// FUN_00699700 checks for an available event and fills local_10[0] with a pointer to event data.
// If an event is found, it calls a global callback (local_4) with that data.
// The loop also returns 1 if cVar1 (from FUN_00699700) is nonzero, otherwise returns 0.

uint32_t __thiscall EventManager::processUpdates(void *this_ptr, uint32_t param_2)
{
    char cVar1;
    int32_t iVar2;
    uint32_t local_10[3];           // buffer for possible event data pointer
    void (*callback)(uint32_t);     // global function pointer, presumed set elsewhere

    iVar2 = DAT_01129f8c;           // global: start of receiver list (offset in bytes?)
    if (DAT_01129f8c != DAT_01129f90) {
        do {
            FUN_004d3bc0(this_ptr); // likely updates/initializes current receiver
            cVar1 = FUN_00699700(local_10, param_2); // checks for available event, stores pointer in local_10[0]
            if (local_10[0] != 0) {
                callback(local_10[0]); // invoke callback with event data pointer
            }
            if (cVar1 != '\0') {
                return 1;           // some condition fired, return success
            }
            iVar2 = iVar2 + 4;      // move to next entry (4 bytes per entry)
        } while (iVar2 != DAT_01129f90);
    }
    return 0;                       // no event fired
}