// FUNC_NAME: DestroyableObject::releaseResources
void __fastcall DestroyableObject::releaseResources(int this)
{
  int resource;
  
  *(uint *)(this + 0x10) = *(uint *)(this + 0x10) & 0xfffffffc;
  resource = *(int *)(this + 0x1c);
  if (resource != 0) {
    FUN_00816660();
    FUN_009c8eb0(resource);
    *(undefined4 *)(this + 0x1c) = 0;
  }
  resource = *(int *)(this + 0x20);
  if (resource != 0) {
    FUN_00816660();
    FUN_009c8eb0(resource);
    *(undefined4 *)(this + 0x20) = 0;
  }
  return;
}