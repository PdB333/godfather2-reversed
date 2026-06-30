// FUNC_NAME: UnknownClass::zeroInit
// Address: 0x004c2840
// Role: Initializes a large block of memory (struct/class instance) to zero. Used as a constructor helper.
// The loop zeros 64*8=512 bytes (64 iterations, 2 ints each), then explicitly zeros a field at offset 0x80.

void UnknownClass::zeroInit() {
    int* data = reinterpret_cast<int*>(this);
    int count = 0x3f; // 63, but loop runs 64 times due to do-while condition
    do {
        *data = 0;
        data[1] = 0;
        data += 2;
        count--;
    } while (count > -1); // Equivalent to count >= 0

    // Explicitly zero the field at offset 0x80 (128 bytes) – may be a pointer/flag
    *(reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(this) + 0x80)) = 0;
}