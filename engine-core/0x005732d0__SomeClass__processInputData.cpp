// FUNC_NAME: SomeClass::processInputData
void FUN_005732d0(int thisPtr, int inputArray, uint count)
{
  int *piVar1;
  char *pcVar2;
  undefined4 *puVar3;
  char *pcVar4;
  undefined4 *puVar5;
  uint uVar6;
  undefined4 unaff_retaddr;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  uVar6 = 0;
  if (count != 0) {
    do {
      piVar1 = *(int **)(inputArray + uVar6 * 4);
      // Check if the entry is active (bit 5 of field +0x2C) and has version >= 2
      if (((piVar1[0xb] & 0x20U) == 0) || (*piVar1 < 2)) {
        pcVar4 = (char *)piVar1[4]; // +0x10 - primary data pointer
      }
      else {
        pcVar4 = (char *)piVar1[6]; // +0x18 - secondary data pointer
      }
      if (pcVar4 != (char *)0x0) {
        // Check for specific data header: first byte 0x04, second byte 0x02
        if ((*pcVar4 == '\x04') && (pcVar4[1] == '\x02')) {
          pcVar2 = (char *)**(undefined4 **)(pcVar4 + 8); // +0x08 - pointer to pointer
          pcVar4 = (char *)(*(undefined4 **)(pcVar4 + 8))[1]; // +0x0C - second pointer
          // Check for specific data pattern: first byte 0x0A, next two bytes zero, second pointer first byte 0x0B, float at +0x04 is 0.0
          if ((*pcVar2 == '\n') &&
             (((*(short *)(pcVar2 + 2) == 0 && (*pcVar4 == '\v')) && (*(float *)(pcVar4 + 4) == 0.0)
              ))) {
            // Clear the data pointer to indicate processed
            if (((piVar1[0xb] & 0x20U) == 0) || (*piVar1 < 2)) {
              piVar1[4] = 0; // +0x10
            }
            else {
              piVar1[6] = 0; // +0x18
            }
            goto LAB_00573355;
          }
        }
        // Mark that we have pending data to process
        *(undefined4 *)(thisPtr + 0x3c) = 1;
      }
LAB_00573355:
      uVar6 = uVar6 + 1;
    } while (uVar6 < count);
  }
  puVar3 = *(undefined4 **)(thisPtr + 0x2c); // +0x2C - some buffer/queue
  if (count != 0) {
    local_c = 0;
    local_8 = 0;
    local_4 = 0;
    // Allocate a new entry in the buffer
    puVar5 = (undefined4 *)(*(code *)**(undefined4 **)*puVar3)(0x10, &local_c);
    *puVar5 = unaff_retaddr; // Store return address
    puVar5[1] = count; // Store count
    *(undefined1 *)(puVar5 + 2) = 0; // Clear flag
    puVar5[3] = puVar3[5]; // +0x14 - link to next
    puVar3[3] = puVar3[3] + count; // +0x0C - increment total count
    puVar3[5] = puVar5; // +0x14 - update head
    *(undefined1 *)(puVar3 + 4) = 1; // +0x10 - set flag
  }
  return;
}