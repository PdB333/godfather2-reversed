// FUNC_NAME: MissionState::isPhaseOne
bool __thiscall MissionState::isPhaseOne(MissionState* this) {
    // +0x20: phase field (0=inactive, 1=phaseOne, 2=phaseTwo, 3=phaseThree)
    switch (*(int*)((char*)this + 0x20)) {
        case 0:
        case 2:
        case 3:
            break;
        case 1:
            return true;
    }
    return false;
}