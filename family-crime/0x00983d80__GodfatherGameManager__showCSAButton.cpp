// FUNC_NAME: GodfatherGameManager::showCSAButton
void __thiscall GodfatherGameManager::showCSAButton(int this, undefined4 param_2, undefined4 param_3)
{
  undefined1 *puVar1;
  undefined1 *local_10;
  undefined4 local_c;
  undefined4 local_8;
  code *local_4;
  
  local_10 = (undefined1 *)0x0;
  local_c = 0;
  local_8 = 0;
  local_4 = (code *)0x0;
  FUN_004d4ad0(&local_10,&PTR_LAB_00d78708,param_2); // Get localized string for button text
  puVar1 = local_10;
  if (local_10 == (undefined1 *)0x0) {
    puVar1 = &DAT_0120546e; // Default empty string
  }
  FUN_005a04a0("ShowCSAButton",0,&DAT_00d77dc0,1,puVar1); // Show CSA button with text
  *(undefined4 *)(this + 0x108) = param_3; // Store CSA button state +0x108
  if (*(char *)((int)DAT_01129a74 + 0x3a1) == '\0') { // Check if game is not paused
    (**(code **)(*DAT_01129a74 + 0x28))(); // Call game update function
  }
  if (local_10 != (undefined1 *)0x0) {
    (*local_4)(local_10); // Release localized string
  }
  return;
}