// FUNC_NAME: GhostManager::initialize
undefined4 * __thiscall GhostManager::initialize(GhostManager *this, int *pConnection, undefined8 *pConfig, uint maxGhosts)
{
  ushort uVar1;
  short sVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  int *piVar5;
  uint uVar6;
  undefined4 *puVar7;
  int iVar8;
  undefined1 *pSlotBase;
  
  // Vtable setup
  this->field_0x04 = 1;
  this->field_0x08 = 0;
  this->vtable = (void *)0x00e31e80;       // +0x0C: pointer to vtable
  DAT_01223464 = this;                     // store singleton reference
  *(void **)this = (void *)0x00e31e6c;      // +0x00: primary vtable
  this->vtable = (void *)0x00e31e7c;        // +0x0C: secondary vtable (overwrite?)
  
  // Zero 16 ghost slot blocks (each 0x5A ints = 0x168 bytes)
  puVar3 = &this->field_0x10;              // +0x10: start of slot array
  iVar8 = 0xf;
  do {
    *puVar3 = 0;
    puVar3 = puVar3 + 0x5a;                // advance 0x168 bytes per slot
    iVar8 = iVar8 + -1;
  } while (-1 < iVar8);
  
  // Copy configuration data from pConfig (4+1 uint64s = 36 bytes)
  *(undefined8 *)(&this->field_0x1694) = *pConfig;           // +0x1694
  *(undefined8 *)(&this->field_0x169c) = pConfig[1];         // +0x169c
  *(undefined8 *)(&this->field_0x16a4) = pConfig[2];         // +0x16a4
  *(undefined8 *)(&this->field_0x16ac) = pConfig[3];         // +0x16ac
  this->field_0x16b4 = *(undefined4 *)(pConfig + 4);          // +0x16b4 (partial copy)
  this->field_0x18b8 = 0;                                     // +0x18b8: some flag
  this->field_0x1690 = pConnection;                           // +0x1690: store connection pointer
  
  // Call virtual method on connection (offset +8 from pConnection vtable)
  (**(code **)(*pConnection + 8))();
  
  // Reference counting / reuse logic for two global objects
  if (DAT_012069c4 != 0) {
    _DAT_012069c8 = _DAT_012069c8 + 1;
    iVar8 = FUN_00407da0();               // allocate/retrieve object?
    if (iVar8 == 0) {
      FUN_004084d0(&DAT_012069c4,0xfffe);
    }
    else {
      uVar1 = *(ushort *)(iVar8 + 0x14);
      *(ushort *)(iVar8 + 0x14) =
           ((short)((int)((uint)uVar1 * 2) >> 1) + 1U ^ uVar1) & 0x7fff ^ uVar1;
    }
  }
  if (DAT_012069b4 != 0) {
    _DAT_012069b8 = _DAT_012069b8 + 1;
    iVar8 = FUN_00407da0();
    if (iVar8 == 0) {
      FUN_004084d0(&DAT_012069b4,0xfffe);
    }
    else {
      uVar1 = *(ushort *)(iVar8 + 0x14);
      *(ushort *)(iVar8 + 0x14) =
           ((short)((int)((uint)uVar1 * 2) >> 1) + 1U ^ uVar1) & 0x7fff ^ uVar1;
    }
  }
  
  // Allocate a packet buffer pool (0x400 bytes)
  puVar3 = (undefined4 *)FUN_009c8e50(0xc);
  if (puVar3 == (undefined4 *)0x0) {
    DAT_01205400 = (undefined4 *)0x0;
  }
  else {
    uVar4 = FUN_009c8e80(0x400);
    *puVar3 = uVar4;
    puVar3[1] = 0;
    puVar3[2] = 0x80;                     // capacity (128 entries?)
    DAT_01205400 = puVar3;
  }
  
  // Initialize each ghost slot (16 slots, each 0x168 bytes)
  pSlotBase = (undefined1 *)((int)this + 0x5f);  // +0x5F: start of detailed slot data
  puVar3 = &this->field_0x16b8;                   // +0x16B8: slot data array
  // Counter for 16 slots
  // Actual loop uses param_3 as decrementing counter (initial value 0x10)
  while (param_3 != (undefined8 *)0x0) {
    // Clear various fields in the slot structure
    puVar3[0x20] = 0;   // offset within slot? (int index)
    *puVar3 = 0;
    puVar3[0x60] = 0;
    puVar3[0x40] = 0;
    puVar3[0x21] = 0;
    puVar3[1] = 0;
    puVar3[0x61] = 0;
    puVar3[0x41] = 0;
    pSlotBase[0x115] = 1;  // some flag (+0x115 in slot)
    
    // Allocate bit array for ghost IDs (size determined by maxGhosts)
    piVar5 = (int *)FUN_009c8e50(0xc);
    if (piVar5 == (int *)0x0) {
      piVar5 = (int *)0x0;
    }
    else if (maxGhosts == 0) {
      piVar5[1] = 0;
      *(undefined2 *)(piVar5 + 2) = 0;
      *piVar5 = 0;
    }
    else {
      piVar5[1] = maxGhosts;
      sVar2 = (short)(maxGhosts >> 3);       // byte count
      *(short *)(piVar5 + 2) = sVar2;
      if ((maxGhosts & 7) != 0) {
        *(short *)(piVar5 + 2) = sVar2 + 1;
      }
      iVar8 = FUN_009c8e50((short)piVar5[2]);  // allocate actual bytes
      *piVar5 = iVar8;
      if ((iVar8 != 0) && (uVar6 = 0, (short)piVar5[2] != 0)) {
        do {
          *(undefined1 *)(uVar6 + *piVar5) = 0;  // zero the bit array
          uVar6 = uVar6 + 1;
        } while (uVar6 < *(ushort *)(piVar5 + 2));
      }
    }
    *(int **)(pSlotBase + 0x10d) = piVar5;  // store bit array pointer in slot (+0x10D)
    
    // Allocate ghost state object (size 0x28)
    iVar8 = FUN_009c8e50(0x28);
    if (iVar8 == 0) {
      uVar4 = 0;
    }
    else {
      uVar4 = FUN_004640d0(iVar8, maxGhosts);  // constructor for ghost state
    }
    *(undefined4 *)(pSlotBase + 0x111) = uVar4;  // store ghost state pointer (+0x111)
    
    // Clear more fields in slot
    pSlotBase[-0x18] = 0;   // offset -0x18 bytes from base
    *pSlotBase = 0;
    *(undefined4 *)(pSlotBase + 0x109) = 0;  // +0x109
    
    // Clear a 48-byte key array (12 ints) within slot
    puVar7 = (undefined4 *)(pSlotBase + 0x11);  // +0x11: start of key array
    iVar8 = 0x10;
    do {
      puVar7[-2] = 0;
      puVar7[-1] = 0;
      *puVar7 = 0;
      puVar7 = puVar7 + 4;       // advance 16 bytes
      iVar8 = iVar8 + -1;
    } while (iVar8 != 0);
    
    // Advance to next slot
    puVar3 = puVar3 + 2;          // note: puVar3 seems to advance by 2 ints per slot? 
    pSlotBase = pSlotBase + 0x168; // each slot is 0x168 bytes
    param_3 = (undefined8 *)((int)param_3 + -1);
  }
  
  // Zero out trailing fields
  *(undefined8 *)(this + 0x62f) = 0;   // high offset (possibly beyond slots)
  *(undefined8 *)(this + 0x631) = 0;
  
  return this;
}