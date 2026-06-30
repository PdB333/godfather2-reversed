// FUNC_NAME: SimNpc::releaseOrDestroy
void __fastcall SimNpc::releaseOrDestroy(int this)
{
  undefined **local_18;
  int local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined1 *local_8;
  undefined1 local_4;
  
  local_8 = (undefined1 *)&local_18;
  local_18 = &PTR_FUN_00e31e2c;
  if (this == 0) {
    local_14 = 0;
  }
  else {
    local_14 = this + 0x48;  // +0x48: mRefCount pointer (or ref count structure)
  }
  local_10 = 0;
  if (local_14 != 0) {
    local_10 = *(undefined4 *)(local_14 + 4);  // +0x4: next pointer in ref list
    *(int **)(local_14 + 4) = &local_14;       // unlink from ref list
  }
  local_c = *(undefined4 *)(this + 0x284);     // +0x284: some handle or pointer
  local_4 = 0;
  FUN_00408a00(&local_c,0);                    // release handle (likely SimObject handle)
  if (local_14 != 0) {
    FUN_004daf90(&local_14);                   // free ref count structure
  }
  return;
}