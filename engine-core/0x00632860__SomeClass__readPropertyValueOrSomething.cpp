// FUNC_NAME: SomeClass::readPropertyValueOrSomething
undefined4 FUN_00632860(int thisPtr)

{
  float fVar1;
  int iVar2;
  int *piVar3;
  undefined2 in_FPUControlWord;
  float local_14;
  undefined8 local_10;
  
  piVar3 = *(int **)(thisPtr + 0xc); // +0xC: current data pointer
  if (*(int **)(thisPtr + 8) <= piVar3) goto LAB_0063291b; // +0x8: end pointer
  if (piVar3 == (int *)0x0) goto LAB_0063291b;
  if (*piVar3 != 3) { // Token type 3 = maybe a float literal?
    if (*piVar3 != 4) goto LAB_0063291b; // Token type 4 = maybe something else
    iVar2 = FUN_00636850(&local_14); // Read next token value
    if (iVar2 == 0) goto LAB_0063291b;
    local_10 = CONCAT44(local_14,3); // Pack type 3 with value
    piVar3 = (int *)&local_10;
  }
  local_14 = (float)piVar3[1]; // Extract float value from token
  if (local_14 == DAT_00e2b05c) { // Compare with a special constant (likely -1.0 or some sentinel)
    do {
      piVar3 = *(int **)(thisPtr + 0xc);
      if ((piVar3 < *(int **)(thisPtr + 8)) && (piVar3 != (int *)0x0)) {
        if (*piVar3 == 3) break; // Type 3 means float value
        if (*piVar3 == 4) {
          iVar2 = FUN_00636850(&local_10);
          if (iVar2 != 0) break;
        }
      }
      FUN_00627ac0(PTR_s_number_00e2a8a8); // Print some warning/error "number"
LAB_0063291b:
      local_14 = 0.0;
    } while( true );
  }
  fVar1 = local_14;
  local_14 = (float)CONCAT22(local_14._2_2_,in_FPUControlWord);
  local_10 = (longlong)ROUND(fVar1);
  FUN_00b9a183((int)local_10); // Cast to int and call some function (maybe clamp or set)
  return 0;
}