// FUNC_NAME: PlayerActionHandler::handleAction
// Address: 0x00766fa0
// This function appears to handle player input actions (action IDs 10-18).
// It is a member function of a class (likely PlayerActionHandler) with the following known offsets:
// +0x50: m_pPlayerObject (pointer to a player object struct)
// +0x54: m_selectedItem (int, possibly item/entity ID, 0x48 = invalid)
// +0x60: m_actionFlags (byte, bits: 1=used, 2=used, 8=pending)
// The player object has fields at +0x1c78 (state flag), +0x8e0 (bitfield for combat state)

#include <cstdint>

bool __thiscall PlayerActionHandler::handleAction(
    int param_2,
    int param_3,
    int param_4,
    int actionId,       // param_5: action index (10-18 handled, others forwarded to base)
    int param_6
)
{
    bool result = true; // local_11, default to true
    
    switch (actionId - 10)
    {
    case 0: // actionId == 10
    {
        // Check if player object exists and is not in a specific state (0x48)
        if ( (*(int*)(m_pPlayerObject + 0x1c78) != 0) && 
             (*(int*)(m_pPlayerObject + 0x1c78) != 0x48) &&
             (m_selectedItem != 0) && 
             (m_selectedItem != 0x48) &&
             (isActionAllowed(8) == false) )
        {
            lockActionInput(8);
            playSound(0x22, 0);       // Play sound ID 34
            stopSound();               // Stop current sound?
            m_actionFlags |= 1;        // Set flag bit 0
            if ((m_actionFlags & 8) == 0)
            {
                int canAct = canPerformAction(m_pPlayerObject); // Check if object can act
                if (canAct != 0)
                {
                    setTargetMode(1);    // Possibly enter targeting or attack mode
                }
                m_actionFlags |= 8;    // Set pending action flag
                result = true;
            }
        }
        break;
    }
    case 1: // actionId == 11
    {
        if ( (*(int*)(m_pPlayerObject + 0x1c78) != 0) && 
             (*(int*)(m_pPlayerObject + 0x1c78) != 0x48) &&
             (m_selectedItem != 0) )
        {
            int itemId = m_selectedItem - 0x48;
            if (itemId != 0)
            {
                useItem(itemId, 1);   // Use item with ID
                m_actionFlags |= 2;    // Set flag bit 1
                result = true;
            }
        }
        break;
    }
    case 2: // actionId == 12
        resetState(0);                // Reset some state
        result = true;
        break;
    case 3: // actionId == 13
    {
        uint32_t effectHash;
        uint32_t bitfield = *(uint32_t*)(m_pPlayerObject + 0x8e0);
        if ((bitfield >> 10 & 1) == 0)
        {
            effectHash = 0xa02d23ec;   // Hash for a specific effect/animation
        }
        else
        {
            int inCombat = isInCombat();
            if (inCombat == 0)
                effectHash = getContextAction();  // Normal context action
            else
                effectHash = 0x1193fb8b;          // Combat-specific effect
        }
        // Call a virtual function (vtable+0x2c) to play the effect
        (this->vtable->playEffect)(effectHash, 1, 1, 0, 1.0f, 1.0f);
        result = false; // uVar4 = 0
        break;
    }
    case 4: // actionId == 14
    {
        if ( (m_selectedItem != 0) && (m_selectedItem != 0x48) &&
             (isActionAllowed(8) == false) )
        {
            cancelCurrentAction();    // Cancel active action
            result = true;
        }
        break;
    }
    case 5: // actionId == 15
        // No operation (break)
        break;
    case 6: // actionId == 16
    {
        if ( (m_selectedItem != 0) && (m_selectedItem != 0x48) )
        {
            int* playerMgr = getPlayerManager();   // Returns a global manager pointer
            if ( (playerMgr != 0) && ((*(uint32_t*)(playerMgr + 0xc88) | 8) != *(uint32_t*)(playerMgr + 0xc88)) )
            {
                // vtable at +0x58, method offset 0x28
                (*(void (__thiscall**)(int))(*(int*)(playerMgr + 0x58) + 0x28))(0x10);
                *(uint32_t*)(playerMgr + 0xc88) |= 8;   // Set bit 3 (0x8)
                result = ???; // unaff_ESI >> 0x18 – likely a bool from something else, but we treat as true
                // Note: unaff_ESI is not defined; probably the previous return value from getPlayerManager or similar
                // We'll assume true for safety
            }
        }
        break;
    }
    case 7: // actionId == 17
    {
        if ( (m_selectedItem != 0) && (m_selectedItem != 0x48) &&
             (isActionAllowed(8) == true) )
        {
            playSoundEvent(0x4c223f, 0);   // Play a specific sound event hash
            if (m_selectedItem != 0)
            {
                useGenericItem(m_selectedItem - 0x48, 0xa6593d03); // Use item with target hash
                result = true;
            }
            else
            {
                useGenericItem(0, 0xa6593d03);
                result = true;
            }
        }
        break;
    }
    case 8: // actionId == 18
    {
        uint32_t cameraHash = getCameraType(0, 0);   // Get current camera type?
        setCameraMode(0, 0, cameraHash, 0);          // Set camera mode
        resetCamera();                               // Reset camera
        result = true;
        break;
    }
    default:
        result = (bool)baseClassHandler(param_2, param_3, param_4, actionId, param_6);
        break;
    }
    
    return result;
}

/* Helper function declarations (not defined here, but likely exist in the game) */
extern bool isActionAllowed(int lockSlot);
extern void lockActionInput(int lockSlot);
extern void playSound(uint32_t soundId, int unknown);
extern void stopSound(void);
extern int canPerformAction(void* playerObj);
extern void setTargetMode(int mode);
extern void useItem(int itemId, int count);
extern void resetState(int value);
extern int isInCombat(void);
extern uint32_t getContextAction(void);
extern void cancelCurrentAction(void);
extern int* getPlayerManager(void);
extern void playSoundEvent(uint32_t hash, int unknown);
extern void useGenericItem(int itemId, uint32_t targetHash);
extern uint32_t getCameraType(int a, int b);
extern void setCameraMode(int a, int b, uint32_t hash, int d);
extern void resetCamera(void);
extern bool baseClassHandler(int a, int b, int c, int actionId, int d);