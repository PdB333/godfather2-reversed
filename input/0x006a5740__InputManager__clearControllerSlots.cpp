// FUNC_NAME: InputManager::clearControllerSlots
void __fastcall InputManager::clearControllerSlots(int this)
{
  int i;
  int *slotPtr;
  
  slotPtr = (int *)(this + 0x24);
  i = 0x20;
  do {
    slotPtr[-1] = 0; // +0x20: controller slot active flag
    if (*slotPtr != 0) {
      FUN_004daf90(slotPtr); // likely free/delete controller data
      *slotPtr = 0; // +0x24: controller data pointer
    }
    slotPtr[7] = 0;  // +0x4C: some field
    slotPtr[8] = 0;  // +0x50: some field
    slotPtr[5] = 0;  // +0x44: some field
    slotPtr[2] = 0;  // +0x38: some field
    slotPtr[3] = 0;  // +0x3C: some field
    slotPtr[4] = 0;  // +0x40: some field
    slotPtr = slotPtr + 10; // each slot is 0x28 bytes (10 ints)
    i = i + -1;
  } while (i != 0);
  
  // Clear additional fields after the 32 slots
  slotPtr = (int *)(this + 0x524);
  *(undefined4 *)(this + 0x520) = 0; // +0x520: some flag
  if (*slotPtr != 0) {
    FUN_004daf90(slotPtr);
    *slotPtr = 0; // +0x524: another pointer
  }
  *(undefined4 *)(this + 0x530) = 0; // +0x530: field
  *(undefined4 *)(this + 0x52c) = 0; // +0x52c: field
  *(undefined4 *)(this + 0x534) = 0; // +0x534: field
  return;
}