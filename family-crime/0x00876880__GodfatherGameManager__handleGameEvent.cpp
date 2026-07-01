// FUNC_NAME: GodfatherGameManager::handleGameEvent
void __fastcall GodfatherGameManager::handleGameEvent(int thisPtr)
{
  int eventId;
  undefined4 local_30;
  undefined ***local_2c;
  undefined1 local_28;
  undefined **local_24;
  undefined4 local_20;
  int local_1c;
  undefined4 local_18;
  undefined8 local_14;
  undefined4 local_c;
  undefined1 local_8;
  undefined4 local_4;
  
  eventId = FUN_00471610(); // likely getCurrentEventId or similar
  local_24 = &PTR_FUN_00d5dbbc; // vtable or function pointer table
  local_20 = 0x6e39452; // some event type or hash
  if (thisPtr == 0) {
    local_1c = 0;
  }
  else {
    local_1c = thisPtr + 0x48; // +0x48: some member offset
  }
  local_18 = 0;
  if (local_1c != 0) {
    local_18 = *(undefined4 *)(local_1c + 4); // +0x04: next pointer in linked list
    *(int **)(local_1c + 4) = &local_1c; // circular linked list setup
  }
  local_4 = DAT_01205228; // global variable
  local_8 = 1;
  local_14 = *(undefined8 *)(eventId + 0x30); // +0x30: some data from event
  local_c = *(undefined4 *)(eventId + 0x38); // +0x38: more event data
  local_2c = &local_24;
  local_30 = DAT_0112ad8c; // another global
  local_28 = 0;
  FUN_00408a00(&local_30,0); // likely some initialization or processing
  if (local_1c != 0) {
    FUN_004daf90(&local_1c); // cleanup or free
  }
  return;
}