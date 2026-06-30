// FUNC_NAME: ScriptEngine::processEvent

#include <intrin.h>

// Global constants (event IDs, likely from an enum)
const int kEventInit = DAT_01206960;    // Placeholder name
const int kEventUpdate = DAT_01206968;  // Placeholder
const int kEventSelect = DAT_012069d4;  // Placeholder
const int kEventBack = DAT_012069ec;    // Placeholder
const int kEventStart = DAT_01206980;   // Placeholder
const int kEventCancel = DAT_01206970;  // Placeholder

// Global state
extern int gScriptDepth;          // DAT_01194540 - current menu/script depth
extern int gScriptCountdown;      // DAT_0119453c - countdown timer
extern void* gScriptRuntime;      // DAT_01205510 - probably a runtime context
extern int gScriptStackPtr;       // DAT_01206880 + 0x14? Actually base pointer
extern int* gScriptStack;         // Pointer to execution stack (derived from FS)

// Forward declarations of called functions (with guessed names)
void ScriptRuntime::activate(int param); // FUN_004e9fa0 -> might return context index
void ScriptRuntime::execute(int context); // FUN_004ea270
void ScriptEngine::resetSequence();      // FUN_0051c350
void ScriptEngine::executeCallback(int id); // FUN_0051c390 - takes a parameter from (*piVar3 + 0x24)
void UIHelper::setState(int state);      // FUN_004e3e80 - sets UI state
void Renderer::update(int context);      // FUN_00519020 - updates renderer
void UISystem::transition(int context, bool forward); // FUN_0051c710
void AudioSystem::playSound();           // FUN_00525b40 - plays a sound effect

void ScriptEngine::processEvent(int* eventId)
{
    int iVar1;
    int* piVar2;
    int* piVar3;
    int* pThreadLocal; // derived from FS

    // Get thread-local pointer to the script runtime context
    // FS:0x2c holds a pointer to a per-thread structure (e.g., script engine instance)
    piVar3 = (int*)__readfsdword(0x2c);

    // Handle initialization event
    if (*eventId == kEventInit) {
        iVar1 = ScriptRuntime::activate();      // Get or create script runtime context
        ScriptRuntime::execute(iVar1);
        // Check some condition in a vtable/array: offset = ( (*(int*)(*piVar3 + 0x34) != 0) * 0x98 + 4 + iVar1 )
        // This likely checks if a specific entry in a function table is non-null
        if (*(int*)((uint)(*(int*)(*piVar3 + 0x34) != 0) * 0x98 + 4 + iVar1) == 0) {
            return; // If null, skip further processing
        }
    }
    // Handle update event: push a new script operation onto a stack
    else if (*eventId == kEventUpdate) {
        piVar2 = (int*)((int)&gScriptStackPtr + 0x14); // Actually DAT_01206880 + 0x14 is a pointer to a stack pointer
        **(undefined4**)((int)&gScriptStackPtr + 0x14) = &PTR_LAB_01124a7c; // Push a new symbol/operation
        *piVar2 = *piVar2 + 4; // Advance stack pointer
    }

    // Process further if script depth > 3 (meaning deep enough for interactive flow)
    if (3 < gScriptDepth) {
        if ((*eventId == kEventSelect) || (*eventId == kEventBack)) {
            if (gScriptDepth == 5) {
                // Handle selection/back at depth 5
                UIHelper::setState(0);
                Renderer::update(gScriptRuntime);
                gScriptCountdown--;
                if (gScriptCountdown < 1) {
                    // Pop the current operation from stack
                    piVar3 = (int*)((int)&gScriptStackPtr + 0x14);
                    **(undefined4**)((int)&gScriptStackPtr + 0x14) = &PTR_LAB_01124a68; // Push a different symbol
                    *piVar3 = *piVar3 + 4;
                    gScriptDepth = 6;
                    return;
                }
            }
            else if ((gScriptDepth != 6) && (gScriptDepth == 7)) {
                int state = (int)&kEventSelect; // placeholder, actually DAT_012067e8 for select, DAT_01206800 for back
                if (*eventId == kEventBack) {
                    state = (int)&kEventBack; // placeholder, actually DAT_01206800
                }
                UIHelper::setState(state);
                UISystem::transition(state, (*eventId == kEventBack));
                Renderer::update(gScriptRuntime);
                if (*eventId == kEventBack) {
                    AudioSystem::playSound();
                    return;
                }
                AudioSystem::playSound();
            }
        }
        else {
            if (*eventId == kEventStart) {
                ScriptEngine::resetSequence();
                return;
            }
            if (*eventId == kEventCancel) {
                ScriptEngine::executeCallback(*(int*)(*piVar3 + 0x24));
                return;
            }
        }
    }
    return;
}