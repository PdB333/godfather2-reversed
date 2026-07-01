//FUNC_NAME: ActionHandler::processAction
// Function address: 0x007781a0
// This function processes various action types based on the actionId parameter (param_5).
// It handles state transitions, animations, sound effects, and gameplay logic.

#include <cstdint>

// Forward declarations of called functions (assumed to be in the same module)
void playSound(int soundId);
void setState(int state);
void* getComponent(int offset);
void beginMessage(int a, int b);
void sendMessage(uint32_t msgId, int size, void* data, int flags);
void endMessage();
void finishAction();
void* getPlayer();
void resetSomething();
void* getSomething();
void updateSomething(float time, bool flag);
void handleAnotherAction(float time);
bool checkCondition1();
bool checkCondition2();
float getSomeValue();
float calculateSomething(void* obj);
void doSomething();
void clearFlag();
void doSomething2();
void doSomething3();
void doSomething4();
void doSomething5(void* obj, int param);
bool baseClassHandler(float time, int a, int b, int actionId, int c);

// Global constants (from data section)
extern float g_defaultValue;       // _DAT_00d5c458
extern float g_altValue;           // DAT_00e445f0
extern float g_floatConstant;      // DAT_00e44578 (used for negative float conversion)
extern float g_scaleFactor;        // DAT_00d5efb8
extern float g_anotherConstant;    // _DAT_00d5780c
extern float g_multiplier;         // DAT_00d681a4
extern float g_someValue;          // DAT_00d5ccf8

// Action IDs (interpreted from float constants)
enum ActionId : int {
    ACTION_SET_FLAG = 0x5A,           // 4.90454e-44
    ACTION_UPDATE_POSITION = 0x5B,    // 5.04467e-44 (and 5.32493e-44, 5.60519e-44)
    ACTION_PLAY_SOUND = 0x5C,         // 5.74532e-44
    ACTION_START_MOVEMENT = 0x5D,     // 5.88545e-44
    ACTION_UPDATE_STATE = 0x5E,       // 6.02558e-44
    ACTION_HANDLE_ANIMATION = 0x5F,   // 6.16571e-44
    ACTION_CHECK_CONDITION = 0x60,    // 6.30584e-44
    ACTION_DO_SOMETHING = 0x61,       // 6.44597e-44
    ACTION_SET_STATE_6 = 0x62,        // 6.5861e-44
    ACTION_SET_STATE_7 = 0x63,        // 6.72623e-44
    ACTION_CLEAR_FLAG = 0x64,         // 6.86636e-44 (and 7.00649e-44)
    ACTION_DO_SOMETHING2 = 0x65,      // 7.14662e-44
    ACTION_UPDATE_TIMER = 0x66,       // 7.28675e-44
    ACTION_RESET = 0x67,              // 7.42688e-44
    ACTION_GET_INFO = 0x68,           // 7.56701e-44
    ACTION_CLEAR_FLAG2 = 0x69,        // 7.70714e-44
    ACTION_DO_SOMETHING3 = 0x6A       // 7.84727e-44
};

uint32_t __thiscall ActionHandler::processAction(float time, int param3, int param4, int actionId, int param6) {
    // piVar1 = pointer to another object (vtable) at offset 0x5c
    void** vtablePtr = *(void***)(this + 0x5c);
    bool result = true;

    switch (actionId) {
        case ACTION_SET_FLAG: // 0x5A
            playSound(0x5a);
            // Fall through to next case? Actually, the decompiled code shows fall-through for case 0x5A to 0x5B/0x5C/0x5D? Wait, the switch has multiple cases grouped.
            // The decompiled switch has cases: 4.90454e-44 (0x5A), then 5.1848e-44 (0x5B?), 5.46506e-44 (0x5C?) - but they are separate cases with same code.
            // Actually, the decompiled code shows:
            // case 4.90454e-44: // 0x5A
            //   FUN_007f63e0(0x5a);
            // case 5.1848e-44: // 0x5B
            // case 5.46506e-44: // 0x5C
            //   if ((param_5 == 4.90454e-44) && ...) { ... }
            //   ...
            // So it's a fall-through from 0x5A to 0x5B/0x5C. We'll replicate that.
            // But we need to handle the fall-through correctly. The decompiled code shows that after the first case, it falls through to the next cases.
            // However, the switch is on float, so the cases are separate. The decompiler might have merged them due to identical code.
            // We'll keep the fall-through as in the original.
            // Actually, the decompiled code shows:
            // case 4.90454e-44:
            //   FUN_007f63e0(0x5a);
            // case 5.1848e-44:
            // case 5.46506e-44:
            //   if ((param_5 == 4.90454e-44) && ...) { ... }
            //   ...
            // So the first case calls FUN_007f63e0 and then falls through to the next cases.
            // We'll replicate that with a fall-through.
            // But note: the switch variable is actionId (int), so we need to handle the fall-through correctly.
            // We'll use a switch with fall-through for the first case.
            // However, the decompiled code also has a separate case for 5.04467e-44 etc. So we need to be careful.
            // Let's restructure based on the decompiled code.
            // Actually, the decompiled code shows:
            // switch(param_5) {
            //   case 4.90454e-44: // 0x5A
            //     FUN_007f63e0(0x5a);
            //   case 5.1848e-44: // 0x5B
            //   case 5.46506e-44: // 0x5C
            //     if ((param_5 == 4.90454e-44) && ...) { ... }
            //     param_5 = _DAT_00d5c458;
            //     ...
            //     return 1;
            //   case 5.04467e-44: // 0x5D? Actually 5.04467e-44 is different from 5.1848e-44.
            //   case 5.32493e-44:
            //   case 5.60519e-44:
            //     ...
            //     return 1;
            //   case 5.74532e-44: // 0x5E?
            //     ...
            //     return 1;
            //   ...
            // }
            // So the first group (0x5A, 0x5B, 0x5C) share code after the first case's call.
            // We'll implement that with a switch that has fall-through for 0x5A to 0x5B/0x5C.
            // But note: the condition inside checks if param_5 == 4.90454e-44, which is actionId == 0x5A.
            // So we need to handle that.
            // We'll write the code accordingly.
            // For simplicity, we'll use a switch with explicit cases and fall-through where needed.
            // However, the decompiled code is complex. We'll replicate the logic as closely as possible.
            // Let's write the code for each case group.

        case 0x5A: // ACTION_SET_FLAG
            playSound(0x5a);
            // Fall through to next cases
        case 0x5B:
        case 0x5C:
            if ((actionId == 0x5A) && ((*(uint32_t*)(this + 0xac) >> 7 & 1) == 0)) {
                *(uint32_t*)(this + 0xac) |= 0x80;
            }
            {
                float baseValue = g_defaultValue;
                if ((*(uint32_t*)(this + 0xac) >> 10 & 1) != 0) {
                    baseValue = g_altValue;
                }
                setState(4);
                float intTime = (float)(int)time;
                if ((int)time < 0) {
                    intTime += g_floatConstant;
                }
                *(float*)(this + 0xa4) = intTime * g_scaleFactor + baseValue;
            }
            return 1;

        case 0x5D:
        case 0x5E:
        case 0x5F:
            {
                float intTime = (float)(int)time;
                if ((int)time < 0) {
                    intTime += g_floatConstant;
                }
                float baseValue = g_defaultValue;
                if ((*(uint32_t*)(this + 0xac) >> 10 & 1) != 0) {
                    baseValue = g_altValue;
                }
                if (*(float*)(this + 0xa4) <= intTime * g_scaleFactor) {
                    time = g_anotherConstant;
                } else {
                    time = g_anotherConstant - (*(float*)(this + 0xa4) - intTime * g_scaleFactor) / baseValue;
                }
                int* component = (int*)getComponent(this + 0x80);
                if (actionId == 0x5D) {
                    *(float*)(component + 0x14) = time * g_multiplier;
                    return 1;
                }
                *(float*)(component + 0x14) = g_multiplier - time * g_multiplier;
                return 1;
            }

        case 0x60: // ACTION_PLAY_SOUND
            setState(5);
            playSound(0x5a);
            {
                void* data = beginMessage(0, 0);
                sendMessage(0x5393fcca, 4, data, 0);
                endMessage();
                finishAction();
            }
            return 1;

        case 0x61: // ACTION_START_MOVEMENT
            {
                void* player = getPlayer();
                float val = g_someValue;
                float intTime = (float)(int)time;
                if ((int)time < 0) {
                    intTime += g_floatConstant;
                }
                float scaledTime = intTime * g_scaleFactor;
                *(float*)(this + 0x9c) = g_someValue;
                scaledTime += g_defaultValue;
                *(float*)(this + 0xa8) = val;
                *(float*)(this + 0xa0) = scaledTime;
                resetSomething();
                if (player != nullptr) {
                    if (*(char*)((int)player + 0x1aa) == '\x01') {
                        setState(0);
                        return 1;
                    }
                    setState(1);
                    return 1;
                }
            }
            break;

        case 0x62: // ACTION_UPDATE_STATE
            {
                void* player = getPlayer();
                if (player == nullptr) {
                    void* obj = getSomething();
                    (*(void (**)(void*, int))(*(void**)obj + 600))(obj, 0);
                }
                updateSomething(time, ~(*(uint32_t*)(this + 0xac) >> 1) & 1);
            }
            return 1;

        case 0x63: // ACTION_HANDLE_ANIMATION
            handleAnotherAction(time);
            return 1;

        case 0x64: // ACTION_CHECK_CONDITION
            {
                void* player = getPlayer();
                if ((player != nullptr) && checkCondition1() && checkCondition2()) {
                    float intTime = (float)(int)time;
                    if ((int)time < 0) {
                        intTime += g_floatConstant;
                    }
                    float scaledTime = intTime * g_scaleFactor;
                    float currentTime = getSomeValue();
                    if (currentTime + *(float*)(this + 0x98) < scaledTime) {
                        *(float*)(this + 0x98) = scaledTime;
                        (*(void (**)(void*))(*(void**)vtablePtr + 0x264))(vtablePtr);
                    }
                }
                updateSomething(time, ~(*(uint32_t*)(this + 0xac) >> 1) & 1);
            }
            return 1;

        case 0x65: // ACTION_DO_SOMETHING
            {
                void* player = getPlayer();
                if (player != nullptr) {
                    doSomething();
                    return 1;
                }
            }
            break;

        case 0x66: // ACTION_SET_STATE_6
            setState(6);
            return 1;

        case 0x67: // ACTION_SET_STATE_7
            setState(7);
            return 1;

        case 0x68: // ACTION_CLEAR_FLAG
            setState(6);
            if ((*(int*)(this + 0x70) != 0) && (*(int*)(this + 0x70) != 0x48) && ((*(uint32_t*)(this + 0xac) >> 0xb & 1) != 0)) {
                *(uint32_t*)(this + 0xac) &= 0xfffff7ff;
                if (*(int*)(this + 0x70) != 0) {
                    clearFlag();
                    return 1;
                }
                clearFlag();
                return 1;
            }
            break;

        case 0x69: // ACTION_DO_SOMETHING2
            doSomething2();
            return 1;

        case 0x6A: // ACTION_UPDATE_TIMER
            doSomething3();
            {
                void* player = getPlayer();
                if (player != nullptr) {
                    void* obj = getSomeValue();
                    float val = calculateSomething(obj);
                    float intTime = (float)(int)time;
                    if ((int)time < 0) {
                        intTime += g_floatConstant;
                    }
                    *(float*)(this + 0x94) = intTime * g_scaleFactor + val;
                    return 1;
                }
            }
            break;

        case 0x6B: // ACTION_RESET
            doSomething4();
            return 1;

        case 0x6C: // ACTION_GET_INFO
            if ((*(int*)(this + 0x70) != 0) && (*(int*)(this + 0x70) != 0x48)) {
                int local_18 = 0;
                int local_14 = 0;
                void* obj;
                if (*(int*)(this + 0x70) == 0) {
                    obj = nullptr;
                } else {
                    obj = (void*)(*(int*)(this + 0x70) - 0x48);
                }
                (*(void (**)(void*, int*))(*(void**)obj + 0x1f8))(obj, &local_18);
                if (*(int*)(this + 0x70) == 0) {
                    obj = nullptr;
                } else {
                    obj = (void*)(*(int*)(this + 0x70) - 0x48);
                }
                int result = (*(int (**)(void*))(*(void**)obj + 0x280))(obj);
                (*(void (**)(void*, int, int))(*(void**)vtablePtr + 0x14c))(vtablePtr, result, 1, 0);
                return (uint32_t)(result >> 0x18);
            }
            break;

        case 0x6D: // ACTION_CLEAR_FLAG2
            *(uint32_t*)(this + 0xac) &= 0xffffff7f;
            playSound(0x5a);
            return 1;

        case 0x6E: // ACTION_DO_SOMETHING3
            if (*(int*)(this + 0x70) != 0) {
                doSomething5(vtablePtr, *(int*)(this + 0x70) - 0x48);
                return 1;
            }
            doSomething5(vtablePtr, 0);
            return 1;

        default:
            result = baseClassHandler(time, param3, param4, actionId, param6);
    }
    return (uint32_t)result;
}