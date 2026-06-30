// FUNC_NAME: NetPacketPool::allocatePacketNode

// Function at 0x004cac00
// Allocates a 24-byte packet node from the internal pool and initializes it.
// The class this pointer contains:
//   +0x04: pointer to allocator vtable (object with allocate(void* this, uint size, void* hint) method)
//   +0x08: hint pointer (previously freed node or null)
// The allocated structure (PacketNode) layout (0x18 bytes):
//   +0x00: undefined4 field_0
//   +0x04: undefined4 field_4
//   +0x08: undefined4 field_8
//   +0x14: byte flag1 (set to 1)
//   +0x15: byte flag2 (set to 0)

class NetPacketPool {
public:
    struct PacketNode {
        uint field_0;  // +0x00
        uint field_4;  // +0x04
        uint field_8;  // +0x08
        byte pad[0x0C]; // unused gap
        byte flag1;     // +0x14 (set to 1 on allocation)
        byte flag2;     // +0x15 (set to 0 on allocation)
        // total 0x18 bytes
    };

    // +0x04: allocator vtable pointer
    struct AllocatorVTable {
        void* (__thiscall *allocate)(void* self, uint size, void* hint);
    } *allocator;

    // +0x08: hint pointer (previous free node address, or null)
    void* hint;

    PacketNode* allocatePacketNode() {
        PacketNode* node;
        void* hintPtr;

        // If no hint available, use a local zeroed buffer
        if (this->hint == 0) {
            uint hintBuffer[3] = {0,0,0};
            hintPtr = hintBuffer;
        } else {
            hintPtr = this->hint;
        }

        // Call allocator's allocate method
        node = (PacketNode*)this->allocator->allocate(this->allocator, 0x18, hintPtr);
        if (node != 0) {
            node->field_0 = 0;
            node->field_4 = 0;
            node->field_8 = 0;
            node->flag2 = 0; // +0x15
            node->flag1 = 1; // +0x14
        }
        return node;
    }
};