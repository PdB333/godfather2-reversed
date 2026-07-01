// FUNC_NAME: GameObject::syncTimeFields
void __thiscall GameObject::syncTimeFields(GameObject* this)
{
    // Retrieve global time values and store them in the object
    float globalTime = getGlobalTime();   // FUN_007ef4a0
    float deltaTime = getGlobalDeltaTime(); // FUN_007ef4b0

    // Store at offsets +0x724 and +0x730 (likely m_timeSinceStart and m_deltaTime)
    *(float*)((uint8_t*)this + 0x724) = globalTime;
    *(float*)((uint8_t*)this + 0x730) = deltaTime;
}