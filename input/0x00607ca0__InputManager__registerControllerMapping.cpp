// FUNC_NAME: InputManager::registerControllerMapping
void InputManager::registerControllerMapping(uint controllerId, uint actionId, byte priority)
{
    int index;
    uint i;
    byte* priorityArray;
    uint local_4;
    
    local_4 = CONCAT31(local_4._1_3_, priority);
    if (priority != 0) {
        if (priority == 0xff) {
            // Priority 0xFF means "always add at end" (like a default mapping)
            if (DAT_012224a8 < 0x20) {
                index = DAT_012224a8 * 0xc;
                // Store controllerId and actionId as a 64-bit pair
                *(ulonglong *)(&DAT_01222328 + DAT_012224a8 * 3) = CONCAT44(actionId, controllerId);
                *(undefined4 *)(&DAT_01222330 + index) = local_4;
                DAT_012224a8 = DAT_012224a8 + 1;
                return;
            }
        }
        else {
            // Find insertion point based on priority (sorted ascending)
            i = 0;
            if (DAT_012224a8 != 0) {
                priorityArray = &DAT_01222330;
                do {
                    if (priority < *priorityArray) goto LAB_00607cc2;
                    i = i + 1;
                    priorityArray = priorityArray + 0xc;
                } while (i < DAT_012224a8);
            }
            // Insert at end if no higher priority found
            if (DAT_012224a8 < 0x20) {
                index = DAT_012224a8 * 0xc;
                *(ulonglong *)(&DAT_01222328 + DAT_012224a8 * 3) = CONCAT44(actionId, controllerId);
                *(undefined4 *)(&DAT_01222330 + index) = local_4;
                DAT_012224a8 = DAT_012224a8 + 1;
            }
        }
        return;
    }
LAB_00607cc2:
    // Priority 0 means "remove this mapping" - call removal function
    FUN_00609bf0();
    return;
}