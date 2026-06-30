// FUNC_NAME: someClass::getCurrentAnimStateEntry
int __fastcall someClass::getCurrentAnimStateEntry(int this)
{
  short animIndex;
  int animStateArray;
  
  animStateArray = *(int *)(this + 0x70);
  if ((((animStateArray != 0) && (0 < *(int *)(animStateArray + 0x18))) && (*(int *)(animStateArray + 0x1c) != 0)) &&
     ((animIndex = *(short *)(this + 0x76), -1 < animIndex && ((int)animIndex < *(int *)(animStateArray + 0x18))))) {
    return *(int *)(animStateArray + 0x1c) + animIndex * 0x18;
  }
  return 0;
}