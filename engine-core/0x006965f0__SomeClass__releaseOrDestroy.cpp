// FUNC_NAME: SomeClass::releaseOrDestroy
void __fastcall SomeClass::releaseOrDestroy(int this)
{
  undefined1 local_8 [8];
  
  FUN_006961f0(local_8, this, **(undefined4 **)(this + 4), this, *(undefined4 **)(this + 4));
  FUN_009c8eb0(*(undefined4 *)(this + 4));
  *(undefined4 *)(this + 4) = 0;
  *(undefined4 *)(this + 8) = 0;
  return;
}