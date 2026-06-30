// FUNC_NAME: UnknownClass::preparePacket
// Function address: 0x005571f0
// Role: Constructs and sends a network packet with a global constant and virtual call

void __thiscall preparePacket(void* this) {
    // Stack buffer for packet data (12 bytes)
    uint8_t packetBuffer[12];
    // Zero-initialized fields
    uint32_t field1 = 0;  // local_84
    uint32_t field2 = 0;  // local_74
    uint32_t field3 = 0;  // local_64
    // Global packet type constant
    uint32_t packetType = DAT_00e2b1a4;  // local_54
    // Flag indicating this packet should be sent
    uint32_t sendFlag = 1;  // uStack_94

    // Pointer to beginning of packet buffer (used as output parameter)
    uint8_t* bufferPtr = packetBuffer;  // puStack_9c
    // Secondary buffer for additional data (8 bytes)
    uint8_t secondBuffer[8];  // auStack_5c

    // Offset +0x48: pointer to some object (unused here)
    void* objAt0x48 = *(void**)((unsigned char*)this + 0x48);  // iStack_98

    // Virtual function call via vtable pointer at this+0x44, offset 0x90.
    // This likely writes sequence numbers or timestamps into packetBuffer or modifies stack.
    void* vtable = *(void**)((unsigned char*)this + 0x44);
    void (*__thiscall vfunc)(void) = (void (__thiscall*)(void))*(unsigned int*)((unsigned char*)vtable + 0x90);
    vfunc();  // May also set stack values (uStack_6c, uStack_68) indirectly

    // Copy stack values – likely from results of the virtual call or previous initialization
    uint32_t tmp1 = 0;  // uStack_6c (uninitialized; kept for reconstruction)
    uint32_t tmp2 = 0;  // uStack_68 (uninitialized)
    // These assignments mirror the original decompilation
    // (They might actually be part of a struct copy, but exact purpose unknown)
    uint32_t outputField1 = tmp1;   // uStack_2c
    uint32_t outputField2 = tmp2;   // uStack_28
    uint32_t outputField3 = field3; // uStack_24
    uint32_t outputField4 = packetType; // uStack_20

    // Serialize or finalize the packet (function 0x004b59d0)
    // Takes pointer to bufferPtr and secondBuffer
    FUN_004b59d0(&bufferPtr, secondBuffer);

    // Process the packet on this object (function 0x00aa1fc0)
    FUN_00aa1fc0(this);

    // If a pointer at offset +0x40 is non-null, free the secondary buffer
    if (*(void**)((unsigned char*)this + 0x40) != 0) {
        FUN_009f4cd0(secondBuffer);  // cleanup
    }

    return;
}