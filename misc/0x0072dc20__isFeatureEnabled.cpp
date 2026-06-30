// FUNC_NAME: isFeatureEnabled
// Function at 0x0072dc20: Checks if a feature is enabled by calling a global manager's method.
// Returns 0 if featureId is 0, otherwise returns result of manager's method.
int isFeatureEnabled(int featureId) {
    if (featureId != 0) {
        // DAT_0112af98 is a global pointer to a manager object (likely singleton).
        // FUN_0043b870 is a method that checks something based on the feature ID.
        return FUN_0043b870(*(int*)0x0112af98);  // cast to int for compatibility
    }
    return 0;
}