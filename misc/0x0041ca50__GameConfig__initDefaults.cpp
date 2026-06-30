// FUNC_NAME: GameConfig::initDefaults

struct GameConfigData {
    uint32_t field_0x00; // +0x00
    uint32_t field_0x04; // +0x04
    uint32_t someFlags;  // +0x08
    uint32_t pointerOrValue; // +0x0C
    uint32_t toggleA;    // +0x10, default 1
    uint32_t toggleB;    // +0x14, default 1
    uint32_t value0x18;  // +0x18
    uint32_t value0x1C;  // +0x1C
    uint32_t value0x20;  // +0x20
    uint32_t value0x24;  // +0x24
    uint32_t value0x28;  // +0x28
    uint32_t ptr0x2C;    // +0x2C
    uint32_t ptr0x30;    // +0x30 (same as ptr0x2C)
    uint32_t value0x34;  // +0x34
    uint32_t value0x38;  // +0x38
    uint32_t zero0x3C;   // +0x3C
    uint32_t zero0x40;   // +0x40
    uint32_t zero0x44;   // +0x44
    uint32_t zero0x48;   // +0x48
    uint32_t value0x4C;  // +0x4C
    uint32_t zero0x50;   // +0x50
    uint32_t zero0x54;   // +0x54
    uint32_t zero0x58;   // +0x58
    uint32_t zero0x5C;   // +0x5C
    uint32_t value0x60;  // +0x60
    uint32_t zero0x64;   // +0x64
    uint32_t zero0x68;   // +0x68
    uint32_t zero0x6C;   // +0x6C
    uint32_t zero0x70;   // +0x70
};

static GameConfigData& g_config = *(GameConfigData*)0x01206a78;

uint32_t* GameConfig::initDefaults()
{
    // Initialize configuration defaults from game constants
    g_config.value0x1C  = 0x00e44630; // +0x1C: unknown default
    g_config.value0x24  = 0x00e2fc48; // +0x24
    g_config.value0x28  = 0x00e2cb90; // +0x28
    g_config.ptr0x2C    = 0x00e2b1a4; // +0x2C: pointer to default array
    g_config.ptr0x30    = 0x00e2b1a4; // +0x30: duplicate pointer
    g_config.someFlags  = 0;          // +0x08: cleared
    g_config.pointerOrValue = 0;      // +0x0C: cleared
    g_config.value0x34  = 0x00e2cd48; // +0x34
    g_config.value0x18  = 0x00e3ac58; // +0x18
    g_config.value0x20  = 0x00e3ac58; // +0x20 (same as +0x18)
    g_config.value0x38  = 0x00e3ac58; // +0x38 (same value)
    g_config.value0x4C  = 0x00e2cd54; // +0x4C
    g_config.toggleA    = 1;          // +0x10: enabled
    g_config.toggleB    = 1;          // +0x14: enabled
    g_config.zero0x3C   = 0;          // +0x3C
    g_config.zero0x40   = 0;          // +0x40
    g_config.zero0x44   = 0;          // +0x44
    g_config.zero0x48   = 0;          // +0x48
    g_config.zero0x50   = 0;          // +0x50
    g_config.zero0x54   = 0;          // +0x54
    g_config.zero0x58   = 0;          // +0x58
    g_config.zero0x5C   = 0;          // +0x5C
    g_config.value0x60  = 0x00e2b118; // +0x60: default value
    g_config.zero0x64   = 0;          // +0x64
    g_config.zero0x68   = 0;          // +0x68
    g_config.zero0x6C   = 0;          // +0x6C
    g_config.zero0x70   = 0;          // +0x70
    return (uint32_t*)&g_config;
}