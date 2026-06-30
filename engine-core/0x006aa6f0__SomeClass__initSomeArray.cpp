// FUNC_NAME: SomeClass::initSomeArray
void __fastcall SomeClass::initSomeArray(int this)
{
  undefined4 *puVar1;
  int iVar2;
  
  iVar2 = 7;
  puVar1 = (undefined4 *)(this + 0xc);
  do {
    // Initialize each element of an array (size 0x6C per element)
    puVar1[-3] = &PTR_FUN_00d5d9b0; // vtable pointer at offset -0xC from puVar1
    puVar1[-2] = 0;                 // +0x00
    puVar1[-1] = 0;                 // +0x04
    *puVar1 = 0;                    // +0x08
    puVar1[1] = 0;                  // +0x0C
    puVar1[2] = 0;                  // +0x10
    puVar1[3] = 0;                  // +0x14
    puVar1[4] = 0;                  // +0x18
    puVar1[5] = 0;                  // +0x1C
    puVar1[6] = 0;                  // +0x20
    puVar1[7] = 0;                  // +0x24
    puVar1[8] = 0;                  // +0x28
    puVar1[9] = 0;                  // +0x2C
    puVar1[10] = 0;                 // +0x30
    puVar1[0xb] = 0;                // +0x34
    puVar1[0xc] = 0;                // +0x38
    puVar1[0xd] = 0;                // +0x3C
    puVar1[0xe] = 0;                // +0x40
    *(undefined2 *)(puVar1 + 0xf) = 0;   // +0x44 (2 bytes)
    *(undefined2 *)((int)puVar1 + 0x3e) = 0; // +0x46 (2 bytes)
    puVar1[0x10] = 0;               // +0x48
    *(undefined2 *)(puVar1 + 0x11) = 0;   // +0x4C (2 bytes)
    *(undefined2 *)((int)puVar1 + 0x46) = 0; // +0x4E (2 bytes)
    puVar1[0x12] = 0;               // +0x50
    *(undefined2 *)(puVar1 + 0x13) = 0;   // +0x54 (2 bytes)
    *(undefined2 *)((int)puVar1 + 0x4e) = 0; // +0x56 (2 bytes)
    puVar1[0x14] = 0;               // +0x58
    *(undefined2 *)(puVar1 + 0x15) = 0;   // +0x5C (2 bytes)
    *(undefined2 *)((int)puVar1 + 0x56) = 0; // +0x5E (2 bytes)
    puVar1[0x16] = 100;             // +0x60 (default value 100)
    *(undefined1 *)(puVar1 + 0x17) = 0;   // +0x64 (1 byte)
    puVar1 = puVar1 + 0x1b;         // Advance to next element (0x6C bytes per element)
    iVar2 = iVar2 + -1;
  } while (-1 < iVar2);
  
  // Initialize field at offset 0x360
  *(undefined4 *)(this + 0x360) = 0;
  return;
}