// FUNC_NAME: ConfigFileParser::parsePairsFromSection
void __thiscall ConfigFileParser::parsePairsFromSection(int sectionKey, void* context)
{
    // Offsets:
    // +0x104: count of parsed items (uint32)
    // +0x110: pointer to token buffer (string storage)
    // +0x114: pointer to parser state machine object (vtable at base)
    // +4: array of item pointers (up to 0x40 items)

    // Get the parser state machine from this+0x114
    ParserStateMachine* parserSM = *(ParserStateMachine**)(this + 0x114);
    // Store the initial token buffer (from this+0x110) – used by the parser
    char* tokenBuffer = *(char**)(this + 0x110);

    // Local tokens/state variables
    TokenContext currentTokenCtx;
    TokenResult firstResult;
    char sectionString[36]; // buffer for sprintf

    // Format the section key as a string
    sprintf(sectionString, "%u", sectionKey);

    // Clear the token handle
    tokenHandle = NULL;

    // Get the first token from the parser
    bool hasMore = parserSM->vtable->getFirstToken(sectionString, context, &firstResult);

    while (hasMore) {
        // Determine the current key string
        const char* keyStr = tokenHandle;
        if (keyStr == NULL) {
            keyStr = &DEFAULT_TOKEN_STRING; // e.g., an empty string at 0x0120546e
        }

        // Add this key-value pair to the internal list
        uint32_t itemId = FUN_00568db0(parserSM, tokenBuffer, keyStr, &currentTokenCtx, context);

        // Store item if there's room (max 64 items)
        if (*(uint32_t*)(this + 0x104) < 0x40) {
            *(uint32_t*)(this + 4 + *(uint32_t*)(this + 0x104) * 4) = itemId;
            *(uint32_t*)(this + 0x104) += 1;
        }

        // Advance to the next token
        hasMore = parserSM->vtable->getNextToken(&currentTokenCtx, context, &tokenHandle, &nextTokenAux);
    }

    // Close/finalize the parser
    parserSM->vtable->close();

    // Free any allocated token handle if needed (via free function pointer)
    if (tokenHandle != NULL) {
        free(tokenHandle); // unaff_EBX likely points to free
    }
}