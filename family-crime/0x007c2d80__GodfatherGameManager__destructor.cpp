// FUNC_NAME: GodfatherGameManager::destructor
void __fastcall GodfatherGameManager::~GodfatherGameManager(undefined4 *this)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int *piVar3;
  
  *this = &PTR_LAB_00d6e464;
  this[0x1d] = &PTR_LAB_00d6e460;
  piVar3 = (int *)FUN_007ab150(); // likely engine::getAudioManager
  (**(code **)(*piVar3 + 4))(this[0x20]); // release audio resource
  piVar3 = (int *)FUN_007ab130(); // likely engine::getStreamManager
  (**(code **)(*piVar3 + 4))(this[0x21]); // release stream resource
  piVar3 = (int *)FUN_007ab140(); // likely engine::getDialogTreeManager
  (**(code **)(*piVar3 + 4))(4); // release dialog resource
  *(uint *)(this[0x16] + 0x24a0) = *(uint *)(this[0x16] + 0x24a0) & 0xfffff7ff; // clear bit 11 of some flag at +0x24a0
  FUN_006f6ea0(); // likely SimulationManager::stop()
  FUN_007f6420(0x31); // likely set game phase to 0x31 (shutdown?)
  *(uint *)(this[0x16] + 0x24a4) = *(uint *)(this[0x16] + 0x24a4) & 0xfffffeff; // clear bit 8 of flag at +0x24a4
  if (*(char *)((int)this + 0x7d) != '\0') { // some flag at +0x7d
    FUN_007c2bc0(); // probably cleanup player data
  }
  if (this[0x24] != 0) {
    FUN_004daf90(this + 0x24); // delete object at +0x90
  }
  if (this[0x22] != 0) {
    FUN_004daf90(this + 0x22); // delete object at +0x88
  }
  this[0x1d] = &PTR_FUN_00e32808;
  puVar2 = (undefined4 *)this[0x1e]; // linked list head at +0x78
  while (puVar2 != (undefined4 *)0x0) {
    puVar1 = (undefined4 *)puVar2[1];
    puVar2[1] = 0;
    *puVar2 = 0;
    puVar2 = puVar1;
  }
  *this = &PTR_LAB_00d6b95c; // set vtable to base class
  FUN_0080ea60(); // call base class destructor
  return;
}