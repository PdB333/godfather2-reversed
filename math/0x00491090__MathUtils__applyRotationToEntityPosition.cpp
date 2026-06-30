// FUNC_NAME: MathUtils::applyRotationToEntityPosition

// Reconstructed C++ function at 0x00491090
// Purpose: Applies a world-space rotation matrix (stored as global constants) to an input vector
// and stores the result into the entity's position field at offset 0x1D0, preserving the 4th component at +0x1DC.
// If the entity is the special camera/player object (DAT_012058e8), also calls FUN_0060ad20 to update a related sub-object.

class MathUtils {
public:
    // Note: The calling convention used by the original binary is __fastcall (ECX = inputVector, EDX = entity).
    // We keep it as a static function to match the original signature.
    static void __fastcall applyRotationToEntityPosition(float* inputVector, Entity* entity);
};

// Global rotation matrix constants (3x3 stored in row-major order, but accessed as columns)
// These are likely updated by the engine each frame to represent the camera or world rotation.
extern float gRotationMatrix[3][3]; // Addresses: 0x011f69f0-0x011f6a1c (12 floats)
extern Entity* gCameraEntity; // DAT_012058e8

void __fastcall MathUtils::applyRotationToEntityPosition(float* inputVector, Entity* entity)
{
    // entity->position is at offset 0x1D0 (3 floats)
    // entity->positionW (or rotation quaternion component) at offset 0x1DC
    float* pos = (float*)(entity + 0x1D0 / sizeof(float)); // offset 0x1D0

    // Copy input vector to the entity's position first
    pos[0] = inputVector[0];
    pos[1] = inputVector[1];
    pos[2] = inputVector[2];

    // Save the 4th component at +0x1DC (e.g., quaternion w, or a padding value)
    unsigned int savedW = *(unsigned int*)(entity + 0x1DC);

    // Apply rotation matrix (global) to the input vector
    float x = inputVector[0];
    float y = inputVector[1];
    float z = inputVector[2];

    // Matrix multiplication: new = M * old
    // Global matrix layout (addresses used):
    // M[0][0] = gRotationMatrix[0][0] at 0x011f69f0
    // M[0][1] = gRotationMatrix[0][1] at 0x011f69f4
    // M[0][2] = gRotationMatrix[0][2] at 0x011f69f8
    // M[1][0] = gRotationMatrix[1][0] at 0x011f69fc? Actually the pattern continues...
    // Better to list the exact globals to match the assembly.
    // The code uses the following global floats in order:
    // fRam011f69f0 (M00), fRam011f69f4 (M01), fRam011f69f8 (M02), fRam011f69fc (M10?)
    // But the reordering suggests it might be column-major.
    // For clarity, we'll assume a 3x3 matrix arranged as:
    // gMat[0] = {0x011f69f0, 0x011f69f4, 0x011f69f8} // first row?
    // gMat[1] = {0x011f6a00, 0x011f6a04, 0x011f6a08} // second row?
    // gMat[2] = {0x011f6a10, 0x011f6a14, 0x011f6a18} // third row?
    // The final assignment uses fVar4 (y) * _DAT_011f6a00 + fVar3 (x) * _DAT_011f69f0 + fVar5 (z) * _DAT_011f6a10 for newX.
    // This is effectively newX = y*M[0][1] + x*M[0][0] + z*M[0][2] assuming column-major?
    // To avoid confusion, we maintain the original arithmetic.

    float newX = y * gRotationMatrix[1][0] + x * gRotationMatrix[0][0] + z * gRotationMatrix[2][0]; // correspond to original expression
    float newY = y * gRotationMatrix[1][1] + x * gRotationMatrix[0][1] + z * gRotationMatrix[2][1];
    float newZ = y * gRotationMatrix[1][2] + x * gRotationMatrix[0][2] + z * gRotationMatrix[2][2];

    // Store the rotated vector into entity's position
    pos[0] = newX;
    pos[1] = newY;
    pos[2] = newZ;

    // Restore the 4th component from saved value (previously overwritten by copy)
    *(unsigned int*)(entity + 0x1DC) = savedW;

    // If this entity is the special camera/player object, update a related sub-object.
    // FUN_0060ad20 pushes the result to offset 0x14 and 0x1C0 of the entity.
    if (entity == gCameraEntity)
    {
        // Sub-object update: calls with (entity->someField at +0x14, entity->someOtherField at +0x1C0, &pos)
        // This might update the camera's target or a linked transform.
        extern void updateCameraSubobject(void* target, void* origin, float* position); // FUN_0060ad20
        updateCameraSubobject(*(void**)(entity + 0x14), *(void**)(entity + 0x1C0), pos);
    }
}