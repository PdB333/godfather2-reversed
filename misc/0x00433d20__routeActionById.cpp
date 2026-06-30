// FUNC_NAME: routeActionById
// Function at 0x00433d20: routes action IDs to specific handlers; currently only action 5 is handled.
void routeActionById(int actionId)
{
    if (actionId == 5) {
        // Dispatch to the handler for action 5 (at 0x00433d90)
        executeActionFive();
    }
}