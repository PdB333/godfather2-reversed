// FUNC_NAME: Player::writeDebugSnapshot
// Address: 0x007a52a0
// Description: Debug state dumper for Player class. Writes various player state segments
// based on a bitmask. Called from debug console or network snapshot code.

#include <cstdint>

// Forward declarations of helper functions (implementations elsewhere)
extern bool isDebugConsoleOpen();                   // FUN_0089c630
extern uint32_t processDebugCommand(uint32_t cmd, uint32_t flags, uint32_t extra); // FUN_00806f70
extern void writeDebugChunk(uint32_t size, void *data); // FUN_0064b810 - writes raw data
extern void writeDebugString(const char *str, uint32_t maxLen); // FUN_0064c760 - writes string with max length
extern uint32_t getNthDebugValue(uint32_t index);    // FUN_00700090
extern void writeTransform(uint32_t extra, float transform[4]); // FUN_004a9cf0 - writes a transform (quaternion+pos?)

// Constants for bitmask bits
enum DebugDumpBits {
    kDumpBasicInfo     = 1 << 0,   // Name, ID, flags
    kDumpFlag7         = 1 << 7,   // Unused? masked initially
    kDumpAnimState1    = 1 << 9,   // +0x2670  (0x20 bytes)
    kDumpAnimState2    = 1 << 10,  // +0x2658
    kDumpAnimState3    = 1 << 11,  // +0x264c
    kDumpAnimState4    = 1 << 12,  // +0x2664
    kDumpAnimState5    = 1 << 13,  // +0x26f0
    kDumpArray6        = 1 << 14,  // 6 items from array function
    kDumpTransform     = 1 << 16,  // Position/rotation at +0x30f4
    kDumpExtraInt      = 1 << 17,  // Int at +0x3108
    kDumpGlobalData    = 1 << 15,  // Global data if basic info also set and global condition
};

uint32_t __thiscall Player::writeDebugSnapshot(uint32_t cmd, uint32_t flags, uint32_t extra) {
    // this offset base: param_1
    uint32_t ret;

    // If debug console is open, restrict flags to basic info and flag7? (mask = 0x81)
    if (isDebugConsoleOpen()) {
        flags &= 0x81;
    }

    uint32_t currentFlags = flags;

    // Process main debug command (probably returns some result)
    ret = processDebugCommand(cmd, flags, extra);

    // Always write some base flags from +0x2444, +0x2448, +0x2447
    writeDebugChunk(0x20, (void*)(*(uint32_t*)(this + 0x2444) >> 0x17 & 0xffffff01));  // likely misdecompiled, ignore
    writeDebugChunk(0x20, (void*)(*(uint32_t*)(this + 0x2448) >> 7 & 0xffffff01));     // same pattern
    writeDebugChunk(0x20, (void*)(*(uint8_t*)(this + 0x2447) & 1));

    // Bit 0: Dump basic info (name, ID, strings)
    if (currentFlags & kDumpBasicInfo) {
        writeDebugString((const char*)(this + 0x30c4), 1);  // single byte? or string
        uint32_t id = *(uint32_t*)(this + 0x30c0);
        writeDebugChunk(0x20, &id);

        // Three name strings
        const char* name1 = *(const char**)(this + 0x258);
        if (name1 == nullptr) name1 = &DAT_0120546e; // placeholder
        writeDebugString(name1, 0xff);

        const char* name2 = *(const char**)(this + 0x268);
        if (name2 == nullptr) name2 = &DAT_0120546e;
        writeDebugString(name2, 0xff);

        const char* name3 = *(const char**)(this + 0x278);
        if (name3 == nullptr) name3 = &DAT_0120546e;
        writeDebugString(name3, 0xff);
    }

    // Bit 9: Dump animation state at +0x2670
    if (currentFlags & (1 << 9)) {
        uint32_t data = *(uint32_t*)(this + 0x2670);
        writeDebugChunk(0x20, &data);
    }

    // Bit 10: +0x2658
    if (currentFlags & (1 << 10)) {
        uint32_t data = *(uint32_t*)(this + 0x2658);
        writeDebugChunk(0x20, &data);
    }

    // Bit 11: +0x264c
    if (currentFlags & (1 << 11)) {
        uint32_t data = *(uint32_t*)(this + 0x264c);
        writeDebugChunk(0x20, &data);
    }

    // Bit 12: +0x2664
    if (currentFlags & (1 << 12)) {
        uint32_t data = *(uint32_t*)(this + 0x2664);
        writeDebugChunk(0x20, &data);
    }

    // Bit 13: +0x26f0
    if (currentFlags & (1 << 13)) {
        uint32_t data = *(uint32_t*)(this + 0x26f0);
        writeDebugChunk(0x20, &data);
    }

    // Bit 14: Dump 6 items from an array (e.g., crew members, weapons)
    if (currentFlags & (1 << 14)) {
        for (uint32_t i = 0; i < 6; i++) {
            uint32_t val = getNthDebugValue(i);
            writeDebugChunk(0x20, &val);
        }
    }

    // Bit 16: Dump transform (position/rotation) from +0x30f4
    if (currentFlags & (1 << 16)) {
        float transform[4];
        transform[0] = *(float*)(this + 0x30f4);
        transform[1] = *(float*)(this + 0x30f8);
        transform[2] = *(float*)(this + 0x30fc);
        transform[3] = *(float*)(this + 0x3100);
        writeTransform(extra, transform);
    }

    // Bit 17: Dump extra integer at +0x3108
    if (currentFlags & (1 << 17)) {
        uint32_t extraVal = *(uint32_t*)(this + 0x3108);
        writeDebugChunk(0x20, &extraVal);
    }

    // Bit 15 combined with bit 0: Dump global data if basic info is set and a global condition holds
    if ((currentFlags & kDumpBasicInfo) && (* (int*)(DAT_01223484 + 8) == 0)) {
        // DAT_01223484 is a global structure; condition likely checks if something is not null
        // If condition holds, write two values from another global
        uint32_t global1 = *(uint32_t*)(DAT_0112991c + 0x1c);
        writeDebugChunk(0x20, &global1);
        uint32_t global2 = *(uint32_t*)(DAT_0112991c + 0x20);
        writeDebugChunk(0x20, &global2);
    }

    return ret;
}