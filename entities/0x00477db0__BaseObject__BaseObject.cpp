// FUNC_NAME: BaseObject::BaseObject

undefined4 * __thiscall BaseObject::BaseObject(BaseObject *this, undefined4 param_2)
{
  ushort refCountNodeValue;
  int refCountNode;
  
  BaseClassConstructor(param_2);
  *this = &VTable_00e32f6c; // Main vtable
  this->field_0x3c = &VTable_00e32f88; // Secondary vtable 1
  this->field_0x48 = &VTable_00e32f98; // Secondary vtable 2
  this->field_0x50 = 0; // Some pointer
  this->field_0x54 = 0; // Some 16-bit value
  *(undefined2 *)((int)this + 0x56) = 0; // Another 16-bit
  this->field_0x58 = 0;
  this->field_0x5c = 0;
  if (g_bRefCountEnabled != 0) {
    g_RefCountCount++;
    refCountNode = AllocateRefCountNode();
    if (refCountNode != 0) {
      refCountNodeValue = *(ushort *)(refCountNode + 0x14); // Current reference count from node
      // Increment reference count with wraparound protection (max 0x7fff)
      *(ushort *)(refCountNode + 0x14) =
           ((short)((int)((uint)refCountNodeValue * 2) >> 1) + 1U ^ refCountNodeValue) & 0x7fff ^ refCountNodeValue;
      return this;
    }
    ResetRefCountSystem(&g_bRefCountEnabled, 0x7fff);
  }
  return this;
}