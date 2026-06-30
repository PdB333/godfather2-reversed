// FUNC_NAME: Packet::CreateNetPacket

struct PacketSubObject {
    void* vtable;       // +0x18 (offset from Packet)
    void* functionPtr;  // +0x1C
    // total size 8 bytes
};

struct Packet {
    void* vtable1;            // +0x00
    uint32_t unknown1;        // +0x04, set to 0
    uint32_t unknown2;        // +0x08, set to 0
    uint32_t unknown3;        // +0x0C, set to 1
    uint32_t unknown4;        // +0x10, set to 0
    PacketSubObject* subObjPtr; // +0x14, points to subObject
    PacketSubObject subObject; // +0x18
    uint32_t param;           // +0x20, stores caller's argument
};

// External references (replace with actual names from Ghidra)
extern void* allocMemory(size_t size);        // FUN_009c8e50
extern void initPacket(Packet* packet);       // FUN_0064ef60
extern void* g_PacketVTable;                  // PTR_LAB_00e43004
extern void* g_PacketExtraVTable;             // PTR_LAB_00e42fec
extern void* g_PacketFunction;                // LAB_00652750
extern uint32_t g_lastPacketParam;            // uRam00000020

void FUN_00650930(void* thisIgnored, uint32_t param2) {
    Packet* packet = (Packet*)allocMemory(0x24);
    if (packet != nullptr) {
        packet->vtable1 = g_PacketVTable;
        packet->unknown1 = 0;
        packet->unknown2 = 0;
        packet->unknown3 = 1;
        packet->unknown4 = 0;
        packet->subObjPtr = &packet->subObject;
        packet->subObject.vtable = g_PacketExtraVTable;
        packet->subObject.functionPtr = g_PacketFunction;
        packet->param = param2;
        initPacket(packet);
    } else {
        g_lastPacketParam = param2;
        initPacket(nullptr);
    }
}