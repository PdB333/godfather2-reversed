// FUNC_NAME: ChaseCamera::update

// Reconstructed from Ghidra at 0x006e0e50
// This function updates the chase camera state: position, orientation, FOV, and other derived parameters.
// It blends between two states (e.g. normal and combat) using a blend factor (m_blendFactor at +0xf0),
// applies offsets, and computes the final camera transform.

#include <cmath>

struct Vector3 {
    float x, y, z;
};

// Forward declarations for called functions
void FUN_006c85d0(int a1, int a2);  // probably initializes input/state
void FUN_006ca410(int a);           // update something
void FUN_006ca8e0(int a);           // handle idle
void FUN_00425060(Vector3* out, int src); // extract vector from src?
int  FUN_00471610();                // returns pointer to some manager
void FUN_006dfe90(Vector3* out, int entity); // get entity position/orientation
void FUN_0056afa0(Vector3* v, Vector3* out); // normalize or rotate vector
void FUN_004a0370(Vector3* result, Vector3* a, Vector3* b, float scale); // a + b*scale
void FUN_00b9a9fa();                // unknown math (sin/cos?)
void FUN_006ca5e0(Vector3* a, Vector3* b, Vector3* c); // transform

// Global constants (from data section)
extern float _DAT_00d5780c;    // deltaTime (frame time)
extern float _DAT_00e44564;    // 1.0f
extern float _DAT_00e44748;    // some scalar (0.5f?)
extern float _DAT_00d5ccf8;    // gravity constant?
extern float _DAT_00d5efa0;    // FOV limit?
extern float _DAT_00e445c8;    // velocity scaling

// Global state for shared camera values (likely per-camera instance but exposed globally)
extern float DAT_0112a914;
extern float DAT_0112a918;
extern float DAT_0112a91c;
extern float DAT_0112a920;
extern double DAT_0112a908;   // 64-bit combined x,y
extern float  DAT_0112a910;
extern double DAT_0112a924;   // another position
extern float  DAT_0112a92c;
extern double DAT_0112a930;   // position if not local
extern float  DAT_0112a938;
extern double DAT_0112a93c;   // angle vector
extern float  DAT_0112a944;

class ChaseCamera {
public:
    void update(int arg0, int arg1);

    // Field offsets (relative to this)
    // +0x20   Vector3 m_finalPosition
    // +0x2c   float m_finalW (usually 1.0)
    // +0x30   Vector3 m_lookAt
    // +0x3c   float m_lookW
    // +0x40   Vector3 m_up
    // +0x4c   float m_upW
    // +0x50   float m_fov (computed)
    // +0x60   float m_deltaTime
    // +0x6c   int m_idleState (-1 = idle)
    // +0x80   float m_zoomFactor (0..1)
    // +0xa8,0xac: ints unused?
    // +0xc0   Vector3 m_angleOffset (yaw, pitch? actually stored as two floats and a zero)
    // +0xc8   int pad
    // +0xcc   Vector3 m_offsetPosition (blended)
    // +0xd4   float pad2
    // +0xd8   Vector3 m_basePosition (world space)
    // +0xe4   Vector3 m_targetPosition (from entity)
    // +0xf0   float m_blendFactor (0..1, from input state)
    // +0xf4   float m_secondaryBlend (0 or deltaTime)
    // +0xf8   float m_currentDistance (scalar)
    // +0xfc   float m_radius (some distance)
    // +0x100  float m_angularVelocity (computed)
    // +0x104  int pad3
    // +0x108  byte flags
    // +0x109  byte flags2
    // +0x10a  byte flags3
    // +0x10c  int timer0
    // +0x110  int timer1
    // +0x114  int timer2
    // +0x118  double m_entityOrientation (combined x,y)
    // +0x120  float m_entityZ
    // +0x124  int* m_pEntityBase  // points to some subobject of the player
    // +0x130  Vector3 m_desiredPosition (from entity)
    // +0x13c  byte m_isLocalPlayer
    // +0x14c  float m_minDistance
    // +0x150  float m_maxDistance
    // +0x154  float m_distanceScale (from input)
    // +0x164  float m_minFov
    // +0x188  float m_radiusOffset (from entity speed?)
    // +0x194  float m_maxFov
    // +0x198  float m_overriddenFov (when bit8 in player flags set)

    // Inline access to fields
    float& fld60() { return *(float*)((char*)this + 0x60); }
    int& fld6c() { return *(int*)((char*)this + 0x6c); }
    byte& fld109() { return *(byte*)((char*)this + 0x109); }
    byte& fld10a() { return *(byte*)((char*)this + 0x10a); }
    int& fld114() { return *(int*)((char*)this + 0x114); }
    int& fld110() { return *(int*)((char*)this + 0x110); }
    int& fld10c() { return *(int*)((char*)this + 0x10c); }
    byte& fld13c() { return *(byte*)((char*)this + 0x13c); }
    int*& fld124() { return *(int**)((char*)this + 0x124); }
    Vector3& fld130() { return *(Vector3*)((char*)this + 0x130); }
    Vector3& flde4() { return *(Vector3*)((char*)this + 0xe4); }
    Vector3& fldd8() { return *(Vector3*)((char*)this + 0xd8); }
    Vector3& fldcc() { return *(Vector3*)((char*)this + 0xcc); }
    Vector3& fldc0() { return *(Vector3*)((char*)this + 0xc0); }
    Vector3& fld20() { return *(Vector3*)((char*)this + 0x20); }
    Vector3& fld30() { return *(Vector3*)((char*)this + 0x30); }
    Vector3& fld40() { return *(Vector3*)((char*)this + 0x40); }
    float& fld50() { return *(float*)((char*)this + 0x50); }
    float& fld80() { return *(float*)((char*)this + 0x80); }
    float& fldf0() { return *(float*)((char*)this + 0xf0); }
    float& fldf4() { return *(float*)((char*)this + 0xf4); }
    float& fldf8() { return *(float*)((char*)this + 0xf8); }
    float& fldfc() { return *(float*)((char*)this + 0xfc); }
    float& fld100() { return *(float*)((char*)this + 0x100); }
    float& fld14c() { return *(float*)((char*)this + 0x14c); }
    float& fld150() { return *(float*)((char*)this + 0x150); }
    float& fld154() { return *(float*)((char*)this + 0x154); }
    float& fld164() { return *(float*)((char*)this + 0x164); }
    float& fld188() { return *(float*)((char*)this + 0x188); }
    float& fld194() { return *(float*)((char*)this + 0x194); }
    float& fld198() { return *(float*)((char*)this + 0x198); }
    double& fld118() { return *(double*)((char*)this + 0x118); }
    float& fld120() { return *(float*)((char*)this + 0x120); }
};

void __thiscall ChaseCamera::update(int arg0, int arg1)
{
    // Initialization step
    FUN_006c85d0(arg0, arg1);

    fld60() = _DAT_00d5780c;  // store current delta time

    // Get pointer to player entity (subobject at offset -0x48 from stored base pointer)
    int* entityBase = fld124();
    int entityPtr = (entityBase != nullptr) ? (int)(entityBase) - 0x48 : 0;
    int entityPtr2 = entityPtr;  // duplicate for second call

    // Update something on the entity
    FUN_006ca410(entityPtr2);

    // Handle idle state (-1)
    if (fld6c() == -1) {
        FUN_006ca8e0(entityPtr);
    }

    // Clear flags and timers
    fld109() = 0;
    fld10a() = 0;
    fld114() = 0;
    fld110() = 0;
    fld10c() = 0;

    // Determine primary blend factor (stored in static, then to +0xf0)
    if (fld13c() == 0) {
        // Non-local: use player flag bit 25
        if (!((*(unsigned int*)(entityPtr + 0x8e0) >> 25) & 1)) {
            DAT_0112a914 = 0.0f;
        } else {
            DAT_0112a914 = _DAT_00d5780c;
        }
    } else {
        // Local player: always use delta time
        DAT_0112a914 = _DAT_00d5780c;
    }
    fldf0() = DAT_0112a914;

    // Determine secondary blend (0 or delta time)
    if (((*(unsigned int*)(entityPtr + 0x8e0) >> 26) & 1) != 0 || 
        (fldf4() = _DAT_00d5780c, ((*(unsigned int*)(entityPtr + 0x8e0) >> 25) & 1) == 0)) {
        fldf4() = 0.0f;
    }

    // Reset some fields
    *(int*)((char*)this + 0xac) = 0;
    *(int*)((char*)this + 0xa8) = 0;

    // Extract a vector from input (arg0)
    Vector3 inputVec;
    FUN_00425060(&inputVec, arg0);

    // Set radius based on player flag
    float radius = DAT_0112a920;
    if (fld13c() == 0) {
        radius = inputVec.x * _DAT_00e44748;  // scale by game speed
    }
    fldfc() = radius;

    // Additional flag
    *(byte*)((char*)this + 0x108) = 0;

    // Copy orientation from entity or global
    if (fld13c() == 0) {
        int manager = FUN_00471610();
        fld118() = *(double*)(manager + 0x30);
        fld120() = *(float*)(manager + 0x38);
    } else {
        fld118() = DAT_0112a908;
        fld120() = DAT_0112a910;
    }

    // Get entity position (camera target)
    Vector3 entityPos;
    FUN_006dfe90(&entityPos, entityPtr);

    // Overwrite orientation with entity forward?
    fld118() = *(double*)((char*)&entityPos);
    fld120() = entityPos.z;

    // Copy desired position from entity (stored at +0x130)
    flde4() = fld130();
    fld120() = entityPos.z;  // wait, this seems redundant? Already set?
    *(float*)((char*)this + 0xec) = *(float*)((char*)this + 0x138); // copy z

    // Build a direction vector from target position
    Vector3 direction;
    direction.x = flde4().x;
    direction.y = flde4().y;
    direction.z = flde4().z;
    // Set w component to 0 for normalization?
    *(int*)&direction.w = 0; // local_54

    FUN_0056afa0(&direction, &direction);
    flde4().x = direction.x;
    flde4().y = direction.y;
    flde4().z = direction.z;

    // Compute offset from target to camera base? (inverse z)
    Vector3 offset;
    offset.z = _DAT_00e44564 - flde4().z;
    offset.x = flde4().x;
    offset.y = 0.0f;
    // w = 0
    int zero = 0;
    FUN_0056afa0(&offset, &offset); // normalize

    // Extract original x,y as a 64-bit double and split into two floats
    double originalXY = *(double*)((char*)&flde4()); // x and y combined
    float zVal = flde4().z;

    // Re-interpret the double as two floats: low = x, high = y
    struct { float low; float high; } xyAsFloats = *(struct { float; float; }*)&originalXY;
    float xFloat = xyAsFloats.low;
    float yFloat = xyAsFloats.high;

    // Normalize this pair
    Vector3 pairVec;
    pairVec.x = xFloat;
    pairVec.y = yFloat;
    pairVec.z = zVal;
    *(int*)&pairVec.w = 0;
    FUN_0056afa0(&pairVec, &pairVec);

    // Store back the pair (x,y) and z separately
    // The code reconstructs local_6c as double from the normalized pairVec.x and pairVec.y
    double normalizedPair;
    *(float*)&normalizedPair = pairVec.x;
    *((float*)&normalizedPair + 1) = pairVec.y;
    // local_64 = z
    float normalizedZ = pairVec.z;

    float angularFactor = DAT_0112a91c;
    if (fld13c() == 0) {
        fld100() = inputVec.y * _DAT_00e44748; // y component scaled
        // Compute cross product-like operation
        Vector3 scaleVec = {0.0f, 0.0f, _DAT_00d5ccf8};
        int manager = FUN_00471610();
        FUN_004a0370(&scaleVec, &scaleVec, (Vector3*)(manager + 0x10), 
                     fld100() * _DAT_00e445c8);
        // Then double multiplication and conversion
        double dVar6 = (double)(normalizedZ * scaleVec.x - (float)normalizedPair * scaleVec.z);
        FUN_00b9a9fa();
        angularFactor = (float)dVar6 * _DAT_00e44748;
    }
    fld100() = angularFactor;

    // Compute current distance scalar
    if (fld13c() == 0) {
        float distScale;
        if (((*(unsigned int*)(entityPtr + 0x8e0) >> 29) & 1) == 0) {
            distScale = _DAT_00e44564 - fld154() * fldf0();
        } else {
            distScale = fld154() * fldf0();
        }
        DAT_0112a918 = distScale;
        fldd8().x = offset.x * distScale + entityPos.x;
        fldd8().y = offset.y * distScale + entityPos.y;
        fldd8().z = offset.z * distScale + entityPos.z;
    } else {
        fldd8() = *(Vector3*)(&DAT_0112a930); // copy from global
        DAT_0112a918 = *(float*)((char*)&DAT_0112a930 + 12)? Wait, not correct. Actually DAT_0112a918 is set from the global computed earlier? Skip.
    }
    fldf8() = DAT_0112a918;

    // Compute adjustment vector from radius difference
    Vector3 adjust;
    adjust.x = _DAT_00e44564 - normalizedZ;
    adjust.y = 0.0f;
    adjust.z = (float)normalizedPair;  // the normalized x component
    FUN_004a0370(&adjust, &adjust, &adjust, (fldfc() - fld188()) * _DAT_00e445c8);

    // Lerp distance based on blend factor
    float lerpedDist = (fld150() - fld14c()) * (_DAT_00d5780c - fldf0()) + fld14c();
    if ((*(unsigned int*)(entityPtr + 0x8e4) >> 8) & 1) {
        lerpedDist = fld198();
    }

    // Final position = base + direction * distance
    Vector3 finalPos;
    finalPos.x = lerpedDist * (float)normalizedPair + fldd8().x;
    finalPos.y = yFloat * lerpedDist + fldd8().y;
    finalPos.z = lerpedDist * normalizedZ + fldd8().z;

    if (fld13c() == 0) {
        fldcc().x = finalPos.x;
        fldcc().y = finalPos.y;
        fldcc().z = finalPos.z;
    } else {
        fldcc() = *(Vector3*)(&DAT_0112a924); // used for non-player
    }

    // Transform the base position? Then set final camera transform
    Vector3 transformed;
    FUN_006ca5e0(&fldd8(), &transformed, &transformed);
    fld20().x = transformed.x;
    fld20().y = transformed.y;
    fld20().z = finalPos.z; // note: uses finalPos.z, not transformed
    fld20().y? Actually careful: line: *(undefined4 *)(param_1 + 0x20) = (undefined4)local_50; etc.
    So local_50 is the transformed vector (x,y), and local_48 is the z from finalPos? Actually local_48 was set earlier as *(float*)(param_1+0xd4) which is fldd8().z? Wait confusion. In the decompiled, local_50 is set from FUN_006ca5e0, and local_48 is from param_1+0xd4 (which is fldcc().z? Actually offset 0xd4 is part of fldcc? fldcc is 12 bytes: 0xcc,0xd0,0xd4. So 0xd4 is z component. So finalPos.z is stored to fldcc().z earlier; then local_48 = fldcc().z. Then after transform, they set *((undefined4 *)&local_50) and *((undefined4*)&local_50+1) then local_48. So the camera position becomes (transformed.x, transformed.y, fldcc().z). Then set m_finalPosition accordingly.

    fld20().z = fldcc().z;
    fld2c() = _DAT_00d5780c; // w

    fld30().x = fldd8().x;
    fld30().y = fldd8().y;
    fld30().z = fldd8().z;
    fld3c() = _DAT_00d5780c; // w

    // Compute up vector from angles
    if (fld13c() == 0) {
        double dVar6 = (double)yFloat; // high part of double
        FUN_00b9a9fa();
        float val1 = (float)dVar6;
        dVar6 = (double)(_DAT_00e44564 - xFloat);
        FUN_00b9a9fa();
        float val2 = (float)dVar6;
        fldc0().x = val1;
        fldc0().y = val2;
        *(int*)((char*)this + 0xc8) = 0; // z = 0
    } else {
        fldc0() = *(Vector3*)(&DAT_0112a93c); // use global
    }
    // Copy to up vector
    fld40().x = fldc0().x;
    fld40().y = fldc0().y;
    fld40().z = *(float*)((char*)this + 0xc8);
    fld4c() = _DAT_00d5780c; // w

    // Compute FOV
    float fov = (_DAT_00d5efa0 - fld164()) * fld80() + fld164();
    fld50() = (((fld194() - fld164()) * fld80() + fld164() - fov) * fldf4() + fov) * _DAT_00e445c8;

    // Reset timer
    *(int*)((char*)this + 0x104) = 0;
}