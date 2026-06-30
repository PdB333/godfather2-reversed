// FUNC_NAME: Player::getNextValidAction
int __thiscall Player::getNextValidAction(int this, int actionContainer)
{
    int result = 9;                          // default action type (e.g., ACTION_NONE)
    uint currentIdx = *(uint *)(this + 0x35c); // +0x35c: current action slot index

    if (currentIdx < 5)                       // max 5 action slots
    {
        do
        {
            // +0x44: array of 5 action type integers in actionContainer
            result = *(int *)(actionContainer + 0x44 + currentIdx * 4);
            currentIdx = *(uint *)(this + 0x35c) + 1;
            *(uint *)(this + 0x35c) = currentIdx; // advance index
            if (currentIdx > 4)                   // past last slot
            {
                return result;
            }
        } while (result == 0xD);                 // skip action type 13 (e.g., ACTION_UNAVAILABLE)
    }
    return result;
}