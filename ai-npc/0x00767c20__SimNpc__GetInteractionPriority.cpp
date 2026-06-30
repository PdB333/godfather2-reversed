// FUNC_NAME: SimNpc::GetInteractionPriority
// Function address: 0x00767c20
// Returns a priority value for interaction based on NPC state and local player team.
char SimNpc::GetInteractionPriority()
{
    NpcBehaviorComponent* pBehavior = *(NpcBehaviorComponent**)(this + 0x21DC); // +0x21DC: m_pBehaviorComponent
    int isSpecialActionActive = 0;

    // State 0x08 likely corresponds to a combat/attack state
    if (pBehavior->m_state == 0x08) // +0x88: m_state (bitmask: 1=idle, 2=walk, 4=run, 8=attack)
    {
        isSpecialActionActive = pBehavior->CheckPerformableSpecialAction(this); // returns 1 if special action is possible
    }

    byte state = pBehavior->m_state;
    char result = 0;

    if (IsMultiplayer()) // FUN_00800ad0: global check for multiplayer session
    {
        int localPlayerTeam = GetLocalPlayerTeam(); // FUN_00701050: returns 0 or 1 (player team/index)
        int stateIndex = state - 1;

        if (localPlayerTeam == 1) // team 1
        {
            switch (stateIndex)
            {
                case 0: // state == 1 (idle)
                    return 0;
                case 1: // state == 2 (walking)
                    return 4;
                case 3: // state == 4 (running)
                    return 2;
                case 7: // state == 8 (attack)
                    return (isSpecialActionActive != 0) ? 4 : 2;
            }
        }
        else // team 0
        {
            switch (stateIndex)
            {
                case 0:
                    return 1;
                case 1:
                    return 5;
                case 3:
                    return 3;
                case 7:
                    result = (isSpecialActionActive != 0) ? 5 : 3;
            }
        }
    }

    return result;
}