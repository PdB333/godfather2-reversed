// FUNC_NAME: InterpolationManager::setInterpolationValues
void __fastcall InterpolationManager::setInterpolationValues(uint32_t *inputData)
{
    // Store raw float values at global addresses (likely start/end/delta for interpolation)
    *(float*)0x01219a00 = *(float*)inputData[0];    // +0x00: startValue
    *(float*)0x01219a04 = *(float*)inputData[1];    // +0x04: endValue
    *(float*)0x01219a08 = *(float*)inputData[2];    // +0x08: currentTime/delta
    *(float*)0x01219a0c = *(float*)inputData[3];    // +0x0c: duration

    // Check if we are using the default interpolation mode (DAT_012058e8 == &DAT_01219940)
    if (DAT_012058e8 == &DAT_01219940) {
        // Determine which interpolation type to use
        if (DAT_01219954 == DAT_012198f0) {
            // Linear interpolation path
            FUN_0060add0(DAT_01219954, DAT_01219920, inputData);
            return;
        }
        if (DAT_01219954 == DAT_01219a48) {
            // Smooth step interpolation path
            FUN_0060add0(DAT_01219954, DAT_01219a3c, inputData);
            return;
        }
        if (DAT_01219954 == DAT_012198f8) {
            // Ease in/out interpolation path
            FUN_0060add0(DAT_01219954, DAT_0121991c, inputData);
        }
    }
    // If not using default mode, do nothing (return)
}