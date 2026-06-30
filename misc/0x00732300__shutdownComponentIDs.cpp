// FUNC_NAME: shutdownComponentIDs
// Address: 0x00732300
// Identified role: Calls a component-disable function with IDs 5,4,3,2 in descending order.
// Likely part of a cleanup or shutdown sequence for a game subsystem (e.g., audio, input, physics).
void __fastcall shutdownComponentIDs(void* componentManager)
{
    // Disable component with index 5
    FUN_008f67c0(5, componentManager);   // +0x14? (assuming unknown callee)
    // Disable component with index 4
    FUN_008f67c0(4, componentManager);   // +0x10?
    // Disable component with index 3
    FUN_008f67c0(3, componentManager);   // +0x0C?
    // Disable component with index 2
    FUN_008f67c0(2, componentManager);   // +0x08?
}