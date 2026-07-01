// FUNC_NAME: FamilyManager::Constructor
void __fastcall FamilyManager::Constructor(undefined4 *this)
{
  int *piVar1;
  int iVar2;
  undefined4 *puVar3;
  
  // Set primary vtable pointer (offset 0x00)
  *this = &PTR_FUN_00d831bc;
  // Set additional vtable pointers (offsets 0x3C, 0x48, 0x50)
  this[0xf] = &PTR_LAB_00d831ac;
  this[0x12] = &PTR_LAB_00d831a8;
  this[0x14] = &PTR_LAB_00d831a4;
  
  // Initialize sub-system (likely family data pool)
  FamilyManager::InitSubsystem(1);
  // Perform global initialization
  GlobalInit(&DAT_0112ff74);  // global resource lock?
  
  // Clean up previous data in a linked or paired array
  puVar3 = this + 0x28;  // start at offset 0xA0 (array of 5 family pairs)
  iVar2 = 5;
  do {
    piVar1 = puVar3 + -2;  // check the 'first' field of the previous pair
    puVar3 = puVar3 + -2;  // move to previous pair
    if (*piVar1 != 0) {
      // If the first field is not null, delete the object pointed by the second field
      FamilyManager::DeleteFamilyData(puVar3);
    }
    iVar2 = iVar2 + -1;
  } while (-1 < iVar2);
  
  // Clean up an additional pointer at offset 0x64 (this[0x19])
  if (this[0x19] != 0) {
    FamilyManager::DeleteFamilyData(this + 0x19);
  }
  
  // Finish initialization
  FamilyManager::PostInit();
  // Update vtable entry to final behavior (offset 0x50)
  this[0x14] = &PTR_LAB_00d83188;
  
  // Reset global flag
  DAT_011298e4 = 0;
  
  // Finalize creation
  Engine::FinalizeConstruction();
  return;
}