// FUNC_NAME: BaseResource::~BaseResource
void __fastcall BaseResource::destructor(BaseResource *this)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = this->reference; // +0x14 (offset 5 * 4)
  this->vtablePtr = &PTR_FUN_00e37ae0; // vtable for BaseResource
  if (iVar1 != 0) {
    // Manage global reference list (singleton-like structure at 0x012068e8)
    piVar2 = (int *)(DAT_012068e8 + 0x14);  // +0x14 is the "list tail" pointer offset
    **(undefined4 **)(DAT_012068e8 + 0x14) = &PTR_LAB_01124ba8; // sentinel
    *piVar2 = *piVar2 + 4;
    *(int *)*piVar2 = iVar1;
    *piVar2 = *piVar2 + 4;
    this->reference = 0;
  }
  if (this->dataPtr != 0) { // +0x1c (offset 7 * 4)
    FUN_009c8f10(this->dataPtr); // deallocate data
  }
  this->vtablePtr = &PTR_LAB_00e37304; // base class vtable (possibly EARSObject)
  return;
}