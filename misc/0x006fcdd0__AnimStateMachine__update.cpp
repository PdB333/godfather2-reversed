// FUNC_NAME: AnimStateMachine::update

#include <cstdint>

// Forward declarations of engine functions
extern void __cdecl lock_acquire(void *mutex);               // FUN_00ab4db0
extern void __cdecl lock_release(void *mutex);               // FUN_00ab4e70
extern void __cdecl stateTransition1(void);                  // FUN_006fbd80
extern void __cdecl stateTransition2(void);                  // FUN_006fbd30
extern int __cdecl hashFunction(int input, uint32_t magic);  // FUN_004756b0
extern bool __cdecl isAnimFinished(int id, int handle);      // FUN_0045ef40
extern void __cdecl resetAnim(int handle);                   // FUN_0045f250

// Global variables (from data section)
extern float g_threshold1;     // DAT_00d5ef70
extern float g_threshold2;     // DAT_00d60c60
extern float g_threshold3;     // _DAT_00d5c458
extern void *g_animMutex;      // DAT_00d60c08

class AnimStateMachine {
public:
    int state;          // +0x00 (1-6 state machine)
    float timer;        // +0x04 (accumulated time)
    // padding at +0x08, +0x0C
    int someId;         // +0x10 (entity/component ID)
    int animHandle;     // +0x14 (animation resource handle)
    int animIndex;      // +0x18 (animation index, 0x48 special)
};

void __thiscall AnimStateMachine::update(float deltaTime)
{
    lock_acquire(g_animMutex);

    switch (state) {
    case 1:
        if (g_threshold1 < timer) {
            stateTransition1();
        }
        break;

    case 2:
        if (timer <= g_threshold1) break;
        state = 6;
        timer = 0.0f;
        // fallthrough to case 6
    case 6:
        stateTransition2();
        break;

    case 3:
        if (timer <= g_threshold2) break;
        if ((animIndex != 0) && (animIndex != 0x48)) {
            // animIndex is guaranteed non-zero and not 0x48 at this point
            int calc = animIndex - 0x48;
            int hashResult = hashFunction(calc, 0xae986323);
            if ((hashResult != 0) && isAnimFinished(someId, animHandle)) {
                resetAnim(animHandle);
            }
        }
        // unconditional transition to state 6
        goto transitionToIdle;

    case 4:
        if (timer <= g_threshold3) break;
        if ((animIndex != 0) && (animIndex != 0x48)) {
            int calc = animIndex - 0x48;
            int hashResult = hashFunction(calc, 0xae986323);
            if ((hashResult != 0) && isAnimFinished(someId, animHandle)) {
                resetAnim(animHandle);
            }
        }
        // fallthrough to state 6 transition
    transitionToIdle:
        state = 6;
        timer = 0.0f;
        break;

    case 5:
        if (0.0f < timer) {
            state = 6;
            timer = 0.0f;
        }
        break;
    }

    timer += deltaTime;
    lock_release(g_animMutex);
}