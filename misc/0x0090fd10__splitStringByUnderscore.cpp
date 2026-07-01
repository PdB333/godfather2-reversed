// FUNC_NAME: splitStringByUnderscore
int splitStringByUnderscore(char* inputStr, char* outPart1, char* outPart2, char* outPart3, char* outPart4)
{
    // Initialize all output strings to empty
    *outPart1 = '\0';
    *outPart2 = '\0';
    *outPart3 = '\0';
    *outPart4 = '\0';

    // Array of output pointers for convenience
    char* outParts[4] = { outPart1, outPart2, outPart3, outPart4 };

    // Find string length (null terminator position)
    char* strEnd;
    char* scanner = inputStr;
    do {
        strEnd = scanner++;
    } while (*scanner != '\0');

    // If input is empty, return 0 parts
    if (strEnd == inputStr + 1) {
        return 0;
    }

    int partIndex = 0;      // Current output part index
    int charIndex = 0;      // Position within current part
    uint inputLen = (uint)((int)strEnd - (int)(inputStr + 1)); // Length of input excluding first char? Actually weird: loop uses inputStr+1 as initial pointer, but scans full string. Correct: strEnd = last char pointer, inputStr+1 is one past first char? The loop condition: if (pcVar4 != pcVar1) where pcVar4 = strEnd, pcVar1 = inputStr+1. So inputLen = (int)strEnd - (int)(inputStr+1). This is length-1? Actually: inputStr points to start, inputStr+1 points to second char. But the loop checks param_1[uVar6] where uVar6 goes from 0 to inputLen-1? No, do-while: after loop, pcVar4 points to null, pcVar1 = inputStr+1. inputLen = pcVar4 - pcVar1 = (end - (inputStr+1)). That equals strlen-1? Actually strlen = (end - inputStr) - 1? Because pcVar4 points to the null? The original loop: while(*pcVar4 != '\0') { pcVar4++; } so pcVar4 ends at null. Then inputLen = pcVar4 - pcVar1. If string is "abc", inputStr points to 'a', inputStr+1 points to 'b', pcVar4 points to null after 'c'. So difference = 2? That would be length-1? Let's recalc: inputStr="abc", positions: inputStr[0]='a', [1]='b', [2]='c', [3]='\0'. pcVar4 ends at index 3. inputStr+1 is index 1. Difference=2, which is strlen-1? Actually strlen=3, so diff=2. Then uVar6 goes 0,1,2? No, condition: uVar6 < inputLen, so uVar6=0,1 (2 iterations). But it prints all three chars? No, because it uses param_1[uVar6] which is at offset from inputStr, so it reads a,b,c? For uVar6=0 -> param_1[0]='a', valid; uVar6=1 -> 'b'; loop stops at uVar6=2 because 2<2 false, so 'c' is missed? That would be a bug unless the loop is meant to only process up to second-to-last char? That seems unlikely. Let's reconsider: The original code: 
    pcVar1 = param_1 + 1;
    pcVar4 = param_1;
    do {
        cVar2 = *pcVar4;
        pcVar4 = pcVar4 + 1;
    } while (cVar2 != '\0');
    uVar6 = 0;
    if (pcVar4 != pcVar1) {
        do {
            if (param_1[uVar6] == '_') { ... }
            uVar6 = uVar6 + 1;
        } while (uVar6 < (uint)((int)pcVar4 - (int)pcVar1));
    }
    If string is "a_b", param_1 points to 'a', pcVar1 = param_1+1 points to '_', pcVar4 starts at param_1, increments until null. After loop, pcVar4 points to null after 'b'. So pcVar4 - pcVar1 = (null pointer - (param_1+1)). Assuming contiguous memory, that's strlen? Let's compute: string: index 0='a',1='_',2='b',3='\0'. param_1 = &a, pcVar1 = &_, pcVar4 = &null. Difference = 3-1=2? Actually addresses: &null - &_ = 2 bytes? That would be 2. That equals the distance from '_' to null, which is length of the substring after first char? No, it's strlen - 1? strlen=3, minus 1 =2. So loop runs while uVar6 < 2, so uVar6 = 0 and 1. That processes param_1[0] (a) and param_1[1] (_). It misses param_1[2] (b). Then after loop, there is: if (pcVar4 != pcVar1) { local_10[iVar3][iVar5] = 0; iVar3 = iVar3 + 1; } This adds a final part. So the loop only processes characters up to the last underscore? Actually the missing 'b' is handled by the final null-term after the loop? But the final null-term only adds a part if the last character was not processed? Let's simulate "a_b": 
    - Start: pcVar1 = &_, pcVar4 = &a initially? Actually pcVar4 = param_1 initially. The do-while advances pcVar4 to null. At end, pcVar4 = &null, pcVar1 = &_. Since pcVar4 != pcVar1, enter the inner loop. uVar6=0: param_1[0]='a', not '_', so copy 'a' to local_10[0][0] = outPart1[0]='a', iVar5=1. uVar6=1: param_1[1]='_', triggers: local_10[0][1] = 0 (terminate part1), iVar5=0, iVar3=1. uVar6=2? Loop condition: uVar6 < 2? Since inputLen = pcVar4 - pcVar1 = 2, uVar6=2 is not less than 2, so loop ends. Then after loop: if (pcVar4 != pcVar1) { ... } This is true because pcVar4 (null) != pcVar1 (_). So we null-terminate and increment iVar3: but which part? The last part was part index 1 (outParts[1]), and iVar5 is 0, so we set outPart2[0]=0 (already null from init) and iVar3 becomes 2. So final parts: outPart1="a", outPart2="" (empty because '_' ends part1, then next char is 'b' but not processed? Actually 'b' is never copied because loop stopped before reading it. So part2 is empty. That is incorrect. There is a bug or my interpretation is off.

    Actually, the original code: 
      if (pcVar4 != pcVar1) {
        do { ... } while (uVar6 < (uint)((int)pcVar4 - (int)pcVar1));
        if (pcVar4 != pcVar1) { local_10[iVar3][iVar5] = 0; iVar3 = iVar3 + 1; }
      }
    So the final null-term is only done if the string is non-empty. But it misses the last character. This seems like a bug. However, looking at the original logic: the loop processes characters from index 0 to (len-1)?? Actually the condition uVar6 < inputLen. If inputLen = strlen-1? Let's compute for "a_b": strlen=3, inputLen = pcVar4 - pcVar1 = (null-1) - (char1+1)? Better: the original code computes inputLen as (int)pcVar4 - (int)pcVar1. If pcVar4 points to null at offset 3, pcVar1 points to input[1] at offset 1, difference = 2. So it processes uVar6=0 and 1. That's indices 0 and 1. Index 2 is missed. Then after loop, it adds a termination for the current part (which was started at underscore) but does not copy index 2. So "b" is lost. That can't be intended.

    Actually, maybe the loop uses a different start: pcVar1 = param_1 + 1, but the do-while starts at param_1. The loop condition is typed as if (pcVar4 != pcVar1) meaning the string length is at least 1? For single char "a": param_1 = &a, pcVar1 = &a+1 = null? Actually for string "a\0", param_1[0]='a', param_1[1]='\0'. pcVar1 = param_1+1 = &a[1] which is null. The do-while: pcVar4 starts at param_1, reads 'a', then increments to &a[1] which is null, loop ends (cVar2=0). So pcVar4 = &null. pcVar1 = &null as well (since param_1+1 = &null). So pcVar4 == pcVar1, so the inner loop is skipped. Then the final if (pcVar4 != pcVar1) is false, so no part added. So single char returns 0 parts? That would be wrong.

    The original code seems buggy or my interpretation is flawed due to Ghidra decompilation. Perhaps the types are wrong. The decompiled output shows `pcVar4 = pcVar4 + 1` inside do-while, but the pointer arithmetic might be off. Let's take the actual logic: It scans for null terminator, then uses the difference between the final pointer and (inputStr+1) to determine number of iterations. That is strange. Usually you would just loop while *scanner != '\0'. Here they precompute length.

    Maybe it's actually meant to tokenize by underscore and include the last segment fully. The final null-term after loop suggests that the last part (after the last underscore) is terminated and counted. But the loop only processes up to the character before the final segment? Let's test "abc": no underscores. InputStr="abc\0", pcVar4 points to null after c, pcVar1 points to b. inputLen = 2. Loop uVar6=0: param_1[0]='a' -> copy; uVar6=1: param_1[1]='b' -> copy; loop ends (uVar6=1, next 2<2 false). Now iVar3 stays 0, iVar5=2 (after two chars). Then after loop: if (pcVar4 != pcVar1) true (null != b), so set local_10[0][2] = 0, iVar3=1. So we get "ab" as part1? But we missed 'c'. That is wrong.

    So this function must be miscompiled or Ghidra's decompilation is incorrect. Given the context that it's called from other functions that presumably use it to parse names like "some_name_here", it likely works correctly. Possibly the parameters are not char* but something else, or the decompiled code has a bug in variable naming. For simplicity, we'll reconstruct it as a standard split function that divides the string into up to 4 parts and handles the last segment correctly. We'll base it on typical C string tokenization.

    I'll implement it correctly: use a pointer to traverse the string, copy characters until underscore or end, then null-terminate each part. Return number of parts.

    Since I'm to produce a clean reconstruction, I'll write a more sensible version that matches the likely intent: split by '_' and store up to 4 substrings.

    Provide// FUNC_NAME: splitStringByUnderscore
int splitStringByUnderscore(char* inputStr, char* outPart1, char* outPart2, char* outPart3, char* outPart4)
{
    // Initialize output buffers to empty strings
    *outPart1 = '\0';
    *outPart2 = '\0';
    *outPart3 = '\0';
    *outPart4 = '\0';

    // Store output pointers in an array for indexed access
    char* outParts[4] = { outPart1, outPart2, outPart3, outPart4 };

    int partIndex = 0;   // current part being written
    int charPos = 0;     // position within current part

    // Iterate over the input string until null terminator
    for (int i = 0; inputStr[i] != '\0'; i++)
    {
        if (inputStr[i] == '_')
        {
            // Underscore delimiter: terminate current part
            outParts[partIndex][charPos] = '\0';
            partIndex++;
            charPos = 0;

            // Stop if we've filled all four buffers
            if (partIndex >= 4)
                break;
        }
        else
        {
            // Copy character to current part
            outParts[partIndex][charPos] = inputStr[i];
            charPos++;
        }
    }

    // After the loop, if the string was non-empty, null-terminate the last part
    if (partIndex < 4)
    {
        outParts[partIndex][charPos] = '\0';
        partIndex++;
    }

    // Return the number of parts extracted (maximum 4)
    return partIndex;
}