// FUNC_NAME: RefCounted::release
// Address: 0x00421260
// Role: Decrements reference count, triggers cleanup when count reaches zero.
// This is a member function of a reference-counted object (EARS/EA base class).
// Offsets: +0x00: refCount (int), +0x06: flags (ushort, bit 0 = needs custom cleanup)

int RefCounted::release()
{
    // Get internal object pointer (may adjust 'this' or resolve a handle)
    int* internalObj = getInternalObject(); // FUN_00421170
    
    if (internalObj == nullptr)
        return 0;
    
    // Decrement reference count at offset 0
    internalObj[0] = internalObj[0] - 1;
    
    // If reference count reached zero, perform cleanup
    if (internalObj[0] == 0)
    {
        // Check flags at offset +6 for bit 0 (e.g., "owned" or "needs special delete")
        if ((*(byte*)((int)internalObj + 6) & 1) != 0)
        {
            // Custom cleanup routine (e.g., delete internal buffers)
            customCleanup(); // FUN_004218d0
            // Clear the flag to avoid double cleanup
            *(ushort*)((int)internalObj + 6) = *(ushort*)((int)internalObj + 6) & 0xfffe;
        }
        
        // Release memory or perform final destruction
        freeObject(); // FUN_00420ee0
        finalCleanup(); // FUN_00421140
        return 1;
    }
    
    return 0;
}