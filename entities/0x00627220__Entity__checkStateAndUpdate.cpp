// FUNC_NAME: Entity::checkStateAndUpdate
// Address: 0x00627220
// Role: Updates entity state based on conditions from a manager; possibly checks time-based triggers and flags.

class Entity {
public:
    // +0x5: flags byte (unknown bitmask, 0x11 checked)
    char flags_0x5;
    // +0x10: pointer to a structure containing state data (e.g., two condition sets)
    void* stateData_0x10; // actually a pointer to some data
};

class EntityManager {
public:
    // +0x10: pointer to a structure containing entity-related data
    void* entityData_0x10;
    // +0x3c: pointer to current active entity (compared with this)
    Entity* currentEntity_0x3c;
};

// Internal structure referenced by Entity::stateData_0x10
struct StateData {
    // Offset 0x2c: first threshold (checked if > 3)
    int firstThreshold_0x2c;
    // Offset 0x30: pointer to object with byte at +5 for first condition
    void* firstObjectPtr_0x30;
    // Offset 0x34: second threshold (checked if > 3)
    int secondThreshold_0x34;
    // Offset 0x38: pointer to object with byte at +5 for second condition
    void* secondObjectPtr_0x38;
};

// Forward declarations
void triggerStateChange(); // FUN_00626640
void updateSomething();    // FUN_00626ac0

void Entity::checkStateAndUpdate(EntityManager* manager) {
    // Get internal data pointer from manager
    void* managerData = *(void**)((int)manager + 0x10); // iVar1

    StateData* state = (StateData*)this->stateData_0x10;

    // First condition: check threshold and flag
    if (state->firstThreshold_0x2c > 3) {
        void* obj = state->firstObjectPtr_0x2c;
        if ((*(char*)((int)obj + 5) & 0x11) == 0) {
            triggerStateChange();
        }
    }

    // Second condition: check threshold and flag
    if (state->secondThreshold_0x34 > 3) {
        void* obj = state->secondObjectPtr_0x34;
        if ((*(char*)((int)obj + 5) & 0x11) == 0) {
            triggerStateChange();
        }
    }

    // Update internal state machine
    updateSomething();

    // Check if this entity is not the current active entity in the manager
    Entity* current = *(Entity**)((int)managerData + 0x3c);
    if (this != current && (this->flags_0x5 & 0x11) == 0) {
        triggerStateChange();
        return;
    }
}