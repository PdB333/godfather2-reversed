// FUNC_NAME: EARSObject::release
// Function address: 0x006b5c50
// This function decrements the reference count of an EARSObject.
// If the count drops below the threshold (offset 0x6c), it schedules deletion.
// It also handles optional callback notification via a listener list pointed to by offset 0x78.
// The callback is either generated from a new ID (if param2==0 and offset 0xac is valid) or from the provided param2.
// After cleanup, a temporary notification node is constructed and processed.

void __thiscall EARSObject::release(int thisPtr, int param2)
{
    uint prevRefCount;
    int callbackId;

    // If reference count is already zero, do nothing
    if (*(int *)(thisPtr + 0x68) == 0) {
        return;
    }

    // Decrement reference count at offset +0x68
    prevRefCount = *(int *)(thisPtr + 0x68) - 1;
    *(uint *)(thisPtr + 0x68) = prevRefCount;

    // If new count is <= the low-water mark (+0x6c), schedule deletion
    // FUN_008c78b0 is likely EARSObject::scheduleDestruction with flag 1 (immediate)
    if (*(uint *)(thisPtr + 0x6c) <= prevRefCount) {
        FUN_008c78b0(*(undefined4 *)(thisPtr + 0x40), 1);
    }

    // If the listener list pointer (+0x78) is non-null, handle notifications
    if (*(int *)(thisPtr + 0x78) != 0) {
        if (param2 == 0) {
            // No explicit callback ID provided; generate one if object has a valid ID slot (+0xac)
            if (*(int *)(thisPtr + 0xac) == 0) {
                goto LAB_006b5ce9;
            }
            // Increment global callback ID counter and generate new ID
            DAT_012054b4 = DAT_012054b4 + 1;
            callbackId = FUN_00b9a1c0(); // likely "generateUniqueCallbackId"
        }
        else {
            // Use provided param2 as a callback ID (might be a pointer converted to int)
            callbackId = FUN_006b1b10(&param2); // likely "convertPointerToId"
        }

        // If ID is valid (>=0), trigger the callback
        if (callbackId >= 0) {
            FUN_006b56a0(callbackId); // likely "notifyListeners"
        }
    }

LAB_006b5ce9:
    // Build a temporary notification node for further processing
    // The node is attached to a global list (PTR_LAB_00d5dbb0) and includes this object and a global variable (DAT_0112a5a4)
    // local_8 points to local_14 (start of node), local_10 stores thisPtr, local_c stores global data, local_4 = 0
    // FUN_00408a00 processes this node (likely adds to queue or executes deferred actions)
    void* local_14 = &PTR_LAB_00d5dbb0; // static sentinel pointer
    void** local_8 = &local_14;          // pointer to node head
    int local_10 = thisPtr;               // object pointer
    int local_c = DAT_0112a5a4;           // some global context
    char local_4 = 0;                     // flags

    FUN_00408a00(&local_c, 0); // process the temporary node
    return;
}