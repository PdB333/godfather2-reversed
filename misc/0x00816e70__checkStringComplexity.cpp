// FUNC_NAME: checkStringComplexity
// Function address: 0x00816e70
// Role: Validates a string by counting words and assigning a weighted score based on word length.
// Returns true if the total score does not exceed a maximum threshold (7).
// The string is taken from a pointer-to-pointer; if NULL, a default string is used.
// Word count and score total are output via parameters.

#include <cstdint>

bool checkStringComplexity(const char** ppString, int* outWordCount, uint32_t* outScoreTotal)
{
    const char* pChar = *ppString;
    bool inWord = false;
    bool valid = true;

    if (pChar == nullptr) {
        pChar = "\x00"; // DAT_0120546e – likely an empty string or default placeholder
    }

    *outWordCount = 0;
    *outScoreTotal = 0;
    uint32_t wordLength = 0;

    do {
        char c = *pChar;

        // Check if current character is whitespace (space, newline, tab, carriage return, form feed, vertical tab, or null)
        bool isWhitespace = (c == ' ') || (c == '\n') || (c == '\t') || 
                            (c == '\r') || (c == '\f') || (c == '\v') || (c == '\0');

        if (isWhitespace) {
            if (inWord) {
                // End of a word – increment word count and add score based on word length
                *outWordCount += 1;

                int addScore;
                if (wordLength < 4) {
                    addScore = 1;
                } else if (wordLength < 8) {
                    addScore = 2;
                } else if (wordLength < 13) {
                    addScore = 3;
                } else {
                    addScore = 5; // wordLength >= 13
                }

                *outScoreTotal += addScore;

                // If total score exceeds 7, mark as invalid (but continue to allow full parse)
                if (*outScoreTotal > 7) {
                    valid = false;
                }

                wordLength = 0;
                inWord = false;
            }

            // If we hit the null terminator, return the current validity state
            if (c == '\0') {
                return valid;
            }
        } else {
            // It's a non-whitespace character – we are inside a word
            inWord = true;
            wordLength++;
        }

        pChar++;

        // Early exit if validity flag is already false
        if (!valid) {
            return false;
        }
    } while (true);
}