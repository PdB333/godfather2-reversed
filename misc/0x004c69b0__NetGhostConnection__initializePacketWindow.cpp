// FUNC_NAME: NetGhostConnection::initializePacketWindow
// Function address: 0x004c69b0
// Role: Initializes a network connection's packet window structure (TNL 32-slot window) with sentinel values.

extern uint32_t INVALID_HANDLE;   // from DAT_00e2b1a4 (sentinel for unused ghost/object handles)
extern uint32_t INVALID_SEQUENCE; // from DAT_00e2e230 (sentinel for invalid packet sequence numbers)

class NetGhostConnection {
public:
    void __thiscall initializePacketWindow();
};

void NetGhostConnection::initializePacketWindow()
{
    uint32_t* base = reinterpret_cast<uint32_t*>(this);
    uint32_t uVar1 = INVALID_HANDLE;
    uint32_t uVar2 = INVALID_SEQUENCE;

    // Fields at offsets 0x00, 0x04, 0x08 (probably flags/counters)
    base[0] = 0;
    base[1] = 0;
    base[2] = 0;

    // Fields at offsets 0x90-0xCC (indices 0x24-0x33)
    base[0x24] = 0;   // +0x90
    base[0x25] = 0;   // +0x94
    base[0x26] = 0;   // +0x98
    base[0x27] = 0;   // +0x9C
    base[0x28] = 0;   // +0xA0
    base[0x29] = 0;   // +0xA4
    base[0x2A] = 0;   // +0xA8
    base[0x2B] = uVar1;   // +0xAC
    base[0x2E] = uVar2;   // +0xB8
    base[0x2F] = 0;   // +0xBC
    base[0x30] = 0;   // +0xC0
    base[0x31] = 0;   // +0xC4
    base[0x32] = 0;   // +0xC8
    base[0x33] = 0;   // +0xCC
    base[0x2C] = uVar1;   // +0xB0
    base[0x2D] = uVar1;   // +0xB4

    // Initialize two 64-byte (16 dword) packet window slots starting at offset 0x10
    // Each slot holds a fixed pattern: 4 ghost handles (at offsets 0,5,10,15) and 12 zero paddings.
    uint32_t* slotWrite = base + 0x0C; // point to index 12 (offset 48)
    int slotCount = 2;
    do {
        slotWrite[-8] = uVar1;  // index  4
        slotWrite[-7] = 0;      // index  5
        slotWrite[-6] = 0;      // index  6
        slotWrite[-5] = 0;      // index  7
        slotWrite[-4] = 0;      // index  8
        slotWrite[-3] = uVar1;  // index  9
        slotWrite[-2] = 0;      // index 10
        slotWrite[-1] = 0;      // index 11
        slotWrite[0]  = 0;      // index 12
        slotWrite[1]  = 0;      // index 13
        slotWrite[2]  = uVar1;  // index 14
        slotWrite[3]  = 0;      // index 15
        slotWrite[4]  = 0;      // index 16
        slotWrite[5]  = 0;      // index 17
        slotWrite[6]  = 0;      // index 18
        slotWrite[7]  = uVar1;  // index 19
        slotWrite += 0x10;      // advance by 16 dwords (64 bytes) to next slot
        slotCount--;
    } while (slotCount != 0);
}