// FUNC_NAME: ObjectiveManager::activateObjective
// Address: 0x00433000
// Role: Activates a new objective for the player, setting mission state and writing objective ID to mission array.

// Forward declarations for called functions
int __stdcall getMissionPhase(); // FUN_0042cf50
void __stdcall getObjectiveData(char* outBuffer, int* outId, int* outValue); // FUN_0042a5a0
void __stdcall assignObjectiveID(); // FUN_004c4e60 (likely generates/assigns a unique ID)
void __stdcall setupPlayerObjective(ObjectiveManager* manager, int someId, char* buffer, int param, int zero); // FUN_004c4ba0

class ObjectiveManager {
public:
    // +0x08: flags (bit 3 = 0x8 means objective already active)
    uint32_t flags;
    // +0x29: current objective phase/state (0=idle,1=pending,2=running,3=active,5=complete)
    uint8_t phase;
    // +0x2a: index into the mission array (short)
    uint16_t missionIndex;
    // (other members omitted)

    void __thiscall activateObjective(GameWorld* world);
};

// Assumed GameWorld structure with mission array pointer at +0x2620
class GameWorld {
public:
    // +0x2620: pointer to an array of MissionSlot structures (each 0x20 bytes, field at +0x1c is objective ID)
    void* missionArray;  // actually MissionSlot*
};

// MissionSlot: 32 bytes per slot
struct MissionSlot {
    char data[0x1c];  // up to offset 0x1c
    int objectiveID;  // +0x1c: the identifier written here
    char extra[0x20 - 0x1c - 4]; // padding to 0x20
};

void __thiscall ObjectiveManager::activateObjective(GameWorld* world) {
    // Check if objective is already active (bit 3 of flags)
    if ((this->flags & 0x8) != 0) {
        return;
    }

    // Local variables for objective data extraction
    char objectiveBuffer[28];          // local_20
    int objectiveId = 0;              // local_2c
    int objectiveValue = 0;           // local_24
    int someOtherId = 0;              // local_28 (unused? but passed to setup)

    // Get the current mission phase
    int phaseCode = getMissionPhase();
    this->phase = (uint8_t)phaseCode;

    // Allow activation only if phase is 0,1,2 or exactly 5
    if (phaseCode >= 0 && (phaseCode < 3 || phaseCode == 5)) {
        // Retrieve objective data: buffer, id, and value
        getObjectiveData(objectiveBuffer, &objectiveId, &objectiveValue);

        // Assign/commit a new objective ID
        assignObjectiveID();

        // Set up the objective for the player (this)
        setupPlayerObjective(this, someOtherId, objectiveBuffer, objectiveId, 0);

        // Mark objective as active
        this->phase = 3;

        // Write the objective value into the mission array at the slot indicated by missionIndex
        MissionSlot* slot = (MissionSlot*)world->missionArray;
        slot[this->missionIndex].objectiveID = objectiveValue;
    }
}