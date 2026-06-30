// FUNC_NAME: Entity::updateTimeScaledValue

void __thiscall Entity::updateTimeScaledValue(Entity* this)
{
    float globalTimeScale = g_timeDelta; // DAT_012067e8, global frame time scale

    // Check flag at offset +0x61, bit 0x10 (flags byte)
    if ((*(byte*)((uintptr_t)this + 0x61) & 0x10) == 0) {
        int vtablePtr = *(int*)this;  // +0x00: vtable pointer

        // Call vtable function at offset +0x110 (likely GetValue)
        // Returns a float10 (extended precision) which we treat as double
        float value = (*(double (__thiscall**)(Entity*))((byte*)vtablePtr + 0x110))(this);

        float scaledValue = value * globalTimeScale;

        // Call vtable function at offset +0x178 (likely SetValue) with scaled value
        (*(void (__thiscall**)(Entity*, float))((byte*)vtablePtr + 0x178))(this, scaledValue);
    }
}