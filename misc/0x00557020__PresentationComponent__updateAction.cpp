// FUNC_NAME: PresentationComponent::updateAction
// Address: 0x00557020
// Role: Updates or handles an action (animation/sound) tied to a component.
// This is a __thiscall member function. 'this' is passed in EAX.
// Offsets documented in comments.
// Assumes: this+0x40 points to an Action object.
// Uses global Engine pointer at 0x0113dfc8 (likely gEngine).

#include <string>

// Forward declarations of unknown callees (stubs with guessed signatures)
char* ConvertString(char* dest, const char* src); // FUN_00ab06f0, wide to narrow?
int  GetCurrentAction();                         // FUN_00556e10, returns some global action?
void StopAction(void* action);                   // FUN_009e7530
void StartAction(const char* name, void* action); // FUN_009e71f0, may be different

class PresentationComponent {
public:
    // +0x40: Action* m_pAction
    void* m_pAction;  // at offset 0x40

    // Function
    bool updateAction() {
        void* pAction = *(void**)((char*)this + 0x40);
        if (pAction != nullptr) {
            // Get the engine's component/action manager
            // DAT_0113dfc8 is a pointer to the Engine singleton
            int engineBase = *(int*)0x0113dfc8;
            // Vtable-style: offset +0x14 yields a function returning a manager instance
            int (__thiscall *getManager)() = *(int (__thiscall **)())(engineBase + 0x14);
            int manager = getManager();
            // Manager vtable offset +0x10 gets action name as a string (maybe wide)
            const char* (__thiscall *getActionName)(void*) = 
                *(const char* (__thiscall **)(void*))(*(int*)manager + 0x10);
            const char* rawName = getActionName(pAction);
            // Convert to char buffer (stack variable)
            char nameBuffer[256]; // assumed size
            char* name = ConvertString(nameBuffer, rawName);
            if (*name != '\0') {
                // Non-empty name: maybe stop the existing action?
                // Check a flag at pAction+8
                if (*(int*)((char*)pAction + 8) == 0) {
                    return false;
                }
                StopAction(pAction); // FUN_009e7530
                return true;
            }
            // Empty name: fall through to start/default behavior
        }
        // No action or empty name: Get a default/current action
        void* currentAction = (void*)GetCurrentAction(); // FUN_00556e10
        if (currentAction != nullptr && *(int*)((char*)currentAction + 8) != 0) {
            StartAction(nameBuffer, currentAction); // FUN_009e71f0, note 'nameBuffer' is used
            return true;
        }
        return false;
    }
};