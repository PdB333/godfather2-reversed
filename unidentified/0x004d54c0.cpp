// FUNC_004d54c0: StringBuffer::stripQuotes

#include <cstdint>

class StringBuffer {
public:
    char* data;       // +0x00: pointer to character buffer
    int32_t length;   // +0x04: current length of string (excluding null terminator)

    // Removes matching outer quotes (single or double) if present.
    // Returns (original buffer high 24 bits) | 1 on success, or the incoming EAX value unchanged.
    // Note: The incoming EAX is expected to be some flags; stored in 'in_EAX'.
    // Implementation based on Ghidra decompilation.
    uint32_t stripQuotes(uint32_t in_EAX = 0);
};

uint32_t StringBuffer::stripQuotes(uint32_t in_EAX) {
    char* buffer = this->data;
    if (buffer == nullptr) {
        return in_EAX & 0xFFFFFF00U;
    }

    // Skip leading whitespace
    char* start = buffer;
    char ch;
    do {
        ch = *start;
        if (!(ch == ' ' || ch == '\n' || ch == '\t' || ch == '\r' || ch == '\f' || ch == '\v'))
            break;
        ++start;
    } while (true);

    // Check for quote character
    char quote = ch;
    if (quote != '\"' && quote != '\'') {
        return in_EAX & 0xFFFFFF00U;
    }

    // Find last non-whitespace character
    char* end = buffer + this->length - 1;
    while (end >= buffer) {
        char c = *end;
        if (!(c == ' ' || c == '\n' || c == '\t' || c == '\r' || c == '\f' || c == '\v'))
            break;
        --end;
    }

    // Verify matching quote and non‑empty content
    if (*end == quote && start < end) {
        int newLen = (int)(end - start - 1);
        // Copy content (excluding quotes) to the beginning of the buffer
        char* src = start + 1;
        char* dst = buffer;
        for (int i = 0; i < newLen; ++i) {
            *dst++ = *src++;
        }
        *dst = '\0';
        this->length = newLen;
        // Construct return value: high 24 bits of buffer pointer, low byte = 1
        uintptr_t ptrVal = reinterpret_cast<uintptr_t>(buffer);
        return (static_cast<uint32_t>(ptrVal) & 0xFFFFFF00U) | 1U;
    }

    return in_EAX & 0xFFFFFF00U;
}