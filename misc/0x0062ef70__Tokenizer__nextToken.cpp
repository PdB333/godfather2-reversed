// FUNC_NAME: Tokenizer::nextToken

// Address: 0x0062ef70
// Parses a semicolon-separated token from the input string and appends it to the token buffer.
// Returns a pointer to the next character after the token, or nullptr if input is empty.

char* Tokenizer::nextToken(char* inputStart)
{
  // Skip leading semicolons
  if (*inputStart != '\0') {
    if (*inputStart == ';') {
      inputStart++;
    }

    // Find end of token (semicolon or null terminator)
    char* delim = _strchr(inputStart, ';');
    char* tokenEnd;
    if (delim == nullptr) {
      // No semicolon: token extends to end of string
      tokenEnd = inputStart;
      while (*tokenEnd != '\0') {
        tokenEnd++;
      }
    } else {
      tokenEnd = delim;
    }

    // Allocator check: ensure space in token buffer
    if (*(uint*)(*(int*)(this + 0x10) + 0x20) <= *(uint*)(*(int*)(this + 0x10) + 0x24)) {
      growBuffer(); // reallocate buffer if full
    }

    // Write token entry (type 4 = string)
    TokenEntry* entry = *(TokenEntry**)(this + 8);
    entry->type = 4;
    entry->data = allocateStringCopy(this, inputStart, tokenEnd - inputStart);

    // Advance buffer pointer
    *(int*)(this + 8) = *(int*)(this + 8) + 8;

    return tokenEnd;
  }
  return nullptr;
}