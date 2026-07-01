// FUNC_NAME: Entity::isStateValid
bool __thiscall Entity::isStateValid(Entity *this) {
    bool result;

    if (*(int *)(this + 0xC4) == 2) {          // +0xC4: objectState
        result = *(int *)(this + 0x40) == 0x637b907; // +0x40: objectType (magic ID)
    } else {
        result = *(int *)(this + 0xC4) == 5;   // +0xC4: objectState
    }
    return result;
}