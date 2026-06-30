// FUNC_NAME: EntityProximityComponent::onMessage
// Address: 0x00764f20
// Handles proximity events (messageId == 10) and sound triggers (messageId == 11)

class EntityProximityComponent {
public:
    // Processes messages; returns 1 on success
    int onMessage(void* arg2, void* arg3, void* arg4, int messageId, void* arg6);
};

int EntityProximityComponent::onMessage(void* arg2, void* arg3, void* arg4, int messageId, void* arg6) {
    // Offsets relative to this:
    // +0x54 : float m_proximityThresholdSq   (squared distance threshold)
    // +0x58 : float m_positionX
    // +0x5c : float m_positionY
    // +0x60 : float m_positionZ
    // +0x6c : int   m_flags (bit 0 = proximity triggered, bit 3 = sound played)
    float& thresholdSq = *(float*)((int)this + 0x54);
    float& posX = *(float*)((int)this + 0x58);
    float& posY = *(float*)((int)this + 0x5c);
    float& posZ = *(float*)((int)this + 0x60);
    int& flags = *(int*)((int)this + 0x6c);

    if (messageId == 10) {
        // Proximity check: only if flag bit 0 is not set
        if ((flags & 1) == 0) {
            int* entityPosPtr = (int*)FUN_00471610(); // Get reference point (e.g., player)
            float dx = *(float*)(entityPosPtr + 0x30) - posX;
            float dy = *(float*)(entityPosPtr + 0x34) - posY;
            float dz = *(float*)(entityPosPtr + 0x38) - posZ;
            float distSq = dx*dx + dy*dy + dz*dz;
            if (distSq > thresholdSq) {
                return 1; // Not in range yet
            }
            // Within range: set flag to prevent re-triggering
            flags |= 1;
            return 1;
        }
        // Already triggered, just return success
        return 1;
    } else if (messageId == 11) {
        // Trigger sound effect if flag bit 3 is not set
        if ((flags & (1 << 3)) == 0) {
            FUN_004abdd0(0x20); // Play sound/animation ID 0x20
        }
        return 1;
    } else {
        // Default handling for other message IDs
        return FUN_004ac700(arg2, arg3, arg4, messageId, arg6);
    }
}