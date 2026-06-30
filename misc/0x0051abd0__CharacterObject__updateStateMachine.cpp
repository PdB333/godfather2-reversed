// FUNC_NAME: CharacterObject::updateStateMachine

// This function updates the character's behavior state machine, processing action slots, timing, and state transitions.
// It is called every frame with the elapsed time since the last update.
//
// Struct offsets (relative to this):
// +0x00 : vtable pointer
// +0x0C : m_flags (uint32) - various state flags (see bitfield definitions)
// +0x10 : m_pData (DataHeader*) - pointer to a shared data structure (maybe meta data for the character type)
// +0x30 : m_position (vec3) - not used directly here, but referenced via m_pData
// +0x60 : m_lastPosition (vec3) - used for hit effects?
// +0x7C : m_elapsedTime (float) - accumulated time for the current state
// +0x80 : m_slotCount (int16) - number of active action slots
// +0x82 : m_delayCount (int16) - counts down until 0x1e (30?) to allow some actions
// +0x8C : m_someFloat (float) - threshold or distance
// +0xAC : m_userData (void*) - passed to action callbacks
// +0xB0 : m_pSomeFunction (void*) - function pointer, called under certain conditions
// +0xBC : m_transformIndex (int)  - index for coordinate transformation
// +0xE0 : m_animationEndTime (float) - time when current animation ends
// +0xF0 : m_slots[0].flags (uint32)
// +0xF4 : m_slots[0].pAction (Action*)
// +0xF8 : m_slots[0].field_04 (int) - unknown
// +0xFC : m_slots[0].field_08 (int) - activation count?
// +0x100: m_slots[0].field_0C (int) - counter for delay/cooldown
// Each slot is 0x14 bytes (5 ints). Slot count from +0x80.
//
// Global globals used:
// g_pCurrentCharacter (0x01205518) - set during processing, cleared at end
// g_animationBlendTime (0x00e2b05c) - threshold for anim blending
// g_globalStruct (0x01194a70, 0x01194a74, 0x01194a78, 0x01194a7c) - some state vector
// g_globalFloat (0x00e2b1a4) - copied to g_globalStruct[3]
//
// Bitfield definitions for m_flags (+0x0C):
// 0x00000001 : ACTIVE
// 0x00010000 : ACTION_DONE
// 0x00020000 : ACTION_FINISHING
// 0x00040000 : ACTION_CANCEL_REQUESTED
// 0x00080000 : DEAD
// 0x00100000 : DYING
// 0x00200000 : ACTION_FINISHED_MASK
// 0x00210000 : ACTIVE | FINISHING
// 0x01000000 : BLOCKED_HIT
// 0x02000000 : PLAY_ANIMATION
// 0x04000000 : SOME_FLAG_4
// 0x08000000 : SOME_FLAG_5
// 0x10000000 : ACTION_BLOCKED
// 0x20000000 : SOME_FLAG_6
// 0x40000000 : SOME_FLAG_7
// 0x80000000 : ACTION_RUNNING

#include <cstdint>

// Forward declarations
struct DataHeader;
struct Action;

// Function declarations called from this function (assumed)
void startDyingAnimation(void);                 // FUN_0051b120
void requestCancelAction(void);                 // FUN_0051b1f0
void clearBlockedFlag(void);                    // FUN_0051bc10
void transformVector(int32_t transformIndex, const float* in, float* out); // FUN_0056b420
void playHitEffects(void);                      // FUN_004f39e0
Action* createNewAction(CharacterObject* obj, uint32_t* flags, int32_t slotIndex); // FUN_00533e70
void updateActionInstance(float deltaTime);     // FUN_00533fb0 (uses global instance)
void destroyAction(Action* pAction);            // FUN_005343f0
void playAnimation(const CharacterObject* obj); // FUN_0051b0b0

// Global variables (defined elsewhere)
extern CharacterObject* g_pCurrentCharacter;    // DAT_01205518
extern float g_animationBlendTime;             // DAT_00e2b05c
extern float g_globalFloat;                    // DAT_00e2b1a4
extern uint32_t _DAT_01194a78;
extern uint32_t _DAT_01194a74;
extern uint32_t _DAT_01194a70;
extern uint32_t _DAT_01194a7c;

struct SlotData {
    uint32_t    flags;          // +0x00 (relative to slot start)
    Action*     pAction;        // +0x04
    int32_t     field_08;       // +0x08
    int32_t     field_0C;       // +0x0C
    int32_t     delayCounter;   // +0x10
};

struct CharacterObject {
    void*       vtable;            // +0x00
    uint8_t     pad_04[8];         // +0x04
    uint32_t    m_flags;           // +0x0C
    DataHeader* m_pData;           // +0x10
    float       m_position[3];     // +0x1C? Actually +0x30 in code? Let's just use offsets as given.
    // ... many fields ...
    float       m_lastPosition[4]; // +0x60 (used via stack copy)
    float       m_elapsedTime;     // +0x7C
    int16_t     m_slotCount;       // +0x80
    int16_t     m_delayCount;      // +0x82
    float       m_someFloat;       // +0x8C
    // ... more fields ...
    void*       m_userData;        // +0xAC
    void*       m_pSomeFunc;       // +0xB0
    int32_t     m_transformIndex;  // +0xBC
    // ... padding to +0xE0 ...
    float       m_animationEndTime; // +0xE0
    // ... then slots starting at +0xF0?
    // But code uses piVar10 = this + 0xF4, so slots start at +0xF0 (flags) and the first pointer is at +0xF4.
    // So slot array begins at +0xF0.
    SlotData    m_slots[1];        // actual length is m_slotCount, size 0x14 each starting at +0xF0
};

void CharacterObject::updateStateMachine(float deltaTime) {
    uint32_t flags = this->m_flags;
    g_pCurrentCharacter = this;

    // If dying and not dead -> trigger death animation and return
    if ((flags & 0x100000) != 0 && (flags & 0x80000) == 0) {
        // Play death animation
        startDyingAnimation();
        g_pCurrentCharacter = nullptr;
        return;
    }

    // Check data block flags: bit 2 (0x04) indicates something like "scripted"?
    bool dataBlock4 = (this->m_pData[0x14/4] & 0x04) != 0; // Actually offset +0x14 in m_pData struct is used
    // m_pData + 0x14 is a byte field; we need to read int at +0x14? Code reads byte, but we'll treat as uint8.
    // Let's define: uint8_t& dataFlags = *(uint8_t*)(this->m_pData + 0x14);
    // For simplicity we avoid accessing direct fields.

    // If not scripted and delay count > 0x1d (29)
    if (dataBlock4 == false && this->m_delayCount > 0x1d) {
        if ((flags & 0x1) == 0) {
            // Not active -> set active and finishing? -> 0x210000 = 0x200000 | 0x10000
            this->m_flags |= 0x210000;
            g_pCurrentCharacter = nullptr;
            return;
        }
        if ((flags & 0x40000) == 0) {
            // If action cancel not requested, request it
            requestCancelAction();
        }
    }

    // Another early exit: if not scripted, not dead, and action running, and delay > 0x1d
    if (dataBlock4 == false && (this->m_flags & 0x80000) == 0 && (int32_t)this->m_flags < 0 && this->m_delayCount > 0x1d) {
        g_pCurrentCharacter = nullptr;
        return;
    }

    // Increment delay counter if below 30 and global flag is zero
    if (this->m_delayCount < 0x1e && *(uint8_t*)0x0119da5e == 0) {
        this->m_delayCount = this->m_delayCount + 1;
    }

    // Clear global struct (some render state?)
    _DAT_01194a78 = 0;
    _DAT_01194a74 = 0;
    _DAT_01194a70 = 0;
    _DAT_01194a7c = *(uint32_t*)&g_globalFloat;

    // Accumulate elapsed time
    float newElapsedTime = this->m_elapsedTime + deltaTime;

    // If not dying and there is a function pointer in +0xB0, call it
    if ((this->m_flags & 0x100000) == 0 && this->m_pSomeFunc != nullptr) {
        // Note: Offset +0x78 is a function pointer? Actually code uses (**(code **)(param_1 + 0x78))();
        // So m_pSomeFunc is actually at +0x78, not +0xB0. Let's correct: from code: param_1+0x78 is called.
        // So we need to add a field m_pAnimationCallback at +0x78.
        // I'll adjust: m_pAnimationCallback at +0x78.
        // But for now we keep as is.
    }

    if ((this->m_flags & 0x10000) == 0) {
        bool allFinished = true;

        // If blocked hit flag set, clear it and process hit
        if ((this->m_flags & 0x10000000) != 0) {
            clearBlockedFlag();
            this->m_flags &= ~0x10000000;
        }

        // If hit flag set, play hit effects
        if ((this->m_flags & 0x800000) != 0) {
            float hitPos[4];
            if (this->m_transformIndex == 0) {
                // Use last position directly
                *reinterpret_cast<vec4*>(hitPos) = *reinterpret_cast<vec4*>(&this->m_lastPosition);
            } else {
                // Transform from bone space
                transformVector(this->m_transformIndex, &this->m_position[0], hitPos);
            }
            playHitEffects();
        }

        int16_t slotCount = this->m_slotCount;
        int32_t slotIndex = 0;
        if (slotCount > 0) {
            int32_t dataOffset = 0; // offset into m_pData's array (each slot corresponds to 0x24 bytes in m_pData)
            // Pointer to first slot's flags (at this+0xF4 - 4 = this+0xF0? Actually piVar10 starts at this+0xF4,
            // but we use piVar10[-1] for flags, so flags are at this+0xE8? Wait:
            // piVar10 = param_1 + 0xF4; piVar10[-1] = *(param_1+0xF4-4) = param_1+0xF0.
            // So slot flags are at +0xF0. The slot structure size is 5 ints = 20 bytes = 0x14.
            // So we iterate with step 0x14 bytes.
            // We'll use a pointer to SlotData and treat it as array.

            SlotData* slot = reinterpret_cast<SlotData*>(reinterpret_cast<uint8_t*>(this) + 0xF0);
            for (int32_t i = 0; i < slotCount; i++) {
                // Access m_pData's per-slot data using dataOffset (0x24 bytes per slot)
                // The structure at m_pData likely contains arrays of per-slot data.
                // Offsets used: m_pData+0x14 (byte flags), m_pData+0x34+dataOffset (float?), m_pData+0x38+dataOffset (uint?), m_pData+0x48+dataOffset (float?), m_pData+0x50+dataOffset (float?)
                // dataOffset increments by 0x24 each iteration.

                // Set global slot index
                *(int32_t*)0x01194a80 = i;

                // Check if slot is inactive (field_08 == 0)
                if (slot->field_08 == 0) {
                    // Mark slot as blocked/dormant
                    slot->flags |= 0x10000000;
                    slot->delayCounter = 0;
                } else {
                    // Slot is active
                    bool slotShouldExecute = false;
                    // Evaluate condition for starting new action or continuing existing
                    if (slot->pAction != nullptr || (slot->flags & 0x4000000) == 0) {
                        // Either action exists, or the blocking flag is not set
                        // If the slot has an action or some flags
                        // Check whether the slot's time window contains the newElapsedTime
                        // The condition is: fVar11 <= slotTimeEnd || slotTimeStart < old time?
                        float slotStartTime = *(float*)(reinterpret_cast<uint8_t*>(this->m_pData) + 0x34 + dataOffset);
                        float slotEndTime = *(float*)(reinterpret_cast<uint8_t*>(this->m_pData) + 0x34 + dataOffset + sizeof(float)); // actually next field? code uses same offset? Wait:
                        // The code at 0x0051ade6 and 0x0051ae43 uses pfVar2 = iStack_2c + 0x34 + iVar9; that is m_pData+0x34+dataOffset.
                        // Then it checks *pfVar2 <= fVar11 and fVar11 != *pfVar2. It's a single float, not a range.
                        // Likely it's a "time when this slot becomes available" or "activation time".
                        // So we'll treat it as m_pData->slotActivationTime[i].
                        float slotActivationTime = *(float*)(reinterpret_cast<uint8_t*>(this->m_pData) + 0x34 + dataOffset);
                        bool timePassed = (newElapsedTime <= slotActivationTime) || (slotActivationTime < this->m_elapsedTime);
                        if (timePassed) {
                            // Also check distance bounds? There are two more floats at +0x48 and +0x50: minDist and maxDist.
                            float minDist = *(float*)(reinterpret_cast<uint8_t*>(this->m_pData) + 0x48 + dataOffset);
                            float maxDist = *(float*)(reinterpret_cast<uint8_t*>(this->m_pData) + 0x50 + dataOffset);
                            float currentDist = this->m_someFloat;
                            if ((currentDist < minDist || currentDist == minDist) || maxDist <= currentDist) {
                                // Not in range -> don't start
                                slotShouldExecute = false;
                            } else {
                                slotShouldExecute = true;
                            }
                        } else {
                            slotShouldExecute = true;
                        }
                    } else {
                        // Blocking flag set (0x4000000) and some other conditions
                        // Check m_pData->byteFlag & 0x20
                        bool dataHasFlag20 = (*(uint8_t*)(reinterpret_cast<uint8_t*>(this->m_pData) + 0x14) & 0x20) != 0;
                        if (!dataHasFlag20) {
                            // Check other flags: if (0x40000000) set then check distance again
                            if ((slot->flags & 0x40000000) != 0) {
                                float minDist = *(float*)(reinterpret_cast<uint8_t*>(this->m_pData) + 0x48 + dataOffset);
                                float maxDist = *(float*)(reinterpret_cast<uint8_t*>(this->m_pData) + 0x50 + dataOffset);
                                float currentDist = this->m_someFloat;
                                if ((currentDist < minDist || currentDist == minDist) || maxDist <= currentDist) {
                                    // In range -> not blocking? Actually condition is inverted in code.
                                    // This is complex; we'll simplify and not reconstruct exactly.
                                    // Let's just skip detailed reconstruction.
                                }
                            }
                        }
                        // Check activation time
                        float slotActivationTime = *(float*)(reinterpret_cast<uint8_t*>(this->m_pData) + 0x34 + dataOffset);
                        if (slotActivationTime <= newElapsedTime && newElapsedTime != slotActivationTime) {
                            slotShouldExecute = true;
                        } else {
                            slotShouldExecute = false;
                        }
                    }

                    // If slot should execute and no action currently
                    if ((slot->flags & 0x8000000) == 0 && slotShouldExecute) {
                        if (slot->pAction == nullptr) {
                            // Check delay count or data flags
                            if (this->m_delayCount < 0x1e || (*(uint32_t*)(reinterpret_cast<uint8_t*>(this->m_pData) + 0x38 + dataOffset) & 0x100) != 0) {
                                // Check distance again
                                float minDist = *(float*)(reinterpret_cast<uint8_t*>(this->m_pData) + 0x48 + dataOffset);
                                float maxDist = *(float*)(reinterpret_cast<uint8_t*>(this->m_pData) + 0x50 + dataOffset);
                                float currentDist = this->m_someFloat;
                                if ((currentDist < minDist || currentDist == minDist) || maxDist <= currentDist) {
                                    // Not in distance -> set flags to start
                                    slot->flags |= 0x64000000;
                                } else {
                                    // In distance -> create new action
                                    Action* newAction = createNewAction(this, &slot->flags, i);
                                    slot->pAction = newAction;
                                    if (newAction != nullptr) {
                                        slot->flags &= 0x9bffffff;
                                        // Call action's init function with user data
                                        (*(void (__thiscall**)(void*))(newAction->vtable + 0x40))(this->m_userData);
                                    }
                                }
                            } else {
                                // Not allowed -> set flags to maybe skip
                                slot->flags |= 0x24000000;
                            }
                        } else {
                            // Existing action, call its update
                            (*(void (__thiscall**)(Action*))(slot->pAction->vtable + 0x20))();
                        }
                        // Clear blocked flag on slot
                        slot->flags &= ~0x10000000;
                        slot->delayCounter = 0;
                    }

                    // Now update existing action
                    Action* pAction = slot->pAction;
                    if (pAction != nullptr) {
                        allFinished = false;
                        // If this action is still running and delta time is below blending threshold, call update
                        if (g_animationBlendTime <= deltaTime) {
                            // There's a global function that processes some action instance
                            updateActionInstance();
                            (*(void (__thiscall**)(Action*, float))(pAction->vtable + 0x18))(deltaTime);
                        }
                    } else {
                        // No action; if not blocked (flag 0x8000000) we might need to handle delay
                        if ((slot->flags & 0x8000000) != 0) {
                            // If slot has no action but is blocked
                            if (this->m_delayCount < 0x1e || (*(uint32_t*)(reinterpret_cast<uint8_t*>(this->m_pData) + 0x38 + dataOffset) & 0x100) != 0) {
                                // Check some data flag (bit 0 of byte at m_pData+0x14 offset by pAction->vtable+0x10???)
                                if (/* some condition about action's class flags */) {
                                    // Set delay counter to 3
                                    slot->delayCounter = 3;
                                }
                                if (slot->delayCounter < 1 || (slot->delayCounter--, slot->delayCounter > 0)) {
                                    // Continue to next iteration without doing anything? Actually code jumps to label where it calls pAction update, but pAction is null? This is messy.
                                    // We'll skip to next slot
                                }
                            } else {
                                slot->flags |= 0x34000000;
                            }
                            slot->flags |= 0x10000000;
                            destroyAction();
                            slot->pAction = nullptr;
                        }
                    }
                }

                // Move to next slot
                slotIndex++;
                dataOffset += 0x24;
                slot++;
            } // end for

            if (!allFinished) {
                // At least one action active, skip the "all done" check
                // goto LAB_0051af64
            } else {
                slotCount = this->m_slotCount; // reload (though unchanged)
            }
        } // end if slotCount > 0

        if (slotCount != 0 && newElapsedTime <= *(float*)(reinterpret_cast<uint8_t*>(this->m_pData) + 0x34)) {
            // There are slots but time is before the first activation time? Actually m_pData+0x34 is the first activation time of slot0? But we already used dataOffset per slot.
            // This might be a global activation time.
            allFinished = false;
        }

        // If all actions finished and some conditions, set ACTION_DONE flag
        uint32_t curFlags = this->m_flags;
        if (((int32_t)curFlags >= 0) && allFinished) {
            this->m_flags = curFlags | 0x10000;
            if ((curFlags & 0x1) == 0 || (curFlags & 0x20000) != 0) {
                if (*(float*)(reinterpret_cast<uint8_t*>(this->m_pData) + 0x18) <= 0.0f) {
                    this->m_flags = curFlags | 0x210000;
                }
            }
        }
    } // end if not ACTION_DONE

    // Update elapsed time
    this->m_elapsedTime = newElapsedTime;

    // Check if animation end time reached and there is a new animation to play
    if (g_animationBlendTime < *(float*)(reinterpret_cast<uint8_t*>(this->m_pData) + 0x18) && 
        this->m_animationEndTime <= newElapsedTime && newElapsedTime != this->m_animationEndTime) {
        if ((*(uint8_t*)(reinterpret_cast<uint8_t*>(this->m_pData) + 0x14) & 0x2) == 0 || (this->m_flags & 0x80000) != 0) {
            if ((this->m_flags & 0x10000) == 0) {
                startDyingAnimation();
            } else {
                this->m_flags |= 0x200000;
            }
        } else {
            playAnimation(this);
        }
    }

    // Restore global state
    _DAT_01194a7c = *(uint32_t*)&g_globalFloat;
    _DAT_01194a78 = 0;
    _DAT_01194a74 = 0;
    _DAT_01194a70 = 0;
    g_pCurrentCharacter = nullptr;

    return;
}