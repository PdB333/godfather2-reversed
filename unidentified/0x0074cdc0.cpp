// FUN_0074cdc0: Player::processVehicleContact
// Reconstructed from Ghidra decompilation of The Godfather 2 (x86, EARS engine)
// Handles player-vehicle collision response and flag updates
// Offsets documented based on gameplay analysis

class Player {
public:
    // Fields used in this function
    void* mVehicle;        // +0x88: pointer to the current vehicle (HavokWheeledVehicle)
    void* mRigidBody;      // +0x8C: pointer to Havok hkpRigidBody? (if 0x48 sentinel, no collision)
                           //   Actual body may be at (mRigidBody - 0x48) due to engine's header offset
};

class HavokWheeledVehicle {
    uint32_t mFlags;       // +0x1F58: bitfield flags (bit 0x20 = ?; bit 0x10 = ?)
};

// Forward declarations of called functions
namespace GameMath {
    // Returns non-zero if the 4-float data (e.g., impulse/quaternion) is significant
    bool isForceSignificant(Vector4* force);
}

namespace AudioManager {
    void playCollisionSound(void* soundManager); // DAT_01131070 is likely g_soundManager
}

namespace CollisionManager {
    void applyCollisionResponse(int baseOffset); // FUN_0074ca40
}

// Note: Vector4 is 16 bytes (4 floats)
struct Vector4 {
    float x, y, z, w;
};

void __fastcall Player::processVehicleContact(Player* this) {
    int baseOffset; // iVar1: adjusted pointer to actual Havok body
    Vector4 collisionData; // local_10..local_4: read from body +0x84 (i.e., this->mRigidBody + 0x3C)

    // Guard: both vehicle and rigiBody must exist, and rigiBody must not be sentinel 0x48
    if (this->mVehicle != nullptr && 
        this->mRigidBody != nullptr && 
        (int)this->mRigidBody != 0x48) {

        // Compute the base address of the Havok rigid body structure.
        // The pointer stored in mRigidBody points into a larger allocation at offset 0x48.
        if (this->mRigidBody == nullptr) {
            baseOffset = 0; // Should not occur because of preceding check
        } else {
            baseOffset = (int)this->mRigidBody - 0x48;
        }

        // Read collision-related data (e.g., contact impulse or velocity change)
        // from the Havok body at offsets +0x84, +0x88, +0x8C, +0x90.
        collisionData = *(Vector4*)(baseOffset + 0x84);

        // Check if the data indicates a significant collision (non-zero force)
        if (GameMath::isForceSignificant(&collisionData)) {
            // Play collision sound through the global sound manager
            if (this->mVehicle != nullptr) {
                AudioManager::playCollisionSound((void*)DAT_01131070);
            }
            // Apply the collision response to the vehicle/body
            CollisionManager::applyCollisionResponse(baseOffset);
        }

        // Update the vehicle's flag word at +0x1F58:
        // set bit 5 (0x20) and clear bit 4 (0x10)
        HavokWheeledVehicle* vehicle = (HavokWheeledVehicle*)this->mVehicle;
        vehicle->mFlags |= 0x20;
        vehicle->mFlags &= ~0x10;
    }
}