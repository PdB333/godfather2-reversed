// FUNC_NAME: PlasmaErrorHandler::reportError
void PlasmaErrorHandler::reportError(int errorCode, int extraInfo)
{
    // Print the prefix
    PlasmaPrint("Plasma Error: ");

    // Map error code to a descriptive string and print it
    const char* errorName = nullptr;
    if (errorCode < 0x1b5b) {
        if (errorCode == 0x1b5a) {
            errorName = "BLOB_ERR_ID_NOT_FOUND ";
        } else if (errorCode == -0x69) {
            errorName = "ERR_BAD_SERVICE_STATE ";
        } else if (errorCode == -0x66) {
            errorName = "ERR_TIMEOUT ";
        } else if (errorCode == 5000) {
            errorName = "RECORD_ERR_NOT_FOUND ";
        }
    } else {
        switch (errorCode) {
        case 0x1b5b:
            errorName = "BLOB_ERR_OWNER_NOT_FOUND ";
            break;
        case 0x1b5f:
            errorName = "BLOB_ERR_NAME_ALREADY_IN_USE ";
            break;
        case 0x1b61:
            errorName = "BLOB_ERR_INVALID_LOCALE ";
            break;
        case 0x1b62:
            errorName = "BLOB_ERR_PERMISSION_DENIED ";
            break;
        default:
            break;
        }
    }

    if (errorName != nullptr) {
        PlasmaPrintString(errorName);   // likely prints the name string
    }

    // Format error code into a buffer
    char buffer[12];                    // local_18, assumed char array
    PlasmaFormatBuffer(buffer, "%d", errorCode);   // DAT_00e3a72c is "%d" format

    if (extraInfo != 0) {
        PlasmaFormatBuffer(buffer, " %d", extraInfo); // DAT_00e3a734 is " %d"
    }

    // If the buffer is non-empty, call the error callback (if set)
    if (buffer[0] != '\0') {
        if (s_errorCallback != nullptr) {
            s_errorCallback(buffer);    // local_c is a global callback function pointer
        }
    }
}