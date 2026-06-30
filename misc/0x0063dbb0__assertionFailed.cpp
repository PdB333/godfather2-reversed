//FUNC_NAME: assertionFailed
void __fastcall assertionFailed(int assertionId)
{
    char *errorMsg;
    char *formattedMsg;

    if (assertionId < 0x101) {
        // Use default error message string
        errorMsg = (char *)&DAT_00e4242c; // Default assertion message
    } else {
        // Look up error message from table indexed by assertionId
        errorMsg = *(char **)(&DAT_00e2a4bc + assertionId * 4);
    }

    // Format the error string: "`%s' expected"
    formattedMsg = FUN_00636c00("`%s' expected", errorMsg); // Likely sprintf or similar
    FUN_00638b80(formattedMsg); // Output/log the formatted message

    // Trigger debug breakpoint (int3) and call resulting handler
    void (*handler)() = (void (*)())swi(3); // Software interrupt 3 (debug break)
    handler();
}