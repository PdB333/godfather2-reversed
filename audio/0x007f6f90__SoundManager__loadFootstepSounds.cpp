// FUNC_NAME: SoundManager::loadFootstepSounds
void SoundManager::loadFootstepSounds(void)
{
  undefined4 uVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined8 local_18;
  undefined8 local_10;
  
  puVar3 = &DAT_0112ca88;  // +0x0: footstep sound data array
  uVar2 = 0;
  do {
    // Load heel sound (e.g., "f_conc_run_heel")
    FUN_004eacb0(*(undefined4 *)((int)&PTR_s_f_conc_run_heel_00e53790 + uVar2));
    // Load concrete run sound (e.g., "f_concrete_run_heel_01_emx")
    uVar1 = *(undefined4 *)((int)&PTR_s_f_concrete_run_heel_01_emx_00e53794 + uVar2);
    *(undefined8 *)(puVar3 + -4) = local_18;
    *(undefined8 *)(puVar3 + -2) = local_10;
    uVar1 = FUN_004dafd0(uVar1);  // Load sound resource
    *puVar3 = uVar1;  // Store sound handle
    uVar2 = uVar2 + 8;
    puVar3 = puVar3 + 8;
  } while (uVar2 < 0x378);  // 0x378 = 888 bytes = 111 entries * 8 bytes each
  _qsort(&DAT_0112ca78,0x6f,0x20,(_PtFuncCompare *)&LAB_007f6f20);  // Sort 111 entries, 32 bytes each
  return;
}