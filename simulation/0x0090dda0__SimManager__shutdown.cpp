// FUNC_NAME: SimManager::shutdown
void __fastcall SimManager::shutdown(SimManager *this)
{
  int iVar1;
  uint uVar2;
  undefined4 local_c;
  undefined4 local_8;
  undefined1 local_4;
  
  uVar2 = 0;
  this->vtable = &PTR_FUN_00d83744; // +0x00 vtable
  this->field_4 = &PTR_LAB_00d83734; // +0x04
  if (this->numObjects != 0) { // +0x1C
    local_c = DAT_0112ffec;
    local_8 = 0;
    local_4 = 0;
    FUN_00408a00(&local_c,0); // likely some cleanup/notification
  }
  FUN_004086d0(&DAT_012069c4); // shutdown global manager
  if (this->numObjects != 0) { // +0x1C
    do {
      iVar1 = *(int *)(this->objectList + uVar2 * 4); // +0x18
      if (iVar1 != 0) {
        FUN_0090d920(); // destroy object
        FUN_009c8eb0(iVar1); // free memory
      }
      uVar2 = uVar2 + 1;
    } while (uVar2 < (uint)this->numObjects);
  }
  FUN_00408310(&DAT_0112ffe0); // release resource
  FUN_00408310(&DAT_0112ffec); // release resource
  if (this->objectList != 0) { // +0x18
    FUN_009c8f10(this->objectList); // free array
  }
  FUN_004083d0(); // final cleanup
  this->vtable = &PTR_LAB_00d83730; // +0x00 reset vtable
  DAT_0112abd0 = 0; // global flag
  return;
}