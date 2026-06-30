// FUNC_NAME: findShortArraySubstringIndex
// Function address: 0x006a3840
// Role: Search for a null-terminated short array (substring) within another null-terminated short array.
// Returns index of first occurrence (as short count), or -1 if not found.

int __cdecl findShortArraySubstringIndex(short* haystack, short* needle)
{
    int index = 0;

    // If haystack is empty, no match possible
    if (*haystack == 0) {
        return -1;
    }

    do {
        // If needle is empty, return current index
        if (*needle == 0) {
            return index;
        }

        short needleChar = *needle;
        int needleOffset = 0;

        // Scan haystack from current position for first character of needle
        while (haystack[index] != needleChar) {
            needleChar = needle[needleOffset + 1];
            needleOffset = needleOffset + 1;
            if (needleChar == 0) {
                // Reached end of needle without match -> return current index
                return index;
            }
        }

        // Found a match at the current needle character? The loop above exited when haystack[index] == needleChar.
        // Actually the logic: outer while loops over haystack positions; inner while loops over needle characters
        // but the pattern matching is unusual. Let's re-express more clearly.

        // The original logic: 
        // For each i, try to match param_2 at position i.
        // The inner loop: it increments needleOffset while checking if param_1[i] == param_2[needleOffset].
        // But the condition check is done before increment? Actually the code:
        // sVar2 = *param_2;
        // while (param_1[iVar1] != sVar2) {
        //     sVar2 = param_2[iVar3 + 1];
        //     iVar3++;
        //     if (sVar2 == 0) return iVar1;
        // }
        // That is weird: it checks param_1[i] != sVar2, but sVar2 is always param_2[needleOffset].
        // Actually it seems like it is trying to find the position of param_1[i] within param_2.
        // Let me re-read the decompiled assembly? We don't have it.
        // Given the decompiled text, it seems to be a substring search where the inner loop
        // tries to find the current haystack character within the needle. That would be a character set match, not substring.
        // Wait: the outer while condition: if (*param_2 == 0) return iVar1; That means if needle is empty, return current index.
        // Then it sets sVar2 = *param_2 (first character of needle).
        // Then the inner while: while (param_1[iVar1] != sVar2) { ... } 
        // It keeps advancing needleOffset until the haystack char matches the current needle char?
        // But then if it hits end of needle (sVar2==0), it returns iVar1. This is not substring search; it's searching for any character from needle in haystack.
        // Actually, re-reading: The inner loop:
        // sVar2 = *param_2;
        // while (param_1[iVar1] != sVar2) {
        //     sVar2 = param_2[iVar3 + 1];
        //     iVar3 = iVar3 + 1;
        //     if (sVar2 == 0) return iVar1;
        // }
        // This loop increments iVar3 (needle offset) as long as the current haystack char does NOT equal the needle char at that offset.
        // When it finds a match (or needle runs out), it exits. If needle runs out, returns iVar1.
        // So it finds the first character from needle that matches haystack[iVar1]. That is like "strpbrk" for short arrays.
        // But then the outer loop increments iVar1. So overall, it finds the index of the first occurrence of any character from needle in haystack.
        // But the check at the beginning: if *param_2 == 0, return iVar1? That means empty needle -> return current index. So it's like a position of set membership.
        // However, the outer loop condition checks if *param_1 != 0; it increments iVar1 until it hits zero.
        // And if the inner loop returns iVar1, it returns that index.
        // If the inner loop doesn't hit the end of needle, it must have found a match. Then outer loop increments iVar1 and continues.
        // This suggests that the function is doing: for each position i in haystack, check if haystack[i] appears in needle; if yes, return i; else continue. That is exactly strpbrk.
        // But the outer loop condition is while (param_1[iVar1] != 0). So it returns the index of the first haystack character that exists in needle (or -1 if none).
        // However, the original signature says param_1 and param_2 are short*; this could be for Unicode or short index arrays.
        // Given the callers might be using it for set membership, I'll reconstruct accordingly.

        index = index + 1;
    } while (haystack[index] != 0);

    return -1;
}
// End of function

But wait, the decompiled shows "int FUN_006a3840(short *param_1,short *param_2)" and the logic as given. I should follow exactly the logic.
The decompiled logic:
iVar1 = 0;
if (*param_1 != 0) {
    do {
        iVar3 = 0;
        if (*param_2 == 0) { return iVar1; }
        sVar2 = *param_2;
        while (param_1[iVar1] != sVar2) {
            sVar2 = param_2[iVar3 + 1];
            iVar3 = iVar3 + 1;
            if (sVar2 == 0) { return iVar1; }
        }
        iVar1 = iVar1 + 1;
    } while (param_1[iVar1] != 0);
}
return -1;

So the inner while loop:
- Start with sVar2 = first char of needle.
- As long as haystack[iVar1] != sVar2, advance needleOffset iVar3 by 1, get next needle char.
- If we reach end of needle (sVar2 becomes 0), return iVar1.
This means the loop exits when either we find a match (haystack[iVar1] == sVar2) or we exhausted the needle (return). If we found a match, outer loop increments iVar1 and continues.
So the overall behavior: for each index i in haystack (starting at 0), check if haystack[i] appears in needle. If it does, continue to next i; if it does not (i.e., the inner loop exhausts needle without finding a match), then return i? Wait: if inner loop exhausts needle (sVar2 becomes 0), it returns iVar1. That means when the character is NOT in the needle, we return that index. That is the opposite of "find first character that is in needle". Actually, if the character is not in needle, inner loop runs through all needle chars until sVar2==0, then returns iVar1. So it returns the index of the first character that is NOT in the needle. Yes, that's a "find first character not in set" function. Like strcspn but returning index, not count.
Let's test: haystack = "abc", needle = "a". i=0: haystack[0]='a', needle[0]='a' => match, inner loop exits without return. i becomes 1. i=1: haystack[1]='b', inner loop: sVar2='a', compare, not equal; get next sVar2='\0' (since needle has only 'a' and terminator), then sVar2==0 triggers return 1. So returns index 1, which is the first character not in set. If needle = "ab", i=0 match, i=1 match, i=2 'c' not in set, returns 2. If all characters are in set, loop until haystack terminator, then return -1.
That makes sense: it returns the first index in haystack where the character is not in the set defined by needle (including needle termination considered). Or if all haystack characters are in the set, return -1.
But wait: the check at the start: if *param_2 == 0, return iVar1 (=0). That means if needle is empty (no characters), the condition "character not in set" is always true, so return index 0. That matches.
Also, if haystack is empty (*param_1==0), skip loop, return -1 (no index found).
So the function is "findFirstCharNotInSet" or "strcspn" but returning index of first character not in set, not the count.

But the name "strcspn" returns the length of the initial segment not containing any of the set characters. This function returns the index of the first character that is not in the set (which is the same as strcspn when the set is empty? Actually strcspn returns the number of characters before the first occurrence of any character from the set. This function returns the index of the first character NOT in the set. So it's like a complement: given set S, find first index where char ∉ S. That is equivalent to: if we define complement set, then it's like strpbrk on complement. But straightforward.

Given this analysis, I'll name it findFirstNotInSet or findFirstCharNotInSet for short arrays.

I'll produce the reconstructed code with that logic.// FUNC_NAME: findFirstShortNotInSet
// Function address: 0x006a3840
// Role: Search a null-terminated short array (haystack) for the first element that is NOT present
// in the null-terminated short array (set). Returns the index of that element, or -1 if all
// elements in haystack are in the set (including empty haystack).

int __cdecl findFirstShortNotInSet(short* haystack, short* set)
{
    int i = 0;

    // If haystack is empty, return -1 (no element to find)
    if (*haystack == 0) {
        return -1;
    }

    do {
        // If set is empty, the first character is immediately "not in set"
        if (*set == 0) {
            return i;
        }

        // Start with the first character of the set
        short setChar = *set;
        int setIdx = 0;

        // Walk through the set until we find a match for haystack[i] or run out of set
        while (haystack[i] != setChar) {
            setChar = set[setIdx + 1];
            setIdx = setIdx + 1;
            if (setChar == 0) {
                // Exhausted the set without finding haystack[i] -> this is the first not in set
                return i;
            }
        }

        // haystack[i] was found in set; move to next character
        i = i + 1;
    } while (haystack[i] != 0);

    // All characters in haystack were in the set
    return -1;
}