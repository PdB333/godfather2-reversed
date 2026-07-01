// FUNC_NAME: ImpactManager::playRandomImpactSound
void ImpactManager::playRandomImpactSound(void)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  char *pcVar4;
  int iVar5;
  undefined4 uVar6;
  undefined1 local_c;
  undefined1 local_b;
  undefined1 local_a;
  undefined1 local_9;
  undefined4 local_8;
  undefined4 local_4;
  
  pcVar3 = (char *)FUN_0069d890(); // likely returns a string for material/impact type
  pcVar4 = pcVar3;
  do {
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\\0');
  if (pcVar4 != pcVar3 + 1) { // if string length > 0
    iVar5 = FUN_00422930();  // likely some condition check (e.g., player is in car)
    iVar2 = DAT_012234a0;    // global singleton pointer, e.g., g_pGameManager or g_pAudioManager
    if (iVar5 != 0) {
      uVar6 = FUN_004dafd0("impact_lt_std"); // load audio event "impact_lt_std"
      FUN_00488a10(uVar6); // play audio event
      *(undefined4 *)(iVar2 + 0x48) = _DAT_00d5780c; // store some state at +0x48 (e.g., lastImpactTime)
      local_c = 0xff;
      local_a = 0xff;
      local_b = 0xff;
      local_8 = DAT_00d5ef84; // possibly a material/hardness value for bullet impact
      local_9 = 0x80;        // volume or intensity
      local_4 = _DAT_00d8970c; // bullet calibre or damage type
      FUN_00488b00(&local_c,0); // spawn impact visual (particle/decay)
      FUN_00489fd0(&local_8,DAT_00d5f524,pcVar3,0,0,0); // play impact sound with params (material, event, intensity)
    }
  }
  return;
}