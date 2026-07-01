// Xbox PDB: EARS_Vehicles_WhiteboxCar_WhiteboxCar
// FUNC_NAME: WheeledVehicle::WheeledVehicle
undefined4 * __thiscall WheeledVehicle::WheeledVehicle(undefined4 *this, int actorId)
{
  undefined4 uVar1;
  undefined4 uVar2;
  int *piVar3;
  
  // Call base class constructor (likely Entity or Vehicle base)
  FUN_0055afb0(actorId, 0);
  
  // Initialize vtable and derived class vtable pointers
  this[0x1ed] = 0;                          // +0x7B4
  this[0x1ec] = &PTR_LAB_00d58278;          // +0x7B0
  *this = &PTR_FUN_00d767a0;                // +0x0 vtable
  this[0xf] = &PTR_LAB_00d76790;            // +0x3C
  this[0x12] = &PTR_LAB_00d7678c;           // +0x48
  this[0x14] = &PTR_LAB_00d76788;           // +0x50
  this[0x15] = &PTR_LAB_00d76728;           // +0x54
  this[0x16] = &PTR_LAB_00d766c0;           // +0x58
  this[0xb8] = &PTR_FUN_00d766ac;           // +0x2E0
  this[0xb9] = &PTR_LAB_00d76698;           // +0x2E4
  this[0x1ec] = &PTR_FUN_00d76684;          // +0x7B0
  this[0x1f0] = 0;                           // +0x7C0
  
  // Another constructor stage (maybe initializes core vehicle data)
  FUN_0087f020(actorId);
  
  // Zero out a large block of fields (likely internal state, flags, etc.)
  this[0x274] = 0;                          // +0x9D0
  this[0x275] = 0;                          // +0x9D4
  this[0x276] = 0;                          // +0x9D8
  this[0x277] = 0;                          // +0x9DC
  this[0x278] = 0;                          // +0x9E0
  this[0x279] = 0;                          // +0x9E4
  this[0x27a] = 0;                          // +0x9E8
  this[0x27b] = 0;                          // +0x9EC
  this[0x27c] = 0;                          // +0x9F0
  this[0x27d] = 0;                          // +0x9F4
  this[0x27e] = 0;                          // +0x9F8
  this[0x27f] = 0;                          // +0x9FC
  this[0x280] = 0;                          // +0xA00
  this[0x281] = 0;                          // +0xA04
  this[0x282] = 0;                          // +0xA08
  this[0x283] = 0;                          // +0xA0C
  uVar2 = DAT_00d5ccf8;                     // global default (maybe color/team)
  this[0x287] = 0xffffffff;                 // +0xA1C
  *(undefined1 *)(this + 0x288) = 0;        // +0xA20 byte
  this[0x28b] = uVar2;                      // +0xA2C
  this[0x28f] = 0;                          // +0xA3C
  this[0x290] = 0;                          // +0xA40
  this[0x291] = 0;                          // +0xA44
  this[0x292] = 0;                          // +0xA48
  
  // Debug sentinel patterns for uninitialized fields (4 groups of 4 ints)
  this[0x297] = 0xbadbadba;                 // +0xA5C
  this[0x29b] = 0xbadbadba;                 // +0xA6C
  this[0x29f] = 0xbadbadba;                 // +0xA7C
  this[0x2a3] = 0xbadbadba;                 // +0xA8C
  this[0x298] = 0xbeefbeef;                 // +0xA60
  this[0x29c] = 0xbeefbeef;                 // +0xA70
  this[0x2a0] = 0xbeefbeef;                 // +0xA80
  this[0x2a4] = 0xbeefbeef;                 // +0xA90
  this[0x299] = 0xeac15a55;                 // +0xA64
  this[0x29d] = 0xeac15a55;                 // +0xA74
  this[0x2a1] = 0xeac15a55;                 // +0xA84
  this[0x2a5] = 0xeac15a55;                 // +0xA94
  this[0x29a] = 0x91100911;                 // +0xA68
  this[0x29e] = 0x91100911;                 // +0xA78
  this[0x2a2] = 0x91100911;                 // +0xA88
  this[0x2a6] = 0x91100911;                 // +0xA98
  
  // More initialization of vehicle state
  this[0x2a7] = 0;                          // +0xA9C
  this[0x2a8] = 0;                          // +0xAA0
  this[0x2a9] = DAT_00e2e37c;               // +0xAA4 (maybe color or model)
  this[0x2ac] = 0;                          // +0xAB0
  this[0x2ad] = 0;                          // +0xAB4
  this[0x2ae] = 0;                          // +0xAB8
  this[0x2af] = 0;                          // +0xABC
  this[0x2b0] = 0;                          // +0xAC0
  this[0x2b1] = 0;                          // +0xAC4
  this[0x2b2] = 0;                          // +0xAC8
  this[0x2b3] = 0;                          // +0xACC
  this[0x2b4] = 0;                          // +0xAD0
  this[0x2b5] = 0;                          // +0xAD4
  this[0x2b6] = 0;                          // +0xAD8
  this[0x2b7] = 0;                          // +0xADC
  this[0x2b8] = 0;                          // +0xAE0
  this[0x2b9] = 0;                          // +0xAE4
  this[0x2ba] = 0;                          // +0xAE8
  this[699] = 0;                            // +0xAEC (0x2AF? but 699*4=0xAE4? offset)
  this[700] = 0;                            // +0xAF0
  this[0x2bd] = 0;                          // +0xAF4
  this[0x2be] = 0;                          // +0xAF8
  this[0x2bf] = 0;                          // +0xAFC
  this[0x2c0] = 0;                          // +0xB00
  this[0x2c1] = 0;                          // +0xB04
  this[0x2c2] = 0;                          // +0xB08
  this[0x2c3] = 0;                          // +0xB0C
  this[0x2c4] = 0;                          // +0xB10
  this[0x2c5] = 0;                          // +0xB14
  this[0x2c6] = 0;                          // +0xB18
  this[0x2c7] = 0;                          // +0xB1C
  this[0x2c8] = 0;                          // +0xB20
  this[0x2c9] = 0;                          // +0xB24
  this[0x2ca] = 0;                          // +0xB28
  this[0x2cb] = 0;                          // +0xB2C
  this[0x2cc] = 0;                          // +0xB30
  this[0x2cd] = 0;                          // +0xB34
  this[0x2ce] = 0;                          // +0xB38
  this[0x2cf] = 0;                          // +0xB3C
  this[0x2d0] = 0;                          // +0xB40
  this[0x2d1] = 0;                          // +0xB44
  this[0x2d2] = 0;                          // +0xB48
  this[0x2d3] = 0;                          // +0xB4C
  this[0x2d4] = 0;                          // +0xB50
  
  // Set some initial values from globals
  this[0x2d9] = DAT_00d5eee4;               // +0xB64
  this[0x2da] = DAT_00d5779c;               // +0xB68
  uVar1 = _DAT_00d5780c;                    // global color maybe
  this[0x2d8] = _DAT_00d5780c;              // +0xB60
  this[0x2db] = 0;                          // +0xB6C
  this[0x2dc] = 0;                          // +0xB70
  this[0x2dd] = 0;                          // +0xB74
  this[0x2de] = 0;                          // +0xB78
  
  // Zero out more fields (maybe part of a component)
  this[0x2e4] = 0;                          // +0xB90
  this[0x2e5] = 0;                          // +0xB94
  *(undefined2 *)(this + 0x2e6) = 0;        // +0xB98 (16-bit)
  *(undefined2 *)((int)this + 0xb9a) = 0;
  this[0x2e7] = 0;                          // +0xB9C
  *(undefined2 *)(this + 0x2e8) = 0;        // +0xBA0
  *(undefined2 *)((int)this + 0xba2) = 0;
  this[0x2e9] = 0;                          // +0xBA4
  *(undefined2 *)(this + 0x2ea) = 0;        // +0xBA8
  *(undefined2 *)((int)this + 0xbaa) = 0;
  this[0x2eb] = 0;                          // +0xBAC
  *(undefined2 *)(this + 0x2ec) = 0;        // +0xBB0
  *(undefined2 *)((int)this + 0xbb2) = 0;
  this[0x2ed] = 0;                          // +0xBB4
  *(undefined2 *)(this + 0x2ee) = 0;        // +0xBB8
  *(undefined2 *)((int)this + 0xbba) = 0;
  
  // More zeros
  this[0x321] = 0;                          // +0xC84
  this[0x322] = 0;                          // +0xC88
  piVar3 = this + 0x371;                    // pointer to an array of 8 elements (0x371..0x371+2*7)
  this[0x326] = 0;                          // +0xC98
  *piVar3 = 0;                              // +0xDC4 first element
  this[0x372] = 0;                          // +0xDC8
  this[0x373] = 0;                          // +0xDCC
  this[0x374] = 0;                          // +0xDD0
  this[0x375] = 0;                          // +0xDD4
  this[0x376] = 0;                          // +0xDD8
  this[0x377] = 0;                          // +0xDDC
  this[0x378] = 0;                          // +0xDE0
  this[0x379] = 0;                          // +0xDE4
  this[0x37a] = 0;                          // +0xDE8
  this[0x37b] = 0;                          // +0xDEC
  this[0x37c] = 0;                          // +0xDF0
  this[0x37d] = 0;                          // +0xDF4
  this[0x37e] = 0;                          // +0xDF8
  this[0x37f] = 0;                          // +0xDFC
  this[0x380] = 0;                          // +0xE00
  this[0x386] = 0;                          // +0xE18
  this[0x38b] = uVar2;                      // +0xE2C
  this[0x38c] = 0;                          // +0xE30
  this[0x38d] = 0;                          // +0xE34
  this[0x38e] = 0;                          // +0xE38
  this[0x38f] = 0;                          // +0xE3C
  this[0x390] = 0;                          // +0xE40
  this[0x391] = 0;                          // +0xE44
  this[0x392] = uVar1;                      // +0xE48
  this[0x393] = 0xffffffff;                 // +0xE4C
  this[0x395] = 0;                          // +0xE54
  this[0x396] = 0;                          // +0xE58
  this[0x397] = 0;                          // +0xE5C
  this[0x398] = 0;                          // +0xE60
  this[0x399] = 0;                          // +0xE64
  this[0x39a] = 0;                          // +0xE68
  this[0x39b] = 0;                          // +0xE6C
  this[0x39c] = 0;                          // +0xE70
  this[0x39d] = 0;                          // +0xE74
  this[0x39e] = 0;                          // +0xE78
  this[0x39f] = 0;                          // +0xE7C
  this[0x3a0] = 0;                          // +0xE80
  this[0x3a1] = 1;                          // +0xE84 presumably "active" flag
  
  // Call another initialization stage (maybe physics or character)
  FUN_00857aa0(actorId);
  
  this[0x3b5] = 0;                          // +0xED4
  this[0x3b6] = 0;                          // +0xED8
  this[0x3b7] = 0;                          // +0xEDC
  this[0x3b8] = 0;                          // +0xEE0
  this[0x3b9] = 0;                          // +0xEE4
  this[0x3ba] = 0;                          // +0xEE8
  this[0x3bb] = 0;                          // +0xEEC
  this[0x3bc] = 0;                          // +0xEF0
  this[0x3bd] = 0;                          // +0xEF4
  this[0x3be] = 0;                          // +0xEF8
  this[0x3bf] = 0;                          // +0xEFC
  this[0x3c0] = 0;                          // +0xF00
  this[0x3c1] = 0;                          // +0xF04
  
  // Sentinel patterns again
  this[0x3c2] = 0xbadbadba;                 // +0xF08
  this[0x3c3] = 0xbeefbeef;                 // +0xF0C
  this[0x3c4] = 0xeac15a55;                 // +0xF10
  this[0x3c5] = 0x91100911;                 // +0xF14
  
  this[0xaf] = 4;                           // +0x2BC (maybe a type/ID)
  
  // Increment global counter and assign a short ID (last digit)
  DAT_0112e010 = DAT_0112e010 + 1;
  *(short *)(this + 0x2ef) = (short)DAT_0112e010 + (short)(DAT_0112e010 / 10) * -10;
  *(undefined2 *)((int)this + 0xbbe) = 0;   // clear another short
  
  // Clear an array of 8 pointers (starting at piVar3) by stepping by 2 (?)
  actorId = 8;
  do {
    if (*piVar3 != 0) {
      FUN_004daf90(piVar3);   // free or release object
      *piVar3 = 0;
    }
    piVar3 = piVar3 + 2;      // step by 2 ints -> 8 bytes per element?
    actorId = actorId + -1;
  } while (actorId != 0);
  
  // More zeroing
  this[0x32f] = 0;                          // +0xCBC
  this[0x32e] = 0;                          // +0xCB8
  this[0x32d] = 0;                          // +0xCB4
  this[0x338] = 0;                          // +0xCE0
  this[0x337] = 0;                          // +0xCDC
  this[0x336] = 0;                          // +0xCD8
  this[0x335] = 0;                          // +0xCD4
  this[0x334] = 0;                          // +0xCD0
  this[0x333] = 0;                          // +0xCCC
  this[0x332] = 0;                          // +0xCC8
  this[0x331] = 0;                          // +0xCC4
  this[0x330] = 0;                          // +0xCC0
  
  // Call post-constructor functions
  FUN_0087f590();
  FUN_00876470();
  
  uVar1 = _DAT_00d5780c;
  this[0x2e1] = _DAT_00d5780c;              // +0xB84
  this[0x2df] = uVar1;                      // +0xB7C
  this[0x2ac] = 2;                          // +0xAB0 (team/faction? set to 2)
  this[0x2ad] = 2;                          // +0xAB4
  this[0x2ae] = 2;                          // +0xAB8
  this[0x2af] = 2;                          // +0xABC
  this[0x2b0] = 2;                          // +0xAC0
  this[0x2b1] = 2;                          // +0xAC4
  this[0x2b2] = 2;                          // +0xAC8
  this[0x2b3] = 2;                          // +0xACC
  this[0x2b4] = 2;                          // +0xAD0
  
  // Clear sentinel-marked fields (overwrite patterns with 0)
  this[0x293] = 0;                          // +0xA4C
  this[0x297] = 0;
  this[0x29a] = 0;
  this[0x299] = 0;
  this[0x298] = 0;
  this[0x294] = 0;                          // +0xA50
  this[0x29e] = 0;
  this[0x29d] = 0;
  this[0x29c] = 0;
  this[0x29b] = 0;
  this[0x295] = 0;                          // +0xA54
  this[0x2a2] = 0;
  this[0x2a1] = 0;
  this[0x2a0] = 0;
  this[0x29f] = 0;
  this[0x296] = 0;                          // +0xA58
  this[0x2a6] = 0;
  this[0x2a5] = 0;
  this[0x2a4] = 0;
  this[0x2a3] = 0;
  
  // Set some subsystem flags
  FUN_004706f0(0);         // possibly enable/disable something
  uVar1 = DAT_00d5ccf8;
  *(undefined1 *)(this + 800) = 0;          // +0xC80 byte
  this[0x2eb] = 0;
  this[0x1ef] = 0;                          // +0x7BC
  this[0x2e2] = uVar1;
  this[0x2e3] = uVar1;
  this[0x323] = 0;
  this[0x324] = 0;
  this[0x325] = 0;
  this[0x2ed] = 0;
  this[0x329] = 0;
  this[0x328] = 0;
  this[0x327] = 0;
  this[0x32c] = 0;
  this[0x32b] = 0;
  this[0x32a] = 0;
  
  FUN_0046f8f0(1);                          // enable physics? 
  FUN_0046f930(0x80, 0xc0);                 // configure some parameters
  
  // Register message listener for "iMsgCarBomb"
  FUN_00408240(&DAT_0112e020, "iMsgCarBomb"); // get message ID from string
  if (DAT_0112e020 != 0) {
    FUN_00408900(this + 0xf, &DAT_0112e020, 0x8000); // subscribe to message
  }
  if (DAT_0112e038 != 0) {
    FUN_00408900(this + 0xf, &DAT_0112e038, 0x8000);
  }
  if (DAT_0112b36c != 0) {
    FUN_00408900(this + 0xf, &DAT_0112b36c, 0x8000);
  }
  
  *(undefined1 *)(this + 0x394) = 0;        // +0xE50
  FUN_004d3d90(&DAT_00e2f044);              // likely load some string/data
  
  // Clear sentinel fields at the end again
  this[0x3c5] = 0;
  this[0x3c4] = 0;
  this[0x3c3] = 0;
  this[0x3c2] = 0;
  
  return this;
}