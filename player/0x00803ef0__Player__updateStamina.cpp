// FUNC_NAME: Player::updateStamina
// Address: 0x00803ef0
// Purpose: Update player stamina drain based on activity state and modifiers.

// External function declarations (assumed to be in same module)
void __thiscall FUN_008c98a0(int param_2);   // Possibly applies stamina drain effect
void __thiscall FUN_00800f00(int param_2, int param_4); // Possibly early return / skip

// Global minimum stamina threshold (e.g., 0.0f)
extern float s_minStaminaThreshold;

void __thiscall Player::updateStamina(int this, int contextObj, float deltaStamina, int extraParam)
{
    // +0x79c : float m_stamina (current stamina value)
    // +0x7a0 : uint m_activityType (index into activity drain data, 0-7)
    // +0x75c : int[8] m_activityDrainData (array of pointers or flags for each activity)
    // +0x7a4 : int m_drainFlag1 (e.g., bonus/ability flag)
    // +0x7a8 : int m_drainFlag2 (e.g., another modifier flag)
    // +0x81c : uint m_stateFlags (bitfield; bit9 = 0x200, bit11 = 0x800)

    float stamina = *(float *)(this + 0x79c);
    if (stamina <= s_minStaminaThreshold) {
        // Already at minimum, skip drain
        FUN_00800f00(contextObj, extraParam);
        return;
    }

    uint activity = *(uint *)(this + 0x7a0);
    int* drainData = (int*)(this + 0x75c);
    int drainValue = drainData[activity]; // each entry is 8 bytes? but we read as 4-byte int at offset activity*8 because data structure has padding

    // Check if activity is out of valid range ( > 7 ) or if the drain data is null
    bool invalidActivity = (activity > 7);
    bool nullDrain = (drainValue == 0);
    if ((invalidActivity || nullDrain) &&
        (*(int *)(this + 0x7a4) == 0 || ((*(uint *)(this + 0x81c) >> 0xb) & 1) == 0) &&
        (*(int *)(this + 0x7a8) == 0 || ((*(uint *)(this + 0x81c) >> 9) & 1) == 0)) {
        // Conditions for skipping drain met
        FUN_00800f00(contextObj, extraParam);
        return;
    }

    // Perform the drain
    FUN_008c98a0(contextObj);
    *(float *)(this + 0x79c) = stamina - deltaStamina;
}