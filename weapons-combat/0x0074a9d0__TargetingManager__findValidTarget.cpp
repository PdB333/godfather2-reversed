// FUNC_NAME: TargetingManager::findValidTarget

#include <cstdint>

// Forward declaration of target data struct (12 bytes)
struct TargetData {
    uint64_t key;   // +0x00, 8 bytes
    uint32_t value; // +0x08, 4 bytes
};

// Forward declaration of target struct pointer (array of pointers)
class TargetingManager {
public:
    void findValidTarget();
    
private:
    uint32_t m_flags;           // +0x70
    // +0x74: combined 12 bytes - stores the found target data
    TargetData m_foundTarget;   // +0x74
    // +0x80: padding? Actually 0x74+0x0c = 0x80, but we have 0x84 next
    
    // +0x84: pointer to an array of pointers to TargetData structures
    TargetData** m_targetList;  
    int m_targetCount;          // +0x88
    
    // +0x8C: padding?
    // +0x90: temporary storage for current target data being examined
    // Actually the code uses local variables, but we can represent as temp members
};

// External functions (declared elsewhere)
void resetSearch(int zero); // FUN_0074a0d0
void targetToData(TargetData* src, TargetData* dest); // FUN_00717070, converts from m_temp to local
bool isValidTargetData(TargetData* data); // FUN_00718d40, checks if data is valid

void __fastcall TargetingManager::findValidTarget() {
    // Clear the "found" flag (bit 2 of m_flags)
    m_flags &= ~0x04;
    
    int index = 0;
    if (m_targetCount != 0) {
        while (true) {
            // Copy the current target from the list into temporary storage
            // m_targetList[index] points to a TargetData (12 bytes)
            TargetData currentTarget;
            currentTarget.key = m_targetList[index]->key;   // 8 bytes at offset 0x90 from this? Actually stored at this+0x90
            currentTarget.value = m_targetList[index]->value; // 4 bytes at this+0x98
            
            resetSearch(0); // Reset some search state
            
            TargetData tempData;
            targetToData(¤tTarget, &tempData); // Convert current target to a hash/ID
            
            if (isValidTargetData(&tempData)) {
                // Found a valid target
                m_flags |= 0x04; // Set "found" flag
                m_foundTarget = tempData; // Store the valid target data (8+4 = 12 bytes)
                return;
            }
            
            index++;
            if (index >= m_targetCount) {
                return;
            }
        }
    }
    return;
}