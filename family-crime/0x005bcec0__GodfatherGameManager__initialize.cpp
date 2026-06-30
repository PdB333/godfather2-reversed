// FUNC_NAME: GodfatherGameManager::initialize
undefined4 * __thiscall GodfatherGameManager::initialize(undefined4 *this, int *param_2, undefined4 param_3)
{
  ushort uVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined4 uVar5;
  int *piVar6;
  
  // +0x04: initialized flag
  this[1] = 1;
  // +0x08: some state
  this[2] = 0;
  // +0x0C: vtable pointer for base class
  this[3] = &PTR___purecall_00e3e418;
  // +0x10: another vtable
  this[4] = &PTR_LAB_00e3e454;
  // Store global singleton pointer
  DAT_012234f0 = this;
  // Set main vtable
  *this = &PTR_FUN_00e3e42c;
  // Update vtables
  this[3] = &PTR_LAB_00e3e43c;
  this[4] = &PTR_LAB_00e3e450;
  // +0x14: some pointer
  this[5] = 0;
  // +0x18: short value
  *(undefined2 *)(this + 6) = 0;
  // +0x1A: short value
  *(undefined2 *)((int)this + 0x1a) = 0;
  piVar6 = this + 5;
  // +0x1C: byte flag
  *(undefined1 *)(this + 7) = 0;
  // +0x1D: byte
  *(undefined1 *)((int)this + 0x1d) = 0;
  // +0x1E: byte
  *(undefined1 *)((int)this + 0x1e) = 0;
  // +0x20: various pointers
  this[8] = 0;
  this[9] = 0;
  this[10] = 0;
  this[0xb] = 0;
  this[0xc] = 0;
  this[0xd] = 0;
  this[0xe] = 0;
  this[0xf] = 0;
  this[0x10] = 0;
  
  // Initialize some subsystem
  FUN_005d22b0();
  
  // Allocate 8 bytes for a manager object
  puVar3 = (undefined4 *)FUN_009c8e50(8);
  if (puVar3 != (undefined4 *)0x0) {
    DAT_012234ec = puVar3;
    *puVar3 = &PTR_FUN_00e3ea08;
    puVar3[1] = param_2;
    (**(code **)(*param_2 + 8))();
    // Set up function pointers
    DAT_0119caf0 = FUN_005c4410;
    DAT_0119caf4 = FUN_005c4480;
    DAT_0119caf8 = FUN_005c44b0;
    FUN_005c42f0();
  }
  
  // Allocate 0x9F04 bytes for another subsystem
  iVar4 = FUN_009c8e50(0x9f04);
  if (iVar4 != 0) {
    FUN_005d1660();
  }
  
  // Allocate 4 bytes for a small object
  puVar3 = (undefined4 *)FUN_009c8e50(4);
  if (puVar3 != (undefined4 *)0x0) {
    DAT_012234f8 = puVar3;
    *puVar3 = &PTR_LAB_00e3ed64;
    // Set up more function pointers
    DAT_0119cafc = &LAB_005ccfe0;
    DAT_0119cb04 = &DAT_005ccfb0;
    DAT_0119cb0c = &DAT_005ccfc0;
    DAT_0119cb08 = &DAT_005ccfd0;
  }
  
  // Initialize more subsystems
  FUN_005c62d0();
  
  // Set up a large number of function pointers (vtable-like)
  DAT_0119cb38 = &LAB_005cce10;
  DAT_0119cb40 = &LAB_005cceb0;
  DAT_0119cb3c = &LAB_005cce60;
  DAT_0119cb44 = FUN_005cd070;
  DAT_0119cb4c = &LAB_005cd130;
  DAT_0119cb48 = &LAB_005cd110;
  DAT_0119cb50 = &DAT_005cd150;
  DAT_0119cb20 = &LAB_005bcd40;
  DAT_0119cb24 = &LAB_005bcd30;
  DAT_0119cb2c = &LAB_005bcdb0;
  DAT_0119cb30 = &LAB_005bce10;
  DAT_0119cb60 = &LAB_005bce90;
  DAT_0119cb64 = &DAT_005bceb0;
  DAT_0119cb70 = FUN_005c63a0;
  DAT_0119cb6c = &LAB_005c5ae0;
  DAT_0119cb68 = &LAB_005c5be0;
  DAT_0119cb54 = &LAB_005bc570;
  DAT_0119cb5c = &DAT_005bc590;
  DAT_0119cb58 = &DAT_005bc580;
  DAT_0119cb00 = &DAT_005bc5a0;
  DAT_0119cb74 = &LAB_005c57a0;
  DAT_0119cb78 = &LAB_005c5830;
  DAT_0119cb7c = &LAB_005c5890;
  
  // Initialize rendering system
  FUN_0059d000();
  
  // Register message handler for fullscreen render
  uVar5 = FUN_004dafd0("iMsgDoRenderFullScreen");
  FUN_00408260(piVar6, uVar5);
  
  // Handle some timer/counter logic for DAT_012069c4
  if (DAT_012069c4 != 0) {
    _DAT_012069c8 = _DAT_012069c8 + 1;
    iVar4 = FUN_00407da0();
    if (iVar4 == 0) {
      FUN_004084d0(&DAT_012069c4, 0xf00);
    }
    else {
      uVar1 = *(ushort *)(iVar4 + 0x14);
      *(ushort *)(iVar4 + 0x14) =
           ((short)((int)((uint)uVar1 * 2) >> 1) + 1U ^ uVar1) & 0x7fff ^ uVar1;
    }
  }
  
  // Handle similar logic for DAT_012069b4
  if (DAT_012069b4 != 0) {
    _DAT_012069b8 = _DAT_012069b8 + 1;
    iVar4 = FUN_00407da0();
    if (iVar4 == 0) {
      FUN_004084d0(&DAT_012069b4, 0xf00);
    }
    else {
      uVar1 = *(ushort *)(iVar4 + 0x14);
      *(ushort *)(iVar4 + 0x14) =
           ((short)((int)((uint)uVar1 * 2) >> 1) + 1U ^ uVar1) & 0x7fff ^ uVar1;
    }
  }
  
  // Initialize some system if not already done
  if (DAT_01205664 == 0) {
    iVar4 = FUN_005c4410(200, 0);
    if (iVar4 == 0) {
      DAT_01205664 = 0;
    }
    else {
      DAT_01205664 = FUN_005c3070();
    }
    FUN_005c31d0();
  }
  
  DAT_01205648 = 0;
  
  // Set a flag if not already set
  if (*(char *)(this + 7) == '\0') {
    if (*piVar6 != 0) {
      FUN_00408900(this, piVar6, 0);
    }
    *(undefined1 *)(this + 7) = 1;
  }
  
  // Push some data onto a stack-like structure
  iVar4 = DAT_01206880;
  uVar5 = DAT_011260b4;
  **(undefined4 **)(DAT_01206880 + 0x14) = &PTR_LAB_011260b8;
  *(int *)(iVar4 + 0x14) = *(int *)(iVar4 + 0x14) + 4;
  **(undefined4 **)(iVar4 + 0x14) = uVar5;
  *(int *)(iVar4 + 0x14) = *(int *)(iVar4 + 0x14) + 4;
  **(undefined4 **)(iVar4 + 0x14) = param_3;
  *(int *)(iVar4 + 0x14) = *(int *)(iVar4 + 0x14) + 4;
  
  uVar5 = DAT_011260b4;
  this[8] = DAT_011260b4;
  uVar2 = DAT_011260b4;
  piVar6 = (int *)(DAT_01206880 + 0x14);
  **(undefined4 **)(DAT_01206880 + 0x14) = &PTR_LAB_0112611c;
  *piVar6 = *piVar6 + 4;
  *(undefined4 *)*piVar6 = uVar5;
  *piVar6 = *piVar6 + 4;
  *(undefined4 *)*piVar6 = uVar2;
  *piVar6 = *piVar6 + 4;
  
  // Register a message handler
  FUN_004f12a0(0x3033fbe5, this + 3);
  this[8] = 0;
  
  // More stack operations
  iVar4 = DAT_01206880;
  uVar5 = DAT_011260b4;
  **(undefined4 **)(DAT_01206880 + 0x14) = &PTR_LAB_0112611c;
  *(int *)(iVar4 + 0x14) = *(int *)(iVar4 + 0x14) + 4;
  piVar6 = (int *)(iVar4 + 0x14);
  **(undefined4 **)(iVar4 + 0x14) = 0;
  *piVar6 = *piVar6 + 4;
  *(undefined4 *)*piVar6 = uVar5;
  *piVar6 = *piVar6 + 4;
  
  uVar5 = DAT_011260b4;
  piVar6 = (int *)(DAT_01206880 + 0x14);
  **(undefined4 **)(DAT_01206880 + 0x14) = &PTR_LAB_011260f4;
  *piVar6 = *piVar6 + 4;
  *(undefined4 *)*piVar6 = uVar5;
  *piVar6 = *piVar6 + 4;
  
  return this;
}