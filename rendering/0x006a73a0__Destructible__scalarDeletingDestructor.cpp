// FUNC_NAME: Destructible::scalarDeletingDestructor
// Function address: 0x006a73a0
// Role: Scalar deleting destructor for a 0x78-byte object (Destructible).
// First calls the actual destructor (FUN_006a7240), then optionally frees memory
// based on the least significant bit of the flag (param_2).

void __thiscall Destructible::scalarDeletingDestructor(byte flag)
{
    // Call the virtual destructor implementation (FUN_006a7240)
    this->destructor();
    
    // If the low bit of flag is set, free the object's memory (size 0x78)
    if ((flag & 1) != 0) {
        // FUN_0043b960 is the custom memory deallocation (operator delete with size)
        ::operator delete(this, 0x78);
    }
}