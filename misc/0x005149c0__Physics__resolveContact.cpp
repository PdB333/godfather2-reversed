// FUNC_NAME: Physics::resolveContact
// Address: 0x005149c0
// Role: Core collision/contact resolution dispatcher for EARS physics engine.
// Processes two input vectors (min/max or point/velocity), applies clamping,
// and delegates to either an accumulator update or a contact solver based on a flag.

struct Vec4 {
    float x, y, z, w;
};

// Global constants
extern const Vec4 g_clampBound;   // DAT_00e38190
extern const float g_overrideW;   // DAT_00e2eb58
extern bool g_debugOverride;      // DAT_012054fe
extern float g_physicsTimer;      // DAT_01219240
extern const float g_timeDelta;   // DAT_00e2b1a4

// Internal helper functions
void PhysicsFrameAccumulate();                                         // FUN_00514610
bool ContactSolverTest(Vec4* contactData, uint flags, int mode);       // FUN_00514c40
void ResolveAndExit();                                                 // FUN_00515460

void __fastcall Physics::resolveContact(
    Vec4* pVecA,        // EAX: primary vector (e.g., position, velocity)
    Vec4* pVecB,        // ECX: secondary vector (unused in this function)
    uint flags,         // EDX: flag bits (bit0 = 0: accumulate; bit0 = 1: test resolve)
    Vec4* pBoundMin,    // Stack param: bounding volume min (copied locally)
    Vec4* pBoundMax,    // Stack param: bounding volume max (copied locally)
    Vec4* pBoundOther,  // Stack param: other volume/point (clamped via minps)
    float scalar1,      // Stack param: additional scalar (stored at x)
    float scalar2       // Stack param: additional scalar (stored at w)
)
{
    // Copy input bounding vectors
    Vec4 localMin = *pBoundMin;
    Vec4 localMax = *pBoundMax;

    // Clamp pBoundOther components to be at most g_clampBound (minps)
    Vec4 clampedOther;
    clampedOther.x = min(pBoundOther->x, g_clampBound.x);
    clampedOther.y = min(pBoundOther->y, g_clampBound.y);
    clampedOther.z = min(pBoundOther->z, g_clampBound.z);
    clampedOther.w = min(pBoundOther->w, g_clampBound.w);

    // Clamp pVecA components to be at least g_clampBound (maxps)
    Vec4 clampedA;
    clampedA.x = max(pVecA->x, g_clampBound.x);
    clampedA.y = max(pVecA->y, g_clampBound.y);
    clampedA.z = max(pVecA->z, g_clampBound.z);
    clampedA.w = max(pVecA->w, g_clampBound.w);

    // Build local scalar pack from inputs
    Vec4 localScalars;
    localScalars.x = scalar1;
    localScalars.y = pVecA->w;          // offset +0x0c of pVecA
    localScalars.z = pBoundOther->w;    // offset +0x0c of pBoundOther
    localScalars.w = scalar2;

    // Debug override: zero out localMax and set specific scalar values
    if (g_debugOverride) {
        localMax.x = 0.0f;
        localMax.y = 0.0f;
        localMax.z = 0.0f;
        localMax.w = 0.0f;
        localScalars.z = g_overrideW;
        localScalars.w = 0.0f;
    }

    // Decision based on bit 0 of flags
    if ((flags & 1) == 0) {
        PhysicsFrameAccumulate();
        g_physicsTimer += g_timeDelta;
    } else {
        bool contactResolved = ContactSolverTest(&localMin, flags, 0);
        if (contactResolved) {
            ResolveAndExit();
            // return implied after call
        }
    }
}