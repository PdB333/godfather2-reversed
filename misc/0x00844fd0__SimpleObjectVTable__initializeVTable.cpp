// FUNC_NAME: SimpleObjectVTable::initializeVTable
void __fastcall SimpleObjectVTable::initializeVTable(undefined4 *this)
{
  // DAT_012055a8 appears to be a static pointer to the object's VTable pointer
  // param_1 is the object base, the vtable pointer is stored at offset +4 (size of pointer)
  // PTR_LAB_00d74a70, PTR_LAB_00d74b6c, and PTR_LAB_00d74af0 are VTable addresses
  DAT_012055a8 = this + 1;  // +0x04 : vptr offset
  *DAT_012055a8 = &PTR_LAB_00d74a70;  // Set secondary vtable (likely for interface or derived class)
  *this = &PTR_LAB_00d74b6c;          // Set primary vtable (base class vtable)
  *DAT_012055a8 = &PTR_LAB_00d74af0;  // Overwrite secondary vtable with another vtable
  return;
}