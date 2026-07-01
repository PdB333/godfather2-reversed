// Xbox PDB: EARS_Apt_UICredits_Initialize
// FUNC_NAME: CreditsManager::initialize
void __fastcall CreditsManager::initialize(int thisPtr)
{
  float fVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  long lVar4;
  uint uVar5;
  float fVar6;
  undefined1 local_5;
  char *local_4;
  
  fVar6 = 0.0;
  *(int *)(thisPtr + 0x1380) = thisPtr + 0xc0; // +0x1380: pointer to first credit entry
  uVar5 = 0;
  puVar2 = (undefined4 *)(thisPtr + 0xd8); // +0xd8: start of credit entries array
  do {
    puVar2[-6] = 1; // +0xc0: entry active flag (1 = active)
    puVar2[1] = 0;  // +0xdc: unknown
    *puVar2 = 0;    // +0xd8: unknown
    puVar2[-1] = 0; // +0xd4: unknown
    puVar2[-2] = 0; // +0xd0: unknown
    puVar2[2] = 0;  // +0xe0: unknown
    puVar2[3] = 0;  // +0xe4: unknown
    if (uVar5 < 99) {
      puVar2[4] = puVar2 + 6; // +0xe8: next entry pointer
    }
    else {
      puVar2[4] = 0; // last entry has null next pointer
    }
    fVar1 = DAT_00d5efb8; // global constant
    uVar5 = uVar5 + 1;
    puVar2 = puVar2 + 0xc; // each entry is 0x30 bytes (12 * 4)
  } while (uVar5 < 100);
  *(undefined4 *)(thisPtr + 0x1384) = 0; // +0x1384: current credit index
  *(undefined4 *)(thisPtr + 5000) = 0;   // +0x1388: unknown
  *(undefined4 *)(thisPtr + 0x138c) = 0; // +0x138c: unknown
  *(undefined4 *)(thisPtr + 0x1394) = 1; // +0x1394: some flag (1 = enabled)
  *(undefined4 *)(thisPtr + 0xb0) = 0;   // +0xb0: unknown
  if (fVar1 <= *(float *)(thisPtr + 0x84)) { // +0x84: some time value
    fVar6 = *(float *)(thisPtr + 0x6c) / *(float *)(thisPtr + 0x84); // +0x6c: another time value
  }
  *(float *)(thisPtr + 0x1398) = fVar6; // +0x1398: calculated ratio
  *(undefined4 *)(thisPtr + 0x139c) = 0; // +0x139c: unknown
  *(undefined4 *)(thisPtr + 0x13a0) = 0; // +0x13a0: unknown
  uVar3 = FUN_004dafd0("CREDITS_Num"); // get string table entry for credits count
  local_4 = (char *)0x0;
  FUN_006039d0(uVar3,&local_4,&local_5); // get localized string
  *(undefined4 *)(thisPtr + 0x1390) = 0; // +0x1390: credits count from string
  if (local_4 != (char *)0x0) {
    lVar4 = _atol(local_4);
    *(long *)(thisPtr + 0x1390) = lVar4;
  }
  *(undefined1 *)(thisPtr + 0x13a4) = 0; // +0x13a4: unknown byte
  *(undefined1 *)(thisPtr + 0x13b0) = 0; // +0x13b0: unknown byte
  *(undefined1 *)(thisPtr + 0x13b1) = 0; // +0x13b1: unknown byte
  *(undefined1 *)(thisPtr + 0x13b2) = 0; // +0x13b2: unknown byte
  *(undefined4 *)(thisPtr + 0xb0) = 0;   // +0xb0: reset
  *(undefined4 *)(thisPtr + 0x13a8) = 0; // +0x13a8: unknown
  return;
}