// FUNC_NAME: Player::setPositionVector
void __thiscall Player::setPositionVector(int param2, int param3) {
    // Offsets 0x4ac and 0x4b0 store a 2D position (e.g., target or waypoint)
    *(int *)(this + 0x4ac) = param2;
    *(int *)(this + 0x4b0) = param3;
}