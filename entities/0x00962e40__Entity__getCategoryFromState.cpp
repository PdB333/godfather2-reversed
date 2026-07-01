// FUNC_NAME: Entity::getCategoryFromState
int __fastcall Entity::getCategoryFromState(Entity* this) {
    // +0xDC: state or type field (enum)
    switch (*(int*)((char*)this + 0xDC)) {
        case 1: // eState_Active or similar
        case 6: // eState_SomeOther
            return 9; // eCategory_A
        default:
            return 10; // eCategory_B
    }
}