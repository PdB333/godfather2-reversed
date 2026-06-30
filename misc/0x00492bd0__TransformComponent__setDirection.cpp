// FUNC_NAME: TransformComponent::setDirection

#include <cstdint>

// External rotation matrix (3x3 stored as 12 floats, but only 9 used in this function)
extern const float gRotationMatrix0[12]; // Starting at 0x011f69f0

// Forward declaration of the function called when this is the active object
void updateActiveTransform(uint32_t unk0x14, uint32_t unk0x1c0, const float* vectorPtr);

// Structure representing the object's transform fields (partial)
struct TransformComponent {
    // +0x14: unknown pointer/matrix
    uint32_t field_0x14;
    // +0x1c0: unknown (maybe some flag or matrix)
    uint32_t field_0x1c0;
    // +0x1d0: homogeneous direction vector (x,y,z,w) - w is preserved
    float directionX;
    float directionY;
    float directionZ;
    float directionW;
};

// Global pointer to the active transform (e.g. current camera)
extern TransformComponent* gActiveTransform; // DAT_012058e8

void __fastcall TransformComponent::setDirection(const float* inputVec, TransformComponent* thisPtr)
{
    // Copy input vector (x,y,z) into the object's direction
    thisPtr->directionX = inputVec[0];
    thisPtr->directionY = inputVec[1];
    thisPtr->directionZ = inputVec[2];

    // Save the original components for matrix multiplication
    float origX = thisPtr->directionX;
    float origY = thisPtr->directionY;
    float origZ = thisPtr->directionZ;
    float originalW = thisPtr->directionW; // Preserve w component

    // Apply rotation using global matrix gRotationMatrix0 (column-major? see usage)
    // Matrix layout: gRotationMatrix0[0..3] are row0, [4..7] row1, [8..11] row2? Actually used as:
    // newX = origX*gRot[0] + origY*gRot[4] + origZ*gRot[8]
    // newY = origX*gRot[1] + origY*gRot[5] + origZ*gRot[9]
    // newZ = origX*gRot[2] + origY*gRot[6] + origZ*gRot[10]
    // This corresponds to multiplying the transpose of the stored matrix.
    float newX = origY * gRotationMatrix0[4] + origX * gRotationMatrix0[0] + origZ * gRotationMatrix0[8];
    float newY = origY * gRotationMatrix0[5] + origX * gRotationMatrix0[1] + origZ * gRotationMatrix0[9];
    float newZ = origY * gRotationMatrix0[6] + origX * gRotationMatrix0[2] + origZ * gRotationMatrix0[10];

    // Write back the rotated direction
    thisPtr->directionX = newX;
    thisPtr->directionY = newY;
    thisPtr->directionZ = newZ;
    // Restore the original w component
    thisPtr->directionW = originalW;

    // If this transform is the active one (e.g. primary camera), update related rendering data
    if (gActiveTransform == thisPtr) {
        updateActiveTransform(thisPtr->field_0x14, thisPtr->field_0x1c0, &thisPtr->directionX);
    }
}