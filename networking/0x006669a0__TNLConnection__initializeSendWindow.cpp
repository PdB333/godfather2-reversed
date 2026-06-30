// FUNC_NAME: TNLConnection::initializeSendWindow
int TNLConnection::initializeSendWindow(uint bitmask)
{
    // Allocate a temporary 256-byte buffer (4 elements of 64 bytes)
    void* tmpBuffer = _calloc(4, 0x40);
    if (!tmpBuffer) {
        return -2; // Allocation failure
    }

    // Attempt to set up the send window structure
    if (FUN_00665ce0() == 0) {
        // Initialize window control fields (in_EAX points to connection object)
        connection->windowFlags = 0;          // +0x00
        connection->windowSize = 0;           // +0x04
        _memset((void*)connection->windowData, 0, connection->windowElementCount * 4); // +0x0C, +0x08
        *(undefined4*)connection->windowData = 1; // Set first element active
        connection->windowSize = (*(int*)connection->windowData != 0) ? 1 : 0; // +0x04

        int attempt = 0;
        do {
            // Check window readiness via FUN_0066a660 (returns 0 on success)
            if (FUN_0066a660() != 0) {
                if (tmpBuffer) {
                    _memset(tmpBuffer, 0, 0); // No-op (size zero)
                    _free(tmpBuffer);
                }
                return -3; // Error from window check
            }

            // If the high-priority bit (0x8000000) is set, perform urgent processing
            if ((bitmask & 0x8000000) != 0) {
                if (FUN_00668ce0() != 0) {
                    FUN_00665b40(); // Cleanup on failure
                    return -4;
                }
            }

            ++attempt;
            bitmask <<= 1; // Double the mask (exponential backoff)
        } while (attempt < 28);

        // All attempts succeeded; free temporary buffer
        if (tmpBuffer) {
            _memset(tmpBuffer, 0, 0); // No-op
            _free(tmpBuffer);
        }
        return 0; // Success
    }

    // Initial setup failed
    return -1;
}