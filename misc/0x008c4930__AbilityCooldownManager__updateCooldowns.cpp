// FUNC_NAME: AbilityCooldownManager::updateCooldowns
// Address: 0x008c4930
// Role: Updates a set of cooldown timers, capping a global ability cooldown and decrementing per-ability timers

// Globals referenced (from game data)
extern float DAT_00e44578;   // max cooldown cap value
extern float _DAT_00d5780c;  // frame delta time

// External function calls (likely system updates)
void FUN_008c4310();          // unknown, called when type match
void FUN_008bcaf0(float value); // receives global cooldown value
void FUN_00892a10();          // called if flag at +0x230 is set

class AbilityCooldownManager {
public:
    // Offset layout (relative to 'this'):
    // +0x054: uint32_t typeID; // magic = 0x637b907
    // +0x100: float currentAbilityCooldown; // accumulated cooldown
    // +0x104: float cooldownAccumulator; // added to currentAbilityCooldown
    // +0x18C: float* timerArray; // pointer to array of 8-byte entries (float at +4 used as timer)
    // +0x190: int32_t timerCount; // number of entries in timerArray
    // +0x198: float maxTimerValue; // largest remaining time among all timers
    // +0x230: int32_t unknownFlag; // non-zero triggers external update

    void updateCooldowns() {
        // Check if this is the specific cooldown manager type (maybe child class)
        if (*(int*)(this + 0x54) == 0x637b907) {
            FUN_008c4310();
        }

        // Update global ability cooldown accumulator
        float fVar6 = *(float*)(this + 0x104) + *(float*)(this + 0x100);
        if (fVar6 > 0.0f) {
            if (DAT_00e44578 <= fVar6) {
                fVar6 = DAT_00e44578;
            }
        } else {
            fVar6 = 0.0f;
        }
        *(float*)(this + 0x100) = fVar6;

        // Propagate to external system if type matches
        if (*(int*)(this + 0x54) == 0x637b907) {
            FUN_008bcaf0(fVar6);
        }

        // Trigger additional update if flag is set
        if (*(int*)(this + 0x230) != 0) {
            FUN_00892a10();
        }

        float deltaTime = _DAT_00d5780c;   // frame delta
        uint count = 0;
        bool anyTimerActive = false;

        if (*(int*)(this + 0x190) != 0) {
            do {
                // Each entry is 8 bytes: [4 unknown bytes][4 byte float timer at offset +4]
                float* timerPtr = (float*)(*(int*)(this + 0x18C) + 4 + count * 8);
                float timerValue = *timerPtr;
                bool isActive = false;
                if (timerValue > 0.0f) {
                    timerValue -= deltaTime;
                    *timerPtr = timerValue;
                    isActive = true;
                    if (timerValue < 0.0f) {
                        *(int*)(timerPtr) = 0; // clamp to zero
                    }
                }
                count++;
                anyTimerActive = anyTimerActive || isActive;
            } while (count < *(uint*)(this + 0x190));

            if (anyTimerActive) {
                // Recalculate the maximum timer value among all active timers
                count = 0;
                *(float*)(this + 0x198) = 0.0f;
                if (*(int*)(this + 0x190) != 0) {
                    float* iter = (float*)(*(int*)(this + 0x18C) + 4); // start at first timer float
                    do {
                        float current = *iter;
                        float currentMax = *(float*)(this + 0x198);
                        if (currentMax <= current && current != currentMax) {
                            *(float*)(this + 0x198) = current;
                        }
                        count++;
                        iter += 2; // skip 8 bytes per entry (2 floats)
                    } while (count < *(uint*)(this + 0x190));
                }
            }
        }
    }
};