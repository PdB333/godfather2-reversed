// FUNC_NAME: PatternMatcher::matchPattern

// Reconstructed C++ from Ghidra at 0x0062bb40.
// This function is a recursive pattern matcher that operates on an input buffer.
// The PatternMatcher object holds pointers to the input start and end.
// patternText is the pattern string, patternIdx is current position within the pattern.
// The function attempts to match from the current input position (m_inputPos) onward.

class PatternMatcher
{
public:
    char* m_inputPos;   // +0x00: current input pointer (updated during match)
    char* m_inputEnd;   // +0x04: end of input buffer
};

// Forward declarations (external functions)
bool matchAnyRemaining(PatternMatcher* obj); // FUN_0062b830 - try to match '%' (greedy remaining)
bool matchCharClass(char c, int depth);     // FUN_0062b940 - check character class e.g. inside '['

// Recursive pattern matching function
int PatternMatcher::matchPattern(PatternMatcher* this, const char* patternText, int patternIdx)
{
    // Try the same pattern from the start of the input, recursing with patternIdx+1
    int result = matchPattern(this, patternText, patternIdx);
    if (result != 0)
    {
        return result;
    }

    // Iterate over input from current position to end
    char* inputPos = this->m_inputPos;   // current input character
    while (inputPos < this->m_inputEnd)
    {
        char patternChar = patternText[patternIdx];
        if (patternChar == '%')
        {
            // '%' matches any remaining characters (greedy)
            bool matched = matchAnyRemaining(this);
            if (!matched) break;
        }
        else if (patternChar != '.')
        {
            // Not a '.' wildcard: must match exactly
            if (patternChar == '[')
            {
                // Character class: check if current input char is in the class
                matched = matchCharClass(*inputPos, patternIdx - 1);
            }
            else
            {
                // Exact match
                matched = (patternChar == *inputPos);
            }
            if (!matched) break;
        }
        // If we reach here, the pattern character matched (either '.' or exact/class match)
        // Advance input position and try to match the rest of the pattern from the next input char
        inputPos++;
        this->m_inputPos = inputPos; // update object's current position
        result = matchPattern(this, patternText, patternIdx + 1);
        if (result != 0)
        {
            return result;
        }
    }
    // No match found
    return 0;
}