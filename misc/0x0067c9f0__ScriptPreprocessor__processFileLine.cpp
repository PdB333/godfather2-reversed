// FUNC_NAME: ScriptPreprocessor::processFileLine
// Processes a line from a script/config file. If line starts with '#', handles an include directive.
// param1: line from file, param2: filename or include path (string)
// Returns 1 on success.
int ScriptPreprocessor::processFileLine(char* line, char* includeFileOrPath) {
    char cVar1;
    int* piVar2;
    char* puVar3;
    int flag;
    char* local_164;          // current include source string
    char* local_160;          // temporary string buffer
    uint uStack_15c;          // size info
    uint uStack_158;
    code* local_154;          // destructor/free function
    char* local_150;          // resolved include path
    uint local_14c;
    uint local_148;
    code* local_144;          // destructor for local_150
    int local_140[3];         // stack for string operations (3 ints)
    code* local_134;          // destructor for local_140
    char* puStack_130;        // second include source
    uint uStack_12c;
    uint uStack_128;
    code* pcStack_124;        // destructor for puStack_130
    int local_120[3];         // another string stack
    code* pcStack_114;        // destructor for local_120
    code* pcStack_104;        // destructor for puStack_110
    char buffer[256];         // line read buffer

    local_164 = 0;
    flag = 0;
    local_140[0] = 0;
    local_140[1] = 0;
    local_140[2] = 0;
    local_134 = 0;

    if (*line == '#') {
        // Handle #include directive
        stringPush(line);                          // 0x004d3bc0: push line onto string stack
        outputChar(0x23);                          // 0x004d53a0: output '#'
        local_150 = 0;                             // clear resolved include path
        local_14c = 0;
        local_148 = 0;
        local_144 = 0;
        flag = lookupInTable(&DAT_00e2f04c, 0);    // 0x004d46f0: check if this directive exists in table

        if (flag == 0) {
            piVar2 = local_120;                    // use default string stack
        } else {
            piVar2 = (int*)getStringFromTable(&local_160, &DAT_00e2f04c); // 0x004d5170: get associated value
        }
        stringCompare(piVar2);                     // 0x004d3e20: compare and push?
        if ((flag != 0) && (local_160 != 0)) {
            // Call destructor on temporary string
            (*local_154)(local_160);
        }
        outputNewline();                           // 0x004d5570: output newline?
        outputChar(0x5c);                          // 0x004d53a0: output '\' (backslash continuation?)

        // Fallback to default string if none found
        puVar3 = local_150;
        if (local_150 == 0) {
            puVar3 = &DAT_0120546e;                // default string
        }
        flag = resolveIncludePath(puVar3);         // 0x00412740: actually load/include the path
        stringCompare(local_120);                  // 0x004d3e20: cleanup
        if (local_150 != 0) {
            (*local_144)(local_150);               // free resolved path
        }
        if (local_120[0] != 0) {
            (*pcStack_114)(local_120[0]);          // free stack
        }
    } else {
        stringPush(line);                          // 0x004d4300: push line normally
    }

    // Process additional lines from the include file (if any)
    stringPush(&DAT_00e2f048);                     // 0x004d4300: push global string
    puStack_130 = 0;
    uStack_12c = 0;
    uStack_128 = 0;
    pcStack_124 = 0;

    stringPush(includeFileOrPath);                 // 0x004d3bc0: push include file path

    local_164 = puStack_110;                       // source string for reading
    if (puStack_110 == 0) {
        local_164 = &DAT_0120546e;                 // default source
    }

    cVar1 = readLineFromSource(buffer, &local_164, &DAT_00d57620, 0x100, 0); // 0x004d6260: read a line from source
    if (cVar1 != 0) {
        do {
            stringCompare(local_140);              // 0x004d3e20: cleanup previous
            stringPush(buffer);                    // 0x004d4300: push the read line
            local_160 = 0;                         // new temporary string
            uStack_15c = 0;
            uStack_158 = 0;
            local_154 = 0;

            puVar3 = puStack_130;
            if (puStack_130 == 0) {
                puVar3 = &DAT_0120546e;
            }
            resolveMacro(&local_160, puVar3, flag != 0); // 0x00402e90: macro expansion?
            puVar3 = local_160;
            if (local_160 == 0) {
                puVar3 = &DAT_0120546e;
            }
            processMacroExpansion(puVar3, flag);   // 0x00411c70: handle expanded line

            if (local_160 != 0) {
                (*local_154)(local_160);           // free temporary
            }

            cVar1 = readLineFromSource(buffer, &local_164, &DAT_00d57620, 0x100, 0);
        } while (cVar1 != 0);
    }

    // Cleanup allocated memory
    if (puStack_110 != 0) {
        (*pcStack_104)(puStack_110);
    }
    if (puStack_130 != 0) {
        (*pcStack_124)(puStack_130);
    }
    if (local_140[0] != 0) {
        (*local_134)(local_140[0]);
    }

    return 1;
}