// FUNC_NAME: PlayerStateMachine::getMainAnimState
int PlayerStateMachine::getMainAnimState() {
    switch (*(uint8_t*)(this + 0x1AD)) {
    case 0:
    case 1:
        return 9;                        // Transitional/Idle
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 0xA:
    case 0xB:
    case 0xC:
    case 0xD:
    case 0xE:
    case 0xF:
    case 0x10:
    case 0x11:
    case 0x12:
    case 0x13:
        return 5;                        // Combat/Generic
    case 0x14:
        return 1;                        // Walk
    case 0x15:
        return 2;                        // Run
    case 0x16:
        return 3;                        // Sprint
    case 0x17:
        return 4;                        // Cover/Strafe
    case 0x18:
        return 0;                        // Idle
    case 0x19:
        return 6;                        // Fall
    case 0x1A:
        return 8;                        // Swim
    case 0x1B:
        return 7;                        // Climb
    default:
        return 0xB;                      // Unknown
    }
}