// FUNC_NAME: ObjectSelector::popLastSelected
uint __fastcall ObjectSelector::popLastSelected(int this)
{
  int count;
  uint result;
  undefined4 *ppSelected;

  result = in_EAX & 0xffffff00;
  // +0x6030: count of stored selections
  if (*(int *)(this + 0x6030) != 0) {
    count = *(int *)(this + 0x6030);
    ppSelected = (undefined4 *)(count - 1);
    if (ppSelected != (undefined4 *)0x0) {
      // +0x602c: pointer to selected object array
      ppSelected = *(undefined4 **)(this + 0x602c);
      // Copy last selected object from array (each element is 2 dwords)
      *ppSelected = ppSelected[count * 2 - 2];  // copy object pointer
      ppSelected[1] = ppSelected[count * 2 - 1]; // copy extra data
    }
    // Decrement count
    *(int *)(this + 0x6030) = count - 1;
    result = CONCAT31((int3)((uint)ppSelected >> 8), 1);
  }
  return result;
}