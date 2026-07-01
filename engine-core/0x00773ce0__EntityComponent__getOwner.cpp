// FUNC_NAME: EntityComponent::getOwner
// Function address: 0x00773ce0
// Role: Retrieves the owner entity from a component. The component stores a pointer to a subobject at offset 0xd0,
// and the actual owner object is located 0x48 bytes before that pointer (likely due to multiple inheritance or embedded structure).

int __fastcall EntityComponent::getOwner(int thisPtr)
{
    // Check if the pointer at offset 0xd0 is non-null
    if (*(int*)(thisPtr + 0xd0) != 0) {
        // Return the owner object by subtracting 0x48 from the pointer
        return *(int*)(thisPtr + 0xd0) - 0x48;
    }
    return 0;
}