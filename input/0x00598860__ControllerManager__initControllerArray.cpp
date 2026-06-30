// FUNC_NAME: ControllerManager::initControllerArray
void __cdecl ControllerManager::initControllerArray(void)
{
    // Array of 16 controller structures at 0x0119a9d0, each 0x74 bytes
    undefined4 *pSlot = &g_controllerArray; // DAT_0119a9d0
    int slotCount = 16;
    do {
        ControllerSlot::construct(pSlot); // FUN_0059b560
        pSlot = (undefined4 *)((int)pSlot + 0x74); // +0x74 per slot
        slotCount--;
    } while (slotCount != 0);
}