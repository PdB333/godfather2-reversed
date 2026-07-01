// FUNC_NAME: Entity::canPerformAction
// Function address: 0x0087caa0
// Checks if this entity can perform an action identified by actionId (param2).
// Involves virtual cooldown check, global entity lookup, and internal flags.
// +0x48: offset to a sub-entity pointer? (iVar2 = *(uVar1+0x48) - 0x48)
// +0xC88 (param_1[0x322]): internal flags (bit 11 = action enabled? bit2 = something)
// vtable+0xC0: virtual method returning float (cooldown timer)

#include <cstdint>

uint Entity::canPerformAction(uint actionId)
{
    uint result;
    bool allowed = false;

    // Check if actionId maps to a valid state (e.g., through a global lookup)
    if (GameState::isActionAllowed(actionId) != 0)   // FUN_00542f60
    {
        // Cooldown check via virtual method (e.g., GetActionCooldown())
        float cooldownTimer = (*(float (__thiscall **)(Entity*))(*(uint*)this + 0xC0))(this);
        if (cooldownTimer > 0.0f)
        {
            // Retrieve global singleton (e.g., EntityManager)
            Entity* entity = GetEntityManager(DAT_0113108c);   // FUN_0043b870
            if (entity != nullptr)
            {
                // Possibly check if a sub-component (e.g., Owner) is valid
                if (*(int*)(entity + 0x48) != 0)
                {
                    int extra = *(int*)(entity + 0x48) - 0x48; // Sub-entity pointer after adjustment
                    result = (extra != 0) ? 1 : 0;             // flag as allowed if non-zero
                    if (extra != 0) goto end_check;
                }
            }

            // Check internal flags (bit 11 of this->flags[0x322])
            if ((this->flags[0x322] >> 0xB) & 1)
            {
                if ( (* (uint (__thiscall **)(void))0x00543370)() != 0 )   // FUN_00543370, global check (e.g., IsPlayerFree())
                {
                    if ( (this->flags[0x322] >> 2) & 1 )
                    {
                        // If bit2 is set, do nothing (fall through)
                    }
                    else
                    {
                        result = 1; // allowed
                        goto end_check;
                    }
                }
            }
            allowed = true; // if we reach here, all conditions met, return allowed
        }
    }

end_check:
    return allowed ? 1 : 0; // simplified; original returns CONCAT31(upper,1) or (uVar1&0xFFFFFF00)
}