// FUNC_NAME: LuaScript::randomIntRange
undefined4 FUN_006326d0(int this)

{
  int iVar1;
  int iVar2;
  undefined4 *stackPtr;
  int extraout_ECX;
  float fVar4;
  float fVar5;
  
  iVar1 = _rand();
  stackPtr = *(undefined4 **)(this + 8); // +0x8: stack pointer
  iVar2 = (int)stackPtr - *(int *)(this + 0xc) >> 3; // +0xc: stack base, calculate number of arguments
  fVar4 = (float)(iVar1 % 0x7fff) * DAT_00e44590; // random float in [0,1)
  if (iVar2 != 0) {
    if (iVar2 == 1) {
      // One argument: random integer in [0, arg)
      fVar5 = fVar4;
      FUN_00628080(); // pop argument
      iVar1 = (int)fVar5;
      if (iVar1 < 1) {
        FUN_00627a20(this,1,"interval is empty"); // error: interval empty
        iVar1 = extraout_ECX;
      }
      stackPtr = *(undefined4 **)(this + 8);
      fVar4 = (float)iVar1 * fVar4; // scale random to [0, arg)
      fVar5 = (float)(DAT_00e44648 | DAT_00e44564 & (uint)fVar4);
      fVar5 = (fVar4 + fVar5) - fVar5;
      fVar4 = (float)(-(uint)((float)(DAT_00e44564 & (uint)fVar4) < fVar5 - fVar4) & DAT_00e2b1a4);
      *stackPtr = 3; // push integer type
      stackPtr[1] = (float)((int)(fVar5 - fVar4) + 1); // result + 1 (since range is [0, arg))
      *(int *)(this + 8) = *(int *)(this + 8) + 8;
      return 1;
    }
    fVar5 = fVar4;
    if (iVar2 != 2) {
      FUN_00627bd0("wrong number of arguments"); // error
    }
    // Two arguments: random integer in [arg1, arg2]
    FUN_00628080(); // pop arg1 (lower bound)
    iVar2 = (int)fVar5;
    FUN_00628080(); // pop arg2 (upper bound)
    iVar1 = (int)fVar5;
    if (iVar1 < iVar2) {
      iVar1 = FUN_00627a20(this,2,"interval is empty"); // error: interval empty
    }
    stackPtr = *(undefined4 **)(this + 8);
    fVar4 = (float)((iVar1 - iVar2) + 1) * fVar4; // scale random to range size
    fVar5 = (float)(DAT_00e44648 | DAT_00e44564 & (uint)fVar4);
    fVar5 = (fVar4 + fVar5) - fVar5;
    fVar4 = (float)((int)(fVar5 - (float)(-(uint)((float)(DAT_00e44564 & (uint)fVar4) <
                                                 fVar5 - fVar4) & DAT_00e2b1a4)) + iVar2);
  }
  *stackPtr = 3; // push integer type
  stackPtr[1] = fVar4; // result
  *(int *)(this + 8) = *(int *)(this + 8) + 8;
  return 1;
}