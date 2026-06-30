// FUNC_NAME: RandomSizedBuffer::init
struct RandomSizedBuffer {
    int* data;  // +0x00
    int size;   // +0x04
};

void __thiscall RandomSizedBuffer::init(void) {
    // Seed random number generator
    FUN_0065bdf0();
    // Get random value for sizing
    uint randVal = FUN_0065bf40();
    // Compute element count: (rand % 261)*2 + 255 => range [255, 775]
    int newCount = (randVal % 0x105) * 2 + 0xff;
    this->size = newCount;

    // Allocate buffer: newCount * 4 bytes (each element is 4 bytes)
    this->data = (int*)FUN_0065bd60(newCount * 4);

    // Zero-initialize the buffer
    for (uint i = 0; i < (uint)this->size; i++) {
        this->data[i] = 0;
    }
    return;
}