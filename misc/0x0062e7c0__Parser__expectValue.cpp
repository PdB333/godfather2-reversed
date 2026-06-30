// FUNC_NAME: Parser::expectValue
// Address: 0x0062e7c0
// Role: Consumes the next token from the buffer, expecting it to be a value (integer, float, or string).
//       If the token is not a value, calls errorReport with "value expected".
//       After consuming, clears the token buffer (sets entries to zero) and resets read pointer.

bool Parser::expectValue( Parser* thisPtr ) // __thiscall
{
    // +0x08 : current read pointer in token buffer (tokenReadPos)
    // +0x0c : end of token buffer (tokenBufferEnd)
    // +0x10 : pointer to a structure with +0x20 and +0x24 fields (likely buffer manager)
    int* tokenRead = *(int**)(thisPtr + 8);
    int* tokenEnd  = *(int**)(thisPtr + 0xc);

    // Combine into a 64-bit value for unsigned comparison (compiler artifact)
    // In reconstruct we just compare pointers directly.
    // Check that tokenRead is within bounds and the token type is not -1 (invalid)
    if ( tokenRead >= tokenEnd || tokenRead == nullptr || *tokenRead == -1 )
    {
        errorReport( thisPtr, 1, "value expected" );
    }

    int* token = tokenRead; // current token
    int type = *token;
    int data = token[1]; // second field (union: int/ptr/float)

    // If token is empty (type 0) or a string with null data (type==1 && data==0),
    // then try to skip to the next token (if it exists and has positive type)
    if ( type == 0 || (type == 1 && data == 0) )
    {
        char* nextToken = (char*)(token + 2); // advance by 2 ints = 8 bytes
        // Check that nextToken is within bounds and has a valid type (positive)
        if ( nextToken < (char*)tokenEnd && nextToken != nullptr && *(int*)nextToken > 0 )
        {
            // Fall through to the assertion loop
            char* pc = nextToken;
        }
        else
        {
            char* pc = "assertion failed!";
            do
            {
                logAssertionFailed( &DAT_00e3625c, pc ); // &DAT likely a format string "Assertion failed: %s"
                // Re-check boundaries (peephole optimization in decompiled)
                if ( (char*)tokenEnd <= pc || (int*)pc == nullptr ) break;
                if ( *(int*)pc == 4 ) // string token type
                {
                    pc = (char*)(*(int*)((int)pc + 4) + 0x10); // skip string header (+0x10)
                }
                else
                {
                    int result = evaluateTypeOrSomething( thisPtr ); // returns non-zero for success
                    if ( result == 0 )
                    {
                        pc = nullptr;
                    }
                    else
                    {
                        pc = (char*)(*(int*)((int)pc + 4) + 0x10); // same string skip
                    }
                    // Check buffer overflow condition and flush if needed
                    if ( *(uint*)(*(int*)(thisPtr + 0x10) + 0x20) <= *(uint*)(*(int*)(thisPtr + 0x10) + 0x24) )
                    {
                        flushSomething();
                    }
                }
            } while ( (int*)pc != nullptr );

            getStringFromPtr( PTR_s_string_00e2a8ac ); // e.g., "string"
        }
    }

    // Clear the token buffer from the current read position up to end+8
    // Each token entry is 8 bytes; zero them out.
    uint clearStart = (uint)(tokenReadPos); // byte address
    uint clearEnd   = (uint)(tokenBufferEnd) + 8;
    if ( clearEnd > clearStart ) // always true because clearEnd > tokenBufferEnd >= tokenReadPos
    {
        do
        {
            **(undefined4**)(thisPtr + 8) = 0; // clear first 4 bytes of token
            *(int*)(thisPtr + 8) = *(int*)(thisPtr + 8) + 8; // advance read pointer by 8
        } while ( *(uint*)(thisPtr + 8) < (uint)(tokenBufferEnd) + 8U );
    }

    // After clearing, set read pointer to end + 8 (i.e., beyond all tokens)
    *(int*)(thisPtr + 8) = (int)(tokenBufferEnd) + 8;

    return 1; // always returns true
}