// Xbox PDB: EARS_Modules_Family_Family
// FUNC_NAME: FamilyManager::FamilyManager

#include <cstdint>

// Forward declarations of known classes and functions
class FamilyManager;
void EARSObjectConstructor(void* param_2); // FUN_0046c590
void* operator new(size_t size); // FUN_009c8e80
void registerMessage(const char* messageName, void* handler); // FUN_00408240
void setMessageHandler(void* handler, void* target, uint32_t flags); // FUN_00408900

// Global variables (from decompiled)
extern uint32_t g_someGlobal1; // DAT_00e44758
extern uint32_t g_someGlobal2; // _DAT_00d5780c
extern uint32_t g_someGlobal3; // DAT_00e4475c
extern uint32_t g_someGlobal4; // DAT_00d60c60
extern uint32_t g_someGlobal5; // DAT_00e44600
extern int32_t g_familyManagerInitFlag; // DAT_0112f938
extern int32_t g_unknownPtr; // DAT_0112a668
extern void* g_messageHandlerFamilyEliminated; // DAT_0112f940
extern void* g_someHandler; // DAT_0112fe38

class FamilyManager {
public:
    // Vtable pointer at +0x00
    // Sub-object at +0x3C (offset 0xF * 4 = 0x3C) - likely a message handler
    // Many fields...

    FamilyManager(void* param_2) {
        // Call base class constructor
        EARSObjectConstructor(param_2);

        // Set vtable
        *(void**)this = (void*)0x00d7bcf8; // PTR_FUN_00d7bcf8

        // Initialize sub-object vtable pointers
        *(void**)((uint8_t*)this + 0x3C) = (void*)0x00d7bce8; // +0x3C
        *(void**)((uint8_t*)this + 0x48) = (void*)0x00d7bce4; // +0x48

        // Zero-initialize many fields
        *(uint32_t*)((uint8_t*)this + 0x50) = 0; // +0x50
        *(uint32_t*)((uint8_t*)this + 0x54) = 0; // +0x54
        *(uint32_t*)((uint8_t*)this + 0x64) = 0; // +0x64

        // Store global values
        uint32_t val1 = g_someGlobal1; // DAT_00e44758
        uint32_t val2 = g_someGlobal2; // _DAT_00d5780c

        *(uint32_t*)((uint8_t*)this + 0x68) = 0xFFFFFFFF; // +0x68
        *(uint32_t*)((uint8_t*)this + 0x6C) = 0; // +0x6C
        *(uint32_t*)((uint8_t*)this + 0x70) = 0; // +0x70
        *(uint32_t*)((uint8_t*)this + 0x74) = 0; // +0x74
        *(uint32_t*)((uint8_t*)this + 0x78) = 0; // +0x78
        *(uint32_t*)((uint8_t*)this + 0x7C) = 0; // +0x7C
        *(uint32_t*)((uint8_t*)this + 0x80) = 0; // +0x80
        *(uint32_t*)((uint8_t*)this + 0x84) = 0; // +0x84
        *(uint32_t*)((uint8_t*)this + 0x88) = 0; // +0x88
        *(uint32_t*)((uint8_t*)this + 0x8C) = 0xFFFFFFFF; // +0x8C
        *(uint32_t*)((uint8_t*)this + 0x90) = 0; // +0x90
        *(uint32_t*)((uint8_t*)this + 0x94) = 0; // +0x94
        *(uint32_t*)((uint8_t*)this + 0x98) = 0; // +0x98
        *(uint32_t*)((uint8_t*)this + 0x9C) = 0; // +0x9C
        *(uint32_t*)((uint8_t*)this + 0xA0) = 0; // +0xA0
        *(uint32_t*)((uint8_t*)this + 0xA4) = 0; // +0xA4
        *(uint32_t*)((uint8_t*)this + 0xA8) = 0; // +0xA8
        *(uint32_t*)((uint8_t*)this + 0xAC) = 0; // +0xAC
        *(uint32_t*)((uint8_t*)this + 0xB0) = 0; // +0xB0
        *(uint32_t*)((uint8_t*)this + 0xB4) = 0; // +0xB4
        *(uint32_t*)((uint8_t*)this + 0xB8) = 0; // +0xB8
        *(uint32_t*)((uint8_t*)this + 0xBC) = 0; // +0xBC
        *(uint32_t*)((uint8_t*)this + 0xC0) = 0; // +0xC0
        *(uint32_t*)((uint8_t*)this + 0xC4) = 0; // +0xC4
        *(uint32_t*)((uint8_t*)this + 0xC8) = 0; // +0xC8
        *(uint32_t*)((uint8_t*)this + 0xCC) = 0; // +0xCC

        // Sentinel values for family data (8 entries)
        *(uint32_t*)((uint8_t*)this + 0xCC) = 0xBADBADBA; // +0xCC
        *(uint32_t*)((uint8_t*)this + 0xD0) = 0xBEEFBEEF; // +0xD0
        *(uint32_t*)((uint8_t*)this + 0xD4) = 0xEAC15A55; // +0xD4
        *(uint32_t*)((uint8_t*)this + 0xD8) = 0x91100911; // +0xD8
        *(uint32_t*)((uint8_t*)this + 0xDC) = 0xBADBADBA; // +0xDC
        *(uint32_t*)((uint8_t*)this + 0xE0) = 0xBEEFBEEF; // +0xE0
        *(uint32_t*)((uint8_t*)this + 0xE4) = 0xEAC15A55; // +0xE4
        *(uint32_t*)((uint8_t*)this + 0xE8) = 0x91100911; // +0xE8

        *(uint32_t*)((uint8_t*)this + 0xEC) = 0; // +0xEC
        *(uint32_t*)((uint8_t*)this + 0xF0) = val2; // +0xF0
        *(uint32_t*)((uint8_t*)this + 0x100) = 0; // +0x100
        *(uint32_t*)((uint8_t*)this + 0x104) = 0; // +0x104
        *(uint32_t*)((uint8_t*)this + 0x108) = 0; // +0x108
        *(uint32_t*)((uint8_t*)this + 0x10C) = 0; // +0x10C
        *(uint32_t*)((uint8_t*)this + 0x110) = 0; // +0x110
        *(uint32_t*)((uint8_t*)this + 0x114) = 0; // +0x114
        *(uint32_t*)((uint8_t*)this + 0x118) = 0; // +0x118
        *(uint32_t*)((uint8_t*)this + 0x11C) = 0; // +0x11C
        *(uint32_t*)((uint8_t*)this + 0x120) = 0; // +0x120
        *(uint32_t*)((uint8_t*)this + 0x124) = 0; // +0x124
        *(uint32_t*)((uint8_t*)this + 0x128) = 0; // +0x128
        *(uint32_t*)((uint8_t*)this + 0x12C) = 0; // +0x12C
        *(uint32_t*)((uint8_t*)this + 0x130) = 0; // +0x130
        *(uint32_t*)((uint8_t*)this + 0x134) = 0; // +0x134
        *(uint32_t*)((uint8_t*)this + 0x138) = 0; // +0x138
        *(uint32_t*)((uint8_t*)this + 0x13C) = 0; // +0x13C
        *(uint32_t*)((uint8_t*)this + 0x140) = 0; // +0x140
        *(uint32_t*)((uint8_t*)this + 0x144) = 0; // +0x144
        *(uint32_t*)((uint8_t*)this + 0x148) = 0; // +0x148
        *(uint32_t*)((uint8_t*)this + 0x14C) = 0; // +0x14C
        *(uint32_t*)((uint8_t*)this + 0x150) = 0; // +0x150
        *(uint32_t*)((uint8_t*)this + 0x154) = 0; // +0x154
        *(uint32_t*)((uint8_t*)this + 0x158) = val1; // +0x158

        // Byte at +0x15C
        *(uint8_t*)((uint8_t*)this + 0x15C) = 0; // +0x15C

        *(uint32_t*)((uint8_t*)this + 0x160) = val2; // +0x160
        *(uint32_t*)((uint8_t*)this + 0x164) = val2; // +0x164
        *(uint32_t*)((uint8_t*)this + 0x168) = 0; // +0x168
        *(uint32_t*)((uint8_t*)this + 0x16C) = 0; // +0x16C
        *(uint32_t*)((uint8_t*)this + 0x170) = 0; // +0x170
        *(uint32_t*)((uint8_t*)this + 0x174) = 0; // +0x174
        *(uint32_t*)((uint8_t*)this + 0x178) = 0; // +0x178
        *(uint32_t*)((uint8_t*)this + 0x17C) = 0; // +0x17C
        *(uint32_t*)((uint8_t*)this + 0x180) = 0; // +0x180
        *(uint32_t*)((uint8_t*)this + 0x184) = val2; // +0x184
        *(uint32_t*)((uint8_t*)this + 0x188) = val2; // +0x188
        *(uint32_t*)((uint8_t*)this + 0x18C) = 0; // +0x18C
        *(uint32_t*)((uint8_t*)this + 0x190) = 0; // +0x190
        *(uint32_t*)((uint8_t*)this + 0x194) = 0; // +0x194
        *(uint32_t*)((uint8_t*)this + 0x198) = 0; // +0x198
        *(uint32_t*)((uint8_t*)this + 0x19C) = 0; // +0x19C

        // Allocate 128 bytes for some buffer
        void* buffer = operator new(0x80);
        *(void**)((uint8_t*)this + 0x1A4) = buffer; // +0x1A4
        *(uint32_t*)((uint8_t*)this + 0x1A8) = 0; // +0x1A8
        *(uint32_t*)((uint8_t*)this + 0x1AC) = 0x20; // +0x1AC (size?)

        // More globals
        *(uint32_t*)((uint8_t*)this + 0x1D4) = g_someGlobal3; // +0x1D4
        uint32_t val4 = g_someGlobal4; // DAT_00d60c60
        *(uint32_t*)((uint8_t*)this + 0x1D8) = val4; // +0x1D8
        *(uint32_t*)((uint8_t*)this + 0x1DC) = val4; // +0x1DC
        *(uint32_t*)((uint8_t*)this + 0x1E0) = val4; // +0x1E0
        *(uint32_t*)((uint8_t*)this + 0x1E4) = g_someGlobal5; // +0x1E4
        *(uint32_t*)((uint8_t*)this + 0x1D0) = 0; // +0x1D0
        *(uint32_t*)((uint8_t*)this + 0x1E8) = 0; // +0x1E8
        *(uint32_t*)((uint8_t*)this + 0x1EC) = 0; // +0x1EC

        // Initialize arrays of shorts (8 entries each)
        *(uint16_t*)((uint8_t*)this + 0x1F0) = 0; // +0x1F0
        *(uint16_t*)((uint8_t*)this + 0x1F2) = 0; // +0x1F2
        *(uint32_t*)((uint8_t*)this + 0x1F4) = 0; // +0x1F4
        *(uint16_t*)((uint8_t*)this + 0x1F8) = 0; // +0x1F8
        *(uint16_t*)((uint8_t*)this + 0x1FA) = 0; // +0x1FA
        *(uint32_t*)((uint8_t*)this + 0x1FC) = 0; // +0x1FC
        *(uint16_t*)((uint8_t*)this + 0x200) = 0; // +0x200
        *(uint16_t*)((uint8_t*)this + 0x202) = 0; // +0x202
        *(uint32_t*)((uint8_t*)this + 0x204) = 0; // +0x204
        *(uint16_t*)((uint8_t*)this + 0x208) = 0; // +0x208
        *(uint16_t*)((uint8_t*)this + 0x20A) = 0; // +0x20A
        *(uint32_t*)((uint8_t*)this + 0x20C) = 0; // +0x20C
        *(uint16_t*)((uint8_t*)this + 0x210) = 0; // +0x210
        *(uint16_t*)((uint8_t*)this + 0x212) = 0; // +0x212
        *(uint32_t*)((uint8_t*)this + 0x214) = 0; // +0x214
        *(uint16_t*)((uint8_t*)this + 0x218) = 0; // +0x218
        *(uint16_t*)((uint8_t*)this + 0x21A) = 0; // +0x21A
        *(uint32_t*)((uint8_t*)this + 0x21C) = 0; // +0x21C
        *(uint16_t*)((uint8_t*)this + 0x220) = 0; // +0x220
        *(uint16_t*)((uint8_t*)this + 0x222) = 0; // +0x222
        *(uint32_t*)((uint8_t*)this + 0x224) = 0; // +0x224
        *(uint16_t*)((uint8_t*)this + 0x228) = 0; // +0x228
        *(uint16_t*)((uint8_t*)this + 0x22A) = 0; // +0x22A
        *(uint32_t*)((uint8_t*)this + 0x22C) = 0; // +0x22C
        *(uint32_t*)((uint8_t*)this + 0x230) = 0; // +0x230

        // Initialize global flag if needed
        if (g_familyManagerInitFlag == 0) {
            g_familyManagerInitFlag = *(int32_t*)(g_unknownPtr + 0x18);
        }

        // Zero some fields at +0x58, +0x5C, +0x60
        *(uint32_t*)((uint8_t*)this + 0x58) = 0; // +0x58
        *(uint32_t*)((uint8_t*)this + 0x5C) = 0; // +0x5C
        *(uint32_t*)((uint8_t*)this + 0x60) = 0; // +0x60

        // Zero fields at +0x1B0 to +0x1CC (8 entries)
        *(uint32_t*)((uint8_t*)this + 0x1B0) = 0; // +0x1B0
        *(uint32_t*)((uint8_t*)this + 0x1B4) = 0; // +0x1B4
        *(uint32_t*)((uint8_t*)this + 0x1B8) = 0; // +0x1B8
        *(uint32_t*)((uint8_t*)this + 0x1BC) = 0; // +0x1BC
        *(uint32_t*)((uint8_t*)this + 0x1C0) = 0; // +0x1C0
        *(uint32_t*)((uint8_t*)this + 0x1C4) = 0; // +0x1C4
        *(uint32_t*)((uint8_t*)this + 0x1C8) = 0; // +0x1C8
        *(uint32_t*)((uint8_t*)this + 0x1CC) = 0; // +0x1CC

        // Register message handler for family eliminated
        registerMessage("iMsgFamilyEliminated", &g_messageHandlerFamilyEliminated);

        // Set up message handler if global is non-zero
        if (g_someHandler != 0) {
            setMessageHandler((void*)((uint8_t*)this + 0x3C), &g_someHandler, 0x8000);
        }
    }
};