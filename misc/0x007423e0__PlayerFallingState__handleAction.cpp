// FUNC_NAME: PlayerFallingState::handleAction
// Address: 0x007423e0
// Role: State machine handler for player falling/ragdoll states (states 10-16)
// Called when state action occurs (enter, exit, update, etc.)
typedef unsigned int uint;

// Forward declarations of called functions (assumed from context)
extern int __cdecl getComponentFromEntity(void* entity, uint componentHash);
extern void __cdecl soundManagerPlay(int param);
extern void __cdecl soundManagerRegister(int soundId);
extern void __cdecl soundManagerUnregister(int soundId);
extern void __cdecl soundManagerSetVolume(int a, int b);
extern void __cdecl soundManagerStop(int param);
extern void __cdecl soundManagerPlayEvent(uint eventHash, int a, int b, int c, float d, float e);
extern void __cdecl uiBegin(int a, int b);
extern void __cdecl uiEnd();
extern void __cdecl soundManagerPlayWithEvent(uint eventHash, int a, uint b, uint c);
extern void __cdecl setFlag(bool);
extern void __cdecl fallingStateUpdate();
extern void __cdecl fallingStateCleanup();
extern void* __cdecl getManagerInstance(uint managerHash);
extern float __cdecl getEaseValue(int value);
extern void __cdecl applyEaseToVolume(float val, int a, int b);
extern bool __cdecl isSoundPlaying(int soundId);
extern bool __cdecl isInAir();
extern void __cdecl clearState(void* entity, int param);
extern void __cdecl setEntityState(void* entity, int state);
extern bool __cdecl checkGameOption(int option);
extern void __cdecl playAnimation(int animId);
extern void __cdecl stackCleanup(int*);
extern bool __cdecl soundManagerCheck();
extern bool __cdecl canPlayFallSound();
extern void __cdecl enableRagdoll(bool enable, void* globalFlag, bool immediate);
extern void __cdecl resetGlobalFunction(int a, int b, int c);
extern uint __cdecl defaultHandler(uint param2, uint param3, uint param4, int param5, uint param6);

// Globals
extern void* g_someGlobal; // DAT_01205210
extern void* g_ragdollEnableFlag; // DAT_00d5f18c

// Component hashes
const uint COMPONENT_RAGDOLL = 0x369ac561; // Likely ragdoll component


// State IDs (param5 - 10 gives case index)
enum FallStateAction {
    FALL_STATE_ENTER = 10,
    FALL_STATE_UPDATE = 11,
    FALL_STATE_CHECK_THROW = 12,
    FALL_STATE_EXIT = 13,
    FALL_STATE_ENABLE_RAGDOLL = 14,
    FALL_STATE_DISABLE_RAGDOLL = 15,
    FALL_STATE_RESET = 16
};

// Event hashes
const uint EVENT_FALL_START = 0x37a4d62b; // Played on enter
const uint EVENT_FALL_END = 0xee47c440;   // Played on exit

// Sound IDs
const int SOUND_FALL_LOOP = 0x4b;           // Looping fall sound
const int SOUND_FALL_IMPACT_1 = 0x2a;       // First impact variant
const int SOUND_FALL_IMPACT_2 = 0x2b;       // Second impact variant
const int ANIM_FALL_SOFT = 0x10;            // Soft landing animation ID
const int ANIM_FALL_HARD = 0x11;            // Hard landing animation ID

// Structure offsets
// this (param1) is a pointer to the state instance. Known fields:
// +0x50 (this[0x14]): Entity pointer (owner)
// +0x54 (this[0x15]): Timer or counter (set to global on enter)
// +0x60 (this[0x18]): Flags:
//   bit0 (1): ? 
//   bit1 (2): fall sound playing
//   bit2 (4): ragdoll impact flag set on component

// Entity offsets:
// +0x4a4: byte flags (bit0 = isFalling?)
// +0x8e4: uint flags (bit10 = inAir?)
// For component (if ragdoll):
// +0x1f54: uint flags (bit10 = hadImpulse?)

uint __thiscall PlayerFallingState::handleAction(int* thisPtr, uint param2, uint param3, uint param4, int param5, uint param6)
{
    uint ret = 1; // default return success
    void* entity = (void*)thisPtr[0x14]; // +0x50: entity pointer
    int flags = thisPtr[0x18];           // +0x60: state flags
    switch (param5 - 10) {
        case 0: // FALL_STATE_ENTER (state 10)
        {
            // Get ragdoll component from owner entity
            void* ragdollComp = getComponentFromEntity(entity, COMPONENT_RAGDOLL); // 0x369ac561
            if (ragdollComp != 0) {
                // Start looping fall sound if not already playing
                if ((flags & 2) == 0) {
                    soundManagerPlay(3); // play with priority 3
                    soundManagerRegister(SOUND_FALL_LOOP); // 0x4b
                    thisPtr[0x18] |= 2; // set flag bit1
                }
                // Set ragdoll component flag to mark falling impulse
                uint* compFlags = (uint*)((char*)ragdollComp + 0x1f54);
                if ((~(*compFlags >> 10) & 1) != 0) {
                    *compFlags |= 0x400; // set bit10
                    thisPtr[0x18] |= 4;   // set flag bit2
                }
            }
            soundManagerSetVolume(1, 0); // set volume? (1,0)
            // Mark entity as falling (set bit0 at +0x4a4)
            *(uint*)((char*)entity + 0x4a4) |= 1;
            // Play fall start event
            (*(void (**)(uint, int, int, int, float, float))(*((uint*)thisPtr) + 0x2c))(EVENT_FALL_START, 1, 1, 0, 1.0f, 1.0f);
            thisPtr[0x15] = (int)g_someGlobal; // +0x54: set some timer from global
            // Check if entity is in air
            if ((*(uint*)((char*)entity + 0x8e4) >> 10 & 1) != 0) {
                bool canSplat = /* FUN_007420b0 */ someConditionCheck(); // likely check if should play splat
                if (canSplat) {
                    uint uiBeginResult = uiBegin(0, 0); // start UI
                    soundManagerPlayWithEvent(0xdd35d7ac, 0x2b1, uiBeginResult, 0);
                    uiEnd();
                }
                setFlag(0); // set flag to false
                return 1;
            }
            break;
        }
        case 1: // FALL_STATE_UPDATE (state 11)
        {
            fallingStateUpdate(); // update state logic
            return 1;
        }
        case 2: // FALL_STATE_CHECK_THROW (state 12)
        {
            if (entity != 0) {
                void* manager = getManagerInstance(/* DAT_0112afb8 */); // some manager
                if (manager != 0) {
                    int someVal = *(int*)((char*)manager + 0x1c); // +0x1c
                    int paramVal = 0;
                    if (someVal != 0 && someVal != 0x3c) {
                        paramVal = *(int*)((char*)someVal + 0x3c); // +0x3c
                    }
                    float eased = getEaseValue(paramVal);
                    applyEaseToVolume(eased, 1, 1);
                    return 1;
                }
            }
            break;
        }
        case 3: // FALL_STATE_EXIT (state 13)
        {
            void* ragdollComp = getComponentFromEntity(entity, COMPONENT_RAGDOLL);
            if (ragdollComp != 0 && (flags & 2) != 0) {
                soundManagerStop(); // stop fall sound
                soundManagerUnregister(SOUND_FALL_LOOP);
                thisPtr[0x18] &= ~2; // clear bit1
            }
            soundManagerSetVolume(0, 0);
            // Clear falling flag on entity
            *(uint*)((char*)entity + 0x4a4) &= ~1;
            // Play fall end event
            (*(void (**)(uint, int, int, int, float, float))(*((uint*)thisPtr) + 0x2c))(EVENT_FALL_END, 1, 1, 0, 1.0f, 1.0f);
            fallingStateCleanup(); // cleanup
            // Check if was in air - clear flag if needed
            if ((*(uint*)((char*)entity + 0x8e4) >> 10 & 1) != 0) {
                setFlag(1); // set flag to true
            }
            // Check some float from entity's virtual function
            float timeSince = (**(float (**)(void*))(*((uint*)entity) + 0xc0))(); // likely get time since state start
            if (timeSince > 0.0f) {
                goto skipImpactHandling;
            }
            clearState(0, 0); // clear some global state
            setEntityState(entity, 0); // set entity state to 0
            if (ragdollComp != 0) {
                bool isHardImpact = checkGameOption(0x2a) != 0; // 0x2a = hard landing option?
                bool isSoftImpact = checkGameOption(0x2b) != 0; // 0x2b = soft landing?
                if (isHardImpact || isSoftImpact) {
                    int animId = isHardImpact ? ANIM_FALL_HARD : ANIM_FALL_SOFT; // 0x10 or 0x11
                    playAnimation(animId);
                }
            }
            if (/* aiStack_20[0] != 0 */ someStackVariable) {
                stackCleanup(/* &aiStack_20 */);
            }
skipImpactHandling:
            soundManagerUnregister(SOUND_FALL_IMPACT_1);
            soundManagerUnregister(SOUND_FALL_IMPACT_2);
            if ((flags & 4) != 0) {
                thisPtr[0x18] &= ~4; // clear bit2
                bool soundPlaying = isSoundPlaying(SOUND_FALL_IMPACT_1); // check if impact sound still playing?
                if (!soundPlaying) {
                    if (ragdollComp != 0) {
                        uint* compFlags = (uint*)((char*)ragdollComp + 0x1f54);
                        *compFlags &= ~0x400; // clear bit10
                    }
                }
            }
            // Call virtual cleanup on entity
            (*(void (**)(void*))(*((uint*)entity) + 0x27c))();
            bool canPlayFallSound = canPlayFallSound(); // maybe check if not already playing
            if (!canPlayFallSound) {
                (**(void (**)(void*, const char*, int))(*((uint*)entity) + 0xac))(entity, "bodyfall_splat_01.emx", 0);
                return 1;
            }
            (**(void (**)(void*, const char*))(*((uint*)entity) + 0x2d0))(entity, "body_fall");
            return 1;
        }
        case 4: // FALL_STATE_ENABLE_RAGDOLL (state 14)
        {
            enableRagdoll(1, g_ragdollEnableFlag, 1);
            return 1;
        }
        case 5: // FALL_STATE_DISABLE_RAGDOLL (state 15)
        {
            enableRagdoll(0, g_ragdollEnableFlag, 1);
            return 1;
        }
        case 6: // FALL_STATE_RESET (state 16)
        {
            resetGlobalFunction(0, 0, 0);
            return 1;
        }
        default:
        {
            ret = defaultHandler(param2, param3, param4, param5, param6);
            break;
        }
    }
    return ret;
}