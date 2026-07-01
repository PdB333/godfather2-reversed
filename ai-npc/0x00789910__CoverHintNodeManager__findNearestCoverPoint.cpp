// FUNC_NAME: CoverHintNodeManager::findNearestCoverPoint
// Function address: 0x00789910
// Role: Finds the closest valid cover node position to a given input point, storing result in output.
// The manager holds 2 cover slots (each with 3 uint32 handle components) at this+0xAC (12 bytes each).
// Validity check: for slot 0 always considered; for slot 1, only if all three handle components (masked) are non-zero.
// Uses global constants: kMaxDistSq (initial best distance), kFlipThreshold (comparison constant?), kValidityMask (check bits).
// Converts handle to world position via getEntityPosition.

#define kMaxDistSq (3.0e38f)          // DAT_00d5ccf8
#define kFloatZero (0.0f)             // DAT_00e44598 (probably zero for non-zero check)
#define kValidityMask (0xFFFFFFFF)    // DAT_00e44680 (full mask – adjust if game uses specific bits)

// Forward declarations of called functions (from elsewhere in the binary)
uint getSceneTime(void);                             // FUN_00471610
void getPositionFromHandle(uint sceneTime, uint32 handle[3], float outPos[3]); // FUN_0056b420

class CoverHintNodeManager {
public:
    // Array of two cover node slots. Each slot is 3 uint32 members (handle ID, flags, type?).
    // Offsets: slot0 at this+0xAC, slot1 at this+0xB8 (12 bytes stride)
    // Layout: [member0, member1, member2] = [m_handlePart0, m_handlePart1, m_handlePart2]
    // Our code accesses them via a pointer that starts at the third member of the first slot.
    
    // Member variables (hypothetical, to document offsets)
    // uint32 m_coverSlot0[3];   // +0xAC, +0xB0, +0xB4
    // uint32 m_coverSlot1[3];   // +0xB8, +0xBC, +0xC0
    // Note: The array actually starts at +0xAC, but the code initializes a pointer at +0xB4 (third member of slot0).
    
    void findNearestCoverPoint(const float inputPos[3], float outPos[3]) __thiscall;
};

void __thiscall CoverHintNodeManager::findNearestCoverPoint(const float inputPos[3], float outPos[3]) {
    // Get current scene time (used for handle-to-position conversion)
    uint sceneTime = getSceneTime();
    
    float bestDistSq = kMaxDistSq;
    
    // Pointer to third member of first slot (offset this+0xB4)
    uint32* slotThirdPtr = reinterpret_cast<uint32*>(reinterpret_cast<char*>(this) + 0xB4);
    
    for (uint32 slotIdx = 0; slotIdx < 2; ++slotIdx) {
        // Extract three uint32 components of the slot (from positions relative to slotThirdPtr)
        uint32 handlePart0 = slotThirdPtr[-2];  // +0xAC for slot0, +0xB8 for slot1
        uint32 handlePart1 = slotThirdPtr[-1];  // +0xB0 / +0xBC
        uint32 handlePart2 = slotThirdPtr[0];   // +0xB4 / +0xC0
        
        // Validity check: slot0 always valid; for slot1, require all three parts to have non-zero masked bits
        if (slotIdx == 0 ||
            (kFloatZero < static_cast<float>(handlePart0 & kValidityMask) &&
             kFloatZero < static_cast<float>(handlePart1 & kValidityMask) &&
             kFloatZero < static_cast<float>(handlePart2 & kValidityMask)))
        {
            // Convert handle to world position using current scene time
            uint32 handle[3] = { handlePart0, handlePart1, handlePart2 };
            float slotPos[3];
            getPositionFromHandle(sceneTime, handle, slotPos);
            
            // Compute squared distance from input position
            float dx = inputPos[0] - slotPos[0];
            float dy = inputPos[1] - slotPos[1];
            float dz = inputPos[2] - slotPos[2];
            float distSq = dx*dx + dy*dy + dz*dz;
            
            // Update best if closer
            if (distSq < bestDistSq) {
                outPos[0] = slotPos[0];
                outPos[1] = slotPos[1];
                outPos[2] = slotPos[2];
                bestDistSq = distSq;
            }
        }
        
        // Advance to next slot (skip 3 uint32s = 12 bytes)
        slotThirdPtr += 3;
    }
}