// FUNC_NAME: SlotManager::processSlot
// Address: 0x00625030
// Role: Checks if a slot is pending (bit 0 clear) and, if so, validates its resource ID then loads the resource if not already loaded.
// Structure fields: +0x00 flags (byte), +0x04 resourceId (int)
void __fastcall SlotManager::processSlot(byte* slot)
{
    if ((slot[0] & 1) == 0) {
        int resourceId = *(int*)(slot + 4);
        char isLoaded = SlotManager::isResourceLoaded(resourceId); // FUN_006250e0
        if (isLoaded == 0) {
            SlotManager::loadResource(resourceId); // FUN_00624f30
        }
    }
}