// FUNC_NAME: Iterator::next
// Function address: 0x008ebc00
// Role: Advances an iterator over an array of 12-byte structures, returning a pointer to the next element.
// Asserts if the container pointer is null or if the iterator has reached the end.

// Assumes that the container (pointed to by containerPtr) has a "end pointer" at offset +0x4.
// The iterator stores: [containerPtr, currentPtr].
// Returns currentPtr + 0xC (size of each element).

// Note: The assertion function FUN_00b97aea is likely EATS_Assert or similar debug macro.
void __fastcall assert(bool condition); // proto for assertion

struct Iterator
{
    void* containerPtr;   // +0x00: pointer to container (e.g., array/vector)
    void* currentPtr;     // +0x04: current element pointer

    // Returns pointer to the next element (if valid) or asserts.
    void* next()
    {
        // Assert container is not null
        if (containerPtr == nullptr)
        {
            assert(false);
        }

        // Assert we haven't reached the end (end pointer stored at container+0x4)
        if (currentPtr == *(void**)((char*)containerPtr + 0x4))
        {
            assert(false);
        }

        // Advance by element size (0xC = 12 bytes)
        return (char*)currentPtr + 0xC;
    }
};