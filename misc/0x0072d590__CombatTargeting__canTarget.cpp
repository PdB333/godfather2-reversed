// FUNC_NAME: CombatTargeting::canTarget
// Function address: 0x0072d590
// Role: Check if this entity can target another entity (for combat/interaction).
// Checks: target non-null, self can act (virtual 0x140), faction match (virtual 0x28c),
//         distance <= g_maxTargetDistanceSq, and cooldown (offset +0x7AD) has expired.

bool __thiscall CombatTargeting::canTarget(int* self, int* target, bool ignoreCooldown, bool ignoreState, bool ignoreFaction)
{
    char selfCanAct;
    char targetTeam;
    char selfTeam;
    int iSimMgr;
    float fDistanceSq;

    if (target != (int*)0x0)
    {
        // Check if self can act (e.g., not dead, not stunned)
        selfCanAct = (**(code**)(*self + 0x140))();  // virtual CanAct()
        if (selfCanAct != (char)0x0 || ignoreState)
        {
            // Compare team/faction IDs
            targetTeam = (**(code**)(*target + 0x28c))();  // virtual GetTeamID()
            selfTeam = (**(code**)(*self + 0x28c))();      // virtual GetTeamID()
            if (targetTeam == selfTeam || ignoreFaction)
            {
                // Get simulation manager and compute distance squared
                iSimMgr = FUN_00471610();  // GetSimManager()
                fDistanceSq = (float)FUN_004702b0(iSimMgr + 0x30);  // CalcDistanceSq(self->position)
                // Global maximum targeting distance (squared)
                if (fDistanceSq < (float)*g_maxTargetDistanceSq &&
                    ((ignoreCooldown ||
                      (*(int*)(self + 0x7AD) == 0) ||  // +0x7AD: lastTargetTime, 0 means never
                      (*(unsigned int*)(self + 0x7AD) + 5000U < (unsigned int)DAT_01205224))))  // cooldown 5s
                {
                    return true;
                }
            }
            return false;
        }
    }
    return false;
}