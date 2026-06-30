// FUNC_NAME: ControllerManager::reconcileSlotMappings
void __thiscall ControllerManager::reconcileSlotMappings(void)
{
  // Global slot group array: 4 groups, each 0x180 bytes, total 16 slots
  // g_slotGroups[4] at DAT_01206d1c
  // g_currentThreadId = TEB->something (offset 0x2c -> +0x34)
  int currentThreadId = *(int *)(*(int *)(*(int *)(__readfsdword(0x2c)) + 0x34));
  int newPrimaryId = DAT_012058a4;  // +0x?? global new primary ID
  int oldPrimaryId = DAT_0120589c;  // +0x?? global old primary ID

  // Process each of the 4 slot groups
  for (int groupIdx = 0; groupIdx < 4; groupIdx++) {
    int* groupBase = &DAT_01206d1c + groupIdx * 0x60; // Each group is 0x60 ints (0x180 bytes)
    int slotOffset = groupIdx * 4; // Base slot index within group (0,4,8,12)

    // Sub-slot 0: flags at g_slotActiveFlags[0][slotOffset]
    if (g_slotActiveFlags0[slotOffset] != '\0' && groupBase[4] == currentThreadId) {
      if (groupBase[0] == oldPrimaryId) {
        groupBase[0] = newPrimaryId;
      } else if (groupBase[0] == newPrimaryId) {
        groupBase[0] = oldPrimaryId;
      }
    }

    // Sub-slot 1: flags at g_slotActiveFlags[1][slotOffset]
    if (g_slotActiveFlags1[slotOffset] != '\0' && groupBase[0x64] == currentThreadId) {
      if (groupBase[0x60] == oldPrimaryId) {
        groupBase[0x60] = newPrimaryId;
      } else if (groupBase[0x60] == newPrimaryId) {
        groupBase[0x60] = oldPrimaryId;
      }
    }

    // Sub-slot 2: flags at g_slotActiveFlags[2][slotOffset]
    if (g_slotActiveFlags2[slotOffset] != '\0' && groupBase[0xC4] == currentThreadId) {
      if (groupBase[0xC0] == oldPrimaryId) {
        groupBase[0xC0] = newPrimaryId;
      } else if (groupBase[0xC0] == newPrimaryId) {
        groupBase[0xC0] = oldPrimaryId;
      }
    }

    // Sub-slot 3: flags at g_slotActiveFlags[3][slotOffset]
    if (g_slotActiveFlags3[slotOffset] != '\0' && groupBase[0x124] == currentThreadId) {
      if (groupBase[0x120] == oldPrimaryId) {
        groupBase[0x120] = newPrimaryId;
      } else if (groupBase[0x120] == newPrimaryId) {
        groupBase[0x120] = oldPrimaryId;
      }
    }
  }

  // If the current thread ID is zero, update the virtual function pointer
  if (currentThreadId == 0) {
    // Vtable patch at g_someObject + 0x14 (likely InputManager)
    int* vtablePtr = (int*)(DAT_01206880 + 0x14);
    **(int**)vtablePtr = &PTR_LAB_0110b654; // Some default vtable
    *vtablePtr = *vtablePtr + 4; // Advance to next method?
  }
}