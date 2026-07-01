// FUNC_NAME: PlayerActionableInfo::canActivateDonAbility
// Address: 0x007ac3a0
// This function checks whether a don ability (e.g., ordering a hit or shakedown) can be activated.
// It verifies the player's controller input and a numeric threshold from player data.

// Forward declarations for external functions
extern void* __fastcall getInputDevice(int index); // 0x00798f50
extern char __fastcall inputDeviceIsValid(void* device); // 0x0079e970
extern void __fastcall inputDeviceUpdate(void* device, int arg1, int arg2); // 0x0079eb40
extern char __fastcall inputDeviceIsActionActive(void* device, bool actionType, int modifier); // 0x007ab9a0
extern void __fastcall playSound(int soundId, int arg2); // 0x0079f100

bool __thiscall PlayerActionableInfo::canActivateDonAbility()
{
    bool bResult = false;
    
    // Get input device for player 1 ( index 1 )
    void* pController = getInputDevice(1);
    if (inputDeviceIsValid(pController) != '\0')
    {
        // PlayerData pointer is stored at offset 0x58 from this.
        // This should point to the Player object or a large component.
        int* pPlayerData = *(int**)(this + 0x58);
        // Flags at offset 0x8e0 (bit1 determines action type)
        uint flags = *(uint*)(pPlayerData + 0x8e0);
        uint shiftedFlags = flags >> 1;
        bool bActionType = (shiftedFlags & 1) != 0; // true = action type A (sound 6), false = action type B (sound 7)
        
        // Poll controller
        inputDeviceUpdate(pController, 0, 0);
        
        // Read threshold value based on action type
        float fValue;
        if (bActionType)
            fValue = *(float*)(pPlayerData + 0x201c); // offset for action type A
        else
            fValue = *(float*)(pPlayerData + 0x2018); // offset for action type B
        
        // The threshold is unknown; possibly a member of this class or a global.
        // In the decompiled code, the comparison uses a float10 extraout_ST0.
        // We assume threshold is stored somewhere; here we use a placeholder of 0.0f.
        float threshold = 0.0f; // TODO: retrieve actual threshold
        
        // Check if value is below threshold AND the action input is active (opposite action type)
        char cActionInput = inputDeviceIsActionActive(pController, !bActionType, 0);
        if (fValue < threshold || cActionInput == '\0')
        {
            return 0;
        }
        
        // Action valid; play sound based on action type.
        if (bActionType)
            playSound(6, 0);
        else
            playSound(7, 0);
        
        bResult = true;
    }
    return bResult;
}