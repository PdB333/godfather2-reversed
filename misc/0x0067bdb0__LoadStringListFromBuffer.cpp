// FUNC_NAME: LoadStringListFromBuffer
// 0067bdb0: Loads a delimited list of strings from a buffer into a global array.
// Reads tokens separated by a delimiter (DAT_00d57620) from the given buffer (param_1),
// allocates storage for each token, and stores pointers in a global array.
// Uses a tokenizer (FUN_004d6260) and a memory allocator (FUN_009c8e80).

// Global variables (assumed static)
static char** g_pStringListArray;   // DAT_01129808 - array of string pointers
static int g_nStringListCount;      // DAT_01129804 - number of strings in the list
static int g_bStringListLoaded;     // DAT_01129800 - flag indicating list is loaded

// Delimiter for tokenization (likely a string like "," or " ")
// DAT_00d57620 - assumed to be a global constant (e.g., ",")
extern char DAT_00d57620[]; // or use a constant

// Tokenizer function: reads next token from source into buffer
// Returns non-zero if token found, zero if end of source
// Parameters: char* buffer, int* source, char* delimiter, int maxLen, int flags
extern char FUN_004d6260(char* buffer, int* source, char* delimiter, int maxLen, int flags);

// Memory allocator (likely malloc)
extern void* FUN_009c8e80(int size);

void LoadStringListFromBuffer(int param_1)
{
    char cVar1;
    char* pcVar2;
    void* uVar3;
    char* pcVar4;
    uint uVar5;
    int local_104;
    char local_100 [256];

    if (param_1 != 0) {
        uVar5 = 0;
        local_104 = param_1;
        // Read first token
        cVar1 = FUN_004d6260(local_100, &local_104, &DAT_00d57620, 0x100, 0);
        if (cVar1 != '\0') {
            // Count tokens
            do {
                uVar5 = uVar5 + 1;
                cVar1 = FUN_004d6260(local_100, &local_104, &DAT_00d57620, 0x100, 0);
            } while (cVar1 != '\0');
            if (uVar5 != 0) {
                // Allocate array of pointers (uVar5 * 4 bytes)
                // Overflow check is present but simplified here
                g_pStringListArray = (char**)FUN_009c8e80(uVar5 * 4);
                // Reset source and re-read tokens
                local_104 = param_1;
                cVar1 = FUN_004d6260(local_100, &local_104, &DAT_00d57620, 0x100, 0);
                while (cVar1 != '\0') {
                    // Compute length of token (including null terminator)
                    pcVar2 = local_100;
                    do {
                        cVar1 = *pcVar2;
                        pcVar2 = pcVar2 + 1;
                    } while (cVar1 != '\0');
                    // Allocate memory for the string
                    uVar3 = FUN_009c8e80(pcVar2 + (1 - (int)(local_100 + 1)));
                    g_pStringListArray[g_nStringListCount] = (char*)uVar3;
                    // Copy token into allocated memory
                    pcVar4 = g_pStringListArray[g_nStringListCount];
                    pcVar2 = local_100;
                    do {
                        cVar1 = *pcVar2;
                        *pcVar4 = cVar1;
                        pcVar2 = pcVar2 + 1;
                        pcVar4 = pcVar4 + 1;
                    } while (cVar1 != '\0');
                    g_nStringListCount = g_nStringListCount + 1;
                    // Read next token
                    cVar1 = FUN_004d6260(local_100, &local_104, &DAT_00d57620, 0x100, 0);
                }
                g_bStringListLoaded = 1;
            }
        }
    }
    return;
}