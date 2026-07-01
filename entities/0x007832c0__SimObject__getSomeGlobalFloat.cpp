// FUNC_NAME: SimObject::getSomeGlobalFloat
float SimObject::getSomeGlobalFloat() {
    // 0x007832c0: Checks if condition (via FUN_00783210) is met, returns global float value if true, else 0.0f
    float result = 0.0f;
    if (isConditionMet()) {  // FUN_00783210 - likely a boolean check on this object
        // _DAT_00d5780c - global float constant (e.g., damage multiplier, speed scale)
        result = g_someGlobalFloat;
    }
    return result;
}