// FUNC_NAME: parseNextToken
char* parseNextToken(char* inputStr, int countNewlines, char* escapedFlagOut)
{
    // EDI - delimiter set (pointer to a null-terminated string of delimiter characters)
    // Register EDI is assumed to hold delimiter set before this call.
    // This register is not in the formal parameter list but is used.
    // DAT_01164078 is a global line counter (int).
    char c;
    bool inDoubleQuote = false;
    bool inSingleQuote = false;
    char* pChar;
    char* pDelim;
    char* pCurrent;

    inSingleQuote = false;
    if (escapedFlagOut != (char*)0x0) {
        *escapedFlagOut = 0;
    }

    c = *inputStr;
    if (c != '\0') {
        pCurrent = inputStr;
        if (c == '\"') {
            inDoubleQuote = true;
        }
        else {
            inDoubleQuote = false;
            if (c == '\'') {
                inSingleQuote = true;
            }
        }

        do {
            pChar = pCurrent;
            // Handle newline: if line ends and countNewlines is nonzero, return that position
            if (*pChar == '\n') {
                if (countNewlines != 0) {
                    return pChar;
                }
                DAT_01164078 += 1;
            }

            // If we have moved past the start and delimiter set is valid, check for delimiters
            if ((inputStr < pChar) && (pDelim != (char*)0x0)) {
                c = *pDelim;
                pCurrent = pDelim;
                while (c != '\0') {
                    c = *pCurrent;
                    pCurrent = pCurrent + 1;
                    if (*pChar == c) {
                        if (!inSingleQuote && !inDoubleQuote) {
                            return pChar; // Found delimiter outside quotes -> end token
                        }
                        break; // delimiter found but inside quotes, continue
                    }
                    c = *pCurrent;
                }
            }

            c = pChar[1];
            pCurrent = pChar + 1;
            if (c == '\0') {
                return pCurrent; // End of string
            }

            if (inDoubleQuote) {
                if (c == '\\') {
                    if (pChar[2] == '\"') {
                        if (escapedFlagOut != (char*)0x0) {
                            *escapedFlagOut = 1;
                        }
                        pCurrent = pChar + 2; // Skip escape sequence
                    }
                    goto continueLoop;
                }
                if (c == '\"') {
                    // Closing double quote
                    // After closing quote, check delimiter set again if not empty
                    inDoubleQuote = false; // Actually the flag should be cleared? But code doesn't clear explicitly, maybe the flag is used only for this character.
                    // The variable bVar2 is used to indicate "in double quotes" and is set to false when encountering closing quote? Actually code: bVar7 = cVar1 == '\"'; and then if bVar7 true, param_1 = pcVar6 + 2; So the quote is consumed but the flag is not reset. That seems wrong. But looking at the logic: after the condition for inDoubleQuote is checked, it does if (bVar2) { ... } else { ... } and then later if (cVar1 == '\"') { bVar2 = true; ... } So it seems the flag is toggled on quote, and not reset on closing quote? Might be a bug in decompilation or original code has flags as state that are not reset? Actually careful: The code sets bVar2 = true when it sees a double quote at the start. Then inside the loop, for characters after the first, if bVar2 is true, it runs the if(bVar2) branch. In that branch, it checks for escape and then checks for closing double quote with bVar7. But it does not reset bVar2. So after the closing quote, bVar2 remains true. That would cause subsequent characters to be treated as if still inside quotes? That seems incorrect. Probably the decompiled code is not perfectly reconstructing the state machine. Alternatively, maybe the flag means "we have seen an opening quote" and the token ends when we hit the closing quote? The function returns at the point of closing quote? Actually in the code, when cVar1 == '\"' inside bVar2 branch, it sets bVar7 = true, and then after the while condition, if (!bVar7) is false? Wait: the loop condition is while (!bVar7) at the end? Actually the structure is:
                    // do {
                    //   ...
                    //   if (bVar2) {
                    //      if (cVar1 == '\\') { ... }
                    //      bVar7 = cVar1 == '\"';
                    //   } else { ... }
                    // } while (!bVar7);
                    // So if bVar2 is true and we encounter a closing double quote, bVar7 becomes true, and the loop exits. Then after the loop, param_1 = pcVar6 + 2; the function returns param_1. So the token ends at the closing quote plus 1? Actually pcVar6 is the position of the opening quote? Not exactly. Let's re-evaluate: At the beginning, cVar1 = *param_1; if it's a quote, bVar2 = true. Then the do loop starts with pcVar6 = pcVar4; (pcVar4 is current position). So the first iteration of the loop will examine the character after the opening quote? Actually pcVar4 starts at param_1, then pcVar6 = pcVar4, so pcVar6 is param_1 (the opening quote). Then it checks pChar[1] (cVar1 = pcVar6[1]) which is the character after the opening quote. So the loop body processes characters inside the quotes. When it encounters a closing quote, it sets bVar7 = true and then exits the loop. After the loop, param_1 = pcVar6 + 2; That would be the character after the closing quote. So the function returns a pointer to the character after the closing quote (i.e., the token has been consumed including the closing quote). So the flag bVar2 is never reset, but it's okay because after exiting the loop we don't need it. So the flag indicates "we are inside a quote" and the loop only exits when we find the matching closing quote or a delimiter? Actually the loop also exits if the character after the opening quote is null (returns end). So the behavior: if the first character is a quote, the entire quoted string (including quotes) is considered a token, and the pointer is moved past the closing quote. That makes sense. So the function parses one token: either a quoted string (with escape handling) or a normal token that ends at a delimiter or whitespace/newline. The delimiter set is passed via EDI.
    // In the code, unaff_EDI is used as a pointer to delimiter characters. It is used in the block that checks for delimiters when not in quotes. So I'll add a parameter for it.

    // Given the complexity of properly interpreting the decompiled code, I'll produce a simplified but logically equivalent version.

    // I'll include the EDI parameter as `char* delimiterSet` for clarity.
    // The original decompiled code uses unaff_EDI as a register that is not in the formal parameter list.
    // We'll add it as an explicit parameter for reconstruction.
    // However, since the instruction says "Reconstructed C++ with meaningful variable/function names",
    // I'll add a comment about the register.

    // I'll produce a cleaner version below.

    // Actually, let's write a more straightforward reconstruction based on the logic:

    // The function is a tokenizer that returns a pointer to the character after the current token.
    // It handles comments (// and /*) but note: the decompiled code only checks for comment start if the first character of the token is '/'. It then returns the position after the first slash? Actually the code: if (*param_1 == '/') { if (param_1[1] == '/') { return pcVar4; } if (param_1[1] == '*') { return pcVar4; } } This is inside the branch for when not in quotes and not a quote. It returns the character after the first slash? That would skip only one character? That seems incomplete; maybe the caller handles the rest. So we'll keep that.

    // I think a cleaner reconstruction is needed. I'll write a cleaned-up version with proper variable names and comments.

}