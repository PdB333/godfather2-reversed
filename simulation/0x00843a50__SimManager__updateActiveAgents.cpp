// FUNC_NAME: SimManager::updateActiveAgents
void __thiscall SimManager::updateActiveAgents(int this)
{
  int *arrayElement;
  int iValue;
  byte bFlags;
  code *vtableFunc;
  int *currentBase;
  int local_c;
  int local_8;
  byte local_4;

  // Check if the "active" flag (bit 4) is set at offset 0x4c
  if ((*(byte *)(this + 0x4c) & 0x10) != 0) {
    // Set global flag indicating update is in progress
    DAT_0112dcc0 = 1;
    local_c = DAT_0112dcd8;   // Global timer or state
    local_8 = 0;
    local_4 = 0;
    // Call scope/setup function (likely push/pop of some context)
    FUN_00408a00(&local_c, 0);

    // Choose render/debug path based on global flag
    if (DAT_0112dcc0 == 0) {
      FUN_00789480();   // Debug/normal path
    } else {
      FUN_00789450();   // Alternative path
    }

    // Get pointer to array of agent entries at offset +0x64 (100 decimal)
    currentBase = *(int **)(this + 100);
    // Number of entries is stored at +0x68 (off by 8? Actually 0x68 = 104)
    int entryCount = *(int *)(this + 0x68);
    // Each entry consists of 2 ints? So end = currentBase + entryCount * 2
    int *endArray = currentBase + entryCount * 2;

    // Iterate over the array (step by 2 ints)
    while (currentBase != endArray) {
      iValue = *currentBase;   // First int: pointer to agent data
      if (iValue != 0) {
        // The actual agent structure is at offset -0x48 from the entry pointer
        arrayElement = (int *)(iValue - 0x48);
        if (arrayElement != (int *)0x0) {
          // Read flags at offset +0x116 (byte from word)
          bFlags = (byte)*(undefined2 *)(iValue + 0x116);
          // Check bit 1 (0x02) – if clear, call vtable func at +0xCC
          if ((bFlags >> 1 & 1) == 0) {
            vtableFunc = *(code **)(*arrayElement + 0xcc);
          } else {
            // Check bit 5 (0x20) – if clear, call vtable func at +0xD4
            if ((~(bFlags >> 5) & 1) == 0) {
              vtableFunc = *(code **)(*arrayElement + 0xd4);
            } else {
              goto skipCall;
            }
          }
          // Call the selected vtable function
          (*vtableFunc)();
skipCall:
          // After vtable call, if bit 1 is still clear, call cleanup/update function on arrayElement
          if ((*(byte *)(iValue + 0x116) >> 1 & 1) == 0) {
            FUN_004e0630(arrayElement);
          }
        }
      }
      // Advance to next entry (2 ints)
      currentBase += 2;
    }

    // Finalize update: call post-update, register callback, and process pending events
    FUN_00843260();                       // Post-update aggregation
    FUN_004464d0(&LAB_00843810);          // Set up next-frame callback
    FUN_0053f8a0();                       // Flush or process remaining work

    // Clear the active flag
    *(uint *)(this + 0x4c) &= 0xffffffef;
  }
  return;
}