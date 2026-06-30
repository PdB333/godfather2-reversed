// FUNC_NAME: Entity::SetGameObjectID
void __thiscall Entity::SetGameObjectID(uint32 gameObjectID) {
    // +0x0C: m_gameObjectID
    *(uint32*)(this + 0xC) = gameObjectID;
    // Post-set update – likely triggers initialization or state change
    FUN_007ee2e0(); // Not yet identified; may be a member function
}