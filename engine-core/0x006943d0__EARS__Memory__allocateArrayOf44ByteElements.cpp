// FUNC_NAME: EARS::Memory::allocateArrayOf44ByteElements

void __cdecl allocateArrayOf44ByteElements(uint elementCount)
{
    // 0x2c = 44 bytes per element
    if (elementCount == 0) {
        allocateMemory(0); // Calls internal allocation with zero size
        return;
    }

    // Overflow check: ensure elementCount * 44 fits in unsigned int
    if (elementCount > (0xffffffffu / 0x2c)) {
        // Prepare to throw std::bad_alloc or similar exception
        // Uses static exception descriptor table at PTR_LAB_00e31050
        // and optional error handler at DAT_0113d3a0
        undefined** exceptionDescriptor = &PTR_LAB_00e31050;
        if (DAT_0113d3a0 != nullptr) {
            DAT_0113d3a0(&exceptionDescriptor);
        }
        // Call the exception throw function
        ((void (*)(undefined**))exceptionDescriptor[2])();
        std::_Throw((exception*)&exceptionDescriptor);
    }

    // Allocate memory for elementCount * 44 bytes
    allocateMemory(elementCount * 0x2c);
}