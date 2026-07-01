// FUNC_NAME: Object::release
// Address: 0x008cfdd0
// Role: Release/destroy method for a base object with reference counting or lifecycle flags.
// Uses virtual calls to query ownership, sets destruction flags, and optionally calls cleanup.

uint __thiscall Object::release(int* thisPtr, int* pOwner)
{
    uint tempResult; // uVar2
    char canDestroy; // cVar1

    // Clear or initialize something at this+0x20 (offset 8 ints)
    tempResult = Memory::deallocate(thisPtr + 8, 0);
    
    // Check if the object is not already being destroyed (bit 31 clear)
    if (thisPtr[0x18] >= 0) {
        // Call virtual function at index 2 of pOwner's vtable (likely a query)
        (*(code**)(*pOwner + 8))(tempResult);
    }
    
    // Call virtual function at index 8 of this's vtable (e.g., "canRelease?")
    canDestroy = (*(code**)(*thisPtr + 0x20))(pOwner);
    
    if (canDestroy == 0) {
        // If cannot destroy, adjust pOwner pointer (advance by 0x3c bytes)
        // This might be navigating to a sub-object or list node
        pOwner = (pOwner == 0) ? 0 : (pOwner + 0xf);
    }
    else {
        // Mark with destruction flag (bit 30 set)
        thisPtr[0x18] |= 0x40000000;
        
        // If still safe (bit 31 clear)
        if (thisPtr[0x18] >= 0) {
            // Remove this object from some list using pOwner
            Memory::removeFromList(pOwner, thisPtr + 8);
            tempResult = Memory::getNextObject(thisPtr);
            Memory::addToList(pOwner, tempResult);
        }
        
        // If bit 29 is set, skip the final delete call
        if (((uint)thisPtr[0x18] >> 0x1d & 1) != 0) {
            goto done;
        }
        
        // Otherwise, set pOwner to this+0x3c (maybe a self-pointer for delete)
        pOwner = thisPtr + 0xf;
    }
    
    // Delete the object referenced by pOwner
    Memory::free(pOwner);
    
done:
    // Return bit 30 value (0/1) indicating if destruction was in progress
    return (thisPtr[0x18] >> 0x1e) & 1;
}