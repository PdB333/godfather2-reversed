// FUNC_NAME: Entity::setVisibility
void __fastcall Entity::setVisibility(int this)
{
  undefined4 uVar1;
  char acStack_10 [16];
  
  if (*(char *)(this + 0x48) != '\0') {
    // Get the entity's name string from vtable (+0x10) via method at offset 4
    uVar1 = (**(code **)(*(int *)(this + 0x10) + 4))();
    // Build a 4-character tag from the name hash (big-endian)
    DAT_01223564 = (undefined1)((uint)uVar1 >> 0x18);
    DAT_01223565 = (undefined1)((uint)uVar1 >> 0x10);
    DAT_01223566 = (undefined1)((uint)uVar1 >> 8);
    DAT_01223567 = (undefined1)uVar1;
    DAT_01223568 = 0;
    // Format the script variable name as "<tag>._visible"
    _sprintf(acStack_10, "%s._visible", &DAT_01223564);
    // Set the script variable to 0 (invisible)
    FUN_0059ee00(acStack_10, 0);
  }
  return;
}