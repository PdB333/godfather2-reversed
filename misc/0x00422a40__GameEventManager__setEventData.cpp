// FUNC_NAME: GameEventManager::setEventData
void __thiscall GameEventManager::setEventData(int param_2, int param_3, short param_4, short param_5)
{
    // Read a thread-local variable: likely game mode or platform flag
    // fs:0x2c points to TLS array, offset 0x34 holds a per-thread state
    int gameMode = *(int *)(**(int **)(__readfsdword(0x2c) + 0x34));

    // Store event parameters into this object's fields
    *(int *)(this + 0x16c) = param_2;           // +0x16c: event type / ID
    *(int *)(this + 0x170) = param_3;           // +0x170: additional data
    *(short *)(this + 0x174) = param_4;         // +0x174: first short parameter
    *(short *)(this + 0x176) = param_5;         // +0x176: second short parameter

    // Override event ID if in specific mode (e.g. "alternate" or "demo")
    if (gameMode == 1 && param_2 == DAT_0120589c)
    {
        *(int *)(this + 0x16c) = DAT_012058a4;
    }

    // If in default mode (0), delegate to another method for processing
    if (gameMode == 0)
    {
        FUN_00422960(this, param_2, param_3, param_4, param_5);
    }
}