// FUNC_NAME: PhysicsHelper::slideReflection
// Function address: 0x0050ad40
// Role: Computes a reflected/slide velocity vector given an input vector, surface normal, and physics object material properties.
// If the dot product (with axis permutation) is negative and the destination magnitude is below a threshold,
// it applies a blend using friction and restitution coefficients from the material data.

// Fields and data references:
// - physicsObj +0x24: pointer to material data structure (MaterialData*)
// - MaterialData +0x155: friction index (char) into global float table DAT_00e38088
// - MaterialData +0x156: restitution index (char) into global float table DAT_00e3809c
// - DAT_00e44598: squared magnitude threshold for slide condition
// - DAT_00e38088: float table indexed by friction index
// - DAT_00e3809c: float table indexed by restitution index

#include <cmath>

// Global data references (externs)
extern float DAT_00e44598;
extern float DAT_00e38088[];  // Friction coefficient table
extern float DAT_00e3809c[];  // Restitution coefficient table

void __fastcall slideReflection(
    float* const outVec,          // [ECX] Output vector (4 floats)
    const float* const inVec,     // [EDX] Input vector (usually velocity)
    int physicsObj,               // Pointer to a physics object with material data
    const float* const normalVec  // Surface normal (4 floats)
)
{
    float dotPerm, magSq, frictionCoeff, restitutionCoeff;
    float ndot; // standard dot product

    // Copy normal to output initially
    outVec[0] = normalVec[0];
    outVec[1] = normalVec[1];
    outVec[2] = normalVec[2];
    outVec[3] = normalVec[3]; // preserve w component (if any)

    // Compute permuted dot product: inVec[1]*outVec[2] + inVec[2]*outVec[1] + outVec[0]*inVec[0]
    // This may reflect a specific axis alignment (e.g., Z-up vs Y-up swap)
    dotPerm = inVec[1] * outVec[2] + inVec[2] * outVec[1] + outVec[0] * inVec[0];

    // Squared magnitude of output vector
    magSq = outVec[0]*outVec[0] + outVec[1]*outVec[1] + outVec[2]*outVec[2];

    // Condition: dot product negative (opposing direction) and magnitude below threshold
    if (dotPerm < 0.0f && DAT_00e44598 < magSq)
    {
        // Get material coefficients from the physics object's material data
        // physicsObj +0x24 points to a material data structure
        char* materialData = *(char**)(physicsObj + 0x24); // +0x24: pointer to material data

        // Friction coefficient (index 0x155 in materialData)
        frictionCoeff = DAT_00e38088[materialData[0x155]]; // access byte as index

        // Standard dot product for reflection computation
        ndot = outVec[0] * inVec[0] + outVec[1] * inVec[1] + outVec[2] * inVec[2];

        // Restitution coefficient (index 0x156 in materialData)
        restitutionCoeff = DAT_00e3809c[materialData[0x156]];

        // Apply reflection formula: result = lerp(projected_onto_normal, original, friction) * restitution?
        // Actually: new = friction * (original - projected) + restitution * projected
        float projX = ndot * inVec[0];
        float projY = ndot * inVec[1];
        float projZ = ndot * inVec[2];

        outVec[0] = restitutionCoeff * (outVec[0] - projX) + frictionCoeff * projX;
        outVec[1] = restitutionCoeff * (outVec[1] - projY) + frictionCoeff * projY;
        outVec[2] = restitutionCoeff * (outVec[2] - projZ) + frictionCoeff * projZ;

        // Preserve w component (original normal's w)
        outVec[3] = normalVec[3];
    }
}