// FUNC_NAME: Player::processAction
// Function address: 0x00619650
// Role: Updates the player's current action state machine based on stored state IDs.
// It compares the current action ID (+0x14) against several stored action type IDs
// and dispatches to appropriate handler functions with associated parameters.
// Called from Player update loop.

int __thiscall Player::processAction(void)
{
    int currentAction;
    int result;

    // Pre-update step (e.g., clear transient flags)
    Gameplay::preUpdateAction();

    // Initial result from a generic state calculator using first three action parameters
    result = Gameplay::calculateActionState(
                 *(int *)(this + 0x14),   // current action ID
                 *(int *)(this + 0x108),  // action param A
                 *(int *)(this + 0xe0)    // action param B
             );

    currentAction = *(int *)(this + 0x14);

    // Branch based on comparing current action to stored action type IDs
    if (currentAction == *(int *)(this + 0x114))           // Action type: idle/stand
    {
        result = *(int *)(this + 0xa4);                    // Default idle result
        if (*(int *)(this + 0xe4) != 0)                    // Check interrupt flag
        {
            result = Gameplay::executeQuickAction();       // Play immediate action
            return result;
        }
    }
    else if (currentAction == *(int *)(this + 0x118))      // Action type: walk
    {
        result = *(int *)(this + 0xa8);                    // Default walk result
        if (*(int *)(this + 0xe8) != 0)                    // Check walk interrupt
        {
            result = Gameplay::executeQuickAction();
            return result;
        }
    }
    else if (currentAction == *(int *)(this + 0x11c))      // Action type: run
    {
        result = Gameplay::updateActionComponent(
                     currentAction,
                     *(int *)(this + 0xec),                // Run parameter C
                     *(int *)(this + 0xac)                 // Run parameter D
                 );
        return result;
    }
    else if (currentAction == *(int *)(this + 0x128))      // Action type: sprint
    {
        result = Gameplay::updateActionComponent(
                     currentAction,
                     *(int *)(this + 0xf0),                // Sprint parameter E
                     *(int *)(this + 0xac)                 // Reuse D
                 );
        return result;
    }
    else if (currentAction == *(int *)(this + 0x120))      // Action type: crouch
    {
        result = Gameplay::updateActionComponent(
                     currentAction,
                     *(int *)(this + 0xf4),                // Crouch parameter F
                     *(int *)(this + 0xb0)                 // Crouch parameter G
                 );
        return result;
    }
    else if (currentAction == *(int *)(this + 0x124))      // Action type: cover/combat
    {
        // Multiple state updates for combat actions
        Gameplay::updateActionComponent(
            currentAction,
            *(int *)(this + 0xf8),                         // Combat param H
            *(int *)(this + 0xb4)                          // Combat param I
        );
        Gameplay::updateActionComponent(
            *(int *)(this + 0x14),                         // Current action again
            *(int *)(this + 0xfc),                         // Combat param J
            *(int *)(this + 0xb8)                          // Combat param K
        );
        Gameplay::updateActionComponent(
            *(int *)(this + 0x14),
            *(int *)(this + 0x100),                        // Combat param L
            *(int *)(this + 0xbc)                          // Combat param M
        );
        Gameplay::updateActionComponent(
            *(int *)(this + 0x14),
            *(int *)(this + 0x110),                        // Combat param N
            *(int *)(this + 0xa8)                          // Reuse walk default result?
        );
        result = Gameplay::executeComplexAction(
                     *(int *)(this + 0x14),
                     *(int *)(this + 0x104),               // Combat param O
                     this + 0xd0                           // Combat data struct pointer
                 );
        return result;
    }
    else if (currentAction == *(int *)(this + 300))        // Action type 0x12c: special
    {
        result = Gameplay::updateActionComponent(
                     currentAction,
                     *(int *)(this + 0x10c),               // Special param P
                     *(int *)(this + 0xc0)                 // Special param Q
                 );
    }

    return result;
}