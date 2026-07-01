// FUNC_NAME: SomeClass::loadSomeResource
void __fastcall SomeClass::loadSomeResource(int thisPtr)
{
  undefined4 uVar1;
  undefined8 *puVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 uVar6;
  
  uVar6 = 0;
  iVar5 = thisPtr + 0x8a4; // +0x8A4: some resource handle or buffer offset
  uVar4 = 0x4010001; // Resource type or flags
  uVar3 = 0x60f3e; // Resource ID or size
  uVar1 = FUN_0043b490(0x60f3e, 0x4010001, iVar5, 0); // Allocate or prepare resource
  puVar2 = (undefined8 *)FUN_00540bf0(2, uVar1, uVar3, uVar4, iVar5, uVar6); // Load resource data
  *(undefined8 *)(thisPtr + 0x828) = *puVar2; // +0x828: first 8 bytes of loaded data
  *(undefined8 *)(thisPtr + 0x830) = puVar2[1]; // +0x830: next 8 bytes
  *(undefined4 *)(thisPtr + 0x838) = *(undefined4 *)(puVar2 + 2); // +0x838: last 4 bytes
  return;
}