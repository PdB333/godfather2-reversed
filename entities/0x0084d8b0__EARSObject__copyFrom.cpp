// FUNC_NAME: EARSObject::copyFrom
int __thiscall EARSObject::copyFrom(int thisPtr, int sourcePtr)
{
  int iVar1;
  
  // Copy first pointer field with special handling for null/0x48 sentinel
  iVar1 = *(int *)(sourcePtr + 4);
  if ((iVar1 == 0) || (iVar1 == 0x48)) {
    iVar1 = 0;
  }
  else {
    iVar1 = iVar1 + 0x10;
  }
  FUN_004a8ec0(iVar1);  // Likely reference counting or pointer adjustment
  
  // Copy second pointer field with same sentinel handling
  iVar1 = *(int *)(sourcePtr + 0xc);
  if ((iVar1 == 0) || (iVar1 == 0x48)) {
    iVar1 = 0;
  }
  else {
    iVar1 = iVar1 + 0x10;
  }
  FUN_004a8ec0(iVar1);  // Same adjustment function
  
  // Copy data fields from source to destination
  // +0x28 to +0x40: 8 consecutive 4-byte fields (likely matrix/transform data)
  *(undefined4 *)(thisPtr + 0x28) = *(undefined4 *)(sourcePtr + 0x2c);
  *(undefined4 *)(thisPtr + 0x2c) = *(undefined4 *)(sourcePtr + 0x30);
  *(undefined4 *)(thisPtr + 0x30) = *(undefined4 *)(sourcePtr + 0x34);
  *(undefined4 *)(thisPtr + 0x34) = *(undefined4 *)(sourcePtr + 0x38);
  *(undefined4 *)(thisPtr + 0x38) = *(undefined4 *)(sourcePtr + 0x3c);
  *(undefined4 *)(thisPtr + 0x3c) = *(undefined4 *)(sourcePtr + 0x40);
  *(undefined4 *)(thisPtr + 0x40) = *(undefined4 *)(sourcePtr + 0x44);
  
  // +0x10: 8-byte field (likely double or two floats)
  *(undefined8 *)(thisPtr + 0x10) = *(undefined8 *)(sourcePtr + 0x14);
  
  // +0x18: 4-byte field
  *(undefined4 *)(thisPtr + 0x18) = *(undefined4 *)(sourcePtr + 0x1c);
  
  // +0x1c: 8-byte field
  *(undefined8 *)(thisPtr + 0x1c) = *(undefined8 *)(sourcePtr + 0x20);
  
  // +0x24: 4-byte field
  *(undefined4 *)(thisPtr + 0x24) = *(undefined4 *)(sourcePtr + 0x28);
  
  return thisPtr;
}