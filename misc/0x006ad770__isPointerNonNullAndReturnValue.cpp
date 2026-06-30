// FUNC_NAME: isPointerNonNullAndReturnValue
undefined4 FUN_006ad770(int param_1)
{
  undefined4 uVar1;
  
  if (param_1 != 0) {
    // Call FUN_0043b870 with a global data pointer (likely a singleton or state manager)
    uVar1 = FUN_0043b870(DAT_0112afb8);
    return uVar1;
  }
  return 0;
}