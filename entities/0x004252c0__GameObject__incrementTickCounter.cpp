// FUNC_NAME: GameObject::incrementTickCounter
void __thiscall GameObject::incrementTickCounter(GameObject* this) {
    // Increment counter at offset +0x16C (likely tick count or frame counter)
    *(int32_t*)((uint8_t*)this + 0x16C) += 1;
}