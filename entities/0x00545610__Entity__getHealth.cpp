// FUNC_NAME: Entity::getHealth
// Function at 0x00545610: returns health if entity is alive, otherwise 0.0
float __thiscall Entity::getHealth(int* thisPtr) {
    // vtable offset 0x198 -> index 0x66: isAlive() virtual function
    bool isAlive = ((bool (__thiscall*)(int*))((*(int**)thisPtr)[0x66]))(thisPtr);
    if (isAlive) {
        // +0xD8: pointer to damage/health component (e.g., StandardDamageComponent)
        int* damageComponent = *(int**)((char*)thisPtr + 0xD8);
        // vtable offset 0x28 -> index 0x0A: getHealth() virtual function returning float
        return ((float (__thiscall*)(int*))((*(int**)damageComponent)[0x0A]))(damageComponent);
    }
    return 0.0f;
}