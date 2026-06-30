// FUNC_NAME: Entity::checkFlagByHash
uint __fastcall Entity::checkFlagByHash(Entity* this) {
    const uint kFlagHash = 0x1bc97c13; // Hash of some property flag (e.g., "isEnabled" or "isActive")
    int dummyOut = 0;
    // Virtual method at vtable+0x10 takes a hash and an output pointer, returns bool (char)
    bool flagSet = (*(char (__fastcall*)(Entity*, uint, int*))(*(uint*)this + 0x10))(this, kFlagHash, &dummyOut);
    // Return the hash itself if flag is set, else 0 (used as an ID/value in caller)
    return flagSet ? kFlagHash : 0;
}