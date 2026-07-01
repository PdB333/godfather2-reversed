// FUNC_NAME: TNLConnection::receiveReliablePacket

// External functions (reversed from callees)
extern int calculatePacketHash(void* packetHeader);       // FUN_00540cc0
extern int createReliablePacket(TNLConnection* conn, int sequence, int packetId, int hash); // FUN_0054df10
extern void executeReliablePacket(int reliablePacket);    // FUN_0054e3d0

// Class: TNLConnection (networking layer, EA EARS modification of TNL)
// Field offsets (in bytes from this):
// +0x1C94: int mReliablePacketSequence  (param_1[0x725])
// +0x1C98: int mReliablePacketId        (param_1[0x726])
// +0x1C84: int mCurrentReliablePacket   (param_1[0x721])
// +0x0828: packet header buffer         (param_1 + 0x20a)

void __thiscall TNLConnection::receiveReliablePacket()
{
    // Call virtual preprocess handler at vtable offset 0x2f4 (slot 189)
    (*(void (__thiscall**)(TNLConnection*))(*(int*)this + 0x2f4))(this);

    int sequence = *(int*)((char*)this + 0x1C94);
    int packetId = *(int*)((char*)this + 0x1C98);
    int hash = calculatePacketHash((char*)this + 0x828);
    int reliablePacket = createReliablePacket(this, sequence, packetId, hash);
    *(int*)((char*)this + 0x1C84) = reliablePacket;
    executeReliablePacket(reliablePacket);
}