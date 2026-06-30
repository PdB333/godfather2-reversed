// FUNC_NAME: SomeClass::setColorValue
void __thiscall SomeClass::setColorValue(int color) {
    // +0x98: m_pConfig (pointer to some configuration, non-zero indicates valid)
    // +0x9c: m_pTarget (pointer to target object with color field at +0xbc)
    // +0xbc: colorValue (int)

    if (this->m_pConfig != 0) {
        void* target = this->m_pTarget;
        if (color == 0) {
            // Build a color from string constants: "placeholder" and "color"
            // FUN_00ab8560 likely concatenates or formats strings
            // FUN_00611000 likely converts string to color value
            undefined4 result = FUN_00ab8560(0, "placeholder", 0xb);
            result = FUN_00ab8560(result, "color", 5);
            *(int*)((int)target + 0xbc) = FUN_00611000(result);
        } else {
            *(int*)((int)target + 0xbc) = color;
        }
    }
}