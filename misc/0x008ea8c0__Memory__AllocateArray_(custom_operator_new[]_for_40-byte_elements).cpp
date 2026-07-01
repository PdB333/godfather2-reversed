// FUNC_NAME: Memory::AllocateArray (custom operator new[] for 40-byte elements)
// Address: 0x008ea8c0
// Allocates an array of elements of size 0x28 (40 bytes) with overflow checking.
// Throws std::exception on arithmetic overflow before allocation.

void* Memory::AllocateArray(uint elementCount) {
    if (elementCount == 0) {
        elementCount = 0; // intentional no-op to suppress warning
    } else if ((0xFFFFFFFF / elementCount) < 0x28) {
        // Overflow would occur – prepare and throw an exception
        struct ExceptionInfo {
            void** vtable;    // +0x00: pointer to type's vtable (std::exception)
            int reasonCode;   // +0x04: likely 0 for overflow
        };
        ExceptionInfo local;
        local.vtable = &PTR_LAB_00e31050; // global static vtable for exception type
        local.reasonCode = 0;
        if (DAT_0113d3a0 != nullptr) {
            DAT_0113d3a0(&local); // custom exception hook (e.g., __CxxSetUnhandledExceptionFilter)
        }
        (*(code*)local.vtable[2])(); // invoke virtual destructor/thrower
        std::_Throw((exception*)&local); // standard MSVC throw helper
    }
    // Call internal allocator (likely operator new) with total size
    return FUN_009c8e50(elementCount * 0x28);
}