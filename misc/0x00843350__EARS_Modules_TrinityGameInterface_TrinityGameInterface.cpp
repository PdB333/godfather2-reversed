// Xbox PDB: EARS_Modules_TrinityGameInterface_TrinityGameInterface
// FUNC_NAME: GodfatherGameManager::constructor
undefined4 * __thiscall GodfatherGameManager::constructor(undefined4 *this, undefined4 param_2)
{
  int iVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iStack_8;
  
  // Initialize vtable pointer
  *this = &PTR_FUN_00e2f19c;
  this[1] = 1;
  this[2] = 0;
  
  // Call base class constructor
  FUN_0049c610();
  
  // Set up vtable and data pointers
  this[5] = &PTR_LAB_00d74948;
  DAT_01129948 = this;  // Store global singleton pointer
  this[6] = param_2;
  *this = &PTR_FUN_00d74a20;
  this[3] = &PTR_LAB_00d74a14;
  this[5] = &PTR_LAB_00d74a10;
  
  // Initialize member variables to 0
  this[0xe] = 0;  // +0x38
  this[0xf] = 0;  // +0x3C
  this[0x10] = 0; // +0x40
  this[0x11] = 0; // +0x44
  this[0x12] = 0; // +0x48
  this[0x13] = 0; // +0x4C
  this[0x14] = 0; // +0x50
  this[0x15] = 0; // +0x54
  *(undefined1 *)(this + 0x16) = 0; // +0x58 byte
  this[0x17] = 0; // +0x5C
  *(undefined1 *)(this + 0x18) = 0; // +0x60 byte
  *(undefined1 *)((int)this + 0x61) = 0; // +0x61 byte
  this[0x19] = 0; // +0x64
  this[0x1a] = 0; // +0x68
  this[0x1b] = 0; // +0x6C
  
  // Call virtual function on param_2 (offset 8)
  (**(code **)(*(int *)this[6] + 8))();
  
  // Register sequence master
  FUN_0049c6e0("TRINITY_SEQ_MASTER",1);
  
  // Create various subsystems
  iVar1 = FUN_008401e0(0x1c,this[6]);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = FUN_00844010();
  }
  this[7] = uVar2;  // +0x1C - Subsystem 1 (size 0x1C)
  
  iVar1 = FUN_008401e0(0x108,this[6]);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = FUN_00841c80();
  }
  this[8] = uVar2;  // +0x20 - Subsystem 2 (size 0x108)
  
  iVar1 = FUN_008401e0(8,this[6]);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = FUN_00844fd0();
  }
  this[9] = uVar2;  // +0x24 - Subsystem 3 (size 8)
  
  iVar1 = FUN_008401e0(0x48,this[6]);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = FUN_00842020();
  }
  this[10] = uVar2; // +0x28 - Subsystem 4 (size 0x48)
  
  // Create subsystem 5 (size 8)
  puVar3 = (undefined4 *)FUN_008401e0(8,this[6]);
  if (puVar3 == (undefined4 *)0x0) {
    puVar3 = (undefined4 *)0x0;
  }
  else {
    *puVar3 = &PTR_LAB_00d74620;
    FUN_00598d50();
    *puVar3 = &PTR_FUN_00d7494c;
    puVar3[1] = &PTR_LAB_00d74950;
  }
  this[0xb] = puVar3; // +0x2C - Subsystem 5
  
  // Create subsystem 6 (size 0x3C)
  puVar3 = (undefined4 *)FUN_008401e0(0x3c,this[6]);
  if (puVar3 == (undefined4 *)0x0) {
    puVar3 = (undefined4 *)0x0;
  }
  else {
    *puVar3 = &PTR_LAB_00d74620;
    FUN_00598db0();
    *puVar3 = &PTR_FUN_00d74964;
    puVar3[1] = &PTR_LAB_00d74968;
  }
  this[0xc] = puVar3; // +0x30 - Subsystem 6
  
  // Create subsystem 7 (size 0x80)
  iVar1 = FUN_008401e0(0x80,this[6]);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = FUN_00842b80();
  }
  this[0xd] = uVar2; // +0x34 - Subsystem 7
  
  // Initialize subsystem 4 with dimensions
  (**(code **)(*(int *)(this[10] + 4) + 4))(0x20,0x20,0x40);
  
  // Get internal data pointers for subsystems
  if (this[0xd] == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = this[0xd] + 4;
  }
  if (this[0xc] == 0) {
    iStack_8 = 0;
  }
  else {
    iStack_8 = this[0xc] + 4;
  }
  if (this[0xb] == 0) {
    iVar4 = 0;
  }
  else {
    iVar4 = this[0xb] + 4;
  }
  if (this[10] == 0) {
    iVar5 = 0;
  }
  else {
    iVar5 = this[10] + 4;
  }
  if (this[9] == 0) {
    iVar7 = 0;
  }
  else {
    iVar7 = this[9] + 4;
  }
  if (this[8] == 0) {
    iVar6 = 0;
  }
  else {
    iVar6 = this[8] + 4;
  }
  
  // Link subsystems together
  (**(code **)(*(int *)(this[7] + 4) + 4))(iVar6,iVar7,iVar5,iVar4,iStack_8,iVar1);
  
  // Register message handlers
  FUN_004086b0(&DAT_012069c4,0x6001);
  FUN_004086b0(&DAT_012069b4,0x6001);
  
  // Handle additional data if present
  if (DAT_01206980 != 0) {
    FUN_00408900(this,&DAT_01206980,0x8000);
  }
  
  // Register IGC message types
  FUN_00408240(&DAT_0112dcd8,"iMsgIGCEnableActor");
  FUN_00408240(&DAT_0112dcd0,"iMsgIGCDisableActor");
  
  return this;
}