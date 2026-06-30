// FUNC_NAME: PitchCorrection::copy
void __fastcall PitchCorrection::copy(PitchCorrection *this, PitchCorrection *other)
{
  int iVar1;
  
  if (this != other) {
    for (iVar1 = 9; iVar1 != 0; iVar1 = iVar1 - 1) {
      *this = *other;
      other = (PitchCorrection *)((int)other + 4);
      this = (PitchCorrection *)((int)this + 4);
    }
    *(undefined2 *)this = *(undefined2 *)other;
    *(undefined1 *)((int)this + 2) = *(undefined1 *)((int)other + 2);
  }
  return;
}