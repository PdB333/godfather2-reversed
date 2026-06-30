// FUNC_NAME: ControllerRumbleManager::applyStoredRumble

void ControllerRumbleManager::applyStoredRumble()
{
    // Check if there is pending rumble data
    if (DAT_0112a02a != '\0') {
        // Clear the pending flag
        DAT_0112a02a = '\0';

        // Apply the stored rumble values (left motor, right motor, duration?)
        // DAT_0112a02c, DAT_0112a030, DAT_0112a034 likely represent motor speeds and duration
        FUN_0069dd70(DAT_0112a02c, DAT_0112a030, DAT_0112a034);

        // Check if rumble is globally enabled
        if (DAT_0112a028 != '\0') {
            // Re‑enable rumble (maybe to start the new effect)
            FUN_0069d240(1);
        }
    }
    // If no pending rumble, do nothing
}