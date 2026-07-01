// FUNC_NAME: Entity::hasMatchingFlags
bool __thiscall Entity::hasMatchingFlags(int typeOrIndex, int entityHandle) {
    bool result = false;
    char valid = isHandleValid(typeOrIndex, entityHandle);
    if (valid != 0) {
        int entityRef[3]; // EARS smart pointer (refptr)
        resolveHandle(entityRef, entityHandle);
        result = true;
        if (entityRef[0] != 0) {
            // this->flagMask (uint at +0x54) & entity->flagMask (ushort at +0x4e) != 0
            result = (*(uint *)(this + 0x54) & (uint)*(ushort *)(entityRef[0] + 0x4e)) != 0;
            releaseHandle(entityRef);
        }
    }
    return result;
}