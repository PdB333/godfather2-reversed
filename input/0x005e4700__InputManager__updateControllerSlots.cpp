// FUNC_NAME: InputManager::updateControllerSlots
undefined4 InputManager::updateControllerSlots(int this, undefined4 param_2)

{
  uint uVar1;
  char cVar2;
  uint uVar3;
  int *piVar4;
  int local_d8;
  undefined1 local_d0 [32];
  undefined4 local_b0;
  undefined4 local_ac;
  undefined4 local_a8;
  undefined4 local_a4;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  
  // Iterate through controller list at +0x6020 (array of pointers) with count at +0x6024
  uVar1 = *(uint *)(this + 0x6024);
  uVar3 = 0;
  if (uVar1 != 0) {
    do {
      piVar4 = *(int **)(*(int *)(this + 0x6020) + uVar3 * 4);
      if (piVar4 != (int *)0x0) {
        // Call vtable function at offset 4 (likely update or poll)
        (**(code **)(*piVar4 + 4))();
      }
      uVar3 = uVar3 + 1;
    } while (uVar3 < uVar1);
  }
  
  // Zero out 16 controller state blocks (0x44 bytes each? Actually 16*4=64 bytes here)
  local_b0 = 0;
  local_ac = 0;
  local_a8 = 0;
  local_a4 = 0;
  local_80 = 0;
  local_7c = 0;
  local_78 = 0;
  local_74 = 0;
  local_50 = 0;
  local_4c = 0;
  local_48 = 0;
  local_44 = 0;
  local_20 = 0;
  local_1c = 0;
  uStack_18 = 0;
  uStack_14 = 0;
  
  // Initialize controller state buffer
  FUN_005e45d0(local_d0);
  
  // Iterate through 0x200 controller slots (each 0x30 bytes? piVar4 += 0xc * 4 = 0x30)
  piVar4 = (int *)(this + 0x20);
  local_d8 = 0x200;
  do {
    if (piVar4[2] == 2) {  // Check if slot is active/connected
      FUN_005e5f10(piVar4 + -4);  // Process controller input
      FUN_005e61a0(piVar4 + -4, local_d0);  // Update state
      if (*piVar4 != 0) {
        *(undefined2 *)(*piVar4 + 0x5a) = 0;  // Clear some field
        *(undefined1 *)(*piVar4 + 0x58) = 0xff;  // Set to 0xFF
      }
    }
    piVar4 = piVar4 + 0xc;  // Next slot (0x30 bytes)
    local_d8 = local_d8 + -1;
  } while (local_d8 != 0);
  
  // Process input events
  FUN_005f1d60(param_2);
  
  // Update global input state
  _DAT_012056c4 = 0x80;
  FUN_005f0ee0(&DAT_011a0ed8, &DAT_011a0ec0);
  _DAT_012056c4 = _DAT_012056c4 - DAT_011a0ee4;
  DAT_0120569e = 0;
  
  // Check if game should continue (vtable call at offset 0x44)
  cVar2 = (**(code **)(*DAT_01223510 + 0x44))();
  if (cVar2 != '\0') {
    return 1;
  }
  return 0;
}