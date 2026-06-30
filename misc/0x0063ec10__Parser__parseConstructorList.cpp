// FUNC_NAME: Parser::parseConstructorList
void Parser::parseConstructorList(ParserContext* ctx) {
    uint* puVar1;
    uint local_itemCount = 0;
    uint local_subCounter = 0;
    int savedPos = ctx->pos; // param_1[1]
    int* basePtr = (int*)ctx->basePtr; // param_1[7]
    int slotIndex = allocateItemSlot(10, *(undefined4*)(basePtr[3] + 8)); // 0x006438e0
    this->slotIndex = slotIndex; // in_EAX[1]
    this->type = 10; // *in_EAX = 10
    this->field3 = 0xffffffff; // in_EAX[3]
    this->field4 = 0xffffffff; // in_EAX[4]
    int local_array[3] = {0, 0, 0xffffffff};
    int local_array2[2] = {0xffffffff, 0xffffffff};
    int* local_ptr = (int*)this; // local_18 = in_EAX

    resetCurrent(); // FUN_00642ec0

    if (ctx->currentToken != '{') { // 0x7b
        char* errorMsg = formatString(&DAT_00e4242c, 0x7b); // FUN_00636c00
        errorMsg = formatString("`%s' expected", errorMsg);
        printError(errorMsg); // FUN_00638b80
        basePtr = (int*)ctx;
        goto LAB_0063ecb6;
    }

    this->nextToken = 0x11f; // in_EAX set to constant
LAB_0063ee02:
    ctx->pos = savedPos; // param_1[2] = param_1[1]
    if (ctx->nextToken == this->nextToken) {
        int* piVar3 = ctx + 4; // param_1 + 4
        goto LAB_0063ecb6;
    }

    ctx->currentToken = ctx->nextToken; // param_1[3] = param_1[5]
    ctx->tokenValue = ctx->field6; // param_1[4] = param_1[6]
    ctx->nextToken = (int)this->nextToken; // param_1[5] = in_EAX

    do {
        if (ctx->currentToken == ';') { // 0x3b
            ctx->pos = savedPos;
            if (ctx->nextToken == this->nextToken) {
                int token = getNextToken(ctx + 4); // FUN_00639c70
                ctx->currentToken = token;
            } else {
                ctx->currentToken = ctx->nextToken;
                ctx->tokenValue = ctx->field6;
                ctx->nextToken = (int)this->nextToken;
            }
        }

        if (ctx->currentToken == '}') goto LAB_0063ee4c; // 0x7d

        if (local_array[0] != 0) {
            resetCurrent(); // FUN_00642ec0
            local_array[0] = 0;
            if (local_subCounter == 0x20) {
                allocateItemSlot(local_itemCount * 0x40 - 0x21 | (local_ptr[1] << 0x18) | 0x1f,
                                 *(undefined4*)(basePtr[3] + 8)); // FUN_006438e0
                local_subCounter = 0;
                basePtr[9] = local_ptr[1] + 1;
            }
        }

        if (ctx->currentToken == '[') { // 0x5b
LAB_0063edc6:
            parseBracketExpression(local_array); // FUN_0063e960
        } else {
            if (ctx->currentToken == 0x116) { // identifier token
                int token = getNextToken(ctx + 6); // FUN_00639c70
                ctx->nextToken = token;
                if (token == '=') goto LAB_0063edc6; // assign
            }
            parseItem(ctx, local_array, 0xffffffff); // FUN_0063fad0
            if (local_itemCount > 0x3ffff) {
                char* errorMsg = formatString("too many %s (limit=%d)", "items in a constructor", 0x3ffff);
                printError(errorMsg);
                basePtr = (int*)ctx;
                goto LAB_0063ee4c;
            }
            local_itemCount++;
            local_subCounter++;
        }

        if (ctx->currentToken != ',') break; // 0x2c

        ctx->pos = savedPos;
        if (ctx->nextToken == this->nextToken) {
            int* tokenPtr = ctx + 4;
LAB_0063ecb6:
            int token = getNextToken(tokenPtr); // FUN_00639c70
        } else {
            token = ctx->nextToken;
            ctx->tokenValue = ctx->field6;
            ctx->nextToken = (int)this->nextToken;
        }
        ctx->currentToken = token;
    } while (true);

    if (ctx->currentToken != ';') {
LAB_0063ee4c:
        finalizeItem(savedPos); // FUN_0063dc80
        finalizeList(); // FUN_0063eb30

        // Compute bit width for item count
        int bitWidth = 0;
        uint temp = local_itemCount;
        while (temp > 7) {
            temp = (temp + 1) >> 1;
            bitWidth++;
        }

        puVar1 = (uint*)(*(int*)(*basePtr + 0xc) + slotIndex * 4);
        *puVar1 ^= (((bitWidth * 8) | temp) << 0xf) ^ *puVar1 & 0xff8000;

        int randomValue = getRandomValue(); // FUN_006367a0
        *extraout_ECX ^= ((randomValue + 1) * 0x40) ^ *extraout_ECX & 0x7fc0;
        return;
    }

    goto LAB_0063ee02;
}