// FUNC_NAME: Manager::releaseFixedArray
// Function address: 0x007dc070
// Role: Releases an array of 16 handles/pointers using a cleanup function, zeroes them, then zeroes three preceding fields.

__thiscall void Manager::releaseFixedArray(void* thisPtr)
{
    // Structure layout (thisPtr):
    //   offset 0x00: field0 (int)
    //   offset 0x04: field1 (int)
    //   offset 0x08: field2 (int)
    //   offset 0x0C: handles[16] (uint) – each element likely a resource handle or pointer

    uint* arrayStart = static_cast<uint*>(thisPtr) + 3; // +3 uint = +12 bytes
    int remaining = 16;
    do {
        FUN_00852ce0(*arrayStart); // Cleanup/destructor for handle
        *arrayStart = 0;           // Invalidate handle
        arrayStart++;
        remaining--;
    } while (remaining != 0);

    static_cast<uint*>(thisPtr)[2] = 0;
    static_cast<uint*>(thisPtr)[1] = 0;
    static_cast<uint*>(thisPtr)[0] = 0;
}