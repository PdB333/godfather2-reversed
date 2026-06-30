// FUNC_NAME: std::_Throw_length_error
// Address: 0x005d9ed0
// Internal STL function to throw a std::length_error exception with message "vector<T> too long"
void std::_Throw_length_error()
{
    // Local exception object and cleanup structures
    char excBuffer[0x40];          // local_40: buffer for exception object
    uint32_t cleanupState1;        // local_3c: cleanup flag for first allocated buffer
    int32_t exceptionHandle;       // local_2c: exception handle (0)
    uint32_t cleanupFlag;          // local_28: cleanup flag (0xF)
    void** vtablePtr;              // local_24: vtable pointer for exception
    const char* message;           // local_20: exception message
    uint32_t bufferPtr;            // local_18: pointer to dynamically allocated buffer for exception object
    int32_t isDynamic;             // local_8: flag indicating dynamic allocation (0)
    uint32_t cleanupState2;        // local_4: cleanup flag for second allocated buffer (0xF)

    // Initialize cleanup state (mask lower byte to zero)
    cleanupState1 = cleanupState1 & 0xFFFFFF00; // uninitialized, but later overwritten
    cleanupFlag = 0xF;
    exceptionHandle = 0;

    // First call: output error message
    FUN_0043f9f0("vector<T> too long", 0x12); // maybe __std_exception_message or similar

    message = "unknown";                     // local_20: default message (overwritten below)
    vtablePtr = &PTR_FUN_00da9810;          // vtable for exception base class
    cleanupState2 = 0xF;

    // Initialize exception object in excBuffer
    FUN_0043eeb0(excBuffer, 0, 0xFFFFFFFF); // likely _CxxThrowException or __std_exception_copy

    vtablePtr = &PTR_FUN_00da9828;          // vtable for length_error

    // Custom exception translator? Check if hook exists
    if (DAT_0113d3a0 != 0)
    {
        (*DAT_0113d3a0)(&vtablePtr);        // call translator with address of vtable
    }

    // Throw the exception using the vtable
    (*(code*)vtablePtr[2])();               // vtable[2] is the _Throw function pointer

    // If we reach here, throw succeeded so this code is rarely executed
    std::_Throw((std::exception*)&vtablePtr);

    // Cleanup for dynamic allocation if large
    vtablePtr = &PTR_FUN_00da9810;
    if (0xF < cleanupState2)
    {
        FUN_009c8eb0(bufferPtr);            // deallocate dynamic buffer
    }
    isDynamic = 0;
    bufferPtr = bufferPtr & 0xFFFFFF00;
    cleanupState2 = 0xF;

    vtablePtr = &PTR_LAB_00e31044;          // final cleanup vtable

    if (0xF < cleanupFlag)
    {
        FUN_009c8eb0(cleanupState1);        // deallocate first dynamic buffer (if any)
    }

    return; // unreachable normally
}