// FUNC_NAME: NetSession::getPlayerName
char* __thiscall NetSession::getPlayerName(int playerId) {
    // +0x0c: pointer to game session object (e.g., MultiplayerScenario)
    if (*(int**)(this + 0x0c) == nullptr) {
        return "No Game Joined";
    }

    char* result = "Could not find Player name";
    
    // Virtual call: session->getPlayerInfo(playerId) — vtable offset 0x18 (6th entry)
    int* playerInfo = (int*)(*(int (__thiscall**)(int))(**(int**)(this + 0x0c) + 0x18))(playerId);
    
    if (playerInfo != nullptr) {
        // Virtual call: playerInfo->getName() — vtable offset 0x04 (1st entry)
        result = (char*)(*(char* (__thiscall**)())(*playerInfo + 4))();
    }
    
    return result;
}