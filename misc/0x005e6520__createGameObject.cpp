// FUNC_NAME: createGameObject
// Function at 0x005e6520: Creates a game object, calls its init and setup methods, 
// then registers it with the global manager (DAT_012234bc).
// Returns a handle or success code from manager registration.

int createGameObject(int objPtr, int registrationData) // objPtr likely a newly allocated object; registrationData possibly an ID
{
    int result = 0;

    if (objPtr != 0) {
        // Call object's constructor / initializer
        FUN_005dbc10(objPtr);   // objPtr->constructor()
        // Call object's post-initialization setup
        FUN_004dafd0(objPtr);   // objPtr->setup()
        // Register object with the global manager (DAT_012234bc)
        result = FUN_005e49d0(g_globalManager, registrationData); // returns handle or success code
    }

    return result;
}