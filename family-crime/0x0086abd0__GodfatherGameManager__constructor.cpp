// FUNC_NAME: GodfatherGameManager::constructor
undefined4 * __thiscall GodfatherGameManager::constructor(undefined4 *this, undefined4 param_2)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  
  // Call base class constructor
  FUN_00879160(param_2);
  
  // Load global constants
  uVar4 = DAT_00d75880;
  uVar3 = DAT_00d756ec;
  uVar2 = DAT_00d5ccf8;
  
  // Set vtable pointer
  *this = &PTR_FUN_00d759c0;  // +0x00 vtable
  
  // Initialize various vtable entries and pointers
  this[0xf] = &PTR_LAB_00d759b0;   // +0x3C
  this[0x12] = &PTR_LAB_00d759ac;  // +0x48
  this[0x14] = &PTR_LAB_00d759a8;  // +0x50
  this[0x15] = &PTR_LAB_00d75948;  // +0x54
  this[0x16] = &PTR_LAB_00d758e0;  // +0x58
  this[0xb8] = &PTR_FUN_00d758c8;  // +0x2E0
  this[0xb9] = &PTR_LAB_00d758b4;  // +0x2E4
  this[0x1ec] = &PTR_LAB_00d758a0; // +0x7B0
  
  // Initialize game state fields
  this[0x3c8] = 0;                  // +0xF20
  this[0x3c9] = uVar2;              // +0xF24
  this[0x3ca] = 0;                  // +0xF28
  this[0x3cb] = 0;                  // +0xF2C
  this[0x3cc] = 0;                  // +0xF30
  
  // Magic numbers for validation
  this[0x3d1] = 0xbadbadba;         // +0xF44
  this[0x3d2] = 0xbeefbeef;         // +0xF48
  this[0x3d3] = 0xeac15a55;         // +0xF4C
  this[0x3d4] = 0x91100911;         // +0xF50
  
  this[0x3d5] = uVar3;              // +0xF54
  this[0x3d6] = _DAT_00d5780c;      // +0xF58
  
  uVar3 = DAT_00e44750;
  puVar1 = this + 0xf;              // Pointer to +0x3C area
  
  this[0x3d7] = DAT_00e44750;       // +0xF5C
  this[0x3da] = uVar3;              // +0xF68
  this[0x3dc] = uVar3;              // +0xF70
  
  uVar3 = DAT_00e44868;
  this[0x3db] = uVar4;              // +0xF6C
  this[0x3df] = uVar3;              // +0xF7C
  
  uVar3 = DAT_00d5ef70;
  this[0x3e0] = uVar4;              // +0xF80
  
  uVar4 = DAT_00d75764;
  this[999] = uVar3;                // +0xF9C
  
  uVar3 = DAT_00d5eee4;
  this[0x3f3] = uVar4;              // +0xFCC
  
  uVar4 = DAT_00d75778;
  
  // Initialize more fields to zero
  this[0x3d8] = 0;                  // +0xF60
  this[0x3d9] = 0;                  // +0xF64
  this[0x3dd] = 0;                  // +0xF74
  this[0x3de] = 0;                  // +0xF78
  this[0x3e4] = 0;                  // +0xF90
  this[0x3e5] = 0;                  // +0xF94
  this[1000] = 0;                   // +0xFA0
  this[0x3e9] = 0;                  // +0xFA4
  this[0x3f0] = 0;                  // +0xFC0
  this[0x3f1] = uVar3;              // +0xFC4
  this[0x3f2] = uVar3;              // +0xFC8
  this[0x3f6] = 0;                  // +0xFD8
  this[0x3f7] = 0;                  // +0xFDC
  this[0x3fe] = 0;                  // +0xFF8
  this[0x402] = 0;                  // +0x1008
  this[0x406] = 0;                  // +0x1018
  this[0x40a] = uVar4;              // +0x1028
  this[0x40b] = uVar3;              // +0x102C
  this[0x40c] = 0;                  // +0x1030
  this[0x40d] = uVar2;              // +0x1034
  
  // Initialize invalid IDs
  this[0x3f4] = 0xffffffff;         // +0xFD0
  this[0x3f5] = 0xffffffff;         // +0xFD4
  
  // Initialize more fields
  this[0x40e] = 0;                  // +0x1038
  this[0x40f] = 0;                  // +0x103C
  this[0x410] = 0;                  // +0x1040
  this[0x411] = 0;                  // +0x1044
  this[0x412] = 0;                  // +0x1048
  this[0x413] = 0;                  // +0x104C
  
  // Call another initialization function
  FUN_005fdac0();
  
  uVar4 = DAT_00e44850;
  uVar3 = _DAT_00d5c458;
  uVar2 = _DAT_00d5780c;
  
  this[0x465] = 0;                  // +0x1194
  this[0x466] = 0;                  // +0x1198
  
  // Re-initialize some fields
  this[0x3d0] = uVar2;              // +0xF40
  this[0x3cf] = uVar2;              // +0xF3C
  this[0x3ce] = uVar2;              // +0xF38
  this[0x3ca] = 0;                  // +0xF28
  this[0x3d4] = 0;                  // +0xF50
  this[0x3d3] = 0;                  // +0xF4C
  this[0x3d2] = 0;                  // +0xF48
  this[0x3d1] = 0;                  // +0xF44
  this[0x401] = 0;                  // +0x1004
  this[0x400] = 0;                  // +0x1000
  this[0x3ff] = 0;                  // +0xFFC
  this[0x3e1] = 0;                  // +0xF84
  
  uVar2 = _DAT_00d7575c;
  this[0x3e2] = uVar4;              // +0xF88
  this[0x3e3] = 0;                  // +0xF8C
  
  // Set self-reference and function pointers
  this[0x43f] = this;               // +0x10FC
  this[0x43c] = FUN_00867d40;       // +0x10F0
  this[0x43d] = &LAB_0086aba0;      // +0x10F4
  
  FUN_005fea00(uVar2, uVar3);
  
  // Set flags
  this[0x441] = this[0x441] | 0x2400;  // +0x1104
  
  uVar2 = _DAT_00d5c458;
  this[0x443] = 0;                  // +0x110C
  this[0x442] = uVar2;              // +0x1108
  this[0x3ca] = this[0x3ca] & 0xffffcfff;  // +0xF28 clear bits
  
  // Load various data assets if they exist
  if (DAT_0112adb8 != 0) {
    FUN_00408900(puVar1, &DAT_0112adb8, 0x8000);
  }
  if (DAT_0112dfb8 != 0) {
    FUN_00408900(puVar1, &DAT_0112dfb8, 0x8000);
  }
  if (DAT_0112b18c != 0) {
    FUN_00408900(puVar1, &DAT_0112b18c, 0x8000);
  }
  if (DAT_0112fe64 != 0) {
    FUN_00408900(puVar1, &DAT_0112fe64, 0x8000);
  }
  if (DAT_0112b36c != 0) {
    FUN_00408900(puVar1, &DAT_0112b36c, 0x8000);
  }
  if (DAT_0112fc60 != 0) {
    FUN_00408900(puVar1, &DAT_0112fc60, 0x8000);
  }
  
  // Final initialization
  this[0x467] = 0;                  // +0x119C
  this[0x468] = 0;                  // +0x11A0
  
  return this;
}