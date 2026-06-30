// FUNC_NAME: GodfatherGameManager::setMaxCrewSize
// Sets the maximum crew size (clamped to 0-5). Offset +0x174c in game manager singleton.
void GodfatherGameManager::setMaxCrewSize(uint value) {
    GodfatherGameManager* gameManager = (GodfatherGameManager*)DAT_0122350c;
    if (value > 5) {
        *(uint*)((char*)gameManager + 0x174c) = 5;
    } else {
        *(uint*)((char*)gameManager + 0x174c) = value;
    }
}