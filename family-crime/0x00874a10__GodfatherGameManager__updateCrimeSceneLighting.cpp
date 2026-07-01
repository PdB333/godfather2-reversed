// FUNC_NAME: GodfatherGameManager::updateCrimeSceneLighting
void __fastcall GodfatherGameManager::updateCrimeSceneLighting(int *this)
{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  int local_74 [3];
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined1 local_5c [4];
  undefined4 uStack_58;
  undefined4 local_50 [19];
  
  // Check if three light objects exist (offsets 0xCB4, 0xCB8, 0xCBC)
  if (((this[0x32d] != 0) && (this[0x32e] != 0)) && (this[0x32f] != 0)) {
    // Get the current time of day data (returns pointer to 0x40 bytes of time data)
    puVar1 = (undefined4 *)FUN_00471610();
    local_74[0] = this[0x330]; // Light 1 color
    puVar3 = local_50;
    // Copy 0x40 bytes of time data
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar3 = *puVar1;
      puVar1 = puVar1 + 1;
      puVar3 = puVar3 + 1;
    }
    local_74[1] = 0;
    local_74[2] = this[0x331]; // Light 1 intensity
    // Calculate final light color/intensity
    FUN_0045c230(&local_68,local_74,local_50);
    iVar2 = this[0x32d]; // Light 1 object
    *(undefined4 *)(iVar2 + 0x10) = local_68; // +0x10 color R
    *(undefined4 *)(iVar2 + 0x14) = local_60; // +0x14 color G
    *(undefined4 *)(iVar2 + 0xc) = local_64;  // +0x0C color B
    *(int *)(this[0x32d] + 0x18) = this[0x332]; // +0x18 intensity

    // Repeat for light 2
    local_74[0] = this[0x333];
    local_74[1] = 0;
    local_74[2] = this[0x334];
    FUN_0045c230(&local_68,local_74,local_50);
    iVar2 = this[0x32e];
    *(undefined4 *)(iVar2 + 0x10) = local_68;
    *(undefined4 *)(iVar2 + 0x14) = local_60;
    *(undefined4 *)(iVar2 + 0xc) = local_64;
    *(int *)(this[0x32e] + 0x18) = this[0x335];

    // Repeat for light 3
    local_74[0] = this[0x336];
    local_74[1] = 0;
    local_74[2] = this[0x337];
    FUN_0045c230(&local_68,local_74,local_50);
    iVar2 = this[0x32f];
    *(undefined4 *)(iVar2 + 0x10) = local_68;
    *(undefined4 *)(iVar2 + 0x14) = local_60;
    *(undefined4 *)(iVar2 + 0xc) = local_64;
    *(int *)(this[0x32f] + 0x18) = this[0x338];

    // Call virtual function at vtable+0x4C (likely getAmbientColor)
    (**(code **)(*this + 0x4c))(local_5c);
    iVar2 = this[0x32d];
    *(undefined4 *)(iVar2 + 0x1c) = local_60; // +0x1C ambient R
    *(undefined4 *)(iVar2 + 0x20) = uStack_58; // +0x20 ambient G
    iVar2 = this[0x32e];
    *(undefined4 *)(iVar2 + 0x1c) = local_60;
    *(undefined4 *)(iVar2 + 0x20) = uStack_58;
    iVar2 = this[0x32f];
    *(undefined4 *)(iVar2 + 0x1c) = local_60;
    *(undefined4 *)(iVar2 + 0x20) = uStack_58;

    // Increment and wrap lighting update counter at +0xBBE
    *(short *)((int)this + 0xbbe) = *(short *)((int)this + 0xbbe) + 1;
    if (10 < *(ushort *)((int)this + 0xbbe)) {
      *(undefined2 *)((int)this + 0xbbe) = 0;
    }

    // Check if counter matches some threshold at +0xBBC
    if (*(short *)((int)this + 0xbbe) == (short)this[0x2ef]) {
      FUN_005f8d30(DAT_00d64730,0); // Likely play thunder sound effect
    }
  }
  return;
}