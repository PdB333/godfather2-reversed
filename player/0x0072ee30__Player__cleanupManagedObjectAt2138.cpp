// FUNC_NAME: Player::cleanupManagedObjectAt2138
// Function address: 0x0072ee30
// Role: Releases a managed sub-object at offset 0x2138 if it exists.
// Callees: FUN_008c74d0 (likely a release/destroy function), FUN_007196a0 (possibly a delete operator)

void __fastcall Player::cleanupManagedObjectAt2138(Player* thisPtr)
{
    // Check if the sub-object pointer at offset +0x2138 is non-null
    if (*(int*)((uint8_t*)thisPtr + 0x2138) != 0) {
        // Call release/destroy function on the sub-object
        FUN_008c74d0(*(int*)((uint8_t*)thisPtr + 0x2138));
        // Call another cleanup function (likely destructor or deallocation)
        FUN_007196a0(*(int*)((uint8_t*)thisPtr + 0x2138));
    }
}