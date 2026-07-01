// FUNC_NAME: SimManager::spawnObject
// Function address: 0x008aed60
// Description: Spawns a new game object of size 0x50, initializes it with the manager and two parameters,
//              registers it in the object list, and posts it to the frame stack.

// Forward declarations (assumed from game codebase)
bool isGameActive();                            // FUN_00481660 - checks if game is running
void* allocateMemory(int size);                 // FUN_009c8e50 - malloc-like allocator
void* constructObject(SimManager* manager);     // FUN_008aebf0 - constructs base object
void pushObjectToStack(SimObject* obj);         // FUN_004d8a60 - adds to frame update stack
void registerObject(void* obj);                 // FUN_00481690 - registers in manager’s object list
void updateFrameProcessing();                   // FUN_00407430 - runs per-frame logic

// Object struct (size 0x50)
struct GameObject {
    char unknown[0x38];                         // +0x00 – +0x37
    void* userData;                             // +0x38 – data parameter
    uint8_t flags;                              // +0x3C – flag byte (e.g., active state)
    // remaining bytes up to 0x50
};

void SimManager::spawnObject(void* dataParam, uint8_t flagParam) {
    if (!isGameActive()) {
        updateFrameProcessing();
        return;
    }

    GameObject* newObj = (GameObject*)allocateMemory(0x50);
    if (newObj == nullptr) {
        updateFrameProcessing();
        return;
    }

    // Initialize object using manager context (e.g., set up base class fields)
    newObj = (GameObject*)constructObject(this);
    if (newObj == nullptr) {
        updateFrameProcessing();
        return;
    }

    // Assign user-provided parameters to the object
    newObj->userData = dataParam;   // +0x38
    newObj->flags = flagParam;      // +0x3C

    // Push onto frame update stack (likely for rendering/physics order)
    pushObjectToStack(newObj);

    // Register object with the manager (e.g., spatial hashing, active list)
    registerObject(newObj);

    updateFrameProcessing();
}