// FUNC_NAME: isDistanceLessThanThreshold
bool isDistanceLessThanThreshold(float param1, float param2, float param3)
{
    // Calls a function that likely computes distance or some metric given three inputs and flags (0, 1)
    // The result is compared against a global threshold (squared distance?).
    float distance = computeSomeMetric(param1, param2, param3, 0, 1); // FUN_0084cb90
    return distance < g_someGlobalThreshold; // _DAT_00e51b28
}