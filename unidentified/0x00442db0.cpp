// FUN_00442db0: performStartupValidation
// Function performs a startup validation by checking a condition and potentially invoking a handler.
// Called from multiple initialization paths (e.g., 0x006828a0, 0x008cb1d0).

void performStartupValidation(void) {
    int status; // local variable passed as pointer to CheckStatus

    status = CheckStatus(&status); // retrieves/updates status via pointer
    if (status >= 0) {
        HandleStatus(); // perform action when status is non-negative
    }
    return;
}