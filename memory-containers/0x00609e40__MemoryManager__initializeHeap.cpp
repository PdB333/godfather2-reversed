// FUNC_NAME: MemoryManager::initializeHeap
void MemoryManager::initializeHeap(void)
{
  int iVar1;
  int iVar2;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  local_c = 2;  // heap type
  local_8 = 0x10; // alignment
  local_4 = 0;  // flags
  iVar1 = (**(code **)*DAT_01205868)(0x10, &local_c); // allocate heap descriptor (size 0x10)
  *(int *)(iVar1 + 8) = iVar1;  // self-reference at +0x08
  *(undefined4 *)(iVar1 + 4) = 0x100000; // heap size: 1MB at +0x04
  *(undefined1 *)(iVar1 + 0xc) = 1; // heap initialized flag at +0x0C
  iVar2 = (**(code **)(*DAT_01205750 + 0x68))(DAT_01205750, 0x100000, 0x208, 0, 0, iVar1, 0); // allocate memory block
  if ((iVar2 != 0) && (iVar2 == -0x7789fe84)) { // check for specific address
    (*(code *)PTR_FUN_00f15a3c)(2); // callback on success
  }
  DAT_01205844 = 0; // clear error flag
  DAT_01205840 = iVar1; // store heap descriptor
  return;
}