// FUNC_NAME: getCurrentPlayerIndex
int getCurrentPlayerIndex(void)
{
    // DAT_00f17914 is a global index variable, likely the current player slot
    // DAT_01205608 is an array of player indices (or IDs) indexed by slot
    if (DAT_00f17914 >= 0) {
        return (&DAT_01205608)[DAT_00f17914];
    }
    return 0;
}