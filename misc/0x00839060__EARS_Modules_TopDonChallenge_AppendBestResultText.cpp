// Xbox PDB: EARS_Modules_TopDonChallenge_AppendBestResultText
// FUNC_NAME: MissionRecord::displayBestTimeOrScore
void __fastcall MissionRecord::displayBestTimeOrScore(int this) {
    // +0x8c: bool isTimeBased (0 = time, 1 = score)
    // +0xfc: int value (milliseconds for time, raw score)
    // +0xe8: byte flags (bit0: show as currency)

    // Local structures for string management (likely custom strings with destructor callbacks)
    struct ManagedString {
        char* data;
        uint refCount; // or extra fields
        void* destructor; // code*
        // ...
    } localStr1; // corresponding to local_30
    struct { undefined4 field0; undefined4 field1; undefined4 field2; code* destructor; } localStr2; // local_10
    struct { int handle; undefined4 x; undefined4 y; code* destructor; } textEntry; // local_20

    // Initialize local strings to null
    localStr1.data = nullptr;
    localStr1.refCount = 0;
    localStr1.destructor = nullptr;

    textEntry.handle = 0;
    textEntry.x = 0;
    textEntry.y = 0;
    textEntry.destructor = nullptr;

    char* formattedValue = nullptr;
    char* formatString;

    if (*(int*)(this + 0x8c) == 0) {
        // Time-based record
        uint totalSeconds = (*(int*)(this + 0xfc) + 500) / 1000; // round up ms to seconds
        formatString = "Best time: {B} (Loc)";
        FUN_006042f0(totalSeconds / 60, totalSeconds % 60, &localStr1); // Convert to minutes:seconds
    } else {
        // Score-based record
        formatString = "Best score: {B} (Loc)";
        if ((*(byte*)(this + 0xe8) & 1) == 0) {
            FUN_00603d30(*(undefined4*)(this + 0xfc), &localStr1, 1); // Format as integer
        } else {
            FUN_00604000(*(undefined4*)(this + 0xfc), &localStr1, 1); // Format as currency
        }
    }

    // Use formatted value, default to empty string if null
    char* valueStr = localStr1.data;
    if (valueStr == nullptr) {
        valueStr = &DAT_0120546e; // empty string constant
    }

    // Build final string: e.g., "{B:value}{format}"
    FUN_004d4ad0(&localStr2, "{B:%s}{%s}", valueStr, formatString);
    char* finalStr = localStr2.data;
    if (finalStr == nullptr) {
        finalStr = &DAT_0120546e;
    }

    // Create text renderer entry
    FUN_00603970(&textEntry, finalStr);

    // Set font/size
    FUN_004d44b0(10);

    // Draw text at (0, y) (local textEntry.x is 0, local textEntry.y is used as second param)
    FUN_004d43f0(textEntry.handle, 0, textEntry.y);

    // Cleanup: call destructors for each managed string
    if (textEntry.handle != 0) {
        textEntry.destructor(textEntry.handle);
    }
    if (localStr2.data != nullptr) {
        localStr2.destructor(localStr2.data);
    }
    if (localStr1.data != nullptr) {
        localStr1.destructor(localStr1.data);
    }
    return;
}