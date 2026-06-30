// FUNC_NAME: PlayerActionableInfo::constructor
void __thiscall PlayerActionableInfo::constructor(void *this)
{
  // Call base class constructor (likely EARSObject or similar)
  FUN_00581960();
  
  // Set vtable pointer
  *(undefined4 **)this = &PTR_FUN_00e3abe4;
  
  // Get the "invalid" or default value from global
  undefined4 invalidValue = DAT_00e2b1a4;
  
  // Initialize all actionable info slots (0x1c to 0xaf)
  // Each slot appears to be a 4-byte value with a pattern:
  // - offset 0: 0 (type/state)
  // - offset 2: 0xFFFF (invalid/empty ID)
  // - offset 4: 0xFFFF (invalid/empty ID)
  // - offset 6: invalidValue (some default)
  
  // Slot 0 (offset 0x1c = 28 bytes from start)
  *(int *)((int)this + 0x70) = 0;           // +0x70: type/state
  *(short *)((int)this + 0x74) = -1;        // +0x74: ID1
  *(short *)((int)this + 0x76) = -1;        // +0x76: ID2
  *(int *)((int)this + 0x78) = invalidValue; // +0x78: value
  
  // Slot 1 (offset 0x20)
  *(int *)((int)this + 0x80) = 0;           // +0x80
  *(int *)((int)this + 0x84) = 0;           // +0x84
  *(int *)((int)this + 0x88) = 0;           // +0x88
  *(int *)((int)this + 0x8C) = invalidValue; // +0x8C
  
  // Slot 2 (offset 0x24)
  *(int *)((int)this + 0x90) = 0;           // +0x90
  *(int *)((int)this + 0x94) = 0;           // +0x94
  *(int *)((int)this + 0x98) = 0;           // +0x98
  *(int *)((int)this + 0x9C) = invalidValue; // +0x9C
  
  // Slot 3 (offset 0x40)
  *(int *)((int)this + 0x100) = 0;          // +0x100
  *(int *)((int)this + 0x10C) = 0;          // +0x10C
  *(int *)((int)this + 0x130) = invalidValue; // +0x130
  
  // Slot 4 (offset 0x54)
  *(int *)((int)this + 0x150) = 0;          // +0x150
  *(int *)((int)this + 0x158) = 0;          // +0x158
  *(int *)((int)this + 0x154) = 0;          // +0x154
  *(int *)((int)this + 0x15C) = invalidValue; // +0x15C
  
  // Slot 5 (offset 0x58)
  *(int *)((int)this + 0x160) = 0;          // +0x160
  *(int *)((int)this + 0x168) = 0;          // +0x168
  *(int *)((int)this + 0x164) = 0;          // +0x164
  *(int *)((int)this + 0x16C) = invalidValue; // +0x16C
  
  // Slot 6 (offset 0x60)
  *(int *)((int)this + 0x180) = 0;          // +0x180
  *(int *)((int)this + 0x184) = 0;          // +0x184
  *(int *)((int)this + 0x188) = 0;          // +0x188
  *(int *)((int)this + 0x18C) = invalidValue; // +0x18C
  
  // Slot 7 (offset 0x64)
  *(int *)((int)this + 0x190) = 0;          // +0x190
  *(int *)((int)this + 0x194) = 0;          // +0x194
  *(int *)((int)this + 0x198) = 0;          // +0x198
  *(int *)((int)this + 0x19C) = invalidValue; // +0x19C
  
  // Slot 8 (offset 0x6c)
  *(int *)((int)this + 0x1B0) = 0;          // +0x1B0
  *(int *)((int)this + 0x1B4) = 0;          // +0x1B4
  *(int *)((int)this + 0x1B8) = 0;          // +0x1B8
  *(int *)((int)this + 0x1BC) = invalidValue; // +0x1BC
  
  // Slot 9 (offset 0x70)
  *(int *)((int)this + 0x1C0) = 0;          // +0x1C0
  *(int *)((int)this + 0x1C4) = 0;          // +0x1C4
  *(int *)((int)this + 0x1C8) = 0;          // +0x1C8
  *(int *)((int)this + 0x1CC) = invalidValue; // +0x1CC
  
  // Slot 10 (offset 0x78)
  *(int *)((int)this + 0x1E0) = 0;          // +0x1E0
  *(int *)((int)this + 0x1E4) = 0;          // +0x1E4
  *(int *)((int)this + 0x1E8) = 0;          // +0x1E8
  *(int *)((int)this + 0x1EC) = invalidValue; // +0x1EC
  
  // Slot 11 (offset 0x7c)
  *(int *)((int)this + 0x1F0) = 0;          // +0x1F0
  *(int *)((int)this + 0x1F4) = 0;          // +0x1F4
  *(int *)((int)this + 0x1F8) = 0;          // +0x1F8
  *(int *)((int)this + 0x1FC) = invalidValue; // +0x1FC
  
  // Slot 12 (offset 0x84)
  *(int *)((int)this + 0x210) = 0;          // +0x210
  *(int *)((int)this + 0x214) = 0;          // +0x214
  *(int *)((int)this + 0x218) = 0;          // +0x218
  *(int *)((int)this + 0x21C) = invalidValue; // +0x21C
  
  // Slot 13 (offset 0x88)
  *(int *)((int)this + 0x220) = 0;          // +0x220
  *(int *)((int)this + 0x224) = 0;          // +0x224
  *(int *)((int)this + 0x228) = 0;          // +0x228
  *(int *)((int)this + 0x22C) = invalidValue; // +0x22C
  
  // Slot 14 (offset 0x90)
  *(int *)((int)this + 0x240) = 0;          // +0x240
  *(int *)((int)this + 0x244) = 0;          // +0x244
  *(int *)((int)this + 0x248) = 0;          // +0x248
  *(int *)((int)this + 0x24C) = invalidValue; // +0x24C
  
  // Slot 15 (offset 0x94)
  *(int *)((int)this + 0x250) = 0;          // +0x250
  *(int *)((int)this + 0x254) = 0;          // +0x254
  *(int *)((int)this + 0x258) = 0;          // +0x258
  *(int *)((int)this + 0x25C) = invalidValue; // +0x25C
  
  // Slot 16 (offset 0x9c)
  *(int *)((int)this + 0x270) = 0;          // +0x270
  *(int *)((int)this + 0x274) = 0;          // +0x274
  *(int *)((int)this + 0x278) = 0;          // +0x278
  *(int *)((int)this + 0x27C) = invalidValue; // +0x27C
  
  // Slot 17 (offset 0xa0)
  *(int *)((int)this + 0x280) = 0;          // +0x280
  *(int *)((int)this + 0x284) = 0;          // +0x284
  *(int *)((int)this + 0x288) = 0;          // +0x288
  *(int *)((int)this + 0x28C) = invalidValue; // +0x28C
  
  // Slot 18 (offset 0xa8)
  *(int *)((int)this + 0x2A0) = 0;          // +0x2A0
  *(int *)((int)this + 0x2A4) = 0;          // +0x2A4
  *(int *)((int)this + 0x2A8) = 0;          // +0x2A8
  *(int *)((int)this + 0x2AC) = invalidValue; // +0x2AC
  
  // Slot 19 (offset 0xac)
  *(int *)((int)this + 0x2B0) = 0;          // +0x2B0
  *(int *)((int)this + 0x2B4) = 0;          // +0x2B4
  *(int *)((int)this + 0x2B8) = 0;          // +0x2B8
  *(int *)((int)this + 0x2BC) = invalidValue; // +0x2BC
}