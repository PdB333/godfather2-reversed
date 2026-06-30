// FUNC_NAME: NetObject::operator=
undefined8* __thiscall NetObject::operator=(NetObject *this, NetObject *other)
{
  int* pOldPointer1;
  int iNewPointer1;
  int* pOldPointer2;
  int iNewPointer2;

  // Copy all primitive fields (assuming 8-byte aligned blocks and some 4-byte fields)
  *this = *other; // Simplified; actually copies field by field as below
  This->field0 = other->field0;
  This->field1 = other->field1;
  This->field2 = other->field2;
  This->field3 = other->field3;
  // ... (all other fields copied)

  // Handle first intrusive pointer at offset +0x28 (param_1+5 as undefined8*)
  pOldPointer1 = (int*)(&this->field5); // +0x28
  if (pOldPointer1 != (int*)(&other->field5)) {
    iNewPointer1 = *(int*)(&other->field5);
    if (*pOldPointer1 != iNewPointer1) {
      if (*pOldPointer1 != 0) {
        NetObject::releaseRef(pOldPointer1); // FUN_004daf90 – likely decrement refcount
      }
      *pOldPointer1 = iNewPointer1;
      if (iNewPointer1 != 0) {
        // Update back pointer in the newly referenced object (offset +0x04)
        *(int*)((char*)this + 0x2c) = *(int*)(iNewPointer1 + 4);
        *(int**)(iNewPointer1 + 4) = pOldPointer1;
      }
    }
  }

  // Handle second intrusive pointer at offset +0x30 (param_1+6 as undefined8*)
  pOldPointer2 = (int*)(&this->field6); // +0x30
  if (pOldPointer2 != (int*)(&other->field6)) {
    iNewPointer2 = *(int*)(&other->field6);
    if (*pOldPointer2 != iNewPointer2) {
      if (*pOldPointer2 != 0) {
        NetObject::releaseRef(pOldPointer2);
      }
      *pOldPointer2 = iNewPointer2;
      if (iNewPointer2 != 0) {
        // Update back pointer at offset +0x04
        *(int*)((char*)this + 0x34) = *(int*)(iNewPointer2 + 4);
        *(int**)(iNewPointer2 + 4) = pOldPointer2;
      }
    }
  }

  // Copy remaining 32-bit fields at various offsets
  *(unsigned int*)(&this->field7) = *(unsigned int*)(&other->field7);
  *(unsigned int*)((char*)this + 0x3c) = *(unsigned int*)((char*)other + 0x3c);
  *(unsigned int*)(&this->field8) = *(unsigned int*)(&other->field8);
  *(unsigned int*)((char*)this + 0x44) = *(unsigned int*)((char*)other + 0x44);
  *(unsigned int*)(&this->field9) = *(unsigned int*)(&other->field9);
  *(unsigned int*)((char*)this + 0x4c) = *(unsigned int*)((char*)other + 0x4c);
  *(unsigned int*)(&this->field10) = *(unsigned int*)(&other->field10);
  *(unsigned int*)((char*)this + 0x54) = *(unsigned int*)((char*)other + 0x54);
  *(unsigned int*)(&this->field11) = *(unsigned int*)(&other->field11);
  *(unsigned int*)((char*)this + 0x5c) = *(unsigned int*)((char*)other + 0x5c);
  *(unsigned int*)(&this->field12) = *(unsigned int*)(&other->field12);
  *(unsigned int*)((char*)this + 0x64) = *(unsigned int*)((char*)other + 0x64);
  *(unsigned int*)(&this->field13) = *(unsigned int*)(&other->field13);
  *(unsigned int*)((char*)this + 0x6c) = *(unsigned int*)((char*)other + 0x6c);
  *(unsigned int*)(&this->field14) = *(unsigned int*)(&other->field14);
  *(unsigned int*)((char*)this + 0x74) = *(unsigned int*)((char*)other + 0x74);
  *(unsigned int*)(&this->field15) = *(unsigned int*)(&other->field15);
  *(unsigned long long*)((char*)this + 0x7c) = *(unsigned long long*)((char*)other + 0x7c);
  *(unsigned int*)((char*)this + 0x84) = *(unsigned int*)((char*)other + 0x84);
  *(unsigned int*)(&this->field17) = *(unsigned int*)(&other->field17);

  return (undefined8*)this;
}