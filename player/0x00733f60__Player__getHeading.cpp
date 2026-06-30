// FUNC_NAME: Player::getHeading
// Function address: 0x00733f60
// Role: Returns the player's heading (yaw) angle in radians. Caches the value and recalculates if
//       the dirty flag (bit 3 of m_flags at +0x1f58) is set. Recalculation only occurs if the
//       current state (+0x1c78) is not kState_None (0) and not kState_Dead (0x48).

// External helper functions (likely from math utilities)
// Returns a pointer to a transform data structure (e.g., world matrix)
int __fastcall getEntityTransformData();

// Extract yaw angle from a quaternion or matrix at the given offset
float __fastcall getYawFromTransform(void* transformPtr);

// Extract pitch angle from the same transform
float __fastcall getPitchFromTransform(void* transformPtr);

class Player {
public:
    // Offsets relative to this
    // +0x1f58: uint32 m_flags; bit 3 = dirty heading/pitch
    // +0x1c78: int32 m_state; 0 = idle? 0x48 = dead?
    // +0x204c: float m_heading;
    // +0x2050: float m_pitch;

    float getHeading();
};

float Player::getHeading() {
    uint32* flagsPtr = reinterpret_cast<uint32*>(reinterpret_cast<uint8*>(this) + 0x1f58);
    uint32 flags = *flagsPtr;

    if (flags & 0x8) { // Bit 3: dirty heading flag is set
        // Clear the dirty flag
        *flagsPtr = flags & ~0x8;

        int* statePtr = reinterpret_cast<int*>(reinterpret_cast<uint8*>(this) + 0x1c78);
        int state = *statePtr;

        // Only recalculate if the player is not in an invalid state (0 or 0x48)
        if (state != 0 && state != 0x48) {
            // Get a pointer to the player's transform data (e.g., world matrix)
            int transformDataPtr = getEntityTransformData();

            // The transform data likely contains a rotation matrix or quaternion at +0x30
            void* rotationData = reinterpret_cast<void*>(transformDataPtr + 0x30);

            // Extract heading (yaw) and pitch from the rotation
            float heading = getYawFromTransform(rotationData);
            float pitch = getPitchFromTransform(rotationData);

            // Cache the computed values
            *reinterpret_cast<float*>(reinterpret_cast<uint8*>(this) + 0x204c) = heading;
            *reinterpret_cast<float*>(reinterpret_cast<uint8*>(this) + 0x2050) = pitch;
        }
    }

    // Return the cached heading
    return *reinterpret_cast<float*>(reinterpret_cast<uint8*>(this) + 0x204c);
}