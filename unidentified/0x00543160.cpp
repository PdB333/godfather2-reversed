// FUN_00543160: Entity::performTransition (likely animation/state transition with validation)
// This function checks a condition three times via vtable+0x1f8, then applies four actions via vtable+0x210.
// param_2 (actionId) and param_3 (actionData) are used as arguments.
// Returns 1 on success, 0 if any check fails.
undefined4 __thiscall Entity::performTransition(Entity* this, undefined4 actionId, undefined4 actionData)
{
    // Stack variables for temporary storage and SEH handler registrations (compiler‑generated)
    char checkResult;
    // Temporary copies of parameter values used in vtable calls
    undefined4 tempActionId = actionId;      // uStack_30
    // First condition check
    checkResult = (*(code (__thiscall *)(Entity*))(**(int**)this + 0x1f8))(this);
    if (checkResult == 0) {
        return 0;
    }
    // Second check – uses actionData stored in uStack_38
    undefined4 tempActionData = actionData; // uStack_38
    checkResult = (*(code (__thiscall *)(Entity*))(**(int**)this + 0x1f8))(this);
    if (checkResult == 0) {
        return 0;
    }
    // Third check/action – no return value checked, likely a setup call
    undefined4 tempActionId2 = actionId;    // uStack_40
    (*(code (__thiscall *)(Entity*))(**(int**)this + 0x1f8))(this);
    // Apply four actions via vtable+0x210 with different argument patterns
    // (offset 0x210 corresponds to a method: void __thiscall apply(Entity*, int, void*))
    undefined4 tempActionData2 = actionData; // uStack_48
    (*(code (__thiscall *)(Entity*, int, undefined4*))(**(int**)this + 0x210))(this, 0, &tempActionId);
    (*(code (__thiscall *)(Entity*, int, undefined4*))(**(int**)this + 0x210))(this, 0, &tempActionId2);
    (*(code (__thiscall *)(Entity*, undefined4, undefined4*))(**(int**)this + 0x210))(this, actionId, &tempActionData2);
    (*(code (__thiscall *)(Entity*, undefined4, undefined4*))(**(int**)this + 0x210))(this, actionData, &tempActionData2);
    return 1;
}