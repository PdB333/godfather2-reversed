// FUNC_NAME: Container::isValidIndex
uint32_t Container::isValidIndex(int32_t index)

{
  int *piVar1;
  
  if (index < 1) {
    piVar1 = (int *)getFirstElement();
  }
  else {
    // +0x0C: elementDataPtr, +0x08: size/count
    piVar1 = (int *)(*(int *)(this + 0xc) + -8 + index * 8);
    if (*(int **)(this + 8) <= piVar1) {
      return 0;
    }
  }
  // Each element is 8 bytes: first word is some type/flag, second word is data
  // Returns 1 if element is valid (non-null type and not a special empty marker)
  if (((piVar1 != (int *)0x0) && (*piVar1 != 0)) && ((*piVar1 != 1 || (piVar1[1] != 0)))) {
    return 1;
  }
  return 0;
}