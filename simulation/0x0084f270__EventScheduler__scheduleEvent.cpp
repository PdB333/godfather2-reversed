// FUNC_NAME: EventScheduler::scheduleEvent
void EventScheduler::scheduleEvent(undefined4 param_1, int param_2, undefined8 *param_3, undefined4 param_4,
                 undefined4 param_5, undefined4 param_6, undefined4 param_7, undefined4 param_8)
{
  int *piVar1;
  undefined4 *puVar2;
  
  // Call base event setup function
  FUN_0084f140(param_1,param_4,param_5,param_6,param_7,param_8);
  
  // Allocate 0x24 bytes for event data
  puVar2 = (undefined4 *)FUN_009c8e50(0x24);
  if (puVar2 == (undefined4 *)0x0) {
    puVar2 = (undefined4 *)0x0;
  }
  else {
    // Initialize event data structure
    *puVar2 = &PTR_FUN_00d5dbbc;  // vtable pointer
    puVar2[1] = 0xffffffff;       // +0x04: event ID (invalid)
    puVar2[2] = 0;                // +0x08: next pointer
    puVar2[3] = 0;                // +0x0C: prev pointer
    *(undefined1 *)(puVar2 + 7) = 0; // +0x1C: flag byte
    puVar2[6] = 0;                // +0x18: data
    puVar2[5] = 0;                // +0x14: data
    puVar2[4] = 0;                // +0x10: data
    puVar2[8] = DAT_01205228;     // +0x20: some global data
  }
  
  // Set flag to 1 (active)
  *(undefined1 *)(puVar2 + 7) = 1;
  
  // Copy event data from param_3 (8 bytes + 4 bytes)
  *(undefined8 *)(puVar2 + 4) = *param_3;  // +0x10: copy first 8 bytes
  puVar2[6] = *(undefined4 *)(param_3 + 1); // +0x18: copy next 4 bytes
  
  // Set event ID to a specific value (0x1970c04)
  puVar2[1] = 0x1970c04;
  
  // Handle linked list insertion
  piVar1 = puVar2 + 2;  // +0x08: next pointer
  if (param_2 == 0) {
    param_2 = 0;
  }
  else {
    param_2 = param_2 + 0x48;  // Offset into some structure
  }
  
  // Insert into linked list if different
  if (*piVar1 != param_2) {
    if (*piVar1 != 0) {
      FUN_004daf90(piVar1);  // Remove from list
    }
    *piVar1 = param_2;
    if (param_2 != 0) {
      puVar2[3] = *(undefined4 *)(param_2 + 4);  // +0x0C: set prev pointer
      *(int **)(param_2 + 4) = piVar1;           // Update list head
    }
  }
  
  // Post event to the event system
  FUN_00440590(&DAT_0112ad8c, 0, _DAT_00e53fe4, puVar2, 0);
  return;
}