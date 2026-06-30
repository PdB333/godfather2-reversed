// FUNC_NAME: BaseClassUpdate (wrapper calling actual update routine)
// Function address: 0x00466840
// Role: thunk that forwards to FUN_00466090 (the real implementation). Called by many systems across the game.

void BaseClassUpdate(void)
{
    FUN_00466090(); // Forward to the actual update logic
    return;
}