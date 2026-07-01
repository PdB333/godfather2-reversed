// FUNC_NAME: Entity::setOverrideValue
extern int* gpDebugManager; // DAT_01223484

void __thiscall Entity::setOverrideValue(Entity* this, byte value)
{
    // Guard: only set if debug manager and its subsystem exist
    if ((gpDebugManager != 0) && (*(int*)(gpDebugManager + 8) != 0)) {
        *(byte*)(this + 0x1ac) = value;  // +0x1ac: debug flag/override byte
    }
}