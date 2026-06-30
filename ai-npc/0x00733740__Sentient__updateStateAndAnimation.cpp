// FUNC_NAME: Sentient::updateStateAndAnimation
void __thiscall Sentient::updateStateAndAnimation(Sentient *this)
{
    int *pActionScript; // from FUN_00800800
    int iVar1;
    void *vtableFunc; // from FUN_00471610
    uint flagField_0x7d6;
    float fVar;
    int local_c[4]; // used as a struct? Contains float and something
    float fStack_8;
    int local_4;

    flagField_0x7d6 = *(uint *)((int)this + 0x7d6); // +0x7D6: flags/state bitfield
    if ((flagField_0x7d6 >> 0xe & 1) == 0) {
        // Check if pending scripted action fields are all zero
        if (*(int *)((int)this + 0x81d) == 0 &&
            *(int *)((int)this + 0x81e) == 0 &&
            *(int *)((int)this + 0x81f) == 0 &&
            *(int *)((int)this + 0x820) == 0) {
            // No pending scripted action; handle movement animation state
            // +0x801: current animation state (0 = idle, 0x48 = some specific state)
            if (*(int *)((int)this + 0x801) != 0 && *(int *)((int)this + 0x801) != 0x48) {
                // Get random time offset? Calls:
                // FUN_00722870 -> likely getRandomFloat or getGlobalTime
                fVar = (float)FUN_00722870();
                // FUN_007227f0 and 007227c0 convert to internal representation
                int v1 = FUN_007227f0(fVar);
                int v2 = FUN_007227c0(v1);
                // FUN_00733680 plays an animation or triggers a state transition
                FUN_00733680(v2, v1, fVar);
            }
            // Update two sets of "look-at" or "aim" direction targets?
            // +0x825, +0x821 are position/facing vectors
            // +0x82c, +0x82d, +0x82e, +0x829, +0x82a, +0x82b are parameters (yaw, pitch, time?)
            FUN_0072cda0((float *)((int)this + 0x825),
                         *(int *)((int)this + 0x82c),
                         *(int *)((int)this + 0x82d),
                         *(int *)((int)this + 0x82e));
            FUN_0072cda0((float *)((int)this + 0x821),
                         *(int *)((int)this + 0x829),
                         *(int *)((int)this + 0x82a),
                         *(int *)((int)this + 0x82b));
        } else {
            // There is a pending scripted action (pointer at +0x81d)
            pActionScript = (int *)FUN_00800800((int)this + 0x81d);
            if (pActionScript != (int *)0x0) {
                // Get global game manager (e.g., SimManager)
                int *gameManager = (int *)FUN_00471610();
                // Access some data from gameManager (?)
                local_4 = *(int *)((int)gameManager + 0x38); // +0x38: maybe a time delta
                fStack_8 = (float)((ulonglong)*(long long *)((int)gameManager + 0x30) >> 0x20); // +0x30: maybe a double (high part)
                // Combine into local_c (struct of float4?)
                *(float *)&local_c = fStack_8 + *(float *)0x00d5c458; // global offset
                *(int *)((int)local_c + 4) = local_4;
                // Virtual call on this: request an animation resource?
                // vtable[0x58] returns something (maybe a bone node or effect handle)
                int result = (*(int (__thiscall **)(int, int, int, int))vtable(this + 0x58))(1, 0x3f800000, 0);
                // Virtual call on the retrieved script action object:
                // vtable[0x170] with the local_c and result
                (*(void (__thiscall **)(int, int *, int))vtable(pActionScript[0] + 0x170))((int)pActionScript, local_c, result);
            }
        }
        // Check another flag at +0x238 (bit 10)
        if (*(uint *)((int)this + 0x238) >> 10 & 1) {
            // Trigger a custom update via vtable[0x260]
            (*(void (__thiscall **)(int))vtable(this + 0x260))((int)this);
        }
        // Mark that this update has run (set bit 14 of flag field)
        *(int *)((int)this + 0x7d6) = flagField_0x7d6 | 0x4000; // +0x7D6: set bit 14
    }
}