// Xbox PDB: public: __cdecl SortedArrayMask::~SortedArrayMask(void)
// FUNC_NAME: AptDisplayList::assertNoElements
void AptDisplayList::assertNoElements(void)
{
  int *piVar1;
  code *pcVar2;
  int this;
  uint uVar3;
  int unaff_FS_OFFSET;
  char *local_14;
  char *local_10;
  undefined4 local_c;
  int local_8;
  undefined1 *local_4;
  
  // Check if element count at +0x80 is zero
  if (*(int *)(this + 0x80) == 0) {
    return;
  }
  
  // Assertion data: "nElements == 0" from AptDisplayList.cpp line 0x260
  local_14 = "nElements == 0";
  local_10 = "..\\source\\Apt\\AptDisplayList.cpp";
  local_c = 0x260;
  local_8 = 2;
  local_4 = &DAT_0112901b;
  
  if (DAT_0112901b != '\0') {
    // Access assertion handler via FS segment
    piVar1 = *(int **)(**(int **)(unaff_FS_OFFSET + 0x2c) + 0x30);
    uVar3 = 1;
    if (((piVar1 == (int *)0x0) ||
        (uVar3 = (**(code **)(*piVar1 + 8))(&local_14,"nElements == 0"),
        local_4 != (undefined1 *)0x0)) && ((uVar3 & 2) != 0)) {
      *local_4 = 0;
    }
    if (((piVar1 != (int *)0x0) || (local_8 != 4)) &&
       (((uVar3 & 1) != 0 || ((local_8 == 0 || (local_8 == 1)))))) {
      pcVar2 = (code *)swi(3);
      (*pcVar2)();
      return;
    }
    return;
  }
  return;
}