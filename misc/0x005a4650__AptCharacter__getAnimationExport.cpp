// FUNC_NAME: AptCharacter::getAnimationExport
// Function address: 0x005a4650
// Role: Looks up an animation export by name (case-insensitive) and returns a pointer to the animation data.
// Uses the Apt library's animation export system. The class holds an animation data structure with an array of export entries.
// Offsets:
//   this+0x28: mAnimationData (pointer to animation data structure)
//   mAnimationData+0x30: nExports (count of exports)
//   mAnimationData+0x34: aExports (array of {char* name, int nID} pairs, each 8 bytes)
//   mAnimationData+0x14: nCharacters (number of character animation slots)
//   mAnimationData+0x18: aCharacters (array of pointers to animation data, size nCharacters)

int AptCharacter::getAnimationExport(char* name) {
    int* animationData = *(int**)(this + 0x28);
    int nExports = *(int*)(animationData + 0x30);
    
    for (int i = 0; i < nExports; i++) {
        char* exportName = *(char**)(*(int*)(animationData + 0x34) + i * 8);
        if (__stricmp(name, exportName) == 0) {
            int exportID = *(int*)(*(int*)(animationData + 0x34) + 4 + i * 8);
            
            // Validate export ID range
            if (exportID < 0 || exportID >= *(int*)(animationData + 0x14)) {
                // Assertion: "mCharacter->animation.aExports[i].nID >= 0 && mCharacter->animation.aExports[i].nID < mCharacter->animation.nCharacters"
                // Debug assert code omitted for clarity
                return 0;
            }
            
            int* characterPtr = *(int**)(*(int*)(animationData + 0x18) + exportID * 4);
            if (characterPtr != 0) {
                return (int)characterPtr;
            }
            
            // Assertion: "pRet" (pointer should not be null)
            // Debug assert code omitted
            return 0;
        }
    }
    
    // Assertion: "0" (export not found)
    // Debug assert code omitted
    return 0;
}