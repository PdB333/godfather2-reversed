// FUNC_NAME: SomeAnimationStateMachine::updateState
char __fastcall SomeAnimationStateMachine::updateState(int thisPtr)
{
  char result;
  char isEnabled;

  isEnabled = '\0';
  result = FUN_00911f40(0); // Likely check if system is active/initialized
  if (result == '\0') {
    return '\0';
  }
  switch(*(undefined4 *)(thisPtr + 8)) { // +0x8: current state ID
  case 0:
    if (*(char *)(DAT_01129c4c + 0x140) == '\0') { // Check some global flag at offset 0x140
      return '\0';
    }
    FUN_00976b20(*(undefined4 *)(thisPtr + 0x20), 0); // +0x20: some pointer/object, call with param 0
    FUN_0093e520(thisPtr, 0); // Transition to state 0
    return '\x01';
  default:
    goto switchD_0093e747_caseD_1;
  case 3:
    FUN_00976c10(); // Some cleanup or tick function
    FUN_0093e520(thisPtr, 0); // Transition to state 0
    return '\x01';
  case 4:
    FUN_00976b20(*(undefined4 *)(thisPtr + 0x20), 1); // Call with param 1
    FUN_0093e520(thisPtr, 0);
    return '\x01';
  case 5:
    isEnabled = FUN_00980020(*(undefined4 *)(thisPtr + 0x24)); // +0x24: another object, check condition
    break;
  case 6:
    isEnabled = FUN_00980c90(*(undefined4 *)(thisPtr + 0x24)); // Different condition check
  }
  if (isEnabled != '\0') {
    FUN_0093e520(thisPtr, 0); // Transition to state 0 if condition met
  }
switchD_0093e747_caseD_1:
  return isEnabled;
}