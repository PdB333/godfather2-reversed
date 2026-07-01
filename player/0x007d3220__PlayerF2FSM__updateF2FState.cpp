// FUNC_NAME: PlayerF2FSM::updateF2FState
void __thiscall PlayerF2FSM::updateF2FState(int this, undefined4 param_2)

{
  int *piVar1;
  code *pcVar2;
  char cVar3;
  int iVar4;
  int unaff_ESI;
  float10 fVar5;
  float fVar6;
  float fVar7;
  undefined1 local_8 [4];
  undefined4 local_4;
  
  cVar3 = FUN_007ab500(3); // Check if game is in a valid state (e.g., not paused)
  if (cVar3 != '\0') {
    iVar4 = FUN_007ab160(); // Get player controller
    if ((((*(byte *)(iVar4 + 4) & 0x80) != 0) && // Check controller is active (bit 7)
        ((*(byte *)(*(int *)(this + 0x58) + 0x26a4) & 1) != 0)) && // Check some flag at +0x26a4
       ((*(byte *)(*(int *)(this + 0x58) + 0x8e3) & 1) == 0)) { // Check another flag at +0x8e3
      if (*(int *)(this + 0xb8) == 0) {
        iVar4 = 0;
      }
      else {
        iVar4 = *(int *)(this + 0xb8) + -0x48; // Adjust pointer by -0x48
      }
      piVar1 = (int *)(this + 0x7c); // Linked list node at +0x7c
      if (iVar4 == 0) {
        iVar4 = 0;
      }
      else {
        iVar4 = iVar4 + 0x48; // Restore original pointer
      }
      if (*piVar1 != iVar4) {
        if (*piVar1 != 0) {
          FUN_004daf90(piVar1); // Remove from linked list
        }
        *piVar1 = iVar4;
        if (iVar4 != 0) {
          *(undefined4 *)(this + 0x80) = *(undefined4 *)(iVar4 + 4); // Set next pointer
          *(int **)(iVar4 + 4) = piVar1; // Set prev pointer
        }
      }
      pcVar2 = *(code **)(*(int *)(this + 0x74) + 0xc); // Get virtual function at offset 0xc
      *(undefined4 *)(this + 0x78) = *(undefined4 *)(this + 0x58); // Store some pointer at +0x78
      local_4 = param_2;
      (*pcVar2)(&local_4,local_8); // Call virtual function (likely process input)
      *(undefined1 *)(this + 0xb4) = 1; // Set flag at +0xb4 to true
      if (*(int *)(this + 0xb8) == 0) {
        iVar4 = 0;
      }
      else {
        iVar4 = *(int *)(this + 0xb8) + -0x48;
      }
      fVar5 = (float10)FUN_007d27f0(iVar4); // Get some speed/velocity value
      fVar6 = (float)fVar5;
      cVar3 = FUN_00481620(); // Check if game is in slow-motion or similar
      fVar7 = fVar6;
      if ((cVar3 != '\0') && (unaff_ESI != 0)) {
        fVar5 = (float10)FUN_0079eb40(0,0); // Get time delta or multiplier
        fVar7 = (float)(fVar5 * (float10)fVar6);
        if (fVar5 * (float10)fVar6 < (float10)DAT_00d6eed0) {
          fVar7 = DAT_00d6eed0; // Clamp to minimum value
        }
      }
      FUN_007d2a10(local_4); // Apply movement
      FUN_007d2b90(unaff_ESI,fVar7); // Update animation with speed
      *(int *)(*(int *)(this + 0x58) + 0x24f8) = unaff_ESI; // Store ESI at +0x24f8
      return;
    }
  }
  *(undefined4 *)(*(int *)(this + 0x58) + 0x24f8) = 0; // Clear ESI storage
  return;
}