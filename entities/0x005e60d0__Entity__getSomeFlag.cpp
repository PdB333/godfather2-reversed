// FUNC_NAME: Entity::getSomeFlag
undefined1 __fastcall Entity::getSomeFlag(undefined4 param_1, undefined4 param_2)
{
  int entityPtr;
  undefined1 flagValue;
  undefined1 local_4[4];
  
  entityPtr = FUN_005f0560(param_2, &flagValue, local_4);
  if (entityPtr != 0) {
    return *(undefined1 *)(entityPtr + 0x22); // +0x22: some flag byte
  }
  return 0;
}