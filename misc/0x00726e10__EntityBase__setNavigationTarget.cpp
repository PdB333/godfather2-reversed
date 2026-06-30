// FUNC_NAME: EntityBase::setNavigationTarget
void __thiscall EntityBase::setNavigationTarget(int this, int param2) {
    // +0xa0: target point X (or pointer to float)
    // +0xa4: target point Z (or pointer to float)
    // param2: possibly a navigation context or flag
    FUN_009c6b70(this + 0xa0, this + 0xa4, param2);
}