// FUNC_NAME: TimeFormatHelper::formatTimeString
// Function address: 0x0095cf80
// Role: Formats a time string (hours:minutes) from a stored time value (seconds) indexed by a member variable.
// The member at +0x24 is an index into global array g_timeValues (DAT_00d8ccd4). The time value is halved and divided into hours/minutes.
// Result is copied into param_2 buffer (size 0x80) using a safe copy function.

class TimeFormatHelper {
public:
    // Converts a time value (stored as scaled seconds?) to a formatted "H:MM" string.
    // param_2: destination buffer (assumed size >= 0x80)
    void formatTimeString(char* dest);
};

// External unknown functions (not provided, assumed from context):
//   char* SecondsToHoursMinutesString(uint hours, uint minutes, TimeStringStruct* outStruct);  // FUN_006042a0
//   void SafeStringCopy(char* dest, const char* src, int maxLen, int extraFlag);               // FUN_005c4660

// Global arrays (addresses from Ghidra):
extern uint32 g_timeValues[];    // DAT_00d8ccd4
extern const char g_emptyString[]; // DAT_0120546e (empty or default string)

// Struct for time string allocation (assumed from stack layout)
struct TimeStringStruct {
    char* str;      // offset 0x00
    int capacity;   // offset 0x04
    int length;     // offset 0x08
    void (*deleter)(char*); // offset 0x0C (function pointer)
};

void __thiscall TimeFormatHelper::formatTimeString(char* dest) {
    // The member at +0x24 stores an index into g_timeValues
    int timeIndex = *(int*)((uint8*)this + 0x24);
    uint32 rawTime = g_timeValues[timeIndex];

    // The time value appears to be scaled (>>1). Convert to seconds then hours/minutes.
    uint32 seconds = rawTime >> 1;
    uint hours = seconds / 3600;          // 0xe10 = 3600
    uint minutes = (seconds / 60) % 60;   // 0x3c = 60

    // Prepare output struct on stack (initialized to zero)
    TimeStringStruct outStruct;
    outStruct.str = nullptr;
    outStruct.capacity = 0;
    outStruct.length = 0;
    outStruct.deleter = nullptr;

    // Call external function to allocate and format time string
    // (assumes it fills outStruct with a dynamically allocated string)
    SecondsToHoursMinutesString(hours, minutes, &outStruct);

    // Select source string (use fallback if allocation failed)
    const char* src = outStruct.str;
    if (src == nullptr) {
        src = g_emptyString;  // typically an empty string
    }

    // Copy to destination with size limit (0x80) and extra flag
    SafeStringCopy(dest, src, 0x80, outStruct.capacity);  // extra flag may be capacity or similar

    // Free allocated memory if present
    if (outStruct.str != nullptr) {
        outStruct.deleter(outStruct.str);  // call the registered delete function
    }
}