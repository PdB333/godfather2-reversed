// FUNC_NAME: EARSList::incrementSize
// 0x004cf240: Increments the size field of a list container, throwing an exception if it would overflow.
// The size field is at offset +0x1c from the list object.
// The sentinel value 0x3fffffff (max for signed 30-bit) triggers the overflow error.
void EARSList::incrementSize()
{
    // Check for overflow (size already at maximum allowed)
    if (*(int*)((char*)this + 0x1c) == 0x3fffffff)
    {
        // Report length error and throw std::exception
        // FUN_0043f9f0 appears to be std::_Xlength_error or similar
        FUN_0043f9f0("list<T> too long", 0x10);
        std::_Throw(new std::exception("list<T> too long")); // reconstructed throw
        // Note: The original code constructs an exception object on the stack,
        // but the decompiled output is messy; we simplify here.
        // Local destruction of string buffers omitted for clarity.
    }
    // Increment the size/length field
    *(int*)((char*)this + 0x1c) = *(int*)((char*)this + 0x1c) + 1;
}