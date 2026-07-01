// FUNC_NAME: EventManager::createEvent
void __thiscall EventManager::createEvent(undefined4 eventType, undefined8 param_3, undefined8 param_4, undefined8 param_5, undefined4 param_6)
{
  char cVar1;
  int iVar2;
  
  cVar1 = FUN_00481660();  // likely isEventSystemEnabled() or check game state
  if (cVar1 != '\0') {
    iVar2 = FUN_009c8e50(0x58);  // allocate memory of size 0x58 for event data
    if (iVar2 == 0) {
      iVar2 = 0;  // allocation failed
    }
    else {
      iVar2 = FUN_0079fa30(param_1);  // initialize the event object with eventType
    }
    // Set event data fields
    *(undefined8 *)(iVar2 + 0x3c) = param_3;  // +0x3C: eventData1 (uint64)
    *(undefined8 *)(iVar2 + 0x44) = param_4;  // +0x44: eventData2 (uint64)
    *(undefined4 *)(iVar2 + 0x38) = param_2;  // +0x38: eventFlags or subtype
    *(undefined8 *)(iVar2 + 0x4c) = param_5;  // +0x4C: eventData3 (uint64)
    *(undefined4 *)(iVar2 + 0x54) = param_6;  // +0x54: eventData4 (uint32)
    FUN_00481690(iVar2);  // likely queueEvent(iVar2) or dispatchEvent
  }
  return;
}