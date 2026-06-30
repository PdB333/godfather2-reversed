// FUNC_NAME: setSomeGlobalFlag
// Address: 0x0041ca30
// Role: Sets a global byte/flag variable, likely used for game state/options.

void setSomeGlobalFlag(byte newValue)
{
    // +0x00: Global byte at 0x01205358 (likely a flag or setting)
    g_globalFlag = newValue;
}