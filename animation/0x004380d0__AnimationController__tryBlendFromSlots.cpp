// FUNC_NAME: AnimationController::tryBlendFromSlots
// Address: 0x004380d0
// Validates 6 consecutive slot entries (size 0x8 each) for types 3 or 4,
// then retrieves blend values and applies them.

struct SlotEntry {
    int type;        // +0x0: 3=active, 4=conditional
    int padding;     // +0x4: unused, size 0x8 total
};

class AnimationController {
public:
    SlotEntry* m_pSlotStart;   // +0x0C: pointer to first slot (start of array)
    SlotEntry* m_pSlotEnd;     // +0x08: pointer past last slot
    // ... other members

    // validateSlotEntry: returns non-zero if slot type 4 passes extra checks
    bool validateSlotEntry(SlotEntry* slot);

    // getFloatValue: retrieves a float value from the controller by index (1-6)
    float getFloatValue(int index);

    // computeAndApplyBlend: receives 5 floats and applies blend result
    void computeAndApplyBlend(float a, float b, float c, float d, float e);

    // Main logic
    void tryBlendFromSlots();
};

bool AnimationController::validateSlotEntry(SlotEntry* slot) {
    // Stub: called with &this? Real implementation unknown.
    return true;
}

float AnimationController::getFloatValue(int index) {
    // Stub: returns some value based on index.
    return 0.0f;
}

void AnimationController::computeAndApplyBlend(float a, float b, float c, float d, float e) {
    // Stub: applies blend to animation or transformation.
}

void AnimationController::tryBlendFromSlots() {
    // Access slot array via m_pSlotStart
    SlotEntry* slot = m_pSlotStart;
    // Check if there are at least 6 slots and all are valid
    if (slot < m_pSlotEnd && slot != nullptr &&
        (slot->type == 3 || (slot->type == 4 && validateSlotEntry(slot)))) {
        slot = (SlotEntry*)((int*)m_pSlotStart + 2);  // advance by 2 ints = 8 bytes = one SlotEntry
        if (slot < m_pSlotEnd && slot != nullptr &&
            (slot->type == 3 || (slot->type == 4 && validateSlotEntry(slot)))) {
            slot = (SlotEntry*)((int*)m_pSlotStart + 4);  // +0x10
            if (slot < m_pSlotEnd && slot != nullptr &&
                (slot->type == 3 || (slot->type == 4 && validateSlotEntry(slot)))) {
                slot = (SlotEntry*)((int*)m_pSlotStart + 6);  // +0x18
                if (slot < m_pSlotEnd && slot != nullptr &&
                    (slot->type == 3 || (slot->type == 4 && validateSlotEntry(slot)))) {
                    slot = (SlotEntry*)((int*)m_pSlotStart + 8);  // +0x20
                    if (slot < m_pSlotEnd && slot != nullptr &&
                        (slot->type == 3 || (slot->type == 4 && validateSlotEntry(slot)))) {
                        slot = (SlotEntry*)((int*)m_pSlotStart + 10);  // +0x28
                        if (slot < m_pSlotEnd && slot != nullptr &&
                            (slot->type == 3 || (slot->type == 4 && validateSlotEntry(slot)))) {
                            // All six slots valid, retrieve floats and blend
                            float val2 = getFloatValue(2);
                            float val3 = getFloatValue(3);
                            float val4 = getFloatValue(4);
                            float val5 = getFloatValue(5);
                            float val6 = getFloatValue(6);
                            // Note: getFloatValue(1) was called but unused for blend
                            computeAndApplyBlend(val2, val3, val4, val5, val6);
                        }
                    }
                }
            }
        }
    }
}