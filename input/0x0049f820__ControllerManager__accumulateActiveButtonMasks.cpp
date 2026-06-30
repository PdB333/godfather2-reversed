// FUNC_NAME: ControllerManager::accumulateActiveButtonMasks
byte __fastcall ControllerManager::accumulateActiveButtonMasks(int /*unused*/, ControllerManager* pManager)
{
    // Offsets on pManager:
    // +0x8C : pointer to array of Controller pointers (Controller**)
    // +0x90 : number of controllers (int)
    Controller** ppController = *(Controller***)((char*)pManager + 0x8C);
    int numControllers = *(int*)((char*)pManager + 0x90);

    byte combinedMask = 0;

    if (numControllers > 0)
    {
        Controller** ppEnd = ppController + numControllers;
        do
        {
            Controller* pController = *ppController;

            // Offsets on pController:
            // +0xB2 : active flags (byte, bit0 = active)
            // +0xA0 : pointer to state structure (State*)
            if ( (*(byte*)((char*)pController + 0xB2) & 1) != 0 )
            {
                // State structure offset +0x2C : button mask byte
                byte* pButtonMask = *(byte**)((char*)pController + 0xA0);
                combinedMask |= *(byte*)(pButtonMask + 0x2C);
            }

            ppController++;
        } while (ppController != ppEnd);
    }

    return combinedMask;
}