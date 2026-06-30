// FUNC_NAME: SpatialAudioManager::updateActiveEmitters

#include <cstdint>

// Forward declarations of external functions (likely from EA EARS engine math library)
extern void __cdecl GetWorldPosition(uint32_t transformPtr, int componentIndex, float* outPos); // FUN_00c9cbe0
extern void __cdecl MathLock(); // FUN_00c9eac0
extern void __cdecl MathDistanceSquared(const float* a, float* outDistSq); // FUN_00c9cd00
extern float __cdecl MathCompareValue(); // FUN_00c9cd40 (returns something like a global constant?)
extern void __cdecl MathUnlock(); // FUN_00c9eae0
extern int  __cdecl MathGetFlags(uint32_t flagsPtr); // FUN_00c9eb10
extern void __cdecl CleanupObject(uint32_t objID); // FUN_005ea0d0
extern void __cdecl RemoveFromList(uint32_t thisPtr, uint32_t listOffset1, uint32_t listOffset2); // FUN_005ebfa0

// External global comparison value
extern const float DAT_00e2b05c;

// Struct for an active emitter slot (size 0x5c = 92 bytes)
struct EmitterSlot {
    /* +0x00 */ uint32_t flags;           // bitfield, bit1 = active? (pfVar10[-1] is actually this, offset -4 from *pfVar10)
    /* +0x04 */ float volume;            // *pfVar10 (the main value compared)
    /* +0x08 */ uint32_t padding08;
    /* +0x0C */ float field0C;
    /* +0x10 */ int32_t indexIntoRefCountArray; // used for semaphore at 0x81bc + index*0x10
    /* +0x14 */ float field14;
    /* +0x18 */ float field18;
    /* +0x1C */ float field1C;
    /* +0x20 */ float field20;
    /* +0x24 */ float field24;
    /* +0x28 */ float field28;
    /* +0x2C */ float field2C;
    /* +0x30 */ float field30;
    /* +0x34 */ float field34;
    /* +0x38 */ float field38;
    /* +0x3C */ float field3C;
    /* +0x40 */ float field40;
    /* +0x44 */ float field44;
    /* +0x48 */ float field48;
    /* +0x4C */ float field4C;
    /* +0x50 */ float field50;
    /* +0x54 */ float field54;
    /* +0x58 */ float field58; // at offset 0x58 from slot start (used as transform pointer via (int)pfVar10[0xd] )
};

// Size check: 0x5c = 92 bytes, last field is at 0x58, plus 4 bytes makes 0x5c.

// The main class that owns the emitter slots
class SpatialAudioManager {
public:
    int updateActiveEmitters(); // this function at 0x005ee380

    // Offsets in the class (from this):
    // +0x398: first list pointer for one type
    // +0x3c4: another list pointer
    // +0x3c8: corresponding list offset? Actually paired: (0x3c4, 0x398), (0x3f4,0x3c8), (0x424,0x3f8)
    // +0x3f4: another list pointer
    // +0x3f8: another list offset?
    // +0x424: another list pointer
    // +0x428: another list offset?
    // +0x454: another list pointer? (paired with +0x428)
    // +0x580: something (pointer to a transform or audio resource)
    // +0x81A0: pointer to array of pairs (index, some value) used for tracking used IDs
    // +0x81A4: count of entries in the array at +0x81A0
    // +0x81AC: pointer to array of IDs (for another list)
    // +0x81B0: count of entries in that array
    // +0x81B8: callback function pointer (called when an ID is removed)
    // +0x81BC: array of semaphores (10 entries, each 0x10 bytes? Actually used with index*0x10)
    // +0x8344: start of emitter slot array (10 slots, each 0x5c bytes)
};

// Reconstructed function
int SpatialAudioManager::updateActiveEmitters() {
    EmitterSlot* slot = reinterpret_cast<EmitterSlot*>(reinterpret_cast<uint8_t*>(this) + 0x8344);
    int remaining = 10;  // number of slots to process

    do {
        // Check if this slot is active (bit 1 of flags, using flags at offset -4? Actually flags is at offset 0x00, but pfVar10 points to volume at +0x04, so pfVar10[-1] is flags)
        if ((slot->flags >> 1) & 1) {
            bool keepAlive = true;

            // Conditions for automatic removal:
            // volume >= 0.0, indexIntoRefCountArray >= 0, and there is a transform pointer (slot->field58 != 0.0)
            if ((slot->volume >= 0.0f) &&
                (slot->indexIntoRefCountArray >= 0) &&
                (slot->field58 != 0.0f)) {
                float localDistSq = 0.0f;
                float tempPos[2];  // for local_18

                // Get position from the transform at *(int*)(slot->field58 + 0x10)
                GetWorldPosition(*reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(this) + 0x580),
                                *reinterpret_cast<uint32_t*>(static_cast<int>(slot->field58) + 0x10),
                                2, tempPos);

                tempPos[0] = slot->volume;  // override with volume? Strange but per decompiled
                MathLock();
                MathDistanceSquared(0, &localDistSq); // compare distance squared to '0' (probably reference point)
                if (localDistSq < slot->volume) {
                    keepAlive = false;
                } else if (localDistSq == slot->volume) {
                    // Special equality check
                    float cmpVal = MathCompareValue(2, tempPos);
                    if (cmpVal == DAT_00e2b05c) {
                        keepAlive = false;
                    }
                }
                MathUnlock();

                if (!keepAlive) {
                    goto cleanupSlot;
                }
            }

            // If the slot has a valid indexIntoRefCountArray, decrement the semaphore in the array at +0x81BC
            if (slot->indexIntoRefCountArray >= 0) {
                int* semaphore = reinterpret_cast<int*>(reinterpret_cast<uint8_t*>(this) + 0x81BC +
                    slot->indexIntoRefCountArray * 0x10);
                // LOCK/UNLOCK macros assumed to be atomic operations
                Lock();
                *semaphore -= 1;
                Unlock();
            }
            // Call cleanup routine for this specific emitter object
            CleanupObject(/* some ID? */);
        }

cleanupSlot:
        // Advance to next slot (size 0x5c)
        slot = reinterpret_cast<EmitterSlot*>(reinterpret_cast<uint8_t*>(slot) + 0x5C);
        remaining--;
        if (remaining == 0) {
            // After processing all 10 slots, compact the arrays of used IDs
            if ((*reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(this) + 0x580) != 0) &&
                (*reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(this) + 0x81A4) != 0)) {
                uint32_t idx = 0;
                MathLock();
                uint32_t count = *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(this) + 0x81A4);
                if (count != 0) {
                    uint8_t* arrayBase = reinterpret_cast<uint8_t*>(*reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(this) + 0x81A0));
                    do {
                        // Each entry is 8 bytes: a 4-byte ID (not used in this check) and a 4-byte flag
                        int flag = MathGetFlags(*reinterpret_cast<uint32_t*>(arrayBase + 4 + idx * 8));
                        if (flag == 0) {
                            idx++;
                        } else {
                            uint32_t lastIdx = *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(this) + 0x81A4) - 1;
                            if (idx != lastIdx) {
                                // Copy last entry over current
                                std::memcpy(arrayBase + idx * 8, arrayBase + lastIdx * 8, 8);
                            }
                            (*reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(this) + 0x81A4))--;
                        }
                    } while (idx < count);
                }
                MathUnlock();
            }

            // Second array compaction: remove IDs from list at +0x81AC that are no longer in the first array
            uint32_t outerCount = *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(this) + 0x81B0);
            if (outerCount != 0) {
                uint32_t outerIdx = 0;
                do {
                    // Check if outerIdx exists in the first array
                    uint32_t innerCount = *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(this) + 0x81A4);
                    if (innerCount != 0) {
                        uint32_t innerIdx = 0;
                        uint32_t* innerArray = reinterpret_cast<uint32_t*>(*reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(this) + 0x81A0));
                        do {
                            if (innerArray[innerIdx * 2] ==
                                (*reinterpret_cast<uint32_t*>(*reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(this) + 0x81AC) + outerIdx * 4))) {
                                outerIdx++;
                                goto nextOuter;
                            }
                            innerIdx++;
                        } while (innerIdx < innerCount);
                    }
                    // ID not found, call callback if set
                    if (*reinterpret_cast<void (**)(uint32_t)>(reinterpret_cast<uint8_t*>(this) + 0x81B8) != nullptr) {
                        (**reinterpret_cast<void (**)(uint32_t)>(reinterpret_cast<uint8_t*>(this) + 0x81B8))(
                            *reinterpret_cast<uint32_t*>(*reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(this) + 0x81AC) + outerIdx * 4));
                    }
                    uint32_t lastIdx = *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(this) + 0x81B0) - 1;
                    if (outerIdx != lastIdx) {
                        uint32_t* outerArray = reinterpret_cast<uint32_t*>(*reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(this) + 0x81AC));
                        outerArray[outerIdx] = outerArray[lastIdx];
                    }
                    (*reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(this) + 0x81B0))--;
nextOuter:
                    ;
                } while (outerIdx < outerCount);
            }

            // Clear several internal lists (likely referencing different list types)
            RemoveFromList(reinterpret_cast<uint32_t>(this),
                           *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(this) + 0x454),
                           reinterpret_cast<uint32_t>(reinterpret_cast<uint8_t*>(this) + 0x428));
            RemoveFromList(reinterpret_cast<uint32_t>(this),
                           *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(this) + 0x3C4),
                           reinterpret_cast<uint32_t>(reinterpret_cast<uint8_t*>(this) + 0x398));
            RemoveFromList(reinterpret_cast<uint32_t>(this),
                           *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(this) + 0x3F4),
                           reinterpret_cast<uint32_t>(reinterpret_cast<uint8_t*>(this) + 0x3C8));
            RemoveFromList(reinterpret_cast<uint32_t>(this),
                           *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(this) + 0x424),
                           reinterpret_cast<uint32_t>(reinterpret_cast<uint8_t*>(this) + 0x3F8));
            return 1; // success
        }
    } while (true);
    // Unreachable
}