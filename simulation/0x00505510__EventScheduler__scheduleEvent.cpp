// FUNC_NAME: EventScheduler::scheduleEvent
void EventScheduler::scheduleEvent(uint eventType, undefined4 param2, undefined4 param3, undefined4 param4,
                                   undefined2 param5, undefined1 param6, undefined4 param7, undefined4 param8,
                                   undefined4 param9)
{
  undefined4 *eventData;
  uint allocParams[5];
  
  allocParams[1] = 2; // alignment
  allocParams[2] = 0x10; // size
  allocParams[3] = 0; // flags
  eventData = (undefined4 *)FUN_009c8ed0(0x2c, allocParams + 1); // allocate 0x2c bytes for event
  if (eventData == (undefined4 *)0x0) {
    eventData = (undefined4 *)0x0;
  }
  else {
    eventData[1] = param2; // +0x04: event parameter 2
    eventData[2] = param8; // +0x08: event parameter 8
    eventData[3] = param9; // +0x0c: event parameter 9
    eventData[6] = param4; // +0x18: event parameter 4
    *(undefined2 *)(eventData + 7) = param5; // +0x1c: short parameter
    *(undefined1 *)((int)eventData + 0x1e) = param6; // +0x1e: byte parameter
    eventData[4] = 0; // +0x10: initialize to 0
    *eventData = &PTR_FUN_00e37fd4; // +0x00: vtable pointer
    eventData[8] = param3; // +0x20: event parameter 3
    eventData[9] = param7; // +0x24: event parameter 7
    eventData[10] = 0; // +0x28: initialize to 0
  }
  allocParams[0] = eventType; // event type identifier
  FUN_00423cf0(allocParams, &eventData, eventType % *(uint *)(*(int *)(DAT_01223398 + 8) + 8)); // insert into event queue
  return;
}