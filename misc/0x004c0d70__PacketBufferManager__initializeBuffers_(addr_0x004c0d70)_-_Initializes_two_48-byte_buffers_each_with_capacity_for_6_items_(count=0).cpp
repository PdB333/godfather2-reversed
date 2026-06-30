// FUNC_NAME: PacketBufferManager::initializeBuffers (addr 0x004c0d70) - Initializes two 48-byte buffers each with capacity for 6 items (count=0)
// The function allocates two buffers of size 0x30 and sets initial count=0 and capacity=6 for each.
void __thiscall PacketBufferManager::initializeBuffers(PacketBufferManager* this) {
    // Allocate first buffer (size 0x30 = 48 bytes, likely for up to 6 items of 8 bytes each)
    this->buffers[0].buffer = allocBuffer(0x30);   // +0x00: buffer pointer
    this->buffers[0].count = 0;                    // +0x04: current count
    this->buffers[0].capacity = 6;                 // +0x08: maximum capacity

    // Allocate second buffer (same size)
    this->buffers[1].buffer = allocBuffer(0x30);   // +0x0C: buffer pointer
    this->buffers[1].count = 0;                    // +0x10: current count
    this->buffers[1].capacity = 6;                 // +0x14: maximum capacity
}