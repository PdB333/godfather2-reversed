// FUNC_NAME: deactivateButton
// Address: 0x00956b30
// Sends a "DeactivateButton" event to the UI system.
void deactivateButton(void)
{
    // Calls the event dispatcher with event name "DeactivateButton", 
    // an integer parameter (0), a pointer to some global data (DAT_00d8c174),
    // another integer (1), and a pointer to a global object (PTR_DAT_00e5743c).
    // The exact semantics of these parameters are unknown.
    sendEvent("DeactivateButton", 0, &DAT_00d8c174, 1, PTR_DAT_00e5743c);
}