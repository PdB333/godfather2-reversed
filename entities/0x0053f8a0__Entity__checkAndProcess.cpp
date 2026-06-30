// FUNC_NAME: Entity::checkAndProcess
// Address: 0x0053f8a0
// Role: Guards a processing subroutine by checking a flag (bit 0 at offset +0x5c).
// If the flag is clear, calls the actual processing function; otherwise does nothing.
// The flag likely indicates whether the entity has already been processed in this frame.

// Forward declaration of the processing subroutine (address 0x0053f930)
void processInternal();

class Entity {
public:
    // +0x5c: uint8_t flags; bit0 = processed flag
    // Other members omitted for clarity
};

void Entity::checkAndProcess() {
    // Check if the processed flag (bit 0) is clear
    if (!(*(uint8_t*)((uintptr_t)this + 0x5c) & 1)) {
        processInternal(); // perform the actual processing
    }
}