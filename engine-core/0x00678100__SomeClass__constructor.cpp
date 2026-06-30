// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 this, short param_2, short param_3, short param_4)
{
  undefined4 *puVar1;
  int iVar2;
  short *psVar3;
  
  puVar1 = (undefined4 *)FUN_00672f60(0x78);
  *puVar1 = this;
  puVar1[0x10] = 0; // +0x40
  puVar1[0xf] = 0;  // +0x3C
  puVar1[0x16] = 0; // +0x58
  puVar1[0x15] = 0; // +0x54
  puVar1[0x14] = 0; // +0x50
  puVar1[3] = 0;    // +0x0C
  puVar1[4] = 0;    // +0x10
  *(undefined2 *)(puVar1 + 0xd) = 2; // +0x34, set to 2
  *(undefined2 *)(puVar1 + 1) = 0;   // +0x04
  puVar1[2] = 0;    // +0x08
  puVar1[0x18] = 0; // +0x60
  *(undefined2 *)((int)puVar1 + 0x36) = 0; // +0x36
  *(undefined2 *)(puVar1 + 0x1b) = 0;      // +0x6C
  *(undefined2 *)((int)puVar1 + 0x6e) = 0; // +0x6E
  *(undefined2 *)(puVar1 + 0x1c) = 0;      // +0x70
  *(undefined2 *)((int)puVar1 + 0x72) = 0; // +0x72
  puVar1[0x17] = 0; // +0x5C
  puVar1[0x1a] = 0; // +0x68
  puVar1[0x19] = 0; // +0x64
  iVar2 = FUN_00672f60(0x34);
  puVar1[0x14] = iVar2; // +0x50, pointer to allocated block
  puVar1[0x15] = iVar2 + 0x10; // +0x54, pointer to offset 0x10 in block
  psVar3 = (short *)(iVar2 + 0x20);
  puVar1[0x11] = psVar3; // +0x44, pointer to offset 0x20 in block
  puVar1[2] = 0;    // +0x08
  puVar1[0x12] = (undefined2 *)(iVar2 + 0x28); // +0x48, pointer to offset 0x28
  puVar1[0x13] = iVar2 + 0x30; // +0x4C, pointer to offset 0x30
  *(undefined2 *)(iVar2 + 0x28) = 0;
  *psVar3 = 0;
  *(undefined2 *)(iVar2 + 0x2a) = 0;
  *(short *)(iVar2 + 0x22) = *psVar3 + param_2; // +0x22 in block
  *(short *)(iVar2 + 0x2c) = *(short *)((int)puVar1 + 0x72) + param_3; // +0x2c in block, +0x72 in main
  *(undefined2 *)(iVar2 + 0x24) = 0;
  *(short *)(iVar2 + 0x2e) = *(short *)(iVar2 + 0x2c) - param_4; // +0x2e in block
  *(undefined2 *)(iVar2 + 0x26) = 0;
  *(undefined2 *)(puVar1 + 0xe) = 0; // +0x38
  return puVar1;
}