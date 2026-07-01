//FUNC_NAME: MultiplayerFriendsManager::refreshFriendsList
void __fastcall MultiplayerFriendsManager::refreshFriendsList(int thisPtr)
{
    int *piVar1;
    int *piVar2;
    uint count;
    int *piVar4;
    int iVar5;
    FriendStatusUpdate *statusUpdate;
    int *piVar7;
    int statusCode;
    uint index;

    // Check if we are in the correct game state (e.g., multiplayer lobby)
    if (*(int *)(g_globalState + 0x10) == 8) {
        // Clear any pending invites or status updates
        clearPendingInvites();

        // Get the friends manager singleton
        piVar1 = (int *)getFriendsManager();
        if (((piVar1 != nullptr) &&
            (piVar2 = (int *)(**(code **)(*piVar1 + 0x44))(), piVar2 != nullptr)) &&
            (piVar2 = (int *)(**(code **)(*piVar2 + 0x34))(), piVar2 != nullptr)) {
            // Get the number of friends
            count = (**(code **)(*piVar2 + 0xc))();
            if (count == 0) {
                // Show "no friends" message
                showLocalizedMessage("$mp_no_friends", 0);
            } else {
                index = 0;
                if (count != 0) {
                    do {
                        // Get friend object by index
                        piVar4 = (int *)(**(code **)(*piVar2 + 0x28))(index);
                        if (((piVar4 != nullptr) &&
                            (piVar4 = (int *)(**(code **)(*piVar4 + 8))(), piVar4 != nullptr)) &&
                            (iVar5 = (**(code **)(*piVar4 + 4))(), iVar5 != 0)) {
                            // Allocate a new FriendStatusUpdate structure (20 bytes)
                            statusUpdate = (FriendStatusUpdate *)allocateMemory(0x14);
                            if (statusUpdate == nullptr) {
                                statusUpdate = nullptr;
                            } else {
                                statusUpdate->type = 5;
                                statusUpdate->field_4 = 0;
                                statusUpdate->field_8 = 0;
                                statusUpdate->field_C = 0;
                                statusUpdate->field_10 = 0;
                            }
                            statusUpdate->type = 5;
                            statusUpdate->friendObj = piVar4;

                            // Get the friend's online status
                            piVar7 = (int *)(**(code **)(*piVar1 + 0x4c))();
                            if ((piVar7 != nullptr) &&
                                (piVar4 = (int *)(**(code **)(*piVar7 + 4))(piVar4), piVar4 != nullptr)) {
                                statusCode = (**(code **)(*piVar4 + 8))();
                                switch (statusCode) {
                                case 1: // Online
                                    statusUpdate->type = 9;
                                    break;
                                case 2: // Away
                                case 3: // Busy
                                    statusUpdate->type = 6;
                                    break;
                                case 4: // Offline
                                    statusUpdate->type = 8;
                                    break;
                                case 5: // Invisible
                                    statusUpdate->type = 7;
                                    break;
                                default:
                                    statusUpdate->type = 5;
                                }
                            }
                            statusUpdate->field_4 = 0;
                            // Add the status update to the processing queue
                            addFriendStatusUpdate(statusUpdate);
                        }
                        index++;
                    } while (index < count);
                    // Notify the callback handler (e.g., UI update)
                    (**(code **)(*(int *)(thisPtr + 0x50) + 0x6c))(0);
                    return;
                }
            }
        }
        // Notify the callback handler even if no friends or error
        (**(code **)(*(int *)(thisPtr + 0x50) + 0x6c))(0);
    }
    return;
}