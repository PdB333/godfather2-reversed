// FUNC_NAME: reference_counted_assign
// Address: 0x006ff440
// Copies an 8-byte value and a 4-byte value from source to target object fields.
// If the object's reference count (field at +0x1c) is non-zero, decrements it or releases something.
void reference_counted_assign(void* target, void* source) // target = param_1, source = param_2
{
    // Copy first 8 bytes (likely a pointer or 64-bit value) to offset +0x10
    *(uint64_t*)((char*)target + 0x10) = *(uint64_t*)source;
    
    // Copy next 4 bytes (likely length or flags) to offset +0x18
    *(int32_t*)((char*)target + 0x18) = *(int32_t*)((char*)source + 8);
    
    // Check reference count at +0x1c
    if (*(int32_t*)((char*)target + 0x1c) != 0) {
        // Decrement or release the source? Called function at 0x006fbed0 likely handles cleanup.
        FUN_006fbed0(source);
    }
}