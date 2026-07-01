// FUNC_NAME: Player::fireGrabber
// Address: 0x007cb810
// Role: This function handles the player's grabber (grappling hook) weapon. It checks if the player can fire the grabber, then spawns a projectile at the grabber bone, calculates trajectory, and applies force/effects to the target.

#include <cstdint>

// Forward declarations of external functions (based on EA EARS engine)
extern bool isGrabberAvailable(); // FUN_007fd640
extern void stopGrabber(); // FUN_007fcd60
extern void setGrabberState(); // FUN_00624d20, maybe clears target or starts animation
extern int getBoneTransform(const char* boneName); // FUN_00471610, returns pointer to transform struct
extern void spawnProjectile(void* origin, void* direction, int type, uint32_t flags, int, int); // FUN_00542650
extern bool performSweepTest(void* output, void* params); // FUN_009e5ed0, returns if hit something
extern void normalizeVector(float* vec); // FUN_0043a210
extern void applyGrabberForce(int, void* target, float, float, int, int, float, int, float); // FUN_007fca80

// Global constants (inferred from globals)
const float kGrabberSpeed = DAT_00d5780c;           // Base speed for grabber projectile
const float kGrabberSpeedAlt = DAT_00d5eee4;        // Alternative speed (used when target state is 2 or 3)
const float kGrabberOffsetY = DAT_00d5ef50;         // Y offset for spawn point
const float kMinDotThreshold = DAT_00d577a0;        // Dot product threshold for impact angle
const float kForceScale = DAT_00d5c454;             // Scale for force application
const float kExtraFactor = DAT_00d5eeec;            // Additional factor for force

// Known class offsets for Player (param_1)
// +0x1A0: weaponIndex (or grabber variation)
// +0x1C0: pointer to weapon data table
// +0x1D0: flags (bit 6 must be clear to allow grabber, bit 23 set after use)
// +0x58: vtable pointer
// +0x1B4: pointer to target character (if any) - seems to be offset 0x48 inside a larger struct (target - 0x48 gives base)

void __thiscall Player::fireGrabber(void* thisPlayer)
{
    int iVar2;
    int iVar3;
    float* pfVar4;
    int* piVar5;
    uint32_t uVar6;

    // Local variables for transform data
    float local_100;
    float local_104;
    uint8_t auStack_114[4];
    uint8_t auStack_110[4];

    // Temporary stack space for transforms and vectors
    float fStack_10c;
    float fStack_108;
    float fStack_e8, fStack_e4;
    int* local_ec;
    void* ppuStack_e0;
    float fStack_dc, fStack_c0;
    uint32_t uStack_bc, uStack_b0, uStack_90;
    int iStack_80;
    uint8_t auStack_70[108]; // Output for sweep test

    // Calculate pointer to weapon data entry
    int weaponIndex = *(int*)((char*)thisPlayer + 0x1A0);
    int weaponTableBase = *(int*)(*(int*)((char*)thisPlayer + 0x1C0) + 0x10);
    int weaponEntry = weaponIndex * 0x2C + *(int*)(weaponTableBase + 4);

    // Check if weapon entry exists and if the player is allowed to fire (bit 6 of flags must be clear)
    if (weaponEntry != 0 && ((*(uint32_t*)((char*)thisPlayer + 0x1D0) >> 6 & 1) == 0)) {
        piVar5 = *(int**)((char*)thisPlayer + 0x58); // vtable pointer
        local_ec = piVar5; // Used for virtual call later

        // Check a flag on the weapon data (bit 1 of offset 0x20)
        if ((*(uint32_t*)(weaponEntry + 0x20) >> 1 & 1) == 0) {
            // If flag is not set, check if grabber is available and if so, stop it
            if (isGrabberAvailable()) {
                stopGrabber();
            }
        } else {
            // Flag is set - proceed to fire
            if (!isGrabberAvailable()) {
                // Clear previous target state and prepare to fire
                setGrabberState();

                local_100 = 0.0f;
                local_104 = 0.0f;

                // Get player's "m_grabber" bone transform via virtual function at vtable+0x94
                (**(code**)(*piVar5 + 0x94))(&local_100, "m_grabber"); // Likely fills in a vector2 with bone position? Actually passes float*, but expects bone name.

                // Get target object pointer and adjust by -0x48 to get base of some character struct
                void* targetBase = nullptr;
                if (*(int*)((char*)thisPlayer + 0x1B4) != 0) {
                    targetBase = (void*)(*(int*)((char*)thisPlayer + 0x1B4) - 0x48);
                }

                // Get target's "BP_grabPoint_F" bone transform
                (**(code**)(*(int*)targetBase + 0x94))(&fStack_10c, "BP_grabPoint_F");

                uVar6 = 0xFF; // default impact mode
                fStack_10c = kGrabberSpeed; // base speed

                // Check target's state (offset 0x1B8C within target base)
                if (targetBase) {
                    char targetState = *(char*)((char*)targetBase + 0x1B8C);
                    if (targetState == 0x03 || targetState == 0x02) {
                        fStack_10c = kGrabberSpeedAlt; // use alternative speed for certain animations
                    }
                }

                // Get several transforms from player (maybe root, head, etc.)
                // These calls likely return pointers to transform matrices/positions
                int transform1 = getBoneTransform();
                uint64_t uStack_f8 = *(uint64_t*)(transform1 + 0x30); // position/rotation data
                uint32_t uStack_f0 = *(uint32_t*)(transform1 + 0x38);

                int transform2 = getBoneTransform();
                int transform3 = getBoneTransform();

                // Calculate spawn position/orientation for the grabber projectile
                // local_ec is used as a directional vector
                float directionX = *(float*)(transform2 + 0x20) * fStack_10c + *(float*)(transform3 + 0x30);
                float directionY = *(float*)(transform2 + 0x24) * fStack_10c + *(float*)(transform3 + 0x34) + kGrabberOffsetY;
                float directionZ = *(float*)(transform2 + 0x28) * fStack_10c + *(float*)(transform3 + 0x38);

                // Adjust the original position with offset
                // (Note: using int* assignment for local_ec is odd - likely a vector reinterpretation)
                local_ec = (int*)(directionX); // Not ideal, but matches decompiler
                fStack_e4 = directionZ;
                fStack_e8 = directionY;

                // Update origin vector with Y offset
                uStack_f8 = uStack_f8 + kGrabberOffsetY; // probably adding to y component

                // Spawn the grabber projectile (type 0x40122, flags 0x80000000)
                spawnProjectile(&uStack_f8, &local_ec, 0x40122, 0x80000000, 0, 0);

                // Set up sweep/raycast parameters for impact detection
                uStack_bc = 0xFFFFFFFF; // probably no collision with self
                uStack_b0 = 0xFFFFFFFF;
                ppuStack_e0 = &PTR_FUN_00e32a8c; // Function pointer for sweep callback
                iStack_80 = 0;
                fStack_c0 = kGrabberSpeed;
                uStack_90 = 0;
                fStack_dc = kGrabberSpeed;

                // Perform sweep test to find impact point
                performSweepTest(auStack_70, &ppuStack_e0);

                if (iStack_80 != 0) {
                    // Sweep hit something - calculate direction from player to impact
                    int transform4 = getBoneTransform();
                    int transform5 = getBoneTransform();
                    fStack_108 = *(float*)(transform5 + 0x30) - *(float*)(transform4 + 0x30);
                    local_104 = *(float*)(transform5 + 0x34) - *(float*)(transform4 + 0x34);
                    local_100 = *(float*)(transform5 + 0x38) - *(float*)(transform4 + 0x38);
                    normalizeVector(&fStack_108);

                    // Get additional transforms for dot product calculation
                    pfVar4 = (float*)getBoneTransform();
                    int transform6 = getBoneTransform();
                    int transform7 = getBoneTransform();

                    // Compute dot product of impact direction and target's facing direction
                    float dot = *pfVar4 * fStack_108 + 
                                *(float*)(transform6 + 4) * local_104 +
                                *(float*)(transform7 + 8) * local_100;

                    uVar6 = 2; // impact type 2 (stronger)
                    if (dot <= kMinDotThreshold) {
                        uVar6 = 1; // impact type 1 (weaker)
                    }
                }

                // Apply force/impact to the target
                void* target = nullptr;
                if (*(int*)((char*)thisPlayer + 0x1B4) != 0) {
                    target = (void*)(*(int*)((char*)thisPlayer + 0x1B4) - 0x48);
                }
                applyGrabberForce(0, target, (float)auStack_110, (float)auStack_114, 0, 0, kForceScale, uVar6, kExtraFactor);

                // Set flags on target (bit 0 of offset 0x4A4)
                if (*(int*)((char*)thisPlayer + 0x1B4) != 0) {
                    void* targetForFlag = (void*)(*(int*)((char*)thisPlayer + 0x1B4) - 0x48);
                    *(uint32_t*)((char*)targetForFlag + 0x4A4) |= 1;
                }

                // Set player flag indicating grabber used (bit 23 of offset 0x1D0)
                *(uint32_t*)((char*)thisPlayer + 0x1D0) |= 0x800000;
            }
        }
    }
    // Otherwise return without doing anything
}