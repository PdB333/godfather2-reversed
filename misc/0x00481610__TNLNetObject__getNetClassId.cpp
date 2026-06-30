// FUNC_NAME: TNLNetObject::getNetClassId
uint32 TNLNetObject::getNetClassId() const
{
    // Offset +0x0C holds the net class identifier (e.g., GhostObject, PlayerObject, etc.)
    return *(uint32*)(this + 0x0C);
}