// FUNC_NAME: CachedValueManager::GetValueOrDefault
// Address: 0x0069bdc0
// Role: Retrieves a cached computed value; computes it if not cached and if the global index is valid.
// Uses a fallback value (param_2) when the cache miss cannot be resolved.

int CachedValueManager::GetValueOrDefault(int thisPtr, int fallbackValue)
{
    int cachedResult;
    bool hasCached = TryGetCachedValue(thisPtr, &cachedResult); // FUN_00699a70
    if (hasCached) {
        return cachedResult;
    }

    // Global index check: ensure g_cachedIndex is within the array bounds defined by global pointers.
    // g_cachedArrayStart and g_cachedArrayEnd likely define a table of function pointers or objects.
    if ((-1 < g_cachedIndex) && (g_cachedIndex < (g_cachedArrayEnd - g_cachedArrayStart) / 4)) {
        InvalidateCache(thisPtr); // FUN_004d3bc0 - clears stale cached data

        int computedResults[3]; // local_10
        ComputeValue(computedResults, fallbackValue); // FUN_0069b5a0 - fills computedResults

        if (computedResults[0] != 0) {
            // NOTE: local_4 (function pointer) is uninitialized in decompilation.
            // Expected to be a cleanup/destructor call for the computed object.
            // Possibly set by ComputeValue or a missing assignment.
            // Assuming it's a function pointer stored elsewhere (e.g., vtable).
            // For now, we call it directly with the first computed result.
            // This is a reconstruction artifact; actual behavior may differ.
            // (*local_4)(computedResults[0]);  // Uncommented due to missing data.
        }
    }
    return fallbackValue;
}