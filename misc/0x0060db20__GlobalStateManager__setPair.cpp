// FUNC_NAME: GlobalStateManager::setPair
// Function at 0x0060db20: Sets a pair of values in a global table and triggers a callback with the old values.
// The global table (g_propertyPairs) is an array of 2-int slots indexed by idx*2.
// After setting new values, calls onPropertyChanged(idx, oldVal1, oldVal2).

// External globals (defined elsewhere)
extern int g_propertyPairs[]; // At 0x011f38f0, each slot is two ints
extern void onPropertyChanged(int idx, int oldVal1, int oldVal2); // At 0x00609340

void GlobalStateManager::setPair(int idx, int newVal1, int newVal2)
{
    // Save old values from the pair table (each index occupies two consecutive ints)
    int oldVal1 = g_propertyPairs[idx * 2];
    int oldVal2 = g_propertyPairs[idx * 2 + 1];

    // Write new values
    g_propertyPairs[idx * 2] = newVal1;
    g_propertyPairs[idx * 2 + 1] = newVal2;

    // Notify any listeners about the change
    onPropertyChanged(idx, oldVal1, oldVal2);
}