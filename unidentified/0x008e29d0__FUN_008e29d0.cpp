// FUNC_NAME: SomeClass::releaseOrFreeResource
void __fastcall SomeClass::releaseOrFreeResource(int this)
{
  undefined **local_18;
  int local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined1 *local_8;
  undefined1 local_4;
  
  local_8 = (undefined1 *)&local_18;
  if (*(int *)(this + 0x1bc) != 0) {
    local_14 = this + 0x48;
    local_18 = &PTR_FUN_00e31e2c;
    local_10 = 0;
    if (local_14 != 0) {
      local_10 = *(undefined4 *)(this + 0x4c);
      *(int **)(this + 0x4c) = &local_14;
    }
    local_c = *(undefined4 *)(this + 0x1bc);
    local_4 = 0;
    FUN_00408a00(&local_c,0);
    if (local_14 != 0) {
      FUN_004daf90(&local_14);
    }
  }
  return;
}