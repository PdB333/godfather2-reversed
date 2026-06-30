// FUNC_NAME: StringTable::parseStringList
void __thiscall StringTable::parseStringList(int this, undefined4 param_2, undefined4 param_3)
{
  char cVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  code *unaff_EBX;
  undefined4 *puVar4;
  undefined1 *puStack_4c;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  char local_28 [36];
  
  puStack_4c = *(undefined1 **)(this + 0x110); // +0x110: current string pointer
  local_3c = 0;
  _sprintf(local_28, "%u"); // format string for integer conversion
  puStack_4c = (undefined1 *)0x0;
  puVar4 = &local_3c;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  // Call a method on the parser object at +0x114 to parse first token
  cVar1 = (**(code **)(**(int **)(this + 0x114) + 0x1c))(local_28, param_3, &local_38);
  while (cVar1 != '\0') {
    puVar3 = puStack_4c;
    if (puStack_4c == (undefined1 *)0x0) {
      puVar3 = &DAT_0120546e; // default separator/empty string
    }
    // Convert and store the token
    uVar2 = FUN_00568db0(*(undefined4 *)(this + 0x114), *(undefined4 *)(this + 0x110), puVar3,
                         puVar4, param_3);
    // Store in the string table array (max 64 entries at +0x04)
    if (*(uint *)(this + 0x104) < 0x40) {
      *(undefined4 *)(this + 4 + *(uint *)(this + 0x104) * 4) = uVar2;
      *(int *)(this + 0x104) = *(int *)(this + 0x104) + 1;
    }
    // Continue parsing next token
    cVar1 = (**(code **)(**(int **)(this + 0x114) + 0x20))
                      (&local_3c, param_3, &puStack_4c, &stack0xffffffb0);
  }
  // Finalize parsing
  (**(code **)(**(int **)(this + 0x114) + 0x24))();
  if (puStack_4c != (undefined1 *)0x0) {
    (*unaff_EBX)(puStack_4c);
  }
  return;
}