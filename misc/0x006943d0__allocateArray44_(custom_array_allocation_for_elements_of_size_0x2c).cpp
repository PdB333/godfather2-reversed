// FUNC_NAME: allocateArray44 (custom array allocation for elements of size 0x2c)
void* __cdecl allocateArray44(size_t elementCount) {
    // Handle zero-element allocation via internal allocator
    if (elementCount == 0) {
        return internalAlloc(0); // FUN_009c8e50(0)
    }

    // Overflow check: ensure elementCount * 0x2c <= 0xffffffff
    if ((unsigned int)(0xffffffff / elementCount) < 0x2c) {
        // Throw std::bad_alloc using engine exception mechanism
        // Exception descriptor at PTR_LAB_00e31050
        struct ExceptionData {
            void* vtable;          // +0x00
        };
        ExceptionData exceptionData;
        exceptionData.vtable = (void*)&PTR_LAB_00e31050;
        // Global exception handler (if set)
        if (DAT_0113d3a0 != nullptr) {
            ((void (__cdecl*)(ExceptionData*))DAT_0113d3a0)(&exceptionData);
        }
        // Call destructor/throw helper from vtable
        ((void (__cdecl*)(ExceptionData*))(((void**)exceptionData.vtable)[2]))(&exceptionData);
        std::_Throw((std::exception*)&exceptionData);
    }

    return internalAlloc(elementCount * 0x2c); // FUN_009c8e50(param_1 * 0x2c)
}