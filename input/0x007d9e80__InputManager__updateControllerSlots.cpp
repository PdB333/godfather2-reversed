// FUNC_NAME: InputManager::updateControllerSlots
void __fastcall InputManager::updateControllerSlots(InputManager* this)
{
  int controllerData; // pointer to controller config data block
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 local_b0;
  int local_ac; // XInput state flags
  int local_a8;
  int local_a4;
  int local_a0;
  int local_9c; // this pointer copy
  undefined4 local_98; // allocation size low
  undefined4 local_94; // allocation size high
  undefined4 local_90; // allocation flags
  undefined1 local_8c [40]; // buffer for slot state
  int local_64 [2];
  int local_5c [19];
  undefined8 local_10;
  undefined4 local_8;
  
  controllerData = *(int *)(this + 0x58); // +0x58: pointer to controller data array (16 slots * 0x44)
  if ((*(int *)(this + 0xb8) == 0) || (*(int *)(this + 0xb8) == 0x48)) { // +0xb8: slot index or special value (0 = all, 0x48 = initial)
    local_ac = *(int *)(controllerData + 0x2c44); // slot player state flags
    local_a8 = *(int *)(controllerData + 0x2c48); // controller connected flags
    local_a0 = *(int *)(controllerData + 0x2c50); // input mode flags
    local_a4 = *(int *)(controllerData + 0x2c4c); // device type flags
    local_9c = (int)this;
    if ((local_ac == 0) && (((local_a8 == 0 && (local_a4 == 0)) && (local_a0 == 0)))) {
      // No controllers connected - allocate default slot
      local_98 = 2;
      local_94 = 0x10;
      local_90 = 0;
      iVar3 = FUN_009c8ed0(0xf4,&local_98); // allocate 0xf4 bytes for slot data
      if (iVar3 == 0) {
        uVar2 = 0;
      }
      else {
        uVar2 = FUN_006d6ae0(); // initialize default controller slot
      }
    }
    else {
      uVar2 = FUN_00446130(&local_ac,0); // create slot from existing controller state
    }
    FUN_007d9910(uVar2); // register slot in slot manager
    iVar3 = *(int *)(this + 0xb8);
    if (iVar3 == 0) {
      iVar3 = 0;
    }
    else {
      iVar3 = iVar3 + -0x48; // convert from special value to slot index
    }
    FUN_006d74c0(iVar3 + 0x68); // set slot active
    iVar3 = DAT_01129944; // global game manager
    *(undefined8 *)(DAT_01129944 + 0x108) = local_10;
    *(undefined4 *)(iVar3 + 0x110) = local_8;
    if (((local_ac != 0) || (local_a8 != 0)) || ((local_a4 != 0 || (local_b0 = 1, local_a0 != 0))))
    {
      local_b0 = 0; // at least one controller active
    }
    FUN_006d76c0(controllerData,local_b0,2); // update input system with active state
    FUN_006bfa70(local_8c); // clear slot state buffer
    iVar3 = *(int *)(this + 0xb8);
    if (iVar3 == 0) {
      iVar3 = 0;
    }
    else {
      iVar3 = iVar3 + -0x48;
    }
    FUN_00424dc0(*(undefined4 *)(&DAT_00002494 + controllerData),iVar3,0,0,0); // map controller to slot
    FUN_007d9e30(); // finalize slot setup
    if (local_5c[0] != 0) {
      FUN_004daf90(local_5c); // cleanup temporary buffer
    }
    if (local_64[0] != 0) {
      FUN_004daf90(local_64); // cleanup temporary buffer
    }
  }
  return;
}