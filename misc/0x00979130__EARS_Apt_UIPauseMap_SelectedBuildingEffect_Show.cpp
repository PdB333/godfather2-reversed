// Xbox PDB: EARS_Apt_UIPauseMap_SelectedBuildingEffect_Show
// FUNC_NAME: GodfatherGameManager::createVenueSelectIcon
void __thiscall GodfatherGameManager::createVenueSelectIcon(int this, undefined4 *color, int venueType)
{
  int *iconPtr;
  char *iconName;
  int local_b0;
  undefined4 local_ac;
  undefined4 local_a8;
  undefined4 local_a4;
  undefined1 local_a0[16];
  undefined4 local_90;
  undefined4 uStack_8c;
  undefined4 uStack_88;
  undefined4 uStack_84;
  undefined4 local_80;
  undefined4 uStack_7c;
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined4 local_70;
  undefined4 uStack_6c;
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined4 local_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined1 local_50[76];
  
  iconPtr = (int *)(this + 0x108); // +0x108: venueSelectIcon pointer
  FUN_004df650(); // some init/reset function
  FUN_00425060(&local_ac, 0); // color conversion/init
  FUN_0056b8a0(local_a8, local_ac, local_a4, local_50); // build color/transform
  local_90 = _DAT_00d5780c; // global transform/scale value
  uStack_8c = 0;
  uStack_88 = 0;
  uStack_84 = 0;
  local_80 = 0;
  uStack_7c = _DAT_00d5780c;
  uStack_78 = 0;
  uStack_74 = 0;
  local_70 = 0;
  uStack_6c = 0;
  uStack_68 = _DAT_00d5780c;
  uStack_64 = 0;
  local_60 = *color; // copy color RGBA
  uStack_5c = color[1];
  uStack_58 = color[2];
  uStack_54 = color[3];
  
  // Select icon name based on venue type
  if (venueType == 0) {
    iconName = "dv_venue_select_square";
  }
  else if ((venueType == 1) || (venueType == 2)) {
    iconName = "dv_venue_select_circle";
  }
  else if (venueType == 3) {
    iconName = "dv_venue_select_compound";
  }
  else if (venueType == 4) {
    iconName = "dv_venue_select_safehouse";
  }
  else if (venueType == 5) {
    iconName = "dv_venue_select_jobtask";
  }
  else if (venueType == 6) {
    iconName = "dv_venue_select_jobgiver";
  }
  else {
    if (venueType != 7) {
      return;
    }
    iconName = "dv_venue_select_jobreward";
  }
  
  FUN_004eacb0(iconName); // load icon texture
  FUN_004df420(&local_b0, local_a0, &local_90, 0xffffffff, 4, 0, 0xffffffff, 0); // create sprite/icon
  
  // Replace existing icon if any
  if (*iconPtr != 0) {
    *(undefined4 *)(*iconPtr + 8) = 0;
    *iconPtr = 0;
  }
  *iconPtr = local_b0;
  if (local_b0 != 0) {
    *(int **)(local_b0 + 8) = iconPtr; // link back to owner
  }
  return;
}