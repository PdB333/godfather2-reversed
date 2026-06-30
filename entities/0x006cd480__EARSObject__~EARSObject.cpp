// FUNC_NAME: EARSObject::~EARSObject
void __fastcall EARSObject::~EARSObject(undefined4 *this)
{
  int *piVar1;
  int *piVar2;
  undefined4 local_c;
  undefined4 local_8;
  undefined1 local_4;
  
  piVar1 = this + 0x30; // +0xC0: pointer to some sub-object
  *this = &PTR_FUN_00d5f174; // vtable pointer
  this[2] = &PTR_LAB_00d5f16c; // +0x08: another vtable pointer
  if ((*piVar1 != 0) && (*piVar1 != 0x48)) {
    if (*piVar1 == 0) {
      piVar2 = (int *)0x0;
    }
    else {
      piVar2 = (int *)(*piVar1 + -0x48); // offset -0x48 from sub-object
    }
    (**(code **)(*piVar2 + 0x70))(); // call virtual destructor at vtable+0x70
  }
  if ((DAT_0112a804 != 0) && (DAT_0112a804 = DAT_0112a804 + -1, DAT_0112a804 == 0)) {
    local_c = DAT_0112a80c;
    local_8 = 0;
    local_4 = 0;
    FUN_00408a00(&local_c,0); // some cleanup function
    FUN_006cc3b0(); // shutdown function
  }
  if (this[0x32] != 0) { // +0xC8: another pointer
    FUN_004daf90(this + 0x32); // free memory
  }
  if (*piVar1 != 0) {
    FUN_004daf90(piVar1); // free memory
  }
  FUN_006c9820(); // final cleanup
  return;
}