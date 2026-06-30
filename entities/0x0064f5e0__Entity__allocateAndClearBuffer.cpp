// FUNC_NAME: Entity::allocateAndClearBuffer

void Entity::allocateAndClearBuffer() {
    // Field at +0x210: pointer to a 0x1000-byte temporary buffer
    if (this->bufferPtr == nullptr) {
        // Allocate 4KB buffer (likely via malloc or new)
        this->bufferPtr = malloc(0x1000);
        // Zero-initialize the buffer in 4-byte chunks
        for (int i = 0; i < 0x1000; i += 4) {
            *(uint32_t*)((uint8_t*)this->bufferPtr + i) = 0;
        }
    }
}