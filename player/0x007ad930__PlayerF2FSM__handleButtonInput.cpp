// FUNC_NAME: PlayerF2FSM::handleButtonInput
// Function address: 0x007ad930
// Handles button input (1,2,3) in F2F (face-to-face) dialogue system
// Calls base handler for other button IDs

int __thiscall PlayerF2FSM::handleButtonInput(int this,
                                              int arg1,
                                              int arg2,
                                              int arg3,
                                              int buttonId,
                                              int arg5)
{
    int pData;        // this+0x58: pointer to internal state
    int result;        // from virtual call via this+0x78

    if (buttonId == 0x31) // Button '1'
    {
        playSound(0xb);            // Play confirmation sound
        pData = *(int *)(this + 0x58); // +0x58: m_pStateData
        *(char *)(pData + 0x612) = 0; // +0x612: m_bOption1Selected? clear flag
        *(char *)(pData + 0x610) = 0; // +0x610: m_bOptionProcessed? clear flag
        return 1;
    }

    if (buttonId != 0x32) // Not button '2'
    {
        if (buttonId != 0x33) // Not button '3'
        {
            // Delegate to base class handler (e.g., DialogTreeManager::handleInput)
            return baseHandleInput(arg1, arg2, arg3, buttonId, arg5);
        }

        // Button '3'
        stopSound(0xb);            // Stop confirmation sound
        stopSound(0xf);            // Stop cancel sound
        return 1;
    }

    // Button '2'
    pData = *(int *)(this + 0x58);
    // Call virtual function on object at this+0x78 (e.g., m_pPlayer or m_pDialog)
    // vtable offset 0x34 typically is something like "getCurrentResponseIndex"
    result = (**(int (__thiscall **)(int))(**(int **)(this + 0x78) + 0x34))();

    if (*(char *)(pData + 0x610) != 0) // If option 2 is selected/enabled
    {
        if ((*(int *)(result + 0xc) != 0) && (*(int *)(result + 0xc) != 0x48))
        {
            int responseIndex;
            if (*(int *)(result + 0xc) == 0)
                responseIndex = 0;
            else
                responseIndex = *(int *)(result + 0xc) - 0x48;

            // Lookup the response using a hash (maybe string ID)
            if (lookupResponseId(responseIndex, 0x55859efa) != 0)
            {
                playSound(0xe);         // Play error/additional sound
                setResponseAnimation(5, 0); // Trigger response animation (ID 5)
            }
        }
        // Clear the processing flag
        *(char *)(pData + 0x610) = 0;
    }
    return 1;
}