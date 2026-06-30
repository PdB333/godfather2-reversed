// FUNC_NAME: TNLConnection::TNLConnection
class TNLConnection {
public:
    TNLConnection(void* param_2) {
        // Call base class constructor (likely TNLObject or similar)
        // param_2 might be a pointer to a parent or configuration
        FUN_0046c590(param_2);

        // Set virtual function table pointers (multiple inheritance)
        *(void**)this = &PTR_FUN_00e32fe4;            // +0x00: primary vtable
        *(void**)((char*)this + 0x3C) = &PTR_LAB_00e33000; // +0x3C: second vtable
        *(void**)((char*)this + 0x48) = &PTR_LAB_00e33010; // +0x48: third vtable

        // Initialize all member variables to zero
        // Sequence/ack array pairs? (12 shorts total)
        *(short*)((char*)this + 0x54) = 0;  // +0x54
        *(short*)((char*)this + 0x56) = 0;  // +0x56
        *(short*)((char*)this + 0x5C) = 0;  // +0x5C
        *(short*)((char*)this + 0x5E) = 0;  // +0x5E
        *(short*)((char*)this + 0x64) = 0;  // +0x64
        *(short*)((char*)this + 0x66) = 0;  // +0x66
        *(short*)((char*)this + 0x6C) = 0;  // +0x6C
        *(short*)((char*)this + 0x6E) = 0;  // +0x6E
        *(short*)((char*)this + 0x80) = 0;  // +0x80
        *(short*)((char*)this + 0x82) = 0;  // +0x82
        *(short*)((char*)this + 0x88) = 0;  // +0x88
        *(short*)((char*)this + 0x8A) = 0;  // +0x8A

        // Packet/connection state fields (9 ints)
        *(int*)((char*)this + 0x50) = 0;  // +0x50: e.g., mSendSequence
        *(int*)((char*)this + 0x58) = 0;  // +0x58: e.g., mRecvSequence
        *(int*)((char*)this + 0x60) = 0;  // +0x60
        *(int*)((char*)this + 0x68) = 0;  // +0x68
        *(int*)((char*)this + 0x70) = 0;  // +0x70
        *(int*)((char*)this + 0x74) = 0;  // +0x74
        *(int*)((char*)this + 0x78) = 0;  // +0x78
        *(int*)((char*)this + 0x7C) = 0;  // +0x7C
        *(int*)((char*)this + 0x84) = 0;  // +0x84
    }
};