// FUNC_NAME: LuaTokenizer::readLongStringOrComment
void LuaTokenizer::readLongStringOrComment(char** outString)
{
    // Ensure output buffer has at least 0x20 bytes capacity
    // Buffer struct: +0x00 data, +0x04 capacity
    DynamicBuffer* buffer = m_buffer;
    if (buffer->capacity < 5 || buffer->capacity < 0x20) {
        buffer->data = (char*)memoryReallocate(buffer->capacity, 0x20);
        buffer->capacity = 0x20;
    }

    // Write opening '['
    buffer->data[0] = '[';
    // Write the second '[' (current char)
    buffer->data[1] = (char)m_currentChar;

    // Decrement stream byte count, read next character
    StreamInfo* stream = m_stream;
    int remaining = stream->remaining;
    stream->remaining = remaining - 1;
    if (remaining == 0) {
        // Refill stream via callback
        uint32_t newSize;
        byte* chunk = (byte*)stream->refillCallback(0, stream->context, &newSize);
        if (chunk == nullptr || newSize == 0) {
            m_currentChar = 0xFFFFFFFF;
        } else {
            stream->currentPtr = chunk;
            stream->remaining = newSize - 1;
            m_currentChar = *chunk;
            stream->currentPtr = chunk + 1;
        }
    } else {
        byte* ptr = stream->currentPtr;
        m_currentChar = *ptr;
        stream->currentPtr = ptr + 1;
    }

    int nesting = 0; // Tracks nested double brackets
    int writePos = 2; // Current write position in buffer (after opening '[[')

    for (;;) {
        // Ensure buffer has space for up to writePos+5 more chars
        if ((uint)buffer->capacity < writePos + 5) {
            uint32_t newCap = writePos + 0x20;
            if (buffer->capacity < newCap) {
                if (newCap < 0x20) newCap = 0x20;
                buffer->data = (char*)memoryReallocate(buffer->capacity, newCap);
                buffer->capacity = newCap;
            }
        }

        switch (m_currentChar) {
        default:
            buffer->data[writePos] = (char)m_currentChar;
            writePos++;
            // Read next char
            remaining = stream->remaining;
            stream->remaining = remaining - 1;
            if (remaining == 0) {
                uint32_t newSize;
                byte* chunk = (byte*)stream->refillCallback(0, stream->context, &newSize);
                if (chunk == nullptr || newSize == 0) {
                    m_currentChar = 0xFFFFFFFF;
                } else {
                    stream->currentPtr = chunk;
                    stream->remaining = newSize - 1;
                    m_currentChar = *chunk;
                    stream->currentPtr = chunk + 1;
                }
            } else {
                byte* ptr = stream->currentPtr;
                m_currentChar = *ptr;
                stream->currentPtr = ptr + 1;
            }
            break;

        case '\n': // newline
            buffer->data[writePos] = '\n';
            handleNewline(); // Likely increments line number
            writePos++;
            if (outString == nullptr) {
                // For comments, stop reading at newline? Actually stop here?
                writePos = 0; // Reset? This seems odd; maybe it ends the token
            }
            // Continue loop
            break;

        case '[': // Opening bracket
            buffer->data[writePos] = '[';
            writePos++;
            // Read next char
            remaining = stream->remaining;
            stream->remaining = remaining - 1;
            if (remaining == 0) {
                uint32_t newSize;
                byte* chunk = (byte*)stream->refillCallback(0, stream->context, &newSize);
                if (chunk == nullptr || newSize == 0) {
                    m_currentChar = 0xFFFFFFFF;
                } else {
                    stream->currentPtr = chunk;
                    stream->remaining = newSize - 1;
                    m_currentChar = *chunk;
                    stream->currentPtr = chunk + 1;
                }
            } else {
                byte* ptr = stream->currentPtr;
                m_currentChar = *ptr;
                stream->currentPtr = ptr + 1;
            }
            if (m_currentChar == '[') {
                // Double bracket '[[' encountered - increase nesting
                nesting++;
                // Write the second '[' and read next
                buffer->data[writePos] = '[';
                writePos++;
                remaining = stream->remaining;
                stream->remaining = remaining - 1;
                if (remaining == 0) {
                    m_currentChar = refillFromGlobalStream(); // or similar
                } else {
                    byte* ptr = stream->currentPtr;
                    m_currentChar = *ptr;
                    stream->currentPtr = ptr + 1;
                }
            }
            break;

        case ']': // Closing bracket
            buffer->data[writePos] = ']';
            writePos++;
            // Read next char
            remaining = stream->remaining;
            stream->remaining = remaining - 1;
            if (remaining == 0) {
                uint32_t newSize;
                byte* chunk = (byte*)stream->refillCallback(0, stream->context, &newSize);
                if (chunk == nullptr || newSize == 0) {
                    m_currentChar = 0xFFFFFFFF;
                } else {
                    stream->currentPtr = chunk;
                    stream->remaining = newSize - 1;
                    m_currentChar = *chunk;
                    stream->currentPtr = chunk + 1;
                }
            } else {
                byte* ptr = stream->currentPtr;
                m_currentChar = *ptr;
                stream->currentPtr = ptr + 1;
            }
            if (m_currentChar == ']') {
                if (nesting == 0) {
                    // End of top-level double bracket - finish token
                    buffer->data[writePos] = ']';
                    // Read one more char (to clean up)
                    remaining = stream->remaining;
                    stream->remaining = remaining - 1;
                    if (remaining == 0) {
                        m_currentChar = refillFromGlobalStream();
                    } else {
                        byte* ptr = stream->currentPtr;
                        m_currentChar = *ptr;
                        stream->currentPtr = ptr + 1;
                    }
                    buffer->data[writePos + 1] = '\0';
                    // If outString requested, extract content (skip opening '[[' and closing ']]')
                    if (outString != nullptr) {
                        *outString = duplicateStringRange(m_stringTable, buffer->data + 2, writePos - 3);
                    }
                    return;
                } else {
                    // Nested double bracket ']]' - decrease nesting and write second ']'
                    nesting--;
                    buffer->data[writePos] = ']';
                    writePos++;
                    // Read next char
                    remaining = stream->remaining;
                    stream->remaining = remaining - 1;
                    if (remaining == 0) {
                        m_currentChar = refillFromGlobalStream();
                    } else {
                        byte* ptr = stream->currentPtr;
                        m_currentChar = *ptr;
                        stream->currentPtr = ptr + 1;
                    }
                }
            }
            break;

        case 0xFFFFFFFF: // EOF
            buffer->data[writePos] = '\0';
            // Report error
            const char* errorMsg = (outString != nullptr) ? "unfinished long string" : "unfinished long comment";
            logError(errorMsg, PTR_s_<eof>_00e2a938, m_unknownField1);
            // Read one more character (probably trailing garbage)
            writePos; // Current position
            m_currentChar = refillFromGlobalStream(); // This reads next byte
            buffer->data[writePos] = (char)m_currentChar;
            // Null terminate again
            buffer->data[writePos + 1] = '\0';
            // If outString requested, extract content
            if (outString != nullptr) {
                *outString = duplicateStringRange(m_stringTable, buffer->data + 2, writePos - 3);
            }
            return;
        }
    }
}