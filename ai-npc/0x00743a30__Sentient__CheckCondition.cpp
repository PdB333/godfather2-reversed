// FUNC_NAME: Sentient::CheckCondition
// Address: 0x00743a30
// Role: Queries various boolean conditions about the entity based on a condition index.

class Sentient {
public:
    // Vtable call used in cases 3 and 4 (offset 0x1a8/4 = 0x6A)
    virtual float GetSomeAttribute() = 0;

    // Main condition check dispatcher
    bool CheckCondition(int conditionID, uint param2, uint param3, uint param5) {
        switch (conditionID - 10) { // conditionID ranges from 10 to 26
        case 0: // conditionID == 10
            if (m_targetPtr != nullptr)
                return m_targetPtr == reinterpret_cast<void*>(0x48);
            return true;

        case 1: // conditionID == 11
            return IsInVehicle(); // FUN_00743000

        case 2: // conditionID == 12
            return IsInCover();   // FUN_007430a0

        case 3: // conditionID == 13
            if (m_targetPtr != nullptr && m_targetPtr != reinterpret_cast<void*>(0x48)) {
                float val = GetSomeAttribute();
                if (DAT_00d5779c < val)
                    return true;
            }
            break;

        case 4: // conditionID == 14
            if (m_targetPtr != nullptr && m_targetPtr != reinterpret_cast<void*>(0x48)) {
                float val = GetSomeAttribute();
                if (val < DAT_00e445ac)
                    return true;
            }
            break;

        case 5: // conditionID == 15
            return m_health > DAT_00d5eee4; // equivalent to: if (m_health <= threshold) false; else true

        case 6: // conditionID == 16
            if (m_someInt == 0 && m_targetPtr != nullptr && m_targetPtr != reinterpret_cast<void*>(0x48)) {
                int objBase = reinterpret_cast<int>(m_targetPtr) - 0x48; // get base of object from pointer
                int currentMission = GetCurrentMission(); // FUN_007ff880
                if (objBase == currentMission && IsMissionActive(4)) // FUN_00690150(4)
                    return true;
            }
            break;

        case 7: // conditionID == 17
            return IsDead(); // FUN_00742b40

        case 8: // conditionID == 18
            if (m_someInt == 0 && (m_flags & 0x2) != 0)
                return true;
            break;

        case 9: // conditionID == 19
            return (m_flags & 0x4) == 0; // bit 2 NOT set

        case 10: // conditionID == 20
            return (m_flags & 0x8) != 0; // bit 3 set

        case 11: // conditionID == 21
            return (m_flags & 0x4) != 0; // bit 2 set

        case 12: // conditionID == 22
            return IsInCombat(); // FUN_00742ec0

        case 13: // conditionID == 23
            return !IsInCombat();

        case 14: // conditionID == 24
            return m_health > DAT_00d5780c;

        case 15: // conditionID == 25
            return !IsStealthMode(); // FUN_007431a0

        case 16: // conditionID == 26
            return IsStealthMode();

        default:
            // Fallback to base class handler
            return BaseCheckCondition(param2, param3, conditionID, param5); // FUN_004ac640
        }
        return false;
    }

private:
    int m_someInt;          // +0x20
    float m_health;         // +0x30
    void* m_targetPtr;      // +0x54
    uint32 m_flags;         // +0x74

    // Helper member functions (actual implementations elsewhere)
    bool IsInVehicle();     // FUN_00743000
    bool IsInCover();       // FUN_007430a0
    bool IsDead();          // FUN_00742b40
    int  GetCurrentMission(); // FUN_007ff880
    bool IsMissionActive(int slot); // FUN_00690150
    bool IsInCombat();      // FUN_00742ec0
    bool IsStealthMode();   // FUN_007431a0
    bool BaseCheckCondition(uint, uint, int, uint); // FUN_004ac640 (base class virtual or static)

    // Global constants (from data section)
    static const float DAT_00d5779c;
    static const float DAT_00e445ac;
    static const float DAT_00d5eee4;
    static const float DAT_00d5780c;
};

// Global constants definitions (example values – actual values differ)
const float Sentient::DAT_00d5779c = 0.5f;
const float Sentient::DAT_00e445ac = 0.1f;
const float Sentient::DAT_00d5eee4 = 0.0f;
const float Sentient::DAT_00d5780c = 0.2f;