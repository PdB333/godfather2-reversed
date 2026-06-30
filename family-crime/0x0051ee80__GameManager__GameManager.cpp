// FUNC_NAME: GameManager::GameManager
GameManager * __thiscall GameManager::GameManager(GameManager *this)
{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  int iVar7;
  int *piVar8;
  int iVar9;
  long long llVar10;

  // vtable pointer set
  this->vtable = &GameManager_vtable;

  // Initialize first free list (4 elements?)
  // Each node has offset arrays?
  iVar7 = 4;
  piVar6 = &this->freeList4[0];
  do {
    piVar6[-0x19] = this->someHead;  // offset -0x76? Actually from base
    *piVar6 = (int)(piVar6 + -0x19);   // self-pointer offset
    piVar6[0x0e] = (int)(piVar6 + -0x0b);
    piVar6[0x1c] = (int)(piVar6 + 0x03);
    piVar6[0x2a] = (int)(piVar6 + 0x11);
    piVar1 = piVar6 + 0x1f;
    piVar6 += 0x46;  // 70 bytes per entry
    iVar7--;
    this->someHead = piVar1;
  } while (iVar7 != 0);

  // Initialize second free list (40 elements?)
  iVar7 = 0x28;
  piVar6 = &this->freeList40[0];
  do {
    piVar6[-0x11c] = this->someHead2;
    *piVar6 = (int)(piVar6 + -300);
    piVar6[0x11c] = (int)(piVar6 + -0x10);
    piVar6[0x238] = (int)(piVar6 + 0x10c);
    piVar6[0x354] = (int)(piVar6 + 0x228);
    piVar1 = piVar6 + 0x344;
    piVar6 += 0x58c;  // 1420 bytes per entry
    iVar7--;
    this->someHead2 = piVar1;
  } while (iVar7 != 0);

  // Initialize third free list (24 elements?)
  iVar7 = 0x18;
  piVar6 = &this->freeList24[0];
  do {
    piVar6[-0x50] = this->someHead3;
    *piVar6 = (int)(piVar6 + -0x60);
    piVar6[0x50] = (int)(piVar6 + -0x10);
    piVar6[0xa0] = (int)(piVar6 + 0x40);
    piVar6[0xf0] = (int)(piVar6 + 0x90);
    piVar6[0x140] = (int)(piVar6 + 0xe0);
    piVar1 = piVar6 + 0x130;
    piVar6 += 0x1e0;  // 480 bytes per entry
    iVar7--;
    this->someHead3 = piVar1;
  } while (iVar7 != 0);

  // Initialize array of 199 objects (size 0x11c each)
  iVar7 = 0xc7;
  piVar8 = (int *)(this + 0x120);   // offset 0x120: start of first large array
  piVar6 = (int *)(this + 0x236);   // offset 0x236: after first element? Actually puVar4 starts here
  do {
    // Clear some field at offset -0x112
    piVar6[-0x112] = 0;
    // Set vtable for this sub-object
    *(undefined4 **)piVar8 = &SUBOBJECT_VTABLE_0x00e38350;
    // Call vector constructor for 6 elements of size 0xa0
    vector_constructor_iterator(piVar6 + -0xf2, 0xa0, 6, &VECTOR_INIT_FUNC_0x00523130);
    // Clear three fields
    *piVar6 = 0;
    piVar6[1] = 0;
    *(undefined2 *)(piVar6 + 2) = 0;
    // Advance by 0x11c bytes
    piVar8 += 0x11c / 4;     // 0x11c = 284 bytes = 71 ints
    piVar6 += 0x11c / 4;
    iVar7--;
  } while (iVar7 >= 0);

  // Initialize array of 143 objects (size 0x50 each)
  iVar7 = 0x8f;
  piVar8 = (int *)(this + 0xdf04);  // offset 0xdf04: start of second large array
  piVar6 = (int *)(this + 0xdf4d);  // offset 0xdf4d: after first element? Actually puVar4
  do {
    // Clear at offset -0x45
    piVar6[-0x45] = 0;
    // Set vtable
    *(undefined4 **)piVar8 = &SUBOBJECT_VTABLE_0x00e38360;
    // Clear three fields
    piVar6[-0x15] = 0;
    *piVar6 = 0;
    piVar6[1] = 0;
    *(undefined2 *)(piVar6 + 3) = 0;
    // Advance by 0x50 bytes
    piVar8 += 0x50 / 4;      // 0x50 = 80 bytes = 20 ints
    piVar6 += 0x50 / 4;
    iVar7--;
  } while (iVar7 >= 0);

  // Clear large buffer at offset +0x10c20, size 0x5fd80
  memset((char *)this + 0x10c20, 0, 0x5fd80);

  // Call sub-initializer
  subInitializer();  // FUN_0066e1d0

  this->field_0x10 = 0;  // offset 0x10

  // Additional free list init (similar to first, but different loop)
  iVar7 = 4;
  piVar6 = &this->freeList4_2[0];
  do {
    piVar6[-0x0e] = this->someHead4;
    *piVar6 = (int)(piVar6 + -0x19);
    piVar6[0x0e] = (int)(piVar6 + -0x0b);
    piVar6[0x1c] = (int)(piVar6 + 0x03);
    piVar6[0x2a] = (int)(piVar6 + 0x11);
    piVar1 = piVar6 + 0x1f;
    piVar6 += 0x46;
    iVar7--;
    this->someHead4 = piVar1;
  } while (iVar7 != 0);

  // Set a field to 0
  this->field_0x474 = 0;  // offset 0x11d*4? Actually puVar3[0x11d] -> offset 0x474

  // Another free list (40 elements) - similar to second
  iVar7 = 0x28;
  piVar6 = &this->freeList40_2[0];
  do {
    piVar6[-0x11c] = this->someHead5;
    *piVar6 = (int)(piVar6 + -300);
    piVar6[0x11c] = (int)(piVar6 + -0x10);
    piVar6[0x238] = (int)(piVar6 + 0x10c);
    piVar6[0x354] = (int)(piVar6 + 0x228);
    piVar1 = piVar6 + 0x344;
    piVar6 += 0x58c;
    iVar7--;
    this->someHead5 = piVar1;
  } while (iVar7 != 0);

  // Another field set to 0
  this->field_0x37c08 = 0;  // offset 0xdf02*4

  // Another free list (24 elements) - similar to third
  iVar7 = 0x18;
  piVar6 = &this->freeList24_2[0];
  do {
    piVar6[-0x50] = this->someHead6;
    *piVar6 = (int)(piVar6 + -0x60);
    piVar6[0x50] = (int)(piVar6 + -0x10);
    piVar6[0xa0] = (int)(piVar6 + 0x40);
    piVar6[0xf0] = (int)(piVar6 + 0x90);
    piVar6[0x140] = (int)(piVar6 + 0xe0);
    piVar1 = piVar6 + 0x130;
    piVar6 += 0x1e0;
    iVar7--;
    this->someHead6 = piVar1;
  } while (iVar7 != 0);

  // Allocate a small object (size 0x1c)
  iVar2 = memoryAlloc(0x1c);  // FUN_009c8e50
  if (iVar2 != 0) {
    iVar2 = subObjectConstructor();  // FUN_0066d6e0
  }
  this->field_0x37c04 = iVar2;  // offset 0xdf01

  // Global timing calculation: (globalVar * 4) / 1000
  llVar10 = __allmul(DAT_01163ec0, DAT_01163ec4, 4, 0);
  llVar10 = __aulldiv(llVar10, 1000, 0);
  gGlobalTimer = (int)llVar10;  // DAT_01194d08
  gGlobalTimerHigh = (int)((unsigned long long)llVar10 >> 32);  // DAT_01194d0c

  return this;
}