// FUNC_NAME: CharacterMovement::UpdateSteering
// Address: 0x004f8aa0
// This function updates character steering towards a target position/velocity.
// It applies forces, checks animation state, and handles angular damping.

// Forward declarations
class Entity; // Base game object
class IActionSystem; // Interface for checking actions (0xd80c71d2, 0x4f3368d0)
class MovementState; // Stores movement data at offset 0x24 from this
class ObjectFactory; // Factory for spawning objects (FUN_004f95f0)

// Global constants
extern const float kMinSpeedSq;      // DAT_00e2cbe0
extern const float kSpeedNormalizer; // DAT_00e2b1a4
extern const float kSteerThreshold;  // DAT_00e2e210
extern const float kMinRotation;     // DAT_00e2b05c
extern const uint kRotationMask;     // DAT_00e44680
extern const Vector4 kGravity;       // DAT_00e44564
extern void (*gCheckSteerCallback)(Entity*); // DAT_01206688 (nullable)

// Thread-local storage: offset 0x2c gives pointer to a struct with pointer to transform
extern uint* __fs_getTLS(); // approximates unaff_FS_OFFSET + 0x2c

// Function prototypes
ObjectFactory* GetObjectFactory(); // returns DAT_012234c4 (pointer to singleton)
void QuaternionMultiplyAngularVelocity(Vector4* out, const Vector4* angular); // FUN_0066d1d0

class CharacterMovement {
public:
    // +0x10: offset into transform matrix (index into a buffer)
    int transformIndex;
    // +0x24: pointer to MovementState
    MovementState* movementState;
    // +0x04: pointer to some other object (maybe skeleton)
    int* skeletonRef; // +0x20 holds an object pointer

    void UpdateSteering(Entity* entity, const Vector4* target, float dt, uint param4, uint param5);
};

// MovementState structure (allocated at offset 0x24 from CharacterMovement)
struct MovementState {
    // +0x00: flags (bit0 = check action flag, bit2 = use custom velocity, bit3 = scale custom)
    uint flags;
    // +0x04: (unused?)
    // +0x0C: bool? (0xe offset = actionID maybe)
    int actionID;     // +0x38 (0xe * 4)
    // +0x10: speed? (0xf offset)
    float speed;      // +0x3C
    // +0x14: custom velocity components (0x12-0x15 offsets)
    float customVx;   // +0x48
    float customVy;   // +0x4C
    float customVz;   // +0x50
    float customVw;   // +0x54
    // +0x1C: (0x16 offset) scale factor for customVw
    float customScale; // +0x58
    // +0x28: (0x28 offset) something
    float steerFactor; // +0x2C
    // +0x30: (0x30 offset) yaw rate limit?
    uint yawRateLimit; // +0x30
    // +0x34: pitch rate limit?
    uint pitchRateLimit; // +0x34
    // +0x40: (0x40 offset) maybe secondary target?
    int secondaryTarget; // +0x40
    // +0x44: secondary speed?
    float secondarySpeed; // +0x44
};

void CharacterMovement::UpdateSteering(Entity* entity, const Vector4* target, float dt, uint param4, uint param5) {
    // Get the current orientation (quaternion) from the global transform buffer
    // TLS pointer at FS:0x2c -> (some thread context) -> +8 -> +0x80 is base of transform buffer
    float* basePtr = *(float**)(*(int*)(*(int*)(__fs_getTLS() + 0x2c) + 8) + 0x80);
    float* orientation = basePtr + this->transformIndex; // +0x10 is index*sizeof(Vector4)?
    Vector3 currentPos; // fetched as 4 floats? Actually orientation is a quaternion? The code acts as 4D vector.
    currentPos.x = orientation[0];
    currentPos.y = orientation[1];
    currentPos.z = orientation[2];
    currentPos.w = orientation[3];

    // Compute difference vector to target
    Vector3 diff;
    diff.x = target->x - currentPos.x;
    diff.y = target->y - currentPos.y;
    diff.z = target->z - currentPos.z;
    diff.w = target->w - currentPos.w;

    // Normalize difference if length exceeds threshold
    float lenSq = diff.x*diff.x + diff.y*diff.y + diff.z*diff.z;
    if (lenSq > kMinSpeedSq) {
        float invLen = kSpeedNormalizer / sqrtf(lenSq);
        diff.x *= invLen;
        diff.y *= invLen;
        diff.z *= invLen;
    } else {
        diff = Vector3(0.0f, 0.0f, 0.0f);
    }

    // Check if we should ignore this update due to an active action
    if ((this->movementState->flags & 1) != 0) {
        int actionState = 0;
        // Call IActionSystem::GetActionState(entity, 0xd80c71d2, &actionState)
        bool hasAction = reinterpret_cast<bool (__thiscall*)(IActionSystem*, uint, int*)>(entity->vtable->func[0x10])
                         (entity, 0xd80c71d2, &actionState);
        if (hasAction && actionState != 0) {
            return; // Do nothing if action is active
        }
    }

    // Get the object factory (for spawning decals, etc.)
    ObjectFactory* factory = *(ObjectFactory**)(*(int*)kProcess + 0x18); // DAT_012234c4 + 0x18
    if (factory != nullptr) {
        MovementState* ms = this->movementState;
        if (ms->actionID != 0) { // 0xe offset = actionID
            // Build custom velocity vector from movement state
            Vector3 customVel = Vector3(0,0,0);
            if ((ms->flags & 4) != 0) { // Bit2: custom velocity present
                customVel.x = (float)ms->customVx;
                customVel.y = (float)ms->customVy;
                customVel.z = (float)ms->customVz;
                customVel.w = (float)ms->customVw;
                if ((ms->flags & 8) != 0) { // Bit3: scale customVw by dt
                    customVel.w = (float)ms->customScale * customVel.w * dt;
                }
            }
            // Call factory->ApplyForce(entity, &diff, actionID, speed*dt, velocityFlags, customVel)
            reinterpret_cast<void (__thiscall*)(ObjectFactory*, Entity*, Vector3*, int, float, uint, Vector3*)>
                (factory->vtable[2])(factory, entity, &diff, ms->actionID, (float)ms->speed * dt, (ms->flags >> 1) & 0xffffff01, &customVel);
        }

        // Secondary force
        if (ms->secondaryTarget != 0) {
            reinterpret_cast<void (__thiscall*)(ObjectFactory*, Entity*, Vector3*, int, float, uint, Vector3*)>
                (factory->vtable[3])(factory, entity, &diff, ms->secondaryTarget, ms->secondarySpeed * dt);
        }

        // Handle steering damping based on steerFactor
        float steerFactor = ms->steerFactor; // +0x2C
        if (kSteerThreshold < steerFactor) {
            int* someObject = *(int**)(this->skeletonRef[0x20]); // +0x20 offset
            int offsetA = 0, offsetB = 0;
            uint paramC = 0, paramD = 0;
            float fuel = steerFactor;
            if (someObject != nullptr) {
                someObject[1]++; // Ref count increment
            }
            // Spawn a decal/effect object via hash 0x32223764
            int* spawnedObj = reinterpret_cast<int* (__cdecl*)(uint, int*)>(0x004f95f0)(0x32223764, someObject); // FUN_004f95f0
            if (spawnedObj != nullptr) {
                offsetA = (spawnedObj[4] != 0) ? (spawnedObj[4] - 0x48) : 0;
                offsetB = (spawnedObj[2] != 0) ? (spawnedObj[2] - 0x48) : 0;
                paramC = reinterpret_cast<uint (__thiscall*)(int*)>(spawnedObj->vtable[5])(spawnedObj); // vtable+0x14
                if (kMinRotation <= (float)spawnedObj[6]) {
                    fuel = (float)spawnedObj[6];
                }
                paramD = reinterpret_cast<uint (__thiscall*)(int*)>(spawnedObj->vtable[7])(spawnedObj); // vtable+0x1c
            }
            // Call factory->SteerWithDecal(decal, entity, curPos, fuel*dt, ms->+0x28, offsetA, offsetB, paramC, param4, paramD, param5)
            reinterpret_cast<void (__thiscall*)(ObjectFactory*, int*, Entity*, Vector3*, float, int, int, int, uint, uint, uint)>
                (factory->vtable[1])(factory, spawnedObj, entity, &currentPos, fuel * dt, 
                    *(int*)(ms + 0x28), offsetA, offsetB, paramC, param4, paramD, param5);
        }
    }

    // Apply angular damping when rotation speed exceeds threshold
    uint yawLimit   = ms->yawRateLimit & (uint)kRotationMask;
    uint pitchLimit = ms->pitchRateLimit & (uint)kRotationMask;
    if (kSteerThreshold < (float)yawLimit || kSteerThreshold < (float)pitchLimit) {
        bool allowSteer;
        if (gCheckSteerCallback == nullptr) {
            float outFloat;
            bool result = reinterpret_cast<bool (__thiscall*)(IActionSystem*, uint, float*)>(entity->vtable[0x10])
                          (entity, 0x4f3368d0, &outFloat);
            allowSteer = result && (outFloat != 0.0f);
        } else {
            allowSteer = gCheckSteerCallback(entity) != 0;
        }
        if (allowSteer) {
            // Calculate angular velocity
            float yawSpeed   = (float)(ms->yawRateLimit) * dt;
            float pitchSpeed = (float)(ms->pitchRateLimit) * dt;
            Vector3 angularVel;
            angularVel.x = yawSpeed * diff.x;
            angularVel.y = yawSpeed * diff.y + pitchSpeed * dt; // Note: seems odd, original: pitchSpeed + yawSpeed*diff.y? Actually fVar8 * fStack_3c + something
            angularVel.z = yawSpeed * diff.z;
            angularVel.w = yawSpeed * diff.w;

            // Apply gravity-like correction
            Vector3 correction = kGravity - angularVel;
            correction.y = 0.0f; // zero out y? (from afStack_30[1]=0)
            // Actually the original: afStack_30[2] = DAT_00e44564 - local_50; etc.
            // This is a quaternion multiply with angular velocity.
            QuaternionMultiplyAngularVelocity(&angularVel, &correction);
        }
    }
}