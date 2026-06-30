// FUNC_NAME: RefCountedObject::addRef
void __fastcall RefCountedObject::addRef(int this)
{
  *(int *)(this + 0xc) = *(int *)(this + 0xc) + 1; // +0xC: refCount
  return;
}