// FUNC_NAME: initDefaultArraySlot

// Address: 0x0069f0e0
// Initializes a slot in a global array with stride 0x14 (20 bytes).
// Structure contains two uint64 fields (offsets 0x00, 0x08) and one uint32 field (offset 0x10).
// Likely used for animation or input configuration data.

// Assumed global declarations (inferred from offsets)
extern uint64 g_defaultField0;   // 0x00e50be4
extern uint64 g_defaultField8;   // 0x00e50bec
extern uint32 g_defaultField10;  // 0x00e50bf4
extern uint32 g_someCountSrc;    // 0x00e50bc4
extern uint32 g_someCount;       // 0x00e50bcc

struct SlotStruct {              // size = 0x14
    uint64 field0;               // +0x00
    uint64 field8;               // +0x08
    uint32 field10;              // +0x10
};
extern SlotStruct g_slotArray[]; // base at 0x00e50bd0

void initDefaultArraySlot(int index)
{
    g_someCount = g_someCountSrc;
    g_slotArray[index].field0  = g_defaultField0;
    g_slotArray[index].field8  = g_defaultField8;
    g_slotArray[index].field10 = g_defaultField10;
}