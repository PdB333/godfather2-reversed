//FUNC_NAME: clearGameStateComponent
void clearGameStateComponent(int componentIndex)
{
    switch (componentIndex) {
    case 0:
        // DAT_011301c0 - likely a global game state component
        resetComponent(&DAT_011301c0, 0);
        return;
    case 1:
        // DAT_011304d8
        resetComponent(&DAT_011304d8, 0);
        return;
    case 2:
        // DAT_01130448
        resetComponent(&DAT_01130448, 0);
        return;
    case 3:
        // DAT_011302c8
        resetComponent(&DAT_011302c8, 0);
        return;
    case 4:
        // DAT_01130310
        resetComponent(&DAT_01130310, 0);
        return;
    case 5:
        // DAT_01130208
        resetComponent(&DAT_01130208, 0);
        return;
    case 6:
        // DAT_011302c0
        resetComponent(&DAT_011302c0, 0);
        break;
    }
    return;
}