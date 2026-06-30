// FUNC_NAME: isSystemAboveMinimumSpec
bool isSystemAboveMinimumSpec(void)
{
    // Check multiple system parameters against a threshold stored at DAT_00e2af44
    // Return true if at least one of the parameters meets or exceeds the threshold
    if (((DAT_01219220 < DAT_00e2af44) ||
        (((DAT_01219200 < DAT_00e2af44 && (DAT_01219204 < DAT_00e2af44)) &&
         (DAT_01219208 < DAT_00e2af44)))) &&
        ((DAT_0121922c < DAT_00e2af44 ||
        (((DAT_01219210 < DAT_00e2af44 && (DAT_01219214 < DAT_00e2af44)) &&
         (DAT_01219218 < DAT_00e2af44)))))) {
        return false;
    }
    return true;
}