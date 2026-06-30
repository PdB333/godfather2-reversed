// FUNC_NAME: BitSetManager::allocateAndIntersect
int BitSetManager::allocateAndIntersect(int* paramCount, unsigned long long* outHandle)
{
    unsigned int* newBits;
    int iVar3;
    int iVar4;
    unsigned int* oldBitsPtr;
    int localCount;
    unsigned long long oldHandle;

    // Compare the size from the implicit object (this) with the parameter count
    if (*this->count < *paramCount) {
        newBits = (unsigned int*)_calloc(4, 0x40);
        if (newBits == nullptr) {
            return -2;
        }
        iVar3 = FUN_00665ce0(); // Initialize the new bitset buffer
        if (iVar3 != 0) {
            return iVar3;
        }
        iVar3 = *this->count;   // Use the smaller count from this
    } else {
        newBits = (unsigned int*)_calloc(4, 0x40);
        if (newBits == nullptr) {
            return -2;
        }
        iVar3 = FUN_00665ce0(); // Initialize the new bitset buffer
        if (iVar3 != 0) {
            return iVar3;
        }
        iVar3 = *paramCount;    // Use the parameter count
        // Overwrite the implicit pointer to use the second descriptor
        this->data = paramCount; // Actually in_EAX = param_1, meaning this is treated as param_1
    }

    // Perform bitwise AND of the new buffer with bits from the selected descriptor (offset +0x0C)
    for (iVar4 = 0; iVar4 < iVar3; ++iVar4) {
        // newBits[iVar4] is ANDed with the source bits (this->data[iVar4] after adjustment)
        newBits[iVar4] = newBits[iVar4] & *(unsigned int*)((uintptr_t)this->data + iVar4 * 4);
    }

    // If negative count (dead code, but preserved as per decompilation)
    if (iVar4 < 0) {
        for (int i = -iVar4; i != 0; --i) {
            ((unsigned int*)newBits)[iVar4 + i - 1] = 0;
        }
    }

    // Save old handle, then store the new allocated buffer into outHandle
    oldHandle = outHandle[0];               // Original first qword
    oldBitsPtr = (unsigned int*)(outHandle[1] >> 32); // Extract pointer from high 32 bits of second qword

    outHandle[0] = 0x4000000000ULL;         // Magic constant (size/tag)
    outHandle[1] = (unsigned long long)newBits << 32; // Store pointer in upper 32 bits

    // If there was an old buffer, clear it and free
    if (oldBitsPtr != nullptr) {
        // Zero out the old bitset (size stored in low 32 bits of oldHandle)
        memset(oldBitsPtr, 0, (int)oldHandle * 4);
        free(oldBitsPtr);
    }

    return 0;
}