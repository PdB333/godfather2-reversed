// FUNC_NAME: EARS::Framework::ObjectList::~ObjectList
undefined4 * __thiscall ObjectList::~ObjectList(undefined4 *this, byte deleteFlag)
{
  int i;
  undefined4 **ppElement;
  
  // Loop over each element in the array (offset +0x0C = count, +0x10 = array of pointers)
  if (0 < (int)this[3]) {
    for (i = 0; i < (int)this[3]; i++) {
      ppElement = *(undefined4 ***)(this[4] + i * 4); // +0x10 base + i*4
      // Zero out two fields of each element (first two DWORDs)
      *ppElement = 0;          // +0x00
      ppElement[1] = 0;        // +0x04
    }
  }
  // Reset own internal fields
  this[1] = 0;  // +0x04
  this[2] = 0;  // +0x08
  // Set vtable to purecall to prevent further virtual calls
  *this = &PTR___purecall_00e30fac;  // +0x00 vtable
  // If deleteFlag bit 0 is set, release memory via operator delete
  if ((deleteFlag & 1) != 0) {
    FUN_009c8eb0(this);
  }
  return this;
}