// FUNC_NAME: CharacterStateMachine::handleStateEffect
void __thiscall CharacterStateMachine::handleStateEffect(CharacterStateMachine *this, char enableFlag, char activateFlag, float multiplier)
{
    // this+0x74c: pointer to a character component (e.g., player controller)
    Character *character = *(Character **)((int)this + 0x74c);
    if (character == (Character *)0x0) {
        return;
    }
    // Subtract 0x48 to get the base object?  Might be an embedded component offset.
    Character *baseChar = (Character *)((int)character - 0x48);
    if (baseChar == (Character *)0x0) {
        return;
    }
    char state = *(char *)((int)character + 0x160); // state byte (0=?,1=active,2=?,6=?)
    if (state == 2) {
        // fall through to flag set
    } else if (state == 1) {
        if (activateFlag == 0) {
            return;
        }
        // Hash 0x332d5a20 likely identifies a component (e.g., HealthComponent)
        Component *component = FUN_0070a250((int)baseChar, 0x332d5a20);
        if (component != (Component *)0x0) {
            float val = (float)*(int *)((int)component + 0x32c); // some integer value (e.g., timer duration)
            if (*(int *)((int)component + 0x32c) < 0) {
                val = val + DAT_00e44578; // convert negative int to float (likely unsigned conversion)
            }
            int result = (int)(longlong)ROUND(val * multiplier);
            if (result == 0) {
                result = 1;
            }
            FUN_007013f0(result); // apply effect with scaled value (e.g., start timer, apply damage)
        }
        goto setFlag;
    } else {
        // For states other than 1,2: set enableFlag = activateFlag? Actually param_2 = param_3
        enableFlag = activateFlag;
        if (state != 6) {
            return;
        }
    }
    // States 2 or 6: require enableFlag to be non-zero
    if (enableFlag == 0) {
        return;
    }
setFlag:
    // Set bit 0x800 in flags at this+0x1f58 (maybe "dirty" or "needsUpdate")
    *(unsigned int *)((int)this + 0x1f58) |= 0x800;
    FUN_00800960(); // notify global systems of change
    return;
}