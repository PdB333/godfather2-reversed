// FUNC_NAME: BEMAllocator::initializeGlobal
#include <cstdint>

// Global structure initialized by this function, located at 0x1218fd8
struct BEMConfig {
    void*    unknownPtr1;        // +0x00 (points to PTR_LAB_00e37870)
    void*    unknownPtr2;        // +0x04 (points to DAT_00e3781c)
    uint32_t magic;              // +0x08 (0x2e62656d = ".bem")
    uint32_t field_0C;           // +0x0C
    uint32_t blockSize;          // +0x10 (4)
    uint32_t field_14;           // +0x14
    uint32_t maxBlocks;          // +0x18 (0x800 = 2048)
    uint32_t field_1C;           // +0x1C
    uint32_t field_20;           // +0x20
    uint32_t field_24;           // +0x24
};

static BEMConfig g_BEMConfig;

BEMConfig* BEMAllocator::initializeGlobal()
{
    g_BEMConfig.unknownPtr1 = (void*)0x00e37870;   // &PTR_LAB_00e37870
    g_BEMConfig.unknownPtr2 = (void*)0x00e3781c;   // &DAT_00e3781c
    g_BEMConfig.magic       = 0x2e62656d;          // ".bem"
    g_BEMConfig.field_0C    = 0;
    g_BEMConfig.blockSize   = 4;
    g_BEMConfig.field_14    = 0;
    g_BEMConfig.maxBlocks   = 0x800;
    g_BEMConfig.field_1C    = 0;
    g_BEMConfig.field_20    = 0;
    g_BEMConfig.field_24    = 0;
    return &g_BEMConfig;
}