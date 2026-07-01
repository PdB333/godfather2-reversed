// FUNC_NAME: SomeClass::setStateFlags
void __fastcall SomeClass::setStateFlags(int thisPtr)
{
  switch(*(int *)(thisPtr + 0x14)) {  // +0x14: currentState
  case 8:
    *(uint *)(thisPtr + 0xf0) |= 1;  // +0xf0: stateFlags8
  case 7:
    *(uint *)(thisPtr + 0xcc) |= 1;  // +0xcc: stateFlags7
  case 5:
  case 6:
    *(uint *)(thisPtr + 0x84) |= 1;  // +0x84: stateFlags5_6
  case 4:
    *(uint *)(thisPtr + 0xa8) |= 1;  // +0xa8: stateFlags4
  case 3:
    *(uint *)(thisPtr + 0x60) |= 1;  // +0x60: stateFlags3
  case 2:
    *(uint *)(thisPtr + 0x3c) |= 1;  // +0x3c: stateFlags2
  case 1:
    *(uint *)(thisPtr + 0x18) |= 1;  // +0x18: stateFlags1
    return;
  default:
    return;
  }
}