// FUNC_NAME: Entity::getSomeValue
undefined4 __fastcall Entity::getSomeValue(int thisPtr)
{
  char cVar1;
  
  if (((*(int *)(thisPtr + 0x9c) != 0) && (*(int *)(thisPtr + 0x9c) != 0x48)) &&
     (cVar1 = FUN_007f4800(), cVar1 != '\0')) {
    if (*(int *)(thisPtr + 0x9c) != 0) {
      return *(undefined4 *)(*(int *)(thisPtr + 0x9c) + 0x1e8c);
    }
    return uRam00001ed4;
  }
  return *(undefined4 *)(thisPtr + 200);
}