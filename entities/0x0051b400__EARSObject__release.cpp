// FUNC_NAME: EARSObject::release
void __fastcall EARSObject::release(int this)
{
  int iVar1;
  
  // Clear the "alive" flag (bit 0) and "has ref" flag (bit 1)
  *(uint *)(this + 0xc) = *(uint *)(this + 0xc) & 0x7ffffffe;
  
  // If the "in release list" flag (bit 17) is not set, set it and call the release list handler
  if ((*(uint *)(this + 0xc) & 0x20000) == 0) {
    *(uint *)(this + 0xc) = *(uint *)(this + 0xc) | 0x20000;
    FUN_0051b120(); // likely addToReleaseList or processReleaseList
  }
  
  // Clear the "in release list" flag
  *(uint *)(this + 0xc) = *(uint *)(this + 0xc) & 0xfffbffff;
  
  iVar1 = DAT_01205514; // likely g_objectListHead or similar global
  if (*(undefined4 **)(this + 8) != (undefined4 *)0x0) {
    **(undefined4 **)(this + 8) = 0; // clear next pointer in list
    *(undefined4 *)(this + 8) = 0;   // clear this object's next pointer
    iVar1 = DAT_01205514;
  }
  
  // Iterate through the object list and recursively release any objects that reference this one
  for (; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x14)) {
    if (*(int *)(iVar1 + 0x18) == this) {
      FUN_0051b400(); // recursive release call
    }
  }
  return;
}