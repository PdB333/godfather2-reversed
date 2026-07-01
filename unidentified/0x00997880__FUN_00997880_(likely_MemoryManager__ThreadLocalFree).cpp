// FUNC_NAME: FUN_00997880 (likely MemoryManager::ThreadLocalFree)
// Function: Deallocates a count of elements of size 0x10 (shifted left 4) from a thread-local allocator. 
// The TLS index is stored at global 0x01139810. The type tag 0x17 is passed to the actual free routine.
void __fastcall MemoryManager::ThreadLocalFree(int *this_ptr)
{
    int count;
    // param_1[2] is at offset +0x08: number of elements to free
    count = this_ptr[2];
    if (count >= 0) {
        // Fetch thread-local storage handle (may be unused in release, or used for validation)
        TlsGetValue(DAT_01139810);
        // Actual deallocation: pointer at [this_ptr], size = count * 0x10, tag = 0x17
        FUN_00aa26e0(*this_ptr, count << 4, 0x17);
    }
}