// FUNC_NAME: Character::~Character

void __thiscall Character::~Character(Character *this)
{
  int *piVar3;
  uint uVar5;
  int iVar1;
  int iVar2;
  uint *puVar4;
  int iVar6;
  
  // Set primary vtable (most derived)
  *this = &PTR_FUN_00e31bb8;
  // Set base class vtables (multiple inheritance)
  this->baseVtable1 = &PTR_LAB_00e31d4c;   // +0x3C
  this->baseVtable2 = &PTR_LAB_00e31d5c;   // +0x48
  this->baseVtable3 = &PTR_LAB_00e31d60;   // +0x50
  this->baseVtable4 = &PTR_LAB_00e31d68;   // +0x54
  this->baseVtable5 = &PTR_LAB_00e31dc8;   // +0x58
  
  // Free animation handle if present
  if (this->animationHandle != 0) {         // +0x294 (0xa4*4)
    iVar2 = FUN_004025a0(this->animationHandle);
    if (iVar2 != 0) {
      short *animationIndex = (short *)(iVar2 + 0x56);
      if (*animationIndex != -1) {
        FUN_004029a0(animationIndex);       // Free animation by index
      }
    }
  }
  
  // Remove from global animation lists
  FUN_004086d0(&DAT_01206980);
  FUN_004086d0(&DAT_0120e93c);
  
  // Remove from object update list if registered
  if ((this->flags & 0x40) != 0) {          // +0x184 bit 6
    piVar3 = (int *)(DAT_01206880 + 0x14); // Global linked list head
    **(undefined4 **)(DAT_01206880 + 0x14) = &PTR_LAB_0110b938;
    *piVar3 = *piVar3 + 4;
    *(undefined4 **)*piVar3 = this;
    *piVar3 = *piVar3 + 4;
    this->flags &= 0xffffffbf;             // Clear the bit
  }
  
  this->field_0x208 = 0;                   // +0x208
  FUN_0045df20(this);                      // Subobject cleanup
  
  FUN_0046ebb0();                          // Global cleanup
  
  // Delete audio handle if present
  if (this->audioHandle != 0) {            // +0x260
    piVar3 = (int *)FUN_009c8f80();
    (**(code **)(*piVar3 + 4))(this->audioHandle, 0);
    this->audioHandle = 0;
  }
  this->field_0x264 = 0;
  
  FUN_0051aa50();                          // Global resource cleanup
  
  if (this->shortFieldAt0x7C != 0) {       // short at +0x7C (0x1f*4)
    FUN_004086d0(&DAT_012069c4);
  }
  
  // Free array of subobjects
  uVar5 = 0;
  if (this->subObjectCount != 0) {         // +0x220
    do {
      char *stringPtr = (char *)(this->subObjectArray + 4 + uVar5 * 8); // +0x21C plus offset
      if (*stringPtr != '\0') {
        iVar2 = *(int *)(this->subObjectArray + uVar5 * 8);
        if (iVar2 != 0) {
          FUN_00558360();                  // Reference counting?
          FUN_009c8eb0(iVar2);            // Free subobject
        }
      }
      uVar5 = uVar5 + 1;
    } while (uVar5 < (uint)this->subObjectCount);
  }
  this->subObjectCount = 0;
  FUN_009c8f10(this->subObjectArray);      // Free array itself
  this->subObjectArray = 0;
  this->field_0x224 = 0;
  
  // Release resource handles (8 slots at +0x240)
  puVar4 = this->resourceHandlesArray;     // +0x240 (starting at offset 0x90*4)
  iVar6 = 8;
  do {
    uVar5 = *puVar4;
    if ((uVar5 != 0) && ((uVar5 & 0xffff) < 0x200)) {
      iVar1 = (uVar5 & 0xffff) * 0x30 + 0x10 + DAT_012234bc; // Resource table
      if ((iVar1 != 0) && (*(uint *)(iVar1 + 0x2c) == uVar5 && iVar1 != 0)) {
        *(undefined4 *)(iVar1 + 0x24) = 0;
        *(undefined4 *)(iVar1 + 0x28) = 0;
      }
    }
    puVar4 = puVar4 + 1;
    iVar6 = iVar6 + -1;
  } while (iVar6 != 0);
  
  // Second deletion of audio handle (redundant safety)
  if (this->audioHandle != 0) {
    piVar3 = (int *)FUN_009c8f80();
    (**(code **)(*piVar3 + 4))(this->audioHandle, 0);
    this->audioHandle = 0;
  }
  this->field_0x264 = 0;
  this->field_0x208 = 0;
  
  // Free array of linked objects
  iVar2 = this->linkedObjectCount;         // +0x29C
  while (iVar2 = iVar2 + -1, -1 < iVar2) {
    iVar6 = this->linkedObjectArray;       // +0x298
    iVar1 = *(int *)(iVar6 + iVar2 * 4);
    if (iVar1 != 0) {
      *(undefined4 *)(iVar1 + 8) = 0;
      *(undefined4 *)(iVar6 + iVar2 * 4) = 0;
    }
  }
  if (this->linkedObjectArray != 0) {
    FUN_009c8f10(this->linkedObjectArray);
  }
  if (this->subObjectArray != 0) {         // Redundant check
    FUN_009c8f10(this->subObjectArray);
  }
  
  FUN_0046ea20();                          // Final cleanup
  return;
}