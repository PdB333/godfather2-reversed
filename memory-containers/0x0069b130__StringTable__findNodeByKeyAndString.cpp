// FUNC_NAME: StringTable::findNodeByKeyAndString
// Address: 0x0069b130
// Description: Searches a linked list of StringNode (embedded in this+4 sentinel) for a node matching both an integer key and a wide string.
// The list is circular with sentinel at class offset +0x04; first node pointer stored at class offset +0x08.
// Node layout:
//   +0x00: prev pointer
//   +0x04: next pointer
//   +0x10: wchar_t buffer (data storage)
//   +0x20: wchar_t* keyString (pointer to the string used for comparison)
//   +0x24: int32_t keyId
// Input parameter (param_2): pointer to a struct with:
//   +0x00: const wchar_t* inputString
//   +0x04: int32_t inputKey
// Returns 1 if a matching node was found and its buffer reset (via FUN_004d3e20), else 0.

#include <cstdint>

// Forward declarations of internal functions (inlined in decompiled code)
static int32_t __thiscall nextNode(int32_t node);      // FUN_00ab3c50 - returns node->next
static void __thiscall resetStringBuffer(wchar_t* buf); // FUN_004d3e20 - clears or initializes string buffer

int32_t __thiscall StringTable::findNodeByKeyAndString(int32_t thisPtr, int32_t* input) {
    // input: input[0] = const wchar_t*, input[1] = int32_t key
    const wchar_t* inputString = reinterpret_cast<const wchar_t*>(input[0]);
    int32_t inputKey = input[1];

    // Start with first node (sentinel->next)
    int32_t currentNode = *reinterpret_cast<int32_t*>(thisPtr + 0x08);

    while (true) {
        // Check if we've looped back to the sentinel (thisPtr + 0x04)
        if (currentNode == thisPtr + 0x04) {
            return 0; // Not found
        }

        // Compare keys
        if (inputKey == *reinterpret_cast<int32_t*>(currentNode + 0x24)) {
            // Keys match; now compare strings
            const wchar_t* storedString = *reinterpret_cast<const wchar_t**>(currentNode + 0x20);
            
            // Byte-by-byte (wchar_t) string comparison
            const wchar_t* s1 = inputString;
            const wchar_t* s2 = storedString;
            int32_t cmpResult;
            while (true) {
                wchar_t c1 = *s1;
                wchar_t c2 = *s2;
                if (c1 != c2) {
                    // Determine sign
                    cmpResult = (c1 < c2) ? -1 : 1;
                    break;
                }
                if (c1 == L'\0') {
                    cmpResult = 0;
                    break;
                }
                ++s1;
                ++s2;
            }

            if (cmpResult == 0) {
                // Match found; clear the node's buffer (offset +0x10)
                resetStringBuffer(reinterpret_cast<wchar_t*>(currentNode + 0x10));
                return 1;
            }
        }

        // Advance to next node
        currentNode = nextNode(currentNode);
    }
}