// FUNC_NAME: Player::updateSomething
undefined4 __fastcall Player::updateSomething(int thisPtr)
{
  char cVar1;
  
  cVar1 = FUN_009c7920(); // Likely some global condition check
  if (cVar1 == '\0') {
    *(undefined4 *)(thisPtr + 0x60) = 0; // +0x60: some state field
    if ((DAT_01130590 & 1) == 0) {
      FUN_005c0d50(thisPtr + 0x14, &LAB_00931e00, 0); // +0x14: some sub-object, register callback
      DAT_01130590 = DAT_01130590 | 1; // Set global flag
    }
    return 1;
  }
  cVar1 = FUN_00930fc0(DAT_00d942ec); // Check some condition on global data
  if ((cVar1 != '\0') && (*(uint *)(thisPtr + 0x68) < DAT_01205210)) { // +0x68: some counter, compare to global max
    (**(code **)(*DAT_01129924 + 4))(); // Call a function pointer from a global vtable-like structure
  }
  return 0;
}