// Xbox PDB: EARS_Apt_UIHud_ShowItemPickUpInfo
// FUNC_NAME: showAmmoPickupInfo
void showAmmoPickupInfo(int param_1, int ammoType)
{
  undefined4 uVar1;
  char cVar2;
  char *pcVar3;
  undefined1 *puVar4;
  undefined1 *local_1024;
  undefined4 local_1020;
  undefined4 local_101c;
  code *local_1018;
  undefined1 local_1014 [4112];
  undefined4 uStack_4;
  
  uStack_4 = 0x93aaaa;

  // Check if a certain global condition is met
  if ((*(int *)(DAT_01223484 + 0xc) != 0) && (cVar2 = FUN_0089c630(), cVar2 != '\0')) {
    return;
  }
  
  uVar1 = DAT_012234a4;
  FUN_00604be0(); // Probably begins a scope or UI operation
  FUN_00604c80(0x6e, param_1); // Sets some UI parameter (0x6e = some ID)
  
  local_1024 = (undefined1 *)0x0;
  local_1020 = 0;
  local_101c = 0;
  local_1018 = (code *)0x0;
  
  // Determine the ammo type string based on the given ammo type index
  switch(ammoType) {
  case 0:
    pcVar3 = "$ammo_rifle";
    break;
  case 1:
    pcVar3 = "$ammo_pistol";
    break;
  case 2:
    pcVar3 = "$ammo_magnum";
    break;
  case 3:
    pcVar3 = "$ammo_automatic";
    break;
  case 4:
    pcVar3 = "$ammo_shotgun";
    break;
  default:
    goto switchD_0093ab0d_caseD_5;
  case 6:
    pcVar3 = "$ammo_molotov";
    break;
  case 7:
    pcVar3 = "$ammo_dynamite";
    break;
  case 8:
    pcVar3 = "$ammo_bomb";
  }
  
  // Load a localized string for the ammo type
  FUN_006038a0(uVar1, local_1014, &local_1024, pcVar3);
  
  // Use loaded string or default if null
  puVar4 = local_1024;
  if (local_1024 == (undefined1 *)0x0) {
    puVar4 = &DAT_0120546e;
  }
  
  // Display the ammo pickup info
  FUN_005a04a0("ShowAmmoPickUpInfo", 0, &DAT_00d8a64c, 1, puVar4);
  
  // Cleanup the loaded string if allocated
  if (local_1024 != (undefined1 *)0x0) {
    (*local_1018)(local_1024);
  }
  
switchD_0093ab0d_caseD_5:
  FUN_00604c00(); // Ends the scope/UI operation
  return;
}