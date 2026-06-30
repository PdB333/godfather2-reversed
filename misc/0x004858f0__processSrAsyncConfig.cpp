// FUNC_NAME: processSrAsyncConfig
// Function address: 0x004858f0
// Role: Parses command-line or configuration string for "sr_async" related tokens and sets global async load flag.
// The function iterates over a set of possible async override tokens, extracts the associated value, and if it's the first token,
// sets a global boolean indicating whether async loading is enabled.

#include <cstdint>
#include <cstring>

// Static initialization guard
static bool s_asyncConfigInitialized = false;

// Globals (addresses from disassembly)
extern char* g_configString; // DAT_011625d0
extern bool g_asyncLoadEnabled; // DAT_010c3692 (byte)

// Table of tokens to search for (5 entries)
static const char* kAsyncOverrideTokens[5] = {
    "__sr_async__", // placeholder – actual tokens from PTR_s__sr_async_01128684
    "__sr_async2__",
    "__sr_async3__",
    "__sr_async4__",
    "__sr_async5__"
};

// Forward declarations of helper functions (from EARS engine)
void initStreamingSystem(); // FUN_0040ce40
char* getTokenStart(int, int); // FUN_004d5e10 (returns pointer to start of a token)
char* findTokenEnd(char* start, int, char** endOut); // FUN_004d5fd0 (returns pointer to end, writes end pointer)
bool parseIntFromString(int* value); // FUN_004d6d50 (parses integer from string, returns success)

void processSrAsyncConfig(void)
{
    // One-time initialization of streaming system
    if (!(s_asyncConfigInitialized & 1))
    {
        s_asyncConfigInitialized |= 1;
        initStreamingSystem();
    }

    // If no config string present, nothing to do
    if (g_configString == nullptr || *g_configString == '\0')
        return;

    // Check each token in the table
    for (uint32_t tokenIndex = 0; tokenIndex < 5; ++tokenIndex)
    {
        const char* token = kAsyncOverrideTokens[tokenIndex];
        char* foundPos = strstr(g_configString, token);
        if (foundPos == nullptr)
            continue;

        // Token found: extract the value that follows it
        // Use EARS string utility functions to get start and end of the value substring
        char* valueStart = getTokenStart(0, 0); // Returns pointer to start of value (approximation)
        char* valueEnd = nullptr;
        char* /* unused */ = findTokenEnd(valueStart, 0, &valueEnd);

        size_t valueLength = valueEnd - valueStart;
        if (valueLength > 255)
            valueLength = 255;

        char valueBuffer[256]; // local_100
        if (valueLength == 0)
        {
            valueBuffer[0] = '\0';
            // Note: original code had a goto to skip the rest of the loop body for this index – we restructure to continue.
        }
        else
        {
            strncpy(valueBuffer, valueStart, valueLength);
            valueBuffer[valueLength] = '\0';

            // Parse the extracted value as an integer
            int parsedValue = 0;
            bool parseSuccess = parseIntFromString(&parsedValue);
            if (parseSuccess)
            {
                // For the first token (index 0), set the global async load flag based on the parsed value
                if (tokenIndex == 0)
                {
                    g_asyncLoadEnabled = (parsedValue != 0);
                }
            }
        }
        // Continue to next token (original code moved here via goto)
    }
}