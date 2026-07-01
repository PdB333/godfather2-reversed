// FUNC_NAME: PlayerSM::handleInputAction
void __thiscall PlayerSM::handleInputAction(int thisPtr, int actionType, undefined4 param3)
{
  undefined4 *newEvent;
  int eventId;
  
  // Only handle specific action types: 0x1d, 0x1e, 0x20
  if (((actionType != 0x1d) && (actionType != 0x1e)) && (actionType != 0x20)) {
    return;
  }
  
  // Allocate and construct a new event object (0x14 bytes)
  newEvent = (undefined4 *)FUN_009c8e80(0x14);
  if (newEvent == (undefined4 *)0x0) {
    newEvent = (undefined4 *)0x0;
  }
  else {
    _vector_constructor_iterator_(newEvent,0x14,1,(_func_void_ptr_void_ptr *)&LAB_00907620);
  }
  
  // Set event data:
  // +0x08: action data pointer (from action table at this+4, indexed by actionType)
  newEvent[2] = *(undefined4 *)(*(int *)(thisPtr + 4) + actionType * 4);
  // +0x10: some flag (0)
  newEvent[4] = 0;
  // +0x00: event type (3)
  *newEvent = 3;
  // +0x0C: param3
  newEvent[3] = param3;
  
  // Send event to state machine
  FUN_00566000(newEvent,1,&LAB_00907660,0);
  
  // Determine secondary event based on action type and current state
  if (actionType == 0x1d) {
    switch(*(undefined4 *)(thisPtr + 8)) {  // current state at +0x08
    case 0:
      eventId = 0x21;
      break;
    case 1:
      eventId = 0x24;
      break;
    case 2:
      eventId = 0x27;
      break;
    case 3:
      eventId = 0x2a;
      break;
    default:
      goto switchD_00907b58_default;
    }
  }
  else if (actionType == 0x1e) {
    switch(*(undefined4 *)(thisPtr + 8)) {
    case 0:
      eventId = 0x22;
      break;
    case 1:
      eventId = 0x25;
      break;
    case 2:
      eventId = 0x28;
      break;
    case 3:
      eventId = 0x2b;
      break;
    default:
      goto switchD_00907b58_default;
    }
  }
  else {
    if (actionType != 0x20) {
      return;
    }
    switch(*(undefined4 *)(thisPtr + 8)) {
    case 0:
      eventId = 0x23;
      break;
    case 1:
      eventId = 0x26;
      break;
    case 2:
      eventId = 0x29;
      break;
    case 3:
      eventId = 0x2c;
      break;
    default:
      goto switchD_00907b58_default;
    }
  }
  
  // Allocate and send secondary event
  newEvent = (undefined4 *)FUN_009c8e80(0x14);
  if (newEvent == (undefined4 *)0x0) {
    newEvent = (undefined4 *)0x0;
  }
  else {
    _vector_constructor_iterator_(newEvent,0x14,1,(_func_void_ptr_void_ptr *)&LAB_00907620);
  }
  
  newEvent[2] = *(undefined4 *)(*(int *)(thisPtr + 4) + eventId * 4);
  newEvent[4] = 0;
  *newEvent = 3;
  newEvent[3] = param3;
  FUN_00566000(newEvent,1,&LAB_00907660,0);
  
switchD_00907b58_default:
  return;
}