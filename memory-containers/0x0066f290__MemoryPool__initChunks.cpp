// FUNC_NAME: MemoryPool::initChunks
void __thiscall MemoryPool::initChunks(MemoryPool *this, int param_2)
{
  uint uVar1;
  int in_EAX;
  uint uVar2;
  undefined4 uVar3;
  int extraout_ECX;
  uint uVar4;
  uint *puVar5;
  uint uVar6;
  int *unaff_EDI;
  int local_8;
  int local_4;
  
  unaff_EDI[1] = param_1;
  param_1 = in_EAX + -8 + param_1;
  unaff_EDI[3] = param_1;
  *unaff_EDI = in_EAX;
  unaff_EDI[2] = 2;
  unaff_EDI[4] = 0;
  local_4 = 4;
  // param_2 + 0x10 likely points to a chunk size array or metadata
  puVar5 = (uint *)(param_2 + 0x10);
  local_8 = in_EAX;
  do {
    uVar2 = *puVar5;
    if (uVar2 < 4) {
      uVar2 = 4;
    }
    uVar1 = puVar5[-1];
    // Align size calculation
    uVar6 = uVar2 - 1 & uVar1;
    uVar4 = uVar1;
    if (uVar6 != 0) {
      uVar4 = uVar1 + (uVar2 - uVar6);
    }
    uVar2 = puVar5[1];
    if (param_1 == 0x20) {
      uVar3 = 0;
      param_1 = 0;
    }
    else {
      // Allocate memory for chunk slots
      uVar3 = FUN_004abe90(local_8, uVar2 * uVar4, uVar1, *puVar5);
      param_1 = extraout_ECX;
    }
    local_8 = local_8 + uVar2 * uVar4;
    *(undefined4 *)(local_4 + unaff_EDI[3]) = uVar3;
    puVar5 = puVar5 + -3;
    local_4 = local_4 + -4;
  } while (-1 < local_4);
  return;
}