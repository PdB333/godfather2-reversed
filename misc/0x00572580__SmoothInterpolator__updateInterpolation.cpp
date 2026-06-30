// FUNC_NAME: SmoothInterpolator::updateInterpolation

void __thiscall SmoothInterpolator::updateInterpolation(void)
{
    // Check if interpolation is already complete.
    if (*(char *)(this + 0x121) == '\0') {
        if (*(int *)(this + 0x110) == 1) {
            // Interpolation in progress.
            if (*(float *)(this + 0x114) < *(float *)(this + 0x118)) {
                // Compute new current value using an easing formula.
                // Global constants: DAT_00e2b1a4 (some base), DAT_00e2cb90 (scale factor).
                *(float *)(this + 0x114) =
                    (DAT_00e2b1a4 - *(float *)(this + 0x114) / *(float *)(this + 0x118)) * DAT_00e2cb90;
                // Mark as finished and done.
                *(int *)(this + 0x110) = -1;
                *(char *)(this + 0x121) = 1;
                return;
            }
            // If current >= target, reset current to 0 and mark as done.
        }
        *(float *)(this + 0x114) = 0.0f;
        *(int *)(this + 0x110) = -1;
        *(char *)(this + 0x121) = 1;
    }
}