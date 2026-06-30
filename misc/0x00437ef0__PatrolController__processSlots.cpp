// FUNC_NAME: PatrolController::processSlots
// Address: 0x00437ef0
// Reconstructed from Ghidra decompilation.
// This function appears to process an array of 4 action slots (each 8 bytes) 
// stored in the object. It validates each slot's type (3=valid, 4=calls external validation),
// then extracts 4 float parameters and triggers an event on a global manager.

#include <cstdint>

// Forward declarations for called functions
// FUN_00636850: likely checks something, returns 0 if fails
extern int __cdecl someValidationCheck(int* pData); // placeholder

// FUN_006259b0: returns a float given an object pointer and an index (1-4)
extern float __thiscall getParameter(void* obj, int index);

// FUN_00458ec0: triggers an event on the global manager object
extern void __cdecl triggerEvent(void* manager, int64_t packedData, float value);

// Global data references
extern void* g_EventManager; // DAT_012233fc
extern float g_MaxClampValue; // DAT_00e2b050

// Structure for each action slot (8 bytes)
struct ActionSlot {
    int type;   // 0x00: 3 = normal, 4 = needs validation
    int pad;    // 0x04: not used in this function
};

// The class that owns this function
class PatrolController {
public:
    // Offset +0x08: end pointer (one past last slot) ???
    // Offset +0x0C: current slot pointer (start of array)
    // The slots array is 4 elements, each 8 bytes, so total 32 bytes.
    void* m_slotsEnd;   // +0x08
    ActionSlot* m_slots; // +0x0C (points to 4-element array)
    
    void processSlots();
};

void PatrolController::processSlots()
{
    ActionSlot* slotPtr = m_slots;  // from param_1 + 0x0C
    ActionSlot* endPtr = static_cast<ActionSlot*>(m_slotsEnd); // from param_1 + 0x08
    
    // Bail out if array is empty or already at end
    if (endPtr <= slotPtr) {
        return;
    }
    if (slotPtr == nullptr) {
        return;
    }
    
    // Process slot 0
    if (slotPtr->type == 3) {
        // valid, continue
    } else if (slotPtr->type == 4) {
        // need additional validation
        uint64_t temp;
        if (someValidationCheck((int*)&temp) == 0) {
            return; // validation failed
        }
    } else {
        return; // unknown type
    }
    
    // Process slot 1 (offset +8 from base)
    slotPtr = reinterpret_cast<ActionSlot*>(reinterpret_cast<uint8_t*>(m_slots) + 8);
    if (endPtr <= slotPtr) {
        return;
    }
    if (slotPtr == nullptr) {
        return;
    }
    if (slotPtr->type == 3) {
        // valid
    } else if (slotPtr->type == 4) {
        uint64_t temp;
        if (someValidationCheck((int*)&temp) == 0) {
            return;
        }
    } else {
        return;
    }
    
    // Process slot 2 (offset +0x10)
    slotPtr = reinterpret_cast<ActionSlot*>(reinterpret_cast<uint8_t*>(m_slots) + 0x10);
    if (endPtr <= slotPtr) {
        return;
    }
    if (slotPtr == nullptr) {
        return;
    }
    if (slotPtr->type == 3) {
        // valid
    } else if (slotPtr->type == 4) {
        uint64_t temp;
        if (someValidationCheck((int*)&temp) == 0) {
            return;
        }
    } else {
        return;
    }
    
    // Process slot 3 (offset +0x18)
    slotPtr = reinterpret_cast<ActionSlot*>(reinterpret_cast<uint8_t*>(m_slots) + 0x18);
    if (endPtr <= slotPtr) {
        return;
    }
    if (slotPtr == nullptr) {
        return;
    }
    if (slotPtr->type == 3) {
        // valid
    } else if (slotPtr->type == 4) {
        uint64_t temp;
        if (someValidationCheck((int*)&temp) == 0) {
            return;
        }
    } else {
        return;
    }
    
    // Extract 4 float parameters from the object (indices 1..4)
    float param1 = getParameter(this, 1);
    float param2 = getParameter(this, 2);
    float param3 = getParameter(this, 3);
    float param4 = getParameter(this, 4);
    
    // Build a 64-bit packed value from the first three parameters
    int64_t packed = static_cast<int64_t>(static_cast<int>(round(param1)));
    int shift = 32;
    packed |= (static_cast<int64_t>(static_cast<int>(round(param2))) << 32);
    // Note: param3 is stored into the top 32 bits? The decompiled does:
    // local_10 = CONCAT44(local_10._4_4_, (float)fVar3);  -- that merges param3 into high part
    // We'll just pack all three; original code is imprecise, but we mimic.
    packed = (static_cast<int64_t>(static_cast<int>(round(param3))) << 32) | (packed & 0xFFFFFFFF);
    
    // Clamp param4 between 0 and global max
    float clamped = param4;
    if (clamped < 0.0f) {
        clamped = 0.0f;
    } else if (clamped > g_MaxClampValue) {
        clamped = g_MaxClampValue;
    }
    
    // Trigger event on global manager
    triggerEvent(g_EventManager, packed, clamped);
    
    return; // always returns 0 (void)
}