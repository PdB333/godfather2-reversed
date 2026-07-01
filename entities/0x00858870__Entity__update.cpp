// FUNC_NAME: Entity::update
void __thiscall Entity::update() {
    // Bit flags at offset 0x40
    uint32_t flags = *(uint32_t*)((uintptr_t)this + 0x40);

    // Check bit 1 (paused? suspended?)
    if ((flags >> 1) & 1) {
        // Paused or suspended -> execute default update path
        goto defaultPath;
    }

    // Bit 1 is clear
    if (flags & 1) {
        // Active flag is set -> perform special processing if parent object is alive
        // Virtual call: getOwner() or similar, through vtable at +0x1c from a nested object
        // The nested object is obtained via *(int*)(this+8) + 8
        intptr_t nestedPtr = *(intptr_t*)((uintptr_t)this + 8);
        intptr_t vtableBase = *(intptr_t*)(nestedPtr + 8);
        typedef int (__thiscall* GetOwnerFunc)(void*);
        GetOwnerFunc getOwner = *(GetOwnerFunc*)(vtableBase + 0x1c);
        intptr_t owner = getOwner(reinterpret_cast<void*>(nestedPtr));

        // Check a byte at offset 0x161 in the owner object
        if (*(char*)(owner + 0x161) == 0) {
            goto defaultPath;
        }
        // Owner is alive -> do special processing (audio related?)
        audioSpecialFunction(); // FUN_0099cd00
        return;
    }

    // Active flag not set -> also call special processing
    audioSpecialFunction(); // FUN_0099cd00
    return;

defaultPath:
    processDefault(); // FUN_00858770
    audioDefaultFunction(); // FUN_0099cd10
}