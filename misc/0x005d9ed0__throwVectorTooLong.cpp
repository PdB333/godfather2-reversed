// FUNC_NAME: throwVectorTooLong
// Throws a length_error with the message "vector<T> too long".
// Called internally by EA STL vector when reserve would exceed max_size.
// Reconstructed from Ghidra at 0x005d9ed0.
void throwVectorTooLong()
{
    // Exception object storage (size 0x40)
    char exceptionObj[0x40];          // local_40
    uint32_t flags;                   // local_3c
    // Vtable pointer for exception type
    void **vtablePtr;                 // local_24

    flags &= 0xffffff00;
    // Copy exception message into the object (0x12 = 18, includes null terminator)
    FUN_0043f9f0("vector<T> too long", 0x12);
    // Initialize exception base (first param – object, second – maybe exception code, third – -1)
    FUN_0043eeb0(exceptionObj, 0, 0xffffffff);
    vtablePtr = &PTR_FUN_00da9828;   // +0x00 vtable for length_error

    // Optional custom throw handler registered by the engine
    if (DAT_0113d3a0 != nullptr)
    {
        DAT_0113d3a0(&vtablePtr);
    }

    // Perform the actual throw via vtable function index 2 (likely __cxa_throw)
    (*(void (*)())(vtablePtr[2]))();

    // Cleanup path (never reached if throw succeeds)
    vtablePtr = &PTR_FUN_00da9810;
    if (0xf < /* local_4 */ ???)
    {
        FUN_009c8eb0(/* local_18 */);
    }
    // ... further cleanup omitted
}