// FUNC_NAME: Entity::getFloatValue
float __fastcall Entity::getFloatValue(int thisPtr) {
    // Dereference pointer at this+0x18 (likely a child component or member object)
    // Then read float at that object+0x18 (e.g., speed, time, or health value)
    return *(float*)(*(int*)(thisPtr + 0x18) + 0x18);
}