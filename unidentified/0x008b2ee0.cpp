// FUN_NAME: Player::checkKillStreak
void __thiscall Player::checkKillStreak(int thisPlayer, const KillEventContainer& container, int killType)
{
    // +0x50: teamId (int)
    // +0x64: killStreakTimeWindow (int, in ms or game ticks)
    // container holds recent kill events
    // killType identifies the weapon/damage category

    if (killType == -1) {
        return;
    }

    uint32_t streakCount = 0;
    KillEventIterator iter;
    // FUN_004bab20 initializes the iterator to scan events matching killType
    // It takes an output iterator pointer, the container, and a type filter
    KillEventIterator_construct(&iter, container, killType);

    if (!iter.hasMore() && !iter.isValid()) {
        return;
    }

    // Get first event to establish reference timestamp
    KillEvent* firstEvent = iter.current();
    if (firstEvent == nullptr || firstEvent->typeMain != killType) {
        return;
    }

    uint32_t firstTimestamp = firstEvent->timestamp;

    // Scan consecutive events matching team, type, and within time window
    while (iter.hasMore() || iter.isValid()) {
        KillEvent* evt = iter.current();
        if (evt == nullptr) break;

        int playerTeam = *(int*)(thisPlayer + 0x50);
        int timeWindow = *(int*)(thisPlayer + 0x64); // +100 (0x64)

        // Condition: same team, same type, within time window from first event, and kill count positive
        if (evt->teamId == playerTeam &&
            evt->typeMain == killType &&
            firstTimestamp < (uint32_t)(evt->timestamp + timeWindow) &&
            evt->killCount > 0)
        {
            streakCount++;
            iter.next();
        }
        else
        {
            // If the secondary type matches, or timestamp exceeds window, or kill count negative, stop streak
            if (evt->typeSecondary == killType ||
                (uint32_t)(evt->timestamp + timeWindow) <= firstTimestamp ||
                evt->killCount < 0)
            {
                break;
            }
            iter.next();
        }
    }

    // If streak large enough, broadcast fanfare
    if (streakCount > 1) {
        // Logging
        FUN_00604be0();
        uint32_t playerId = FUN_004baf60(killType);
        char** playerNamePtr = (char**)FUN_004bb600(playerId);
        char* playerName = *playerNamePtr;
        if (playerName == nullptr) {
            playerName = "Player"; // fallback string at DAT_0120546e
        }
        FUN_00604c10(0x70, playerName);

        // Select fanfare string based on streak count
        const char* fanfareString;
        if (streakCount == 2) {
            fanfareString = "$hud_fanfare_mp_player_double_kill";
        } else if (streakCount == 3) {
            fanfareString = "$hud_fanfare_mp_player_triple_kill";
        } else {
            fanfareString = "$hud_fanfare_mp_player_multi_kill";
        }

        int params[3] = {0, 0, 0};
        code* callback = nullptr;
        // Build and broadcast UI fanfare event
        FUN_006038a0(DAT_012234a4, (undefined1*)&params, params, fanfareString);
        FUN_0094e5d0(params);
        if (params[0] != 0) {
            callback(params[0]);
        }
        FUN_00604c00();
    }
}