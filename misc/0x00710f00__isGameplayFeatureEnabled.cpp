// FUNC_NAME: isGameplayFeatureEnabled
bool isGameplayFeatureEnabled(void)
{
    char result;

    // Check first condition – possibly if a gameplay flag is active
    result = FUN_007eeb50();
    if (result == '\0') {
        // First condition not met; check second condition
        result = FUN_007eeb70();
        if (result == '\0') {
            // Neither condition true
            return false;
        }
    }
    // At least one condition true
    return true;
}