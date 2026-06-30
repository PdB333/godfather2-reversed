// FUNC_NAME: GameObject::incrementVersionAndReset
void __thiscall GameObject::incrementVersionAndReset(GameObject *this) {
    // Increment version/instances counter at +0x24
    this->m_versionCount++;
    // Clear some flag/state at +0xc
    this->m_flags = 0;
    // Call base class initialization
    FUN_005db0a0((int)this);
}