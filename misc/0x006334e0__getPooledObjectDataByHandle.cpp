// FUNC_NAME: getPooledObjectDataByHandle
// Address: 0x006334e0
// Role: Retrieves a pointer to the data portion of a pooled object by handle.
//   The handle is an index offset by 0xFA. The pool manager holds an array of
//   slots (8 bytes each) at offset +8. If the slot type is 4 (active), returns
//   the object's data pointer (object pointer + 0x10). Otherwise returns a
//   global invalid pointer.

#define ACTIVE_SLOT_TYPE 4
#define HANDLE_BASE 0xFA

extern void* g_invalidPointer; // DAT_00e41518

struct PoolSlot {
    int type;       // +0x00: slot type (4 = active)
    void* pointer;  // +0x04: pointer to the object
};

void* __fastcall getPooledObjectDataByHandle(int handle, void* poolManager)
{
    int index = handle - HANDLE_BASE;
    if (index >= 0)
    {
        PoolSlot* slotArray = *(PoolSlot**)((char*)poolManager + 8); // +0x08: pointer to slot array
        if (slotArray[index].type == ACTIVE_SLOT_TYPE)
        {
            // Object data starts at offset 0x10 from the object pointer
            return (void*)((char*)slotArray[index].pointer + 0x10);
        }
    }
    return g_invalidPointer;
}