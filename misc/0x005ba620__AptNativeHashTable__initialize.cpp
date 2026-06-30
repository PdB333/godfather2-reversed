// FUNC_NAME: AptNativeHashTable::initialize
void __thiscall AptNativeHashTable::initialize(AptNativeHashTable *this, int size)
{
  int *piVar1;
  code *pcVar2;
  uint uVar3;
  int iVar4;
  byte *_Dst;
  byte *unaff_EDI;
  int unaff_FS_OFFSET;
  char *local_14;
  char *local_10;
  undefined4 local_c;
  int local_8;
  undefined1 *local_4;
  
  // Validate size parameter
  if ((0 < size) && (size < 0x10000)) goto LAB_005ba6be;
  
  // Assertion failure handling (size validation failed)
  local_14 = "(_nSize > 0) && (_nSize <= 0xFFFF)";
  local_10 = "..\\source\\Apt\\AptNativeHash.cpp";
  local_c = 0x47;
  local_8 = 2;
  local_4 = &DAT_0112915d;
  if (DAT_0112915d == '\0') goto LAB_005ba6be;
  
  // Exception handling / debug output mechanism
  piVar1 = *(int **)(**(int **)(unaff_FS_OFFSET + 0x2c) + 0x30);
  uVar3 = 1;
  if (piVar1 == (int *)0x0) {
LAB_005ba69b:
    if ((uVar3 & 2) != 0) {
      *local_4 = 0;
    }
  }
  else {
    uVar3 = (**(code **)(*piVar1 + 8))(&local_14,"(_nSize > 0) && (_nSize <= 0xFFFF)");
    if (local_4 != (undefined1 *)0x0) goto LAB_005ba69b;
  }
  
  if (((piVar1 != (int *)0x0) || (local_8 != 4)) &&
     (((uVar3 & 1) != 0 || ((local_8 == 0 || (local_8 == 1)))))) {
    pcVar2 = (code *)swi(3);
    (*pcVar2)();
    return;
  }
  
LAB_005ba6be:
  // Store the hash table size (power of two)
  iVar4 = 1 << ((byte)size & 0x1f);
  *(short *)unaff_EDI = (short)size;  // +0x00: capacity exponent
  unaff_EDI[2] = 0;  // +0x02: count = 0
  unaff_EDI[3] = 0;  // +0x03: padding
  
  // Allocate bucket array
  if (iVar4 < 0x11) {
    _Dst = unaff_EDI + 8;  // Use inline storage for small tables (16 entries or less)
  }
  else {
    _Dst = (byte *)(*DAT_0119caf0)(iVar4 * 4, 0);  // Allocate dynamic memory (heap allocation function)
  }
  *(byte **)(unaff_EDI + 4) = _Dst;  // +0x04: pointer to bucket array
  
  // Clear bucket array
  _memset(_Dst, 0, (1 << (*unaff_EDI & 0x1f)) * 4);  // Initialize all buckets to NULL
  
  return;
}