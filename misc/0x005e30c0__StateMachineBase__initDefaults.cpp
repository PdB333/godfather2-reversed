// FUNC_NAME: StateMachineBase::initDefaults
void __fastcall StateMachineBase::initDefaults(int thisPtr)
{
  // Initialize state machine fields to default values
  *(int *)(thisPtr + 0x8) = 1;   // +0x08: enabledFlag? = true
  *(int *)(thisPtr + 0xc) = 0;   // +0x0c: currentState? = 0
  *(int *)(thisPtr + 0x10) = 0;  // +0x10: prevState? = 0
  *(char *)(thisPtr + 0x14) = 0; // +0x14: flags? = 0
  *(int *)(thisPtr + 0x18) = 1;  // +0x18: nextState? = 1 (maybe initial state)
  *(int *)(thisPtr + 0x1c) = 0;  // +0x1c: timer? = 0
  *(int *)(thisPtr + 0x20) = 0;  // +0x20: subTimer? = 0
  *(int *)(thisPtr + 0x18) = 1;  // redundant? already set above
  *(char *)(thisPtr + 0x24) = 0; // +0x24: byte flag
  *(int *)(thisPtr + 0x2c) = *s_global1; // +0x2c: some global default (DAT_00e2b1a4)
  *(int *)(thisPtr + 0x30) = *s_global2; // +0x30: another global (DAT_00e2b04c)
  *(int *)(thisPtr + 0x34) = *s_global3; // +0x34: third global (DAT_00e2b050)
  *(int *)(thisPtr + 0x3c) = 0;   // +0x3c: state change counter?
  *(char *)(thisPtr + 0x28) = 0;  // +0x28: bool flag
  *(char *)(thisPtr + 0x29) = 0;  // +0x29: another bool flag
  *(int *)(thisPtr + 0x38) = 0;   // +0x38: elapsed time?
  *(int *)(thisPtr + 0x40) = 0;   // +0x40: reserved
  *(int *)(thisPtr + 0x44) = 0;   // +0x44: extra data
  vtableInit(); // calls FUN_005e3130, likely sets up vtable pointer
}