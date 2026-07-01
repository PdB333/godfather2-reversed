// FUNC_NAME: TNL::NetStringTableEntry::operator=
void __thiscall TNL::NetStringTableEntry::operator=(TNL::NetStringTableEntry *this,const TNL::NetStringTableEntry *other)

{
  int *piVar1;
  
  piVar1 = other->entry;
  this->entry = piVar1;
  if (piVar1 != 0) {
    *(int *)(piVar1 + 4) = *(int *)(piVar1 + 4) + 1;  // +0x04: refCount
  }
  *(short *)(this + 1) = other->index;  // +0x04: index (short)
  *(undefined2 *)((int)this + 6) = other->__pad6;  // +0x06: padding
  *(undefined2 *)((int)this + 6) = other->__pad6;  // +0x06: padding (duplicated due to decompiler)
  *(char *)(this + 2) = other->type;  // +0x08: type
  *(undefined1 *)((int)this + 9) = other->__pad9;  // +0x09: padding
  this->dwordC = other->dwordC;  // +0x0C: some value
  this->dword10 = other->dword10;  // +0x10: some value
  this->dword14 = other->dword14;  // +0x14: some value
  this->dword18 = other->dword18;  // +0x18: some value
  return;
}