// FUNC_NAME: plasmaReportError
void plasmaReportError(int errorCode, int extraData)
{
    char *errorString;
    int localBuffer[3];
    code *printFunc;

    FUN_004d3bc0("Plasma Error: ");
    if (errorCode < 0x1b5b) {
        if (errorCode == 0x1b5a) {
            errorString = "BLOB_ERR_ID_NOT_FOUND ";
        }
        else if (errorCode == -0x69) {
            errorString = "ERR_BAD_SERVICE_STATE ";
        }
        else if (errorCode == -0x66) {
            errorString = "ERR_TIMEOUT ";
        }
        else {
            if (errorCode != 5000) goto switchD_0056772e_caseD_1b5c;
            errorString = "RECORD_ERR_NOT_FOUND ";
        }
    }
    else {
        switch(errorCode) {
        case 0x1b5b:
            errorString = "BLOB_ERR_OWNER_NOT_FOUND ";
            break;
        default:
            goto switchD_0056772e_caseD_1b5c;
        case 0x1b5f:
            errorString = "BLOB_ERR_NAME_ALREADY_IN_USE ";
            break;
        case 0x1b61:
            errorString = "BLOB_ERR_INVALID_LOCALE ";
            break;
        case 0x1b62:
            errorString = "BLOB_ERR_PERMISSION_DENIED ";
        }
    }
    FUN_004d4300(errorString);
switchD_0056772e_caseD_1b5c:
    // Format and output the error code to a local buffer
    FUN_004d4b00(localBuffer, &DAT_00e3a72c, errorCode);
    if (extraData != 0) {
        FUN_004d4b00(localBuffer, &DAT_00e3a734, extraData);
    }
    // If the buffer has content, call the print handler on it
    if (localBuffer[0] != 0) {
        (*printFunc)(localBuffer[0]);
    }
    return;
}