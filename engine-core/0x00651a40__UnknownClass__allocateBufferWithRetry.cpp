// FUNC_NAME: UnknownClass::allocateBufferWithRetry
void UnknownClass::allocateBufferWithRetry(uint count) // count passed via EAX
{
    // EAX: desired number of elements (each element is 4 bytes)
    if ((int)count < 1) {
        count = 0;
    }
    else {
        // Check for overflow: if (0xffffffff / count) < 4 => product would overflow 32-bit
        if ((0xffffffff / count) < 4) {
            // Throw a std::exception (or similar) via function pointer at DAT_0113d3a0
            void* exceptData[3];
            exceptData[0] = &PTR_LAB_00e31050; // some exception type
            exceptData[1] = 0;
            // Call the throw function if available
            if (DAT_0113d3a0 != nullptr) {
                ((void(*)(void**))DAT_0113d3a0)(exceptData);
            }
            // Call the destructor or cleanup
            ((void(*)(void))exceptData[2])();
            std::_Throw((exception*)&exceptData); // std::_Throw is internal MSVC, replaces with throw;
        }
    }

    int* ptr = 0;
    // Attempt allocation, halving count on failure until success or count <= 0
    while ((int)count > 0) {
        ptr = (int*)FUN_00ba1adf(count * 4, &DAT_0113d3a4); // alloc function (malloc-like)
        if (ptr != 0) break;
        count = (int)count / 2;
    }

    // Store results in instance fields (offset 0: pointer, offset 4: count)
    this->_buffer = ptr;      // *this = ptr  (unaff_EDI[0])
    this->_count = count;     // *(this+4) = count (unaff_EDI[1])
}