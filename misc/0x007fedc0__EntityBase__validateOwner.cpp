// FUNC_NAME: EntityBase::validateOwner
// Address: 0x007fedc0
// This function appears to validate the relationship between an entity and its parent/owner.
// It retrieves a handle via a virtual function, then checks if this entity is the direct child of a specific owner.

void __fastcall EntityBase::validateOwner(int *this)
{
    // Virtual call at vtable offset 0x28c - likely returns some identifier or resource handle
    undefined1 handle = (*(code (**)(int *))(*(int *)this + 0x28c))(this);

    // Process the handle (e.g., release reference or update state)
    FUN_00470a10(handle);

    // Check if there is an owner reference (offset 0x1d3 in this object)
    // The value is treated as an integer pointer, possibly an owner ID or pointer cast to int
    int ownerField = this[0x1d3]; // +0x74c

    if (ownerField != 0 && ownerField != 0x48) {
        int basePtr;
        if (ownerField == 0) {
            basePtr = 0;
        } else {
            basePtr = ownerField - 0x48; // Convert owner field to a base pointer (subtract offset 0x48)
        }

        // Dereference a pointer at basePtr + 0x68 to get another object
        int *someObject = (int *)(*(int *)(basePtr + 0x68)); // +0x68 from base

        // Convert that object pointer back by subtracting 0x48 to get the owner's this pointer
        int *ownerThis = (someObject == 0) ? 0 : (int *)((int)someObject - 0x48);

        // If the computed owner matches 'this' and the owner field is non-zero, call the handler again and return
        if (ownerThis == this) {
            if (ownerField != 0) {
                FUN_00470a10(handle);
                return;
            }
            // Otherwise fall through and call the handler again
            FUN_00470a10(handle);
        }
    }

    // Default path: always call the handler once more
    return;
}