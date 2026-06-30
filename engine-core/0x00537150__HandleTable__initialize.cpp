// FUNC_NAME: HandleTable::initialize
void HandleTable::initialize(void)
{
    ushort index;           // uVar1
    void* pool;              // uVar2: allocation flags
    ushort* buffer;          // _Dst: pointer to the handle buffer
    ushort* allocBuf;        // local_4: temporary for dynamically allocated buffer

    // Allocate a memory pool of 0x800 bytes. This is the backing for the handle table.
    // The 4th parameter 0x12 might indicate heap type or alignment.
    engineAlloc(0x800, 0, &g_pHandleTable, 0x12);

    // If the flag g_bInitDone is already set (non-zero), we use the global static buffer.
    if (g_bInitDone == false) {
        // First-time initialization: mark as in progress and use the static global buffer.
        g_bInitInProgress = true;
        buffer = g_staticHandleBuffer; // +0x10 (offset from g_pHandleTable?)
    } else {
        // Already initialized: allocate a new buffer via the handle table's virtual methods.
        if (g_bUseAllocator != false) {
            pool = (void*)0x3000; // Some allocation flag constant
        } else {
            pool = (void*)0;
        }
        // Virtual call at vtable+0x2c: likely "allocateBuffer" method.
        // Parameters: (this, 0, 0, &allocBuf, pool flags)
        (**(code**)(*g_pHandleTable + 0x2c))(g_pHandleTable, 0, 0, &allocBuf, pool);
        buffer = allocBuf;
    }

    // Clear the entire buffer (0x800 bytes)
    memset(buffer, 0, 0x800);

    // Fill the buffer with sequential handle indices: 0, 1, 2, ..., 511.
    index = 0;
    do {
        *buffer = index;
        index = index + 1;
        buffer = buffer + 1; // Advance by 2 bytes (ushort*)
    } while (index < 0x200); // 512 iterations

    // If this is a re-initialization, call the finalization virtual method.
    // Virtual call at vtable+0x30: likely "finalizeBuffer" or "releaseBuffer".
    if (g_bInitDone != false) {
        (**(code**)(*g_pHandleTable + 0x30))(g_pHandleTable);
        return;
    }

    // Mark initialization as complete and clear the "in progress" flag.
    g_bInitInProgress = false;
}