// FUNC_NAME: SomeClass::getElementByIndex
undefined4 __fastcall getElementByIndex(int this, int in_EAX)
{
  // this +0x4c: pointer to array of elements
  // this +0x54: count of elements in array
  if ((in_EAX < *(int *)(this + 0x54)) && (*(int *)(*(int *)(this + 0x4c) + in_EAX * 4) != 0))
  {
    return *(undefined4 *)(*(int *)(this + 0x4c) + in_EAX * 4);
  }
  // Return a sentinel value (likely null or invalid handle)
  return DAT_0119cbbc;
}