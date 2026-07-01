// FUNC_NAME: NetPacket::initSentinels

#define SENTINEL_1 0xbadbadba
#define SENTINEL_2 0xbeefbeef
#define SENTINEL_3 0xeac15a55
#define SENTINEL_4 0x91100911

// Base class init (likely virtual or common initialization)
void NetPacket::baseInit(void); // external, at 0x00941ee0

// Initializes packet structure with sentinel values for debugging
// param1 stored at +0x00, param2 stored at +0x70 (offset 0x1c * 4)
void NetPacket::initSentinels(uint32_t param1, uint32_t param2) {
    baseInit();
    this->field_0x00 = param1;               // +0x00: usually packet type / identifier
    this->field_0x70 = param2;               // +0x70: secondary parameter (e.g., size)
    this->field_0x60 = SENTINEL_1;           // +0x60: start magic
    this->field_0x64 = SENTINEL_2;           // +0x64: 
    this->field_0x68 = SENTINEL_3;           // +0x68
    this->field_0x6c = SENTINEL_4;           // +0x6c: end magic
}