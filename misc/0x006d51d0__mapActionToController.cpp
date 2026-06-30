// FUNC_NAME: mapActionToController
void mapActionToController(int controlGroup)
{
    int actionID;
    int controllerType = 0;
    int buttonFlags;

    // Map control group to action ID (8-11)
    if (controlGroup == 1) {
        actionID = 9;   // fire action
    }
    else if (controlGroup == 2) {
        actionID = 10;  // special action
    }
    else if (controlGroup == 3) {
        actionID = 11;  // grenade action
    }
    else {
        actionID = 8;   // default attack action
    }

    // Clear or prepare the input mapping (likely resets current mapping)
    ResetActionMapping(0);

    // Get the player's current controller type from global configuration
    if (gPlayerInputConfig != NULL) {
        controllerType = *(int*)(gPlayerInputConfig + 0xC8); // +0xC8 = offset 200 (controller type enum)
    }

    // Map controller type to button flags (controller-specific button codes)
    switch (controllerType) {
        case 3:  // PlayStation controller
            buttonFlags = 4;
            break;
        case 1:  // Keyboard/Mouse
            buttonFlags = 8;
            break;
        case 6:  // Wii Remote
            buttonFlags = 0x10;
            break;
        case 4:  // GameCube controller
            buttonFlags = 0x20;
            break;
        case 5:  // Other/Generic
            buttonFlags = 0x40;
            break;
        case 2:  // Xbox 360 controller
            buttonFlags = 0x80;
            break;
        default:
            buttonFlags = 0;
            break;
    }

    // Assign the action to the corresponding button on the current controller
    AssignActionToButton(buttonFlags, actionID);
}