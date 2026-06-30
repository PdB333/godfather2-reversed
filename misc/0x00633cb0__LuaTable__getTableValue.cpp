// FUNC_NAME: LuaTable::getTableValue
void LuaTable::getTableValue(undefined4 this, int *tableStack, int *keyStack, int depth)
{
  int *valueStack;
  
  if (100 < depth) {
    FUN_00633920(this,"loop in gettable");
  }
  if (*tableStack != 5) {
    FUN_00633c30(tableStack,keyStack,depth + 1);
    return;
  }
  if (*keyStack == 3) {
    if ((float)(int)(float)keyStack[1] == (float)keyStack[1]) {
      valueStack = (int *)FUN_00637f10(); // luaH_getnum
      goto LAB_00633d1d;
    }
  }
  else if (*keyStack == 4) {
    valueStack = (int *)FUN_00637f90(); // luaH_getstr
    goto LAB_00633d1d;
  }
  valueStack = (int *)FUN_00637ea0(); // luaH_get
LAB_00633d1d:
  if (*valueStack == 0) {
    FUN_00633bc0(this,tableStack,keyStack,depth + 1);
  }
  return;
}