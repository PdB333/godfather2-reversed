// FUNC_NAME: StreamParser::readPrimaryToken

void StreamParser::readPrimaryToken(int context) // context is param_1, a parser state structure
{
    code *pcVar1;
    int this = in_EAX; // implicit this pointer
    undefined4 uVar2;
    int iVar3;
    uint uVar4;
    uint uVar5;
    undefined4 uVar6;
    int iVar7;
    undefined4 local_38[2]; // stack variables for temporary storage
    undefined4 local_30;
    undefined4 local_2c;
    undefined4 local_24;
    undefined4 local_20;

    // this+0x1c points to another structure (likely token reader state)
    iVar7 = *(int *)(this + 0x1c);
    // save current value from that structure +0x24
    uVar6 = *(undefined4 *)(iVar7 + 0x24);

    if (*(int *)(this + 0xc) == 0x116) {
        // Token type is 0x116 (list/array header)
        iVar3 = *(int *)(context + 0x18);
        if (0x7ffffffd < iVar3) {
            uVar2 = formatString("too many %s (limit=%d)", "items in a constructor", 0x7ffffffd);
            reportError(uVar2);
            iVar3 = iVar3;
        }
        *(int *)(context + 0x18) = iVar3 + 1; // increment counter

        local_38[1] = allocateString(); // token string allocation
        local_38[0] = 4; // size hint for readValue
        local_2c = readUint32(*(undefined4 *)(this + 0x1c), &local_38[0]); // read value from stream
        local_24 = 0xffffffff;
        local_20 = 0xffffffff;
        local_30 = 4;
    } else {
        // Token type is something else; process via another method
        readSecondaryToken();
    }

    if (*(int *)(this + 0xc) == 0x3d) {
        // Token type is now 0x3d (value token)
        *(undefined4 *)(this + 8) = *(undefined4 *)(this + 4); // copy field

        if (*(int *)(this + 0x14) == 0x11f) {
            uVar2 = combineFields(this + 0x10);
            *(undefined4 *)(this + 0xc) = uVar2;
        } else {
            *(undefined4 *)(this + 0xc) = *(undefined4 *)(this + 0x14);
            *(undefined4 *)(this + 0x10) = *(undefined4 *)(this + 0x18);
            *(undefined4 *)(this + 0x14) = 0x11f;
        }

        advanceToken(); // next token
        pushBackToken(); // may push back
        uVar4 = advanceToken();
        uVar5 = advanceToken();

        // Construct a packed value: bit fields from context and token stream
        int packedValue = (((*(int *)(*(int *)(context + 0x14) + 4) << 9 | uVar5) << 9 | uVar4) << 6) | 9;
        registerValue(packedValue, *(undefined4 *)(*(int *)(iVar7 + 0xc) + 8));
        // Restore saved state
        *(undefined4 *)(iVar7 + 0x24) = uVar6;
        return;
    }

    // If we reach here, unexpected token type
    uVar6 = formatString(&DAT_00e4242c, 0x3d); // likely format: "`%s' expected" with token name
    uVar6 = formatString("`%s' expected", uVar6);
    reportError(uVar6);
    pcVar1 = (code *)swi(3); // software interrupt (debug break)
    (*pcVar1)();
    return;
}