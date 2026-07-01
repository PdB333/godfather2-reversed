// FUNC_NAME: Vector::init
void __fastcall Vector::init(int thisPtr)
{
    // +0x04: data pointer (void*)
    // +0x08: capacity (uint)
    // +0x0C: count (uint)

    int* data = *(int**)(thisPtr + 4);       // offset 4
    uint capacity = *(uint*)(thisPtr + 8);   // offset 8

    // Call initialization routine (likely copies or constructs elements from a default)
    FUN_0088faf0(data, capacity);

    // Set element count to 0
    *(uint*)(thisPtr + 0xC) = 0;

    // If capacity is greater than 1, perform additional initialization on the data buffer
    if (1 < capacity) {
        FUN_009c8f10(data);
    }
}