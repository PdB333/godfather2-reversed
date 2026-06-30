// FUNC_NAME: Parser::parseBlockOrStatement
void Parser::parseBlockOrStatement(int param_1, int param_2, int param_3) {
    int *piVar1;
    uint *puVar2;
    code *pcVar3;
    int iVar4;
    int local_2c;
    int local_28;
    int local_18;
    int local_14;

    if ((*(int *)(param_2 + 4) < 5) || (8 < *(int *)(param_2 + 4))) {
        // Error: token type out of expected range (5-8)
        FUN_00638b80("syntax error");
        pcVar3 = (code *)swi(3);
        (*pcVar3)();
        return;
    }

    if (*(int *)(param_1 + 0xc) == 0x2c) { // +0x0C: current parse state
        iVar4 = FUN_0063dbf0(); // check for block start
        if (iVar4 != 0) {
            local_18 = param_2;
            FUN_0063f4f0(param_1); // enter block scope
            if (local_14 == 5) { // +0x14: statement count?
                FUN_0063fcb0(); // end block
            }
            // Recursively parse inner statements
            FUN_0063fd40(param_1, &local_18, param_3 + 1);
            goto LAB_0063fdf0;
        }
    }

    FUN_0063dc30(); // reset parse position
    iVar4 = FUN_0063f220(param_1); // get node ID
    if (iVar4 == param_3) { // matching node
        if (local_2c == 0xc) { // +0x2C: token type for semicolon?
            puVar2 = (uint *)(*(int *)(**(int **)(param_1 + 0x1c) + 0xc) + local_28 * 4);
            // +0x1C: current node, +0x0C: flags field
            // Clear bits 7-13 and set bit 7 (0x80 = statement termination flag?)
            *puVar2 = *puVar2 & 0xffff80bf | 0x80;
        }
        FUN_00643090(param_2 + 4); // advance token stream
        return;
    }

    FUN_0063e260(param_3, iVar4); // handle type mismatch
    if (param_3 < iVar4) {
        piVar1 = (int *)(*(int *)(param_1 + 0x1c) + 0x24); // +0x24: node offset
        *piVar1 = *piVar1 + (param_3 - iVar4); // adjust position
    }

LAB_0063fdf0:
    FUN_00643090(param_2 + 4); // advance token stream
    return;
}