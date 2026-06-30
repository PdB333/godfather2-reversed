// FUNC_NAME: ArrayManager::resize
void ArrayManager::resize(uint requestedSize)
{
    // s_capacity is the current capacity (number of elements)
    // s_buffer is the pointer to the dynamic array of 8-byte elements
    if (s_capacity < requestedSize) {
        // Round up to next multiple of 16 to reduce reallocations
        uint newCapacity = requestedSize + (0x10 - (requestedSize & 0xf));
        // Allocate new buffer: each element is 8 bytes
        void* newBuffer = _malloc(newCapacity * 8);
        void* oldBuffer = s_buffer;
        s_buffer = newBuffer;
        // Copy or reinitialize data from old buffer to new buffer
        FUN_0065b3c0(); // likely copyBuffer(oldBuffer, newBuffer, oldCapacity)
        s_buffer = oldBuffer; // temporarily restore old pointer for free? Actually the code sets s_buffer = uVar1 (old) then frees old, then sets s_buffer = newBuffer. So the copy function might use s_buffer as destination.
        _free(oldBuffer);
        s_capacity = newCapacity;
        s_buffer = newBuffer;
    }
}