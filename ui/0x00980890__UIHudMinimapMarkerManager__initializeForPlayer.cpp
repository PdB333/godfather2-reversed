// FUNC_NAME: UIHudMinimapMarkerManager::initializeForPlayer
// Address: 0x00980890
// Role: Initialize a minimap marker for a specific player, setting up render handles and team/player indices

void __fastcall UIHudMinimapMarkerManager::initializeForPlayer(UIHudMinimapMarkerManager* this)
{
    // Get pointer to a sub-object at +0x70 (likely a renderer or scene manager) and invoke its first virtual
    code* pfn = **(code***)((char*)this + 0x70);
    int rendererResult = pfn?();  // Virtual call returning some ID or object

    // Clear state fields
    *(int*)((char*)this + 0x11c) = 0;          // player object ID (store later)
    *(int*)((char*)this + 0x104) = 0;          // team/faction
    *(int*)((char*)this + 0x110) = 0;          // something from player+0x70
    *(int*)((char*)this + 0x114) = 0;          // texture handle 1
    *(int*)((char*)this + 0x118) = 0;          // texture handle 2
    *(char*)((char*)this + 0x12c) = 0;         // unknown flag
    *(char*)((char*)this + 0x129) = 0;         // is current player flag
    *(char*)((char*)this + 0x12d) = 0;         // visible/active flag

    // Convert the virtual result to a game object ID and then to a player index
    int objID = FUN_004dafd0(rendererResult);
    int playerIndex = FUN_008ff210(objID);

    if (playerIndex != 0)
    {
        *(int*)((char*)this + 0x11c) = objID;   // store the converted object ID

        int* manager = (int*)FUN_008fdfd0();            // singleton manager (e.g., SimManager, PlayerManager)
        if (manager)
        {
            int* playerObj = (int*)FUN_008c6d50(manager); // get player object from manager
            if (playerObj)
            {
                *(int*)((char*)this + 0x100) = *(int*)((char*)manager + 0xc4);          // from manager (e.g., team ID or color)
                *(int*)((char*)this + 0x104) = *(int*)((char*)playerObj + 4);           // player team/faction
                *(int*)((char*)this + 0x110) = *(int*)((char*)playerIndex + 0x70);      // some player data (position or component)
                *(int*)((char*)this + 0x114) = FUN_008fda40(1);                         // texture handle 1
                *(int*)((char*)this + 0x118) = FUN_008fda40(2);                         // texture handle 2

                // If the player's team is not 0 or 7, check if this is the local player
                if ((*(int*)((char*)this + 0x104) != 0) && (*(int*)((char*)this + 0x104) != 7))
                {
                    int currentPlayerIndex = FUN_008ff3e0();          // get current local player index
                    *(bool*)((char*)this + 0x129) = (currentPlayerIndex == playerIndex);
                }

                FUN_0097fd50(manager, playerIndex);   // bind/register this marker to the player
            }

            char flag = FUN_008fda60();               // e.g., isMultiplayer, isActive
            if (flag)
            {
                int team = *(int*)((char*)this + 0x104);
                // Check if team is one of 1,2,3,4 (valid game teams)
                if (team == 1 || team == 2 || team == 3 || team == 4)
                {
                    *(char*)((char*)this + 0x12d) = 1;   // enable marker visibility
                }
            }
        }
    }
}