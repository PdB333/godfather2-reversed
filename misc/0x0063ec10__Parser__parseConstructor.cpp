// FUNC_NAME: Parser::parseConstructor
void Parser::parseConstructor(ParserContext* ctx, OutputDescriptor* outDesc)
{
    int* basePtr = (int*)ctx->field_7; // +0x1C? Actually ctx[7] is a pointer
    int currentIndex = ctx->field_1;   // +0x04
    int allocResult = FUN_006438e0(10, *(undefined4*)(basePtr[3] + 8)); // allocate 10 items? basePtr[3] is some size
    outDesc[1] = allocResult; // store allocation index
    int keyFlag = 0;          // local_2c[0] - flag indicating key is being built
    int keyBuffer[3] = {0};   // local_2c array (12 bytes)
    int keyExtra1 = -1;       // local_20
    int keyExtra2 = -1;       // local_1c
    undefined4* keyPtr = outDesc; // local_18 - pointer to output descriptor? Actually set to in_EAX
    int itemCount = 0;        // local_10
    int itemCountInBlock = 0; // local_c - used for bit packing
    int unknown = 0;          // local_14

    outDesc[0] = 10;          // type identifier
    outDesc[3] = -1;
    outDesc[4] = -1;

    FUN_00642ec0(); // reset some state

    // Expect opening brace
    if (ctx->field_3 != 0x7b) { // '{'
        undefined4 errorStr = FUN_00636c00(&DAT_00e4242c, 0x7b); // format error message
        int* errorPtr = (int*)FUN_00636c00("`%s' expected", errorStr);
        FUN_00638b80(errorPtr); // report error
        basePtr = ctx;
        goto exitLabel;
    }

    outDesc = (undefined4*)0x11f; // sentinel value for "no next token"

loopStart:
    ctx->field_2 = ctx->field_1; // save current position
    if ((undefined4*)ctx->field_5 == outDesc) { // if next token is sentinel
        int* tokenPtr = ctx + 4;
        goto getNextToken;
    }
    ctx->field_3 = ctx->field_5; // current token = next token
    ctx->field_4 = ctx->field_6; // save associated data
    ctx->field_5 = (int)outDesc; // set next token to sentinel

    do {
        if (ctx->field_3 == 0x3b) { // ';' - end of statement
            ctx->field_2 = ctx->field_1;
            if ((undefined4*)ctx->field_5 == outDesc) {
                int token = FUN_00639c70(ctx + 4); // get next token
                ctx->field_3 = token;
            } else {
                ctx->field_3 = ctx->field_5;
                ctx->field_4 = ctx->field_6;
                ctx->field_5 = (int)outDesc;
            }
        }
        if (ctx->field_3 == 0x7d) goto exitLabel; // '}' - end of object

        if (keyFlag != 0) {
            FUN_00642ec0(); // reset key buffer
            keyFlag = 0;
            if (itemCountInBlock == 0x20) { // 32 items per block
                // Pack count into allocation header
                FUN_006438e0(itemCount * 0x40 - 0x21 | (keyPtr[1] << 0x18) | 0x1f,
                             *(undefined4*)(basePtr[3] + 8));
                itemCountInBlock = 0;
                basePtr[9] = keyPtr[1] + 1; // increment block index
            }
        }

        if (ctx->field_3 == 0x5b) { // '[' - array start
            FUN_0063e960(keyBuffer); // parse array into key buffer
        } else {
            if (ctx->field_3 == 0x116) { // some token (maybe '='?)
                int token = FUN_00639c70(ctx + 6);
                ctx->field_5 = token;
                if (token == 0x3d) { // '='
                    goto parseArray;
                }
            }
            FUN_0063fad0(ctx, keyBuffer, -1); // parse value
            if (itemCount > 0x3ffff) {
                undefined4 errorStr = FUN_00636c00("too many %s (limit=%d)", "items in a constructor", 0x3ffff);
                FUN_00638b80(errorStr);
                basePtr = ctx;
                goto exitLabel;
            }
            itemCount++;
            itemCountInBlock++;
        }

        if (ctx->field_3 != 0x2c) break; // ',' - separator

        ctx->field_2 = ctx->field_1;
        if ((undefined4*)ctx->field_5 == outDesc) {
            int* tokenPtr = ctx + 4;
getNextToken:
            int token = FUN_00639c70(tokenPtr);
        } else {
            token = ctx->field_5;
            ctx->field_4 = ctx->field_6;
            ctx->field_5 = (int)outDesc;
        }
        ctx->field_3 = token;
    } while (true);

    if (ctx->field_3 == 0x3b) { // ';' - continue to next statement
        goto loopStart;
    }

exitLabel:
    FUN_0063dc80(currentIndex); // cleanup
    FUN_0063eb30(); // finalize

    // Compute bit packing for item count
    int shift = 0;
    unsigned int count = itemCount;
    while (count > 7) {
        count = (count + 1) >> 1;
        shift++;
    }
    // Encode into allocation header
    uint* header = (uint*)(*(int*)(*basePtr + 0xc) + allocResult * 4);
    *header = *header ^ ((shift * 8 | count) << 0xf ^ *header) & 0xff8000;

    int someValue = FUN_006367a0();
    *extraout_ECX = *extraout_ECX ^ ((someValue + 1) * 0x40 ^ *extraout_ECX) & 0x7fc0;
    return;
}