// FUNC_NAME: DonControlManager::checkAndPlaySound
void __fastcall DonControlManager::checkAndPlaySound(DonControlManager* this)
{
    int state = *(int*)(*(int*)((uintptr_t)this + 0x5c) + 0x898);
    if (state != 0 && state != 0x48) {
        // Get current don control state/gadget id
        undefined4 gadgetId = getCurrentDonControlState();
        // Play the corresponding sound (e.g., UI feedback, VO)
        playDonControlSound(gadgetId);
    }
}