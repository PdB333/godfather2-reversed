// FUNC_NAME: GodfatherGameManager::GodfatherGameManager
undefined4 * __thiscall GodfatherGameManager::GodfatherGameManager(undefined4 *this, undefined4 contextA, undefined4 contextB)
{
  int *pSubObj;          // piVar1
  int allocResult;       // iVar2
  undefined4 globalVal;  // uVar3
  undefined4 *pRet;      // puVar4

  // Validate/initialize some context? params: (contextA, contextB, 3, 0x46, 3)
  FUN_008022b0(contextA, contextB, 3, 0x46, 3);

  globalVal = DAT_00d5ddec; // global variable (could be a pointer or config)

  // Initialize vtable pointers and other early fields
  this[0x7cd] = 0;                    // +0x1F34: some flag
  this[0x7cc] = &PTR_LAB_00d61acc;   // +0x1F30: vtable or offset
  this[0x7ce] = 0xffffffff;          // +0x1F38: invalid sentinel
  this[0] = &PTR_FUN_00d62d08;       // +0x00: primary vtable
  this[0xf] = &PTR_LAB_00d62cf8;     // +0x3C: vtable
  this[0x12] = &PTR_LAB_00d62cf4;    // +0x48: vtable
  this[0x14] = &PTR_LAB_00d62cf0;    // +0x50: vtable
  this[0x15] = &PTR_LAB_00d62c90;    // +0x54: vtable
  this[0x16] = &PTR_LAB_00d62c28;    // +0x58: vtable
  this[0xe4] = &PTR_LAB_00d62c08;    // +0x390: vtable
  this[0xe5] = &PTR_FUN_00d62bf4;    // +0x394: vtable
  this[0xe8] = &PTR_LAB_00d62bec;    // +0x3A0: vtable
  this[0x7cc] = &PTR_LAB_00d62be4;   // +0x1F30: vtable (updated)
  this[1999] = 0;                    // +0x1F3C: (index 1999 from 0 -> offset 0x1F3C? Actually 1999*4=0x1F3C)
  this[2000] = globalVal;            // +0x1F40: store global
  this[0x7d1] = 0;                   // +0x1F44: flag
  this[0x7d2] = 0xffffffff;          // +0x1F48: sentinel
  this[0x7d4] = 0;                   // +0x1F50: flag
  this[0x7d5] = 0;                   // +0x1F54: flag
  this[0x7d6] = 0;                   // +0x1F58: flag
  this[0x7d7] = 0;                   // +0x1F5C: flag
  this[0x7d8] = 0;                   // +0x1F60: flag
  this[0x7d9] = 0;                   // +0x1F64: flag

  FUN_00722250();                    // unknown sub-init

  this[0x7e6] = 0;                   // +0x1F98: flag
  this[0x7f0] = 0;                   // +0x1FC0: flag

  // Zero out array of shorts (seems like 6 shorts each for multiple entries)
  *(undefined2 *)(this + 0x7f1) = 0;   // +0x1FC4
  *(undefined2 *)((int)this + 0x1fc6) = 0; // +0x1FC6
  this[0x7f2] = 0;                   // +0x1FC8: int
  *(undefined2 *)(this + 0x7f3) = 0; // +0x1FCC
  *(undefined2 *)((int)this + 0x1fce) = 0; // +0x1FCE
  this[0x7f4] = 0;                   // +0x1FD0
  *(undefined2 *)(this + 0x7f5) = 0; // +0x1FD4
  *(undefined2 *)((int)this + 0x1fd6) = 0; // +0x1FD6
  this[0x7f6] = 0;                   // +0x1FD8
  *(undefined2 *)(this + 0x7f7) = 0; // +0x1FDC
  *(undefined2 *)((int)this + 0x1fde) = 0; // +0x1FDE
  this[0x7f8] = 0;                   // +0x1FE0
  *(undefined2 *)(this + 0x7f9) = 0; // +0x1FE4
  *(undefined2 *)((int)this + 0x1fe6) = 0; // +0x1FE6
  this[0x7fa] = 0;                   // +0x1FE8
  *(undefined2 *)(this + 0x7fb) = 0; // +0x1FEC
  *(undefined2 *)((int)this + 0x1fee) = 0; // +0x1FEE
  this[0x7fc] = 0;                   // +0x1FF0
  *(undefined2 *)(this + 0x7fd) = 0; // +0x1FF4
  *(undefined2 *)((int)this + 0x1ff6) = 0; // +0x1FF6
  this[0x7fe] = 0;                   // +0x1FF8
  *(undefined2 *)(this + 0x7ff) = 0; // +0x1FFC
  *(undefined2 *)((int)this + 0x1ffe) = 0; // +0x1FFE

  this[0x801] = 0;                   // +0x2004
  this[0x802] = 0;                   // +0x2008
  this[0x803] = 0;                   // +0x200C pointer field (later freed if non-null)
  this[0x804] = 0;                   // +0x2010
  this[0x805] = 0;                   // +0x2014
  this[0x806] = 0;                   // +0x2018

  // Debug sentinels (4 ints each) for multiple sub-structures
  this[0x807] = 0xbadbadba;          // +0x201C
  this[0x808] = 0xbeefbeef;          // +0x2020
  this[0x809] = 0xeac15a55;          // +0x2024
  this[0x80a] = 0x91100911;          // +0x2028
  this[0x80d] = 0xeac15a55;          // +0x2034
  this[0x80b] = 0xbadbadba;          // +0x202C
  this[0x80c] = 0xbeefbeef;          // +0x2030
  this[0x80e] = 0x91100911;          // +0x2038
  this[0x80f] = 0;                   // +0x203C
  this[0x810] = 0;                   // +0x2040
  this[0x811] = 0;                   // +0x2044
  this[0x812] = 0;                   // +0x2048

  // More sentinel blocks (appears to be an array of 4-int groups for debug)
  this[0x81b] = 0xeac15a55;
  this[0x819] = 0xbadbadba;
  this[0x81a] = 0xbeefbeef;
  this[0x81c] = 0x91100911;
  this[0x81f] = 0xeac15a55;
  this[0x81d] = 0xbadbadba;
  this[0x81e] = 0xbeefbeef;
  this[0x820] = 0x91100911;
  this[0x823] = 0xeac15a55;
  this[0x821] = 0xbadbadba;
  this[0x822] = 0xbeefbeef;
  this[0x824] = 0x91100911;
  this[0x827] = 0xeac15a55;
  this[0x825] = 0xbadbadba;
  this[0x826] = 0xbeefbeef;
  this[0x828] = 0x91100911;

  this[0x82f] = 0;                   // +0x20BC
  this[0x830] = 0;                   // +0x20C0
  this[0x831] = 0;                   // +0x20C4
  this[0x832] = 0;                   // +0x20C8

  // Another array of short pairs (like padding for other sub-system)
  this[0x834] = 0;                   // +0x20D0
  *(undefined2 *)(this + 0x835) = 0;// +0x20D4
  *(undefined2 *)((int)this + 0x20d6) = 0;
  this[0x836] = 0;                   // +0x20D8
  *(undefined2 *)(this + 0x837) = 0;
  *(undefined2 *)((int)this + 0x20de) = 0;
  this[0x838] = 0;                   // +0x20E0
  *(undefined2 *)(this + 0x839) = 0;
  *(undefined2 *)((int)this + 0x20e6) = 0;
  this[0x83a] = 0;                   // +0x20E8
  *(undefined2 *)(this + 0x83b) = 0;
  *(undefined2 *)((int)this + 0x20ee) = 0;
  this[0x83c] = 0;                   // +0x20F0
  *(undefined2 *)(this + 0x83d) = 0;
  *(undefined2 *)((int)this + 0x20f6) = 0;
  this[0x83e] = 0;                   // +0x20F8
  *(undefined2 *)(this + 0x83f) = 0;
  *(undefined2 *)((int)this + 0x20fe) = 0;

  this[0x841] = 0;                   // +0x2104
  this[0x842] = 0;                   // +0x2108
  this[0x843] = 0;                   // +0x210C
  this[0x844] = 0;                   // +0x2110
  this[0x845] = 0;                   // +0x2114
  this[0x846] = 0;                   // +0x2118
  *(undefined1 *)(this + 0x847) = 0; // byte at +0x211C
  this[0x848] = 0;                   // +0x2120
  this[0x84d] = 0;                   // +0x2134
  this[0x84e] = 0;                   // +0x2138

  // More sentinel blocks
  this[0x851] = 0xeac15a55;
  this[0x84f] = 0xbadbadba;
  this[0x850] = 0xbeefbeef;
  this[0x852] = 0x91100911;
  this[0x855] = 0xeac15a55;
  this[0x853] = 0xbadbadba;
  this[0x854] = 0xbeefbeef;
  this[0x856] = 0x91100911;
  this[0x859] = 0xeac15a55;
  this[0x857] = 0xbadbadba;
  this[0x858] = 0xbeefbeef;
  this[0x85a] = 0x91100911;

  this[0x85d] = 0;                   // +0x2174
  globalVal = DAT_00d5ccf8;         // Another global variable
  this[0x85b] = 1;                   // +0x216C
  this[0x85c] = 0;                   // +0x2170
  this[0x85e] = 0;                   // +0x2178
  this[0x85f] = 0;                   // +0x217C
  this[0x864] = globalVal;           // +0x2190

  FUN_00718750();
  FUN_007325b0();

  globalVal = DAT_00d62b58;         // Another global

  // Final sentinel block for sub-system initialization
  this[0x997] = 0xbadbadba;
  this[0x998] = 0xbeefbeef;
  this[0x999] = 0xeac15a55;
  this[0x99a] = 0x91100911;
  this[0x99b] = globalVal;
  this[0x99c] = globalVal;
  this[0x99d] = 5;                   // +0x2674: some count
  this[0x99e] = 0;                   // +0x2678
  this[0x99f] = 0;                   // +0x267C
  this[0x9a0] = 0;                   // +0x2680
  this[0x9a1] = 0;                   // +0x2684
  this[0x9a2] = 0;                   // +0x2688
  this[0x9a3] = 0;                   // +0x268C
  this[0x9a4] = 0;                   // +0x2690

  FUN_007f7cf0();

  // Clear the sentinel blocks (probably to indicate initialization complete)
  this[0x81c] = 0;
  this[0x81b] = 0;
  this[0x81a] = 0;
  this[0x819] = 0;
  this[0x820] = 0;
  this[0x81f] = 0;
  this[0x81e] = 0;
  this[0x81d] = 0;
  this[0x824] = 0;
  this[0x823] = 0;
  this[0x822] = 0;
  this[0x821] = 0;
  this[0x828] = 0;
  this[0x827] = 0;
  this[0x826] = 0;
  this[0x825] = 0;

  this[0x7d5] = 0;
  this[0x7f0] = 0;
  this[0x7f8] = 0;
  this[0x7f2] = 0;
  this[0x7f4] = 0;
  this[0x7f6] = 0;
  this[0x7fa] = 0;
  this[0x7fc] = 0;
  this[0x800] = 0;                   // +0x2000
  this[0x7d3] = 0;                   // +0x1F4C
  this[0x834] = 0;
  this[0x836] = 0;
  this[0x838] = 0;
  this[0x83a] = 0;
  this[0x83c] = 0;
  this[0x83e] = 0;

  // Register a console variable "use_csa" (probably Client-Side Authority?)
  FUN_00408240(&DAT_0112add0, PTR_s_use_csa_00e5188c);

  this[0x815] = 0;                   // +0x2054
  this[0x816] = 0;
  this[0x817] = 0;
  this[0x818] = 0;

  this[0x7e7] = 0;                   // +0x1F9C
  this[0x7e8] = 0;
  this[0x7e9] = 0;
  this[0x7ea] = 0;
  this[0x7eb] = 0;
  this[0x7ec] = 0xffffffff;          // +0x1FB0

  this[0x82f] = 0;
  this[0x830] = 0;
  this[0x831] = 0;
  this[0x832] = 0;

  this[0x80a] = 0;
  this[0x809] = 0;
  this[0x808] = 0;
  this[0x807] = 0;

  // Check/free a sub-object pointer at +0x200C
  pSubObj = this + 0x803;            // address of pointer at offset 0x200C
  this[0x80e] = 0;
  this[0x80d] = 0;
  this[0x80c] = 0;
  this[0x80b] = 0;
  if (*pSubObj != 0) {
    FUN_004daf90(pSubObj);           // likely destroy the pointed object
    *pSubObj = 0;
  }

  // Clear the final sentinel block (the one at high offset 0x99a..)
  this[0x99a] = 0;
  this[0x999] = 0;
  this[0x998] = 0;
  this[0x997] = 0;

  this[0x833] = 0;                   // +0x20CC
  this[0x84a] = 0;                   // +0x2128
  this[0x84b] = 0;                   // +0x212C
  this[0x84c] = 0xffffffff;          // +0x2130
  this[0x829] = 0;                   // +0x20A4
  this[0x82a] = 0;
  this[0x82b] = 0;
  this[0x82c] = 0;
  this[0x82d] = 0;
  this[0x82e] = 0;

  FUN_004706f0(0);                   // some initialization (passing 0)

  this[0x7da] = 0;                   // +0x1F68

  // Allocate 0x28 bytes for a sub-object (probably a structure of 10 ints)
  allocResult = FUN_009c8e50(0x28);
  if (allocResult == 0) {
    globalVal = 0;
  } else {
    globalVal = FUN_0071ee20(this);  // construct sub-object using this as owner
  }
  this[0x849] = globalVal;           // +0x2124 store sub-object pointer

  // Clear sentinel at +0x213C (maybe just debug indicator)
  this[0x852] = 0;
  this[0x851] = 0;
  this[0x850] = 0;
  this[0x84f] = 0;

  // Copy or initialize a 4-int block from contextA into offset +0x215C
  FUN_0045da60(this + 0x857, contextA); // copies something from contextA to this+0x215C

  pRet = (undefined4 *)FUN_0045d9e0(contextA); // get pointer from contextA
  this[0x853] = *pRet;               // +0x214C
  this[0x854] = pRet[1];             // +0x2150
  this[0x855] = pRet[2];             // +0x2154
  this[0x856] = pRet[3];             // +0x2158

  this[0x85c] = 0;                   // +0x2170

  // Zero out 0x40 bytes (64 bytes) at offset +0x2188
  FUN_004dde90(this + 0x862, 0x40);

  this[0x860] = 0;                   // +0x2180

  return this;
}