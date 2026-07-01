// FUNC_NAME: Entity::playSoundEffect
void __thiscall Entity::playSoundEffect(void) {
    // Virtual function at vtable+0x2c: PlaySound(hash, flag1, flag2, flag3, context, volume)
    (*(void (__thiscall **)(int, int, int, int, void*, float))(*this + 0x2c))(
        0x5485e39, 1, 1, 1, DAT_00d5eee4, 1.0f);
}