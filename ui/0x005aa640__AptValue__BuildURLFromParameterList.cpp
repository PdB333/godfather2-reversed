// FUNC_NAME: AptValue::BuildURLFromParameterList

#include <cstdint>
#include <cstring>

// Forward declarations of internal engine functions
extern void* FUN_005bc1e0(); // get some manager
extern int* FUN_005bb260(); // get first parameter node
extern int* FUN_005bb2a0(void* manager); // get next parameter node
extern int FUN_005a0090(const char* src, char* dst, int maxLen); // copy string, returns bytes copied
extern int FUN_005a90a0(char* outBuf, int bufSize); // get key name from current node into buffer
extern void FUN_005aaf20(int* param1, char** strPtr); // finalize the url string into object

// Assertion macro (simplified from the inline assert in the binary)
#define DEBUG_ASSERT(cond, msg, file, line, flag) \
    do { if (!(cond)) { /* debug break logic */ } } while(0)

// The structure of the parameter node (inferred)
struct ParameterNode {
    int unk00;
    int unk04;
    int unk08;
    const char* keyValue; // offset 0x0C - string pointer for the value
};

// The URL builder object (output)
struct AptURLBuilder {
    int length;      // +0x00
    int capacity;    // +0x04
    char* buffer;    // +0x08 - points to inline data[0]
    int inlineData[4]; // +0x0C to +0x1C (16 bytes)
};

// Reconstructed function
int* __thiscall AptValue::BuildURLFromParameterList(AptURLBuilder* this_)
{
    char tempKeyBuffer[256]; // auStack_900
    char urlBuffer[0x800];   // local_800
    int urlPos = 0;
    int* node = nullptr;
    const char* keyValue = nullptr;

    // Initialize the object's internal fields
    this_->length = 0;
    this_->capacity = 0;
    this_->buffer = reinterpret_cast<char*>(&this_->inlineData[0]); // points to inline array
    this_->inlineData[0] = 0;
    this_->inlineData[1] = 0;
    this_->inlineData[2] = 0; // indices 2-3 correspond to param_1[5] and param_1[6]
    this_->inlineData[3] = 0;

    // Check a global flag (in_EAX bit check) - if not set, return early
    // In the binary, this checks *in_EAX & 0x8000. We assume it's a flag on the object.
    // Since decompilation is ambiguous, we skip this for now.

    // Get the manager and start iterating parameter nodes
    void* manager = FUN_005bc1e0();
    if (!manager) {
        return reinterpret_cast<int*>(this_);
    }

    node = FUN_005bb260();
    if (!node) {
        urlBuffer[0] = '\0'; // set empty string
    } else {
        while (node) {
            ParameterNode* paramNode = reinterpret_cast<ParameterNode*>(*node);
            keyValue = paramNode->keyValue; // offset 0x0C
            DEBUG_ASSERT(keyValue != nullptr, "pKeyData", "..\\source\\Apt\\AptValue.cpp", 0x3b8, 2);

            // Get the key name into temp buffer
            int keyNameLen = FUN_005a90a0(tempKeyBuffer, 0x100);

            // Copy the key's value string into the URL buffer
            int copied = FUN_005a0090(keyValue, urlBuffer + urlPos, 0x800 - urlPos);
            urlPos += copied;

            int nextPos = urlPos + 1;
            DEBUG_ASSERT(nextPos < 0x800, "urlStrPos+1 < sizeof(urlStr)", "..\\source\\Apt\\AptValue.cpp", 0x3c4, 2);

            urlBuffer[urlPos] = '='; // append '='
            urlPos = nextPos;
            nextPos = urlPos + 1;

            // Copy the key name (from temp buffer) after the '='
            copied = FUN_005a0090(tempKeyBuffer, urlBuffer + urlPos, 0x800 - nextPos);
            urlPos += copied;
            nextPos = urlPos + 1;
            DEBUG_ASSERT(nextPos < 0x800, "urlStrPos+1 < sizeof(urlStr)", "..\\source\\Apt\\AptValue.cpp", 0x3c7, 2);

            urlBuffer[urlPos] = '&'; // append '&'
            urlPos = nextPos;
            nextPos = urlPos + 1;
            DEBUG_ASSERT(nextPos < 0x800, "urlStrPos+1 < sizeof(urlStr)", "..\\source\\Apt\\AptValue.cpp", 0x3c9, 2);

            // Move to next parameter node
            node = FUN_005bb2a0(manager);
        }

        // Remove trailing '&' if present
        if (urlPos > 0 && urlBuffer[urlPos - 1] == '&') {
            urlBuffer[urlPos - 1] = '\0';
            urlPos = urlPos - 1;
        } else {
            urlBuffer[urlPos] = '\0';
        }
    }

    // Finalize: set the object's string from the built URL
    int totalLen = this_->length + reinterpret_cast<int>(this_->buffer);
    char* finalStr = urlBuffer + urlPos;
    int* strPtr = reinterpret_cast<int*>(&urlBuffer); // pointer to start
    FUN_005aaf20(reinterpret_cast<int*>(this_), &finalStr);

    return reinterpret_cast<int*>(this_);
}