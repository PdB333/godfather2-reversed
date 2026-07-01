// FUNC_NAME: Player::handleDonControlGadgetInteraction
void __thiscall Player::handleDonControlGadgetInteraction(int this, int *param_2)
{
  int iVar1;
  int iVar2;
  char cVar3;
  int *piVar4;
  int iVar5;
  int *piVar6;
  float10 fVar7;
  undefined4 uVar8;
  int *local_8;
  int *piStack_4;
  
  piVar4 = param_2;
  FUN_00877240(param_2); // likely some initialization or validation
  iVar5 = *piVar4;
  // Traverse linked list to find last node (tail)
  for (iVar1 = *(int *)(iVar5 + 0xc); iVar1 != 0; iVar1 = *(int *)(iVar1 + 0xc)) {
    iVar5 = iVar1;
  }
  iVar1 = piVar4[1];
  // Traverse second linked list to find last node
  for (iVar2 = *(int *)(iVar1 + 0xc); iVar2 != 0; iVar2 = *(int *)(iVar2 + 0xc)) {
    iVar1 = iVar2;
  }
  iVar5 = *(char *)(iVar5 + 0x10) + iVar5; // +0x10: some offset, possibly size or flag
  piVar4 = (int *)0x0;
  if (iVar5 != 0) {
    FUN_004af8c0(&local_8,0x2001); // allocate memory (0x2001 = 8193 bytes?)
    piVar4 = (int *)0x0;
    if (local_8 != (int *)0x0) {
      piVar4 = local_8;
    }
  }
  // Check if allocated pointer matches some expected offset from 'this'
  if (piVar4 == (int *)(this + -0x2e0)) {
    piVar4 = (int *)0x0;
    if (*(char *)(iVar1 + 0x10) + iVar1 != 0) {
      FUN_004af8c0(&local_8,0x2001);
      piVar4 = (int *)0x0;
      if (local_8 != (int *)0x0) {
        piVar4 = local_8;
      }
    }
    piVar6 = (int *)0x0;
    if ((iVar5 != 0) && (FUN_004af8c0(&local_8,0x2001), local_8 != (int *)0x0)) {
      piVar6 = local_8;
    }
    if (piVar4 == (int *)0x0) {
      return;
    }
    if (piVar6 == (int *)0x0) {
      return;
    }
  }
  if (piVar4 == (int *)0x0) {
    return;
  }
  FUN_005403e0(0xcf); // push/pop some context (0xcf = 207)
  param_2 = (int *)0x0;
  // Call virtual function at vtable+0x10 with hash 0xf8b45dfb (likely a query/interface method)
  cVar3 = (**(code **)(*piVar4 + 0x10))(0xf8b45dfb,&param_2);
  uVar8 = _DAT_00d5780c; // global variable
  if (((cVar3 != '\0') && (piStack_4 != (int *)0x0)) && ((*(byte *)(this + 0xc48) & 1) == 0)) {
    // +0xc48: some flag byte, bit 0 checked
    iVar5 = (**(code **)(*piStack_4 + 0x1e4))(); // virtual call at vtable+0x1e4
    if ((iVar5 != 0) && (iVar5 = FUN_004f95c0(iVar5,0xd80c71d2), iVar5 != 0)) {
      // Check bit 0x200000 (>> 0x15 = 21) at +0x9a8 and bit 0x10 (>> 4) at +0x738
      if (((*(uint *)(this + 0x9a8) >> 0x15 & 1) != 0) &&
         ((*(uint *)(this + 0x738) >> 4 & 1) != 0)) {
        // Call virtual at vtable+0x28c on object at this-0x2e0 (likely DonControlGadget)
        (**(code **)(*(int *)(this + -0x2e0) + 0x28c))(1);
      }
      fVar7 = (float10)(**(code **)(*(int *)(this + -0x2e0) + 0x1b0))(); // virtual call at vtable+0x1b0
      if (fVar7 < (float10)DAT_00d68260) {
        uVar8 = DAT_00d75798; // some global threshold
      }
    }
    FUN_00878630(uVar8); // likely play sound or trigger effect
  }
  piStack_4 = (int *)0xcf;
  FUN_00540410(); // pop context
  return;
}