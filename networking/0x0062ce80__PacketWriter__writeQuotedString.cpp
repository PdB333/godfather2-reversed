// FUNC_NAME: PacketWriter::writeQuotedString
void PacketWriter::writeQuotedString(void* thisObj, BufferContext* bufferCtx) {
    const char* str = getString(thisObj); // FUN_00625a70
    if (str == nullptr) {
        logError("string"); // FUN_00627ac0(PTR_s_string_00e2a8ac)
    }

    int remainingLen = getStringLength(); // FUN_00625ae0
    // Ensure space for opening quote
    if (needsFlush(bufferCtx)) { // implied by condition (bufferCtx +0x83 <= currentPtr) and flushCheck
        if (shouldFlush(bufferCtx)) { // FUN_00628940
            flushBuffer(bufferCtx); // FUN_006289a0
        }
    }
    writeByte(bufferCtx, '\"'); // 0x22
    advanceWritePtr(bufferCtx, 1);

    while (true) {
        if (remainingLen == 0) {
            // Write closing quote
            if (needsFlush(bufferCtx)) {
                if (shouldFlush(bufferCtx)) {
                    flushBuffer(bufferCtx);
                }
            }
            writeByte(bufferCtx, '\"');
            advanceWritePtr(bufferCtx, 1);
            return;
        }

        remainingLen--;
        switch (*str) {
            case 0: // Special null token
                writeStaticData(bufferCtx, &DAT_00e418a0, 4); // FUN_00628b20
                goto nextChar;

            default:
                // If buffer is full and we have at least some capacity to flush
                if (needsFlush(bufferCtx)) {
                    int flushSpace = calculateFlushSpace(bufferCtx); // *param_2 - (0xc + param_2)
                    if (flushSpace != 0) {
                        // Complex flush and write via writer object
                        WriterObject* writer = bufferCtx->writerObj; // param_2[2]
                        if (hasRoomInWriterQueue(writer)) { // *(uint*)(*(int*)(writer+0x10)+0x20) <= *(uint*)(*(int*)(writer+0x10)+0x24)
                            int temp = allocateWriterBlock(); // FUN_00627290
                            setWriterState(writer, 0); // FUN_00626f80(writer,0)
                            setWriterFlag(writer, 0); // FUN_00626fd0(0)
                            setWriterState(writer, 0); // FUN_00626f80(writer,0)
                            applyWriterBlock(writer, temp); // FUN_00627010(temp)
                            finalizeWriterBlock(writer); // FUN_006270e0()
                        }
                        int* dest = (int*)writer->writePtr; // *(int**)(writer+8)
                        *dest = 4; // size of data (but might be just a marker)
                        int copied = copyDataToWriter(writer, &bufferCtx->extraData, flushSpace); // FUN_00638920(writer, bufferCtx+3, flushSpace)
                        *(dest + 1) = copied;
                        writer->writePtr += 8; // advance by two ints
                        bufferCtx->count++; // param_2[1]++
                        bufferCtx->currentPtr = (int)(&bufferCtx->extraData); // *param_2 = (int)(param_2+3);
                        flushBuffer(bufferCtx); // FUN_006289a0
                    }
                }
                writeByte(bufferCtx, *str);
                break;

            case '\n': // 0x0a
            case '\"': // 0x22
            case '\\': // 0x5c
                if (needsFlush(bufferCtx)) {
                    if (shouldFlush(bufferCtx)) {
                        flushBuffer(bufferCtx);
                    }
                }
                writeByte(bufferCtx, '\\'); // 0x5c
                advanceWritePtr(bufferCtx, 1);
                if (needsFlush(bufferCtx)) {
                    if (shouldFlush(bufferCtx)) {
                        flushBuffer(bufferCtx);
                    }
                }
                writeByte(bufferCtx, *str);
        }

        advanceWritePtr(bufferCtx, 1); // *param_2 = *param_2 + 1
nextChar:
        str++;
    }
}