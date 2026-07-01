// FUNC_NAME: compareCompositeKey
// 0x00835a60: Lexicographic comparison of two 6-element uint arrays.
// Returns 1 if param_1 > param_2, 0 otherwise.
// Used for ordering composite keys (e.g., GUIDs or hash components).
undefined4 __cdecl compareCompositeKey(uint *keyA, uint *keyB) {
    // Lexicographic comparison: compare elements from index 0 to 5.
    // If keyA[i] < keyB[i] at any point, keyA is less, return 0.
    // If keyA[i] > keyB[i], keyA is greater, return 1.
    // If all equal, returns 0 (not greater).
    if ((*keyA <= *keyB) &&
        ((*keyA < *keyB) ||
         ((keyA[1] <= keyB[1]) &&
          ((keyA[1] < keyB[1]) ||
           ((keyA[2] <= keyB[2]) &&
            ((keyA[2] < keyB[2]) ||
             ((keyA[3] <= keyB[3]) &&
              ((keyA[3] < keyB[3]) ||
               ((keyA[4] <= keyB[4]) &&
                ((keyA[4] < keyB[4]) || (keyA[5] <= keyB[5])))
              )
             )
            )
           )
          )
         )
        )
       ) {
        return 0;
    }
    return 1;
}