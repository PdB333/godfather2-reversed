// FUNC_NAME: SomeArrayClass::getElementAtIndex
undefined4 __thiscall FUN_0056e900(int this, uint param_2)
{
  undefined4 *resultBuffer; // in_EAX
  
  if (*(ushort *)(this + 10) <= param_2) {
    // Element exists at index param_2, copy it to the result buffer
    resultBuffer[0] = 0;
    resultBuffer[1] = 0;
    *(undefined1 *)((int)resultBuffer + 9) = 0;
    resultBuffer[2] = 1; // +0x08: valid flag
    *(undefined2 *)((int)resultBuffer + 10) = *(undefined2 *)(this + 10); // +0x0A: element size?
    resultBuffer[3] = *(undefined4 *)(this + 0xc); // +0x0C: element count
    _memcpy(resultBuffer + 4, (void *)(this + 0x10), *(int *)(this + 0xc) * 8); // +0x10: element data, each element 8 bytes
    return 1; // success
  }
  return 0; // index out of bounds
}