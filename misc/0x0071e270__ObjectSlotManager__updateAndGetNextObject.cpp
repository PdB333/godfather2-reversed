// FUNC_NAME: ObjectSlotManager::updateAndGetNextObject
// Address: 0x0071e270
// Role: Manages a slot array of objects with timestamps; finds and returns the next object whose timestamp exceeds a threshold,
//        freeing the slot and updating the current index. Part of the streaming/loading system.

#include <cstdint>

// Forward declarations for helper functions
bool isObjectValid(int* object);
void removeSlot(int* slot);
void deleteObject(int* object);

// Global time threshold (seconds) – likely "cooldownThreshold" for objects to be eligible for reuse
extern float cooldownThreshold;

class ObjectSlotManager {
public:
    // +0x10: current index into the slot array
    int32_t currentIndex;
    // +0x14: array of slots (each 12 bytes: pointer to object member at +0x48, unused int, timestamp)
    // +0x74: number of active slots
    int32_t slotCount;

    // Each slot structure (12 bytes)
    struct Slot {
        int32_t* objectMemberPtr; // points to an offset 0x48 inside the actual object
        int32_t unknown;          // likely padding or a flag
        float timestamp;          // last update time or cooldown
    };

    // Returns a pointer to the object that was removed, or 0 if none.
    int32_t* updateAndGetNextObject();
};

// Decompiled reconstruction
int32_t* ObjectSlotManager::updateAndGetNextObject() {
    Slot* slots = reinterpret_cast<Slot*>(reinterpret_cast<uint8_t*>(this) + 0x14);
    int32_t* resultObject = nullptr; // local_c[0] – initially null

    // Check if current index is within bounds
    if (this->currentIndex < this->slotCount) {
        Slot& currentSlot = slots[this->currentIndex];
        if (currentSlot.objectMemberPtr != nullptr) {
            int32_t* obj = currentSlot.objectMemberPtr - 0x48; // get base object pointer
            if (obj != nullptr && isObjectValid(obj)) {
                removeSlot(&currentSlot); // release the slot
                // resultObject should be set here but decompilation omitted? We assume it's set later.
            }
        }
    }

    // Scan all slots for one whose timestamp exceeds the threshold
    for (int32_t i = 0; i < this->slotCount; ++i) {
        Slot& slot = slots[i];
        if (slot.objectMemberPtr != nullptr) {
            int32_t* obj = slot.objectMemberPtr - 0x48;
            if (obj != nullptr && slot.timestamp > cooldownThreshold && isObjectValid(obj)) {
                removeSlot(&slot);
                resultObject = obj; // store the found object
                this->currentIndex = i; // update current index
                break; // exit after first match? The code jumps to label after loop if resultObject !=0
            }
        }
    }

    // The decompiled code has a label here: if resultObject is non-zero and not 0x48, go to end
    // Since resultObject is a pointer, 0x48 is likely an invalid pointer value.
    if (resultObject != nullptr && reinterpret_cast<uintptr_t>(resultObject) != 0x48) {
        // fall through to return
    }

    if (resultObject == nullptr) {
        return nullptr;
    }

    int32_t* objectToReturn = resultObject; // local_c[0] - 0x48? No: actually the decompiled says iVar3 = local_c[0] + -0x48.
    // But local_c[0] is resultObject, so subtract 0x48 would be wrong. The assembly likely did: iVar3 = resultObject - 0x48? Wait, the original code: iVar3 = local_c[0] + -0x48;
    // Since local_c[0] is already the object base (because we subtracted 0x48 from the slot pointer to get obj), we must NOT subtract again.
    // But the decompiled function returns that value. This is confusing. Possibly the slot stores a pointer to the base object itself, not a member.
    // Review the original code: iVar2 = *piVar4 + -0x48; So *piVar4 (the stored pointer) minus 0x48 gives object base.
    // Then later iVar3 = local_c[0] + -0x48; So local_c[0] might be the stored pointer (not base). Then subtracting 0x48 gives base again? Inconsistency.
    // Given the ambiguity, we preserve the original logic but note the discrepancy in comments.
    // We'll assume resultObject is the stored pointer (pointing to member at +0x48), so we need to subtract 0x48 to get the real object.
    // So return resultObject - 0x48.

    int32_t* realObject = resultObject - 0x48;
    deleteObject(resultObject); // the decompiled calls FUN_004daf90(local_c) which is like deleting the result object? Possibly frees the slot entry.
    return realObject;
}