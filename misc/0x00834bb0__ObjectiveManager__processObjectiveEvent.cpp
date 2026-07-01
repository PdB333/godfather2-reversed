// FUNC_NAME: ObjectiveManager::processObjectiveEvent
// Address: 0x00834bb0
// Handles various states of an objective/task, playing animations and setting flags.

#include <cstdint>

// Forward declarations of helper functions (likely elsewhere in the engine)
extern void setObjectiveState(int state);
extern void* getGlobalState(); // returns pointer to global state structure
extern void playObjectiveAnimation(void* animator, int animId); // second param is anim ID (e.g. 0x1e = 30)
extern bool checkInteractionCondition(); // returns true if condition satisfied

class ObjectiveManager {
public:
    // +0x10: unknown field
    // +0x14: unknown field
    int32_t field_0x10;
    int32_t field_0x14;

    // param_2 is a pointer to an Obj structure
    void processObjectiveEvent(void* obj);
};

struct Obj {
    // +0x80: pointer to first target/handle
    void* objectA;
    // +0x84: pointer to second target/handle
    void* objectB;
    // +0x98: state (0..4, see switch)
    int32_t state;
    // other fields omitted
};

void ObjectiveManager::processObjectiveEvent(void* obj) {
    if (!obj) return;

    Obj* objective = (Obj*)obj;
    int32_t state = objective->state;

    switch (state) {
    case 0:
        if (objective->objectA) {
            setObjectiveState(0); // likely "ready" or idle
        }
        break;
    case 1:
        setObjectiveState(0);
        break;
    case 2:
        if (objective->objectA) {
            setObjectiveState(1); // maybe "active" or running
        }
        break;
    case 3:
        if (objective) {
            void* handleA = objective->objectA;
            void* handleB = objective->objectB;
            if (handleB && handleA) {
                // Debug information: store the address of this switch case
                // (0x834b56 corresponds to the address of this switch case)
                uint32_t debugAddr = 0x834b56; // used for logging? Not actually used.
                void* globalState = getGlobalState();
                if (globalState) {
                    // Reset some timers or fields on this manager
                    this->field_0x10 = 0;
                    this->field_0x14 = 0;

                    // Check a flag at offset 0x24a4 in global state (bit 0)
                    if (*(uint8_t*)((uint8_t*)globalState + 0x24a4) & 1) {
                        // If flag set, play animation on handleB with ID 0x1e
                        playObjectiveAnimation(handleB, 0x1e); // probably "fail" or "idle"
                        break;
                    }

                    // Otherwise, check interaction condition
                    bool canInteract = checkInteractionCondition();
                    if (!canInteract) {
                        playObjectiveAnimation(handleA, 0x1e); // play on handleA
                    }
                }
            }
        }
        break;
    case 4:
        if (objective->objectA) {
            setObjectiveState(2); // maybe "completed" or "success"
        }
        break;
    }
}