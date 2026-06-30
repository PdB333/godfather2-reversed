// FUNC_NAME: GameManager::GameManager
// Address: 0x00415ce0
// Constructor for the game manager singleton. Initializes internal state and stores pointers.
class GameManager {
    // vtable pointer at +0x00
    // manager (some subsystem) at +0x04
    // helperResult at +0x08
    // someValue2 at +0x0C
    // someValue3 (same as value2) at +0x10
    // someValue1 at +0x14
public:
    GameManager(void* someManager);
};

// Global pointer to the singleton instance
extern GameManager* g_gameManagerInstance;

// Instance of a vtable (assumed defined elsewhere)
extern void* g_GameManagerVtable;

// Globals used for initialization
extern int g_initialSomeValueA; // DAT_00e447e4
extern int g_initialSomeValueB; // DAT_00e447e8

// Forward declaration of a helper function
extern int generateHelperResult(); // FUN_00415c70

__thiscall GameManager::GameManager(void* someManager)
{
    // Store this as global singleton
    g_gameManagerInstance = this;

    // Set vtable pointer (offset +0x00)
    this->vtable = &g_GameManagerVtable;

    // Store the manager pointer at offset +0x04
    this->manager = someManager;

    // Call the manager's initialization virtual function (vtable entry at offset 8, i.e., third function)
    // The manager is expected to be a polymorphic object with a vtable.
    (*(void (**)(void))(*(int*)someManager + 8))();

    // Set member at offset +0x14 from a global
    this->someValue1 = g_initialSomeValueB;

    // Set members at offset +0x0C and +0x10 both to the same global
    this->someValue2 = g_initialSomeValueA;
    this->someValue3 = g_initialSomeValueA;

    // Call a helper function to generate a value stored at offset +0x08
    this->helperResult = generateHelperResult();

    return this;
}