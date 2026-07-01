// FUNC_NAME: CombatPerception::isTargetInRange
undefined4 __fastcall CombatPerception::isTargetInRange(CombatPerception* this)
{
    // Virtual call: get a pointer to something (e.g., a target or a navigation node)
    // vtable offset 0x20: likely returns a pointer to a target object
    void* targetObj = (void*)(*(void*(__thiscall**)(CombatPerception*))(*(uint*)this + 0x20))(this);
    
    // Local structure to receive position (probably 3 floats, but we only use 2D)
    float position[3]; // stack: position[0] at fStack_20, position[1] at uStack_1c, position[2] at fStack_18
    // Virtual call on targetObj at vtable offset 0x4c: fills position array
    (*(void(__thiscall**)(void*, float*))(*(uint*)targetObj + 0x4c))(targetObj, position);
    
    position[1] = 0.0f; // clear the second component (unused or z-component)
    
    float dx = position[2]; // fStack_18
    float dy = position[0]; // fStack_20 (note: order may be swapped, but we assume x at index2, y at index0)
    float distSq = dx * dx + dy * dy;
    
    // Global max distance threshold
    extern float g_maxDistance; // _DAT_00d5cf70
    // Global function that checks some additional condition (e.g., line-of-sight)
    extern bool __fastcall someOtherConditionCheck(); // FUN_00549a00
    
    if (g_maxDistance < sqrt(distSq) || !someOtherConditionCheck()) {
        this->field_0x78 = 0; // param_1[0x1e] - timer or state
        return 0;
    }
    
    // Global ID for tracking target changes
    extern int g_currentTargetId; // DAT_01205224
    // Global increment to add to timer when target changes
    extern float g_targetChangeAdd; // DAT_012067e8
    // Global threshold for timer
    extern float g_timerThreshold; // DAT_00d75e44
    
    if (this->field_0x7c != g_currentTargetId) { // param_1[0x1f]
        this->field_0x7c = g_currentTargetId;
        this->field_0x78 = (int)((float)this->field_0x78 + g_targetChangeAdd);
    }
    
    if ((float)this->field_0x78 <= g_timerThreshold) {
        return 0;
    }
    return 1;
}