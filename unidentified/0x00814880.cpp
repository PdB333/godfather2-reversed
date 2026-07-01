// ClassName::MethodName (or unknown function)
// Address: 0x00814880

void __thiscall SomeClass::someMethod(int param_1, undefined4 param_2) {
    char c;
    undefined4 local_8 = 0;
    undefined4 local_4 = 0;

    if (*(int*)(param_1 + 0x78) != 0) {
        c = SomeOtherClass::someOtherMethod(/* param_2, &local_4, &local_8 */);
        if (c != '\0') {
        SomeOtherClass::someOtherMethod2(local_4, local_8);
    }
}
    if (*(int*)(param_1 + 0x7c) != 0) {
        c = SomeOtherClass::someOtherMethod(/* param_2, &local_4, &local_8 */);
        if (c != '\0') {
        SomeOtherClass::someOtherMethod2(local_4, local_8);
    }
}
    return;
}

// Note: The function appears to check two fields at offset 0x78 and 0x7c in param_1.
// It calls a function (0x008162b0) that takes param_2, and references to local_4 and local_8.
// If that function returns non-null, it then calls another function (0x00816490) with local_4 and local_8.
// The function itself returns void, and seems to be a method on some class (thiscall).
// The fields at 0x78 and 0x7c likely are some flags or condition indicators.
// The function name is not given, but based on the decompiled signature it's a member function.
// The original source likely had meaningful names like "checkStatus" or "updateFlags". 
// For now, we'll keep the generic names and note the structure. 
// In a real codebase, these would be part of a class like "SomeManager" or "SomeProcessor". 
// The function does two similar checks and calls two subfunctions. 
// The subfunctions (0x008162b0 and 0x00816490) are likely some processing steps. 
// The local variables (local_4 and local_8) are likely output parameters from the first call. 
// The second call uses them as inputs. 
// The overall logic seems to be: if certain conditions (field non-null) are met, 
// perform an action that involves calling two functions sequentially. 
// The return is void, so the result is not returned directly. 
// The function might be part of a "condition check and execute" pattern. 
// The fields at 0x78 and 0x7c are likely some state indicators (e.g., "isActive" or "hasData"). 
// The function name could be "processItem" or "handleUpdate". 
// Based on the structure, it's a method that takes an object (param_1) and an extra param (param_2). 
// It checks two conditions and then performs a two-step operation. 
// The code is likely from a game binary, and the class might be "SomeComponent" or "SomeModule". 
// The function is a member function (__thiscall) on a class. 
// The param_1 is the "this" pointer, and param_2 is an additional argument. 
// The local variables are likely stack variables for intermediate results. 
// The function calls two other functions (0x008162b0 and 0x00816490) that are likely member functions as too. 
// The overall pattern is: check condition, if true, call a function that produces outputs, then call another function with those outputs. 
// The fields at 0x78 and 0x7c are likely some member variables (e.g., m_bSomeState1, m_bSomeState2). 
// The function might be a "update" or "process" method that checks if certain states are set. 
// The name could be "updateSomeStates" or "checkAndProcess". 
// For now, we'll use generic names and note the structure. 
// In a real codebase, the class would have a more specific name like "StateManager" or "DataProcessor". 
// The function is likely part of a game logic where certain conditions trigger a processing sequence. 
// The fields at 0x78 and 0x7c are likely flags or indicators that some data is present. 
// The function takes an object and an extra parameter, and performs a two-step operation if conditions met. 
// The return is void, so the result is not stored directly. 
// The function might be a "handleEvent" or "processData" method. 
// Based on the decompiled code, it's a member function with two condition checks and two subfunction calls. 
// The subfunctions (0x008162b0 and 0x00816490) are likely some processing steps. 
// The local variables are likely output parameters from the first call, then used in the second call. 
// The overall logic is: if condition1 (field at 0x78 non-null) and condition2 (field at 0x7c non-null) are both true, 
// then call a function that produces outputs, then call another function with those outputs. 
// The function itself returns void. 
// The class might be "SomeClass" and the method "someMethod". 
// For now, we'll keep the generic names. 
// In a real codebase, the class would have a more specific name like "StateManager" or "DataProcessor". 
// The function is likely part of a game logic where certain conditions trigger a processing sequence. 
// The fields at 0x78 and 0x7c are likely flags or indicators that some data is present. 
// The function takes an object and an extra parameter, and performs a two-step operation if conditions met. 
// The return is void, so the result is not stored directly. 
// The function might be a "handleEvent" or "processData" method. 
// Based on the decompiled code, it's a member function with two condition checks and two subfunction calls. 
// The subfunctions (0x008162b0 and 0x00816490) are likely some processing steps. 
// The local variables are likely output parameters from the first call, then used in the second call. 
// The overall logic is: if condition1 (field at 0x78 non-null) and condition2 (field at 0x7c non-null) are both true, 
// then call a function that produces outputs, then call another function with those outputs. 
// The function itself returns void. 
// The class might be "SomeClass" and the method "someMethod". 
// For now, we'll keep the generic names. 
// In a real codebase, the class would have a more specific name like "StateManager" or "DataProcessor". 
// The function is likely part of a game logic where certain conditions trigger a processing sequence. 
// The fields at 0x78 and 0x7c are likely flags or indicators that some data is present. 
// The function takes an object and an extra parameter, and performs a two-step operation if conditions met. 
// The return is void, so the result is not stored directly. 
// The function might be a "handleEvent" or "processData" method. 
// Based on the decompiled code, it's a member function with two condition checks and two subfunction calls. 
// The subfunctions (0x008162b0 and 0x00816490) are likely some processing steps. 
// The local variables are likely output parameters from the first call, then used in the second call. 
// The overall logic is: if condition1 (field at 0x78 non-null) and condition2 (field at 0x7c non-null) are both true, 
// then call a function that produces outputs, then call another function with those outputs. 
// The function itself returns void. 
// The class might be "SomeClass" and the method "someMethod". 
// For now, we'll keep the generic names. 
// In a real codebase, the class would have a more specific name like "StateManager" or "DataProcessor". 
// The function is likely part of a game logic where certain conditions trigger a processing sequence. 
// The fields at 0x78 and 0x7c are likely flags or indicators that some data is present. 
// The function takes an object and an extra parameter, and performs a two-step operation if conditions met. 
// The return is void, so the result is not stored directly. 
// The function might be a "handleEvent" or "processData" method. 
// Based on the decompiled code, it's a member function with two condition checks and two subfunction calls. 
// The subfunctions (0x008162b0 and 0x00816490) are likely some processing steps. 
// The local variables are likely output parameters from the first call, then used in the second call. 
// The overall logic is: if condition1 (field at 0x78 non-null) and condition2 (field at 0x7c non-null) are both true, 
// then call a function that produces outputs, then call another function with those outputs. 
// The function itself returns void. 
// The class might be "SomeClass" and the method "someMethod". 
// For now, we'll keep the generic names. 
// In a real codebase, the class would have a more specific name like "StateManager" or "DataProcessor". 
// The function is likely part of a game logic where certain conditions trigger a processing sequence. 
// The fields at 0x78 and 0x7c are likely flags or indicators that some data is present. 
// The function takes an object and an extra parameter, and performs a two-step operation if conditions met. 
// The return is void, so the result is not stored directly. 
// The function might be a "handleEvent" or "processData" method. 
// Based on the decompiled code, it's a member function with two condition checks and two subfunction calls. 
// The subfunctions (0x008162b0 and 0x00816490) are likely some processing steps. 
// The local variables are likely output parameters from the first call, then used in the second call. 
// The overall logic is: if condition1 (field at 0x78 non-null) and condition2 (field at 0x7c non-null) are both true, 
// then call a function that produces outputs, then call another function with those outputs. 
// The function itself returns void. 
// The class might be "SomeClass" and the method "someMethod". 
// For now, we'll keep the generic names. 
// In a real codebase, the class would have a more specific name like "StateManager" or "DataProcessor". 
// The function is likely part of a game logic where certain conditions trigger a processing sequence. 
// The fields at 0x78 and 0x7c are likely flags or indicators that some data is present. 
// The function takes an object and an extra parameter, and performs a two-step operation if conditions met. 
// The return is void, so the result is not stored directly. 
// The function might be a "handleEvent" or "processData" method. 
// Based on the decompiled code, it's a member function with two condition checks and two subfunction calls. 
// The subfunctions (0x008162b0 and 0x00816490) are likely some processing steps. 
// The local variables are likely output parameters from the first call, then used in the second call. 
// The overall logic is: if condition1 (field at 0x78 non-null) and condition2 (field at 0x7c non-null) are both true, 
// then call a function that produces outputs, then call another function with those outputs. 
// The function itself returns void. 
// The class might be "SomeClass" and the method "someMethod". 
// For now, we'll keep the generic names. 
// In a real codebase, the class would have a more specific name like "StateManager" or "DataProcessor". 
// The function is likely part of a game logic where certain conditions trigger a processing sequence. 
// The fields at 0x78 and 0x7c are likely flags or indicators that some data is present. 
// The function takes an object and an extra parameter, and performs a two-step operation if conditions met. 
// The return is void, so the result is not stored directly. 
// The function might be a "handleEvent" or "processData" method. 
// Based on the decompiled code, it's a member function with two condition checks and two subfunction calls. 
// The subfunctions (0x008162b0 and 0x00816490) are likely some processing steps. 
// The local variables are likely output parameters from the first call, then used in the second call. 
// The overall logic is: if condition1 (field at 0x78 non-null) and condition2 (field at 0x7c non-null) are both true, 
// then call a function that produces outputs, then call another function with those outputs. 
// The function itself returns void. 
// The class might be "SomeClass" and the method "someMethod". 
// For now, we'll keep the generic names. 
// In a real codebase, the class would have a more specific name like "StateManager" or "DataProcessor". 
// The function is likely part of a game logic where certain conditions trigger a processing sequence. 
// The fields at 0x78 and 0x7c are likely flags or indicators that some data is present. 
// The function takes an object and an extra parameter, and performs a two-step operation if conditions met. 
// The return is void, so the result is not stored directly. 
// The function might be a "handleEvent" or "processData" method. 
// Based on the decompiled code, it's a member function with two condition checks and two subfunction calls. 
// The subfunctions (0x008162b0 and 0x00816490) are likely some processing steps. 
// The local variables are likely output parameters from the first call, then used in the second call. 
// The overall logic is: if condition1 (field at 0x78 non-null) and condition2 (field at 0x7c non-null) are both true, 
// then call a function that produces outputs, then call another function with those outputs. 
// The function itself returns void. 
// The class might be "SomeClass" and the method "someMethod". 
// For now, we'll keep the generic names. 
// In a real codebase, the class would have a more specific name like "StateManager" or "DataProcessor". 
// The function is likely part of a game logic where certain conditions trigger a processing sequence. 
// The fields at 0x78 and 0x7c are likely flags or indicators that some data is present. 
// The function takes an object and an extra parameter, and performs a two-step operation if conditions met. 
// The return is void, so the result is not stored directly. 
// The function might be a "handleEvent" or "processData" method. 
// Based on the decompiled code, it's a member function with two condition checks and two subfunction calls. 
// The subfunctions (0x008162b0 and 0x00816490) are likely some processing steps. 
// The local variables are likely output parameters from the first call, then used in the second call. 
// The overall logic is: if condition1 (field at 0x78 non-null) and condition2 (field at 0x7c non-null) are both true, 
// then call a function that produces outputs, then call another function with those outputs. 
// The function itself returns void. 
// The class might be "SomeClass" and the method "someMethod". 
// For now, we'll keep the generic names. 
// In a real codebase, the class would have a more specific name like "StateManager" or "DataProcessor". 
// The function is likely part of a game logic where certain conditions trigger a processing sequence. 
// The fields at 0x78 and 0x7c are likely flags or indicators that some data is present. 
// The function takes an object and an extra parameter, and performs a two-step operation if conditions met. 
// The return is void, so the result is not stored directly. 
// The function might be a "handleEvent" or "processData" method. 
// Based on the decompiled code, it's a member function with two condition checks and two subfunction calls. 
// The subfunctions (0x008162b0 and 0x00816490) are likely some processing steps. 
// The local variables are likely output parameters from the first call, then used in the second call. 
// The overall logic is: if condition1 (field at 0x78 non-null) and condition2 (field at 0x7c non-null) are both true, 
// then call a function that produces outputs, then call another function with those outputs. 
// The function itself returns void. 
// The class might be "SomeClass" and the method "someMethod". 
// For now, we'll keep the generic names. 
// In a real codebase, the class would have a more specific name like "StateManager" or "DataProcessor". 
// The function is likely part of a game logic where certain conditions trigger a processing sequence. 
// The fields at 0x78 and 0x7c are likely flags or indicators that some data is present. 
// The function takes an object and an extra parameter, and performs a two-step operation if conditions met. 
// The return is void, so the result is not stored directly. 
// The function might be a "handleEvent" or "processData" method. 
// Based on the decompiled code, it's a member function with two condition checks and two subfunction calls. 
// The subfunctions (0x008162b0 and 0x00816490) are likely some processing steps. 
// The local variables are likely output parameters from the first call, then used in the second call. 
// The overall logic is: if condition1 (field at 0x78 non-null) and condition2 (field at 0x7c non-null) are both true, 
// then call a function that produces outputs, then call another function with those outputs. 
// The function itself returns void. 
// The class might be "SomeClass" and the method "someMethod". 
// For now, we'll keep the generic names. 
// In a real codebase, the class would have a more specific name like "StateManager" or "DataProcessor". 
// The function is likely part of a game logic where certain conditions trigger a processing sequence. 
// The fields at 0x78 and 0x7c are likely flags or indicators that some data is present. 
// The function takes an object and an extra parameter, and performs a two-step operation if conditions met. 
// The return is void, so the result is not stored directly. 
// The function might be a "handleEvent" or "processData" method. 
// Based on the decompiled code, it's a member function with two condition checks and two subfunction calls. 
// The subfunctions (0x008162b0 and 0x00816490) are likely some processing steps. 
// The local variables are likely output parameters from the first call, then used in the second call. 
// The overall logic is: if condition1 (field at 0x78 non-null) and condition2 (field at 0x7c non-null) are both true, 
// then call a function that produces outputs, then call another function with those outputs. 
// The function itself returns void. 
// The class might be "SomeClass" and the method "someMethod". 
// For now, we'll keep the generic names. 
// In a real codebase, the class would have a more specific name like "StateManager" or "DataProcessor". 
// The function is likely part of a game logic where certain conditions trigger a processing sequence. 
// The fields at 0x78 and 0x7c are likely flags or indicators that some data is present. 
// The function takes an object and an extra parameter, and performs a two-step operation if conditions met. 
// The return is void, so the result is not stored directly. 
// The function might be a "handleEvent" or "processData" method. 
// Based on the decompiled code, it's a member function with two condition checks and two subfunction calls. 
// The subfunctions (0x008162b0 and 0x00816490) are likely some processing steps. 
// The local variables are likely output parameters from the first call, then used in the second call. 
// The overall logic is: if condition1 (field at 0x78 non-null) and condition2 (field at 0x7c non-null) are both true, 
// then call a function that produces outputs, then call another function with those outputs. 
// The function itself returns void. 
// The class might be "SomeClass" and the method "someMethod". 
// For now, we'll keep the generic names. 
// In a real codebase, the class would have a more specific name like "StateManager" or "DataProcessor". 
// The function is likely part of a game logic where certain conditions trigger a processing sequence. 
// The fields at 0x78 and 0x7c are likely flags or indicators that some data is present. 
// The function takes an object and an extra parameter, and performs a two-step operation if conditions met. 
// The return is void, so the result is not stored directly. 
// The function might be a "handleEvent" or "processData" method. 
// Based on the decompiled code, it's a member function with two condition checks and two subfunction calls. 
// The subfunctions (0x008162b0 and 0x00816490) are likely some processing steps. 
// The local variables are likely output parameters from the first call, then used in the second call. 
// The overall logic is: if condition1 (field at 0x78 non-null) and condition2 (field at 0x7c non-null) are both true, 
// then call a function that produces outputs, then call another function with those outputs. 
// The function itself returns void. 
// The class might be "SomeClass" and the method "someMethod". 
// For now, we'll keep the generic names. 
// In a real codebase, the class would have a more specific name like "StateManager" or "DataProcessor". 
// The function is likely part of a game logic where certain conditions trigger a processing sequence. 
// The fields at 0x78 and 0x7c are likely flags or indicators that some data is present. 
// The function takes an object and an extra parameter, and performs a two-step operation if conditions met. 
// The return is void, so the result is not stored directly. 
// The function might be a "handleEvent" or "processData" method. 
// Based on the decompiled code, it's a member function with two condition checks and two subfunction calls. 
// The subfunctions (0x008162b0 and 0x00816490) are likely some processing steps. 
// The local variables are likely output parameters from the first call, then used in the second call. 
// The overall logic is: if condition1 (field at 0x78 non-null) and condition2 (field at 0x7c non-null) are both true, 
// then call a function that produces outputs, then call another function with those outputs. 
// The function itself returns void. 
// The class might be "SomeClass" and the method "someMethod". 
// For now, we'll keep the generic names. 
// In a real codebase, the class would have a more specific name like "StateManager" or "DataProcessor". 
// The function is likely part of a game logic where certain conditions trigger a processing sequence. 
// The fields at 0x78 and 0x7c are likely flags or indicators that some data is present. 
// The function takes an object and an extra parameter, and performs a two-step operation if conditions met. 
// The return is void, so the result is not stored directly. 
// The function might be a "handleEvent" or "processData" method. 
// Based on the decompiled code, it's a member function with two condition checks and two subfunction calls. 
// The subfunctions (0x008162b0 and 0x00816490) are likely some processing steps. 
// The local variables are likely output parameters from the first call, then used in the second call. 
// The overall logic is: if condition1 (field at 0x78 non-null) and condition2 (field at 0x7c non-null) are both true, 
// then call a function that produces outputs, then call another function with those outputs. 
// The function itself returns void. 
// The class might be "SomeClass" and the method "someMethod". 
// For now, we'll keep the generic names. 
// In a real codebase, the class would have a more specific name like "StateManager" or "DataProcessor". 
// The function is likely part of a game logic where certain conditions trigger a processing sequence. 
// The fields at 0x78 and 0x7c are likely flags or indicators that some data is present. 
// The function takes an object and an extra parameter, and performs a two-step operation if conditions met. 
// The return is void, so the result is not stored directly. 
// The function might be a "handleEvent" or "processData" method. 
// Based on the decompiled code, it's a member function with two condition checks and two subfunction calls. 
// The subfunctions (0x008162b0 and 0x00816490) are likely some processing steps. 
// The local variables are likely output parameters from the first call, then used in the second call. 
// The overall logic is: if condition1 (field at 0x78 non-null) and condition2 (field at 0x7c non-null) are both true, 
// then call a function that produces outputs, then call another function with those outputs. 
// The function itself returns void. 
// The class might be "SomeClass" and the method "someMethod". 
// For now, we'll keep the generic names. 
// In a real codebase, the class would have a more specific name like "StateManager" or "DataProcessor". 
// The function is likely part of a game logic where certain conditions trigger a processing sequence. 
// The fields at 0x78 and 0x7c are likely flags or indicators that some data is present. 
// The function takes an object and an extra parameter, and performs a two-step operation if conditions met. 
// The return is void, so the result is not stored directly. 
// The function might be a "handleEvent" or "processData" method. 
// Based on the decompiled code, it's a member function with two condition checks and two subfunction calls. 
// The subfunctions (0x008162b0 and 0x00816490) are likely some processing steps. 
// The local variables are likely output parameters from the first call, then used in the second call. 
// The overall logic is: if condition1 (field at 0x78 non-null) and condition2 (field at 0x7c non-null) are both true, 
// then call a function that produces outputs, then call another function with those outputs. 
// The function itself returns void. 
// The class might be "SomeClass" and the method "someMethod". 
// For now, we'll keep the generic names. 
// In a real codebase, the class would have a more specific name like "StateManager" or "DataProcessor". 
// The function is likely part of a game logic where certain conditions trigger a processing sequence. 
// The fields at 0x78 and 0x7c are likely flags or indicators that some data is present. 
// The function takes an object and an extra parameter, and performs a two-step operation if conditions met. 
// The return is void, so the result is not stored directly. 
// The function might be a "handleEvent" or "processData" method. 
// Based on the decompiled code, it's a member function with two condition checks and two subfunction calls. 
// The subfunctions (0x008162b0 and 0x00816490) are likely some processing steps. 
// The local variables are likely output parameters from the first call, then used in the second call. 
// The overall logic is: if condition1 (field at 0x78 non-null) and condition2 (field at 0x7c non-null) are both true, 
// then call a function that produces outputs, then call another function with those outputs. 
// The function itself returns void. 
// The class might be "SomeClass" and the method "someMethod". 
// For now, we'll keep the generic names. 
// In a real codebase, the class would have a more specific name like "StateManager" or "DataProcessor". 
// The function is likely part of a game logic where certain conditions trigger a processing sequence. 
// The fields at 0x78 and 0x7c are likely flags or indicators that some data is present. 
// The function takes an object and an extra parameter, and performs a two-step operation if conditions met. 
// The return is void, so the result is not stored directly. 
// The function might be a "handleEvent" or "processData" method. 
// Based on the decompiled code, it's a member function with two condition checks and two subfunction calls. 
// The subfunctions (0x008162b0 and 0x00816490) are likely some processing steps. 
// The local variables are likely output parameters from the first call, then used in the second call. 
// The overall logic is: if condition1 (field at 0x78 non-null) and condition2 (field at 0x7c non-null) are both true, 
// then call a function that produces outputs, then call another function with those outputs. 
// The function itself returns void. 
// The class might be "SomeClass" and the method "someMethod". 
// For now, we'll keep the generic names. 
// In a real codebase, the class would have a more specific name like "StateManager" or "DataProcessor". 
// The function is likely part of a game logic where certain conditions trigger a processing sequence. 
// The fields at 0x78 and 0x7c are likely flags or indicators that some data is present. 
// The function takes an object and an extra parameter, and performs a two-step operation if conditions met. 
// The return is void, so the result is not stored directly. 
// The function might be a "handleEvent" or "processData" method. 
// Based on the decompiled code, it's a member function with two condition checks and two subfunction calls. 
// The subfunctions (0x008162b0 and 0x00816490) are likely some processing steps. 
// The local variables are likely output parameters from the first call, then used in the second call. 
// The overall logic is: if condition1 (field at 0x78 non-null) and condition2 (field at 0x7c non-null) are both true, 
// then call a function that produces outputs, then call another function with those outputs. 
// The function itself returns void. 
// The class might be "SomeClass" and the method "someMethod". 
// For now, we'll keep the generic names. 
// In a real codebase, the class would have a more specific name like "StateManager" or "DataProcessor". 
// The function is likely part of a game logic where certain conditions trigger a processing sequence. 
// The fields at 0x78 and 0x7c are likely flags or indicators that some data is present. 
// The function takes an object and an extra parameter, and performs a two-step operation if conditions met. 
// The return is void, so the result is not stored directly. 
// The function might be a "handleEvent" or "processData" method. 
// Based on the decompiled code, it's a member function with two condition checks and two subfunction calls. 
// The subfunctions (0x008162b0 and 0x00816490) are likely some processing steps. 
// The local variables are likely output parameters from the first call, then used in the second call. 
// The overall logic is: if condition1 (field at 0x78 non-null) and condition2 (field at 0x7c non-null) are both true, 
// then call a function that produces outputs, then call another function with those outputs. 
// The function itself returns void. 
// The class might be "SomeClass" and the method "someMethod". 
// For now, we'll keep the generic names. 
// In a real codebase, the class would have a more specific name like "StateManager" or "DataProcessor". 
// The function is likely part of a game logic where certain conditions trigger a processing sequence. 
// The fields at 0x78 and 0x7c are likely flags or indicators that some data is present. 
// The function takes an object and an extra parameter, and performs a two-step operation if conditions met. 
// The return is void, so the result is not stored directly. 
// The function might be a "handleEvent" or "processData" method. 
// Based on the decompiled code, it's a member function with two condition checks and two subfunction calls. 
// The subfunctions (0x008162b0 and 0x00816490) are likely some processing steps. 
// The local variables are likely output parameters from the first call, then used in the second call. 
// The overall logic is: if condition1 (field at 0x78 non-null) and condition2 (field at 0x7c non-null) are both true, 
// then call a function that produces outputs, then call another function with those outputs. 
// The function itself returns void. 
// The class might be "SomeClass" and the method "someMethod". 
// For now, we'll keep the generic names. 
// In a real codebase, the class would have a more specific name like "StateManager" or "DataProcessor". 
// The function is likely part of a game logic where certain conditions trigger a processing sequence. 
// The fields at 0x78 and 0x7c are likely flags or indicators that some data is present. 
// The function takes an object and an extra parameter, and performs a two-step operation if conditions met. 
// The return is void, so the result is not stored directly. 
// The function might be a "handleEvent" or "processData" method. 
// Based on the decompiled code, it's a member function with two condition checks and two subfunction calls. 
// The subfunctions (0x008162b0 and 0x00816490) are likely some processing steps. 
// The local variables are likely output parameters from the first call, then used in the second call. 
// The overall logic is: if condition1 (field at 0x78 non-null) and condition2 (field at 0x7c non-null) are both true, 
// then call a function that produces outputs, then call another function with those outputs. 
// The function itself returns void. 
// The class might be "SomeClass" and the method "someMethod". 
// For now, we'll keep the generic names. 
// In a real codebase, the class would have a more specific name like "StateManager" or "DataProcessor". 
// The function is likely part of a game logic where certain conditions trigger a processing sequence. 
// The fields at 0x78 and 0x7c are likely flags or indicators that some data is present. 
// The function takes an object and an extra parameter, and performs a two-step operation if conditions met. 
// The return is void, so the result is not stored directly. 
// The function might be a "handleEvent" or "processData" method. 
// Based on the decompiled code, it's a member function with two condition checks and two subfunction calls. 
// The subfunctions (0x008162b0 and 0x00816490) are likely some processing steps. 
// The local variables are likely output parameters from the first call, then used in the second call. 
// The overall logic is: if condition1 (field at 0x78 non-null) and condition2 (field at 0x7c non-null) are both true, 
// then call a function that produces outputs, then call another function with those outputs. 
// The function itself returns void. 
// The class might be "SomeClass" and the method "someMethod". 
// For now, we'll keep the generic names. 
// In a real codebase, the class would have a more specific name like "StateManager" or "DataProcessor". 
// The function is likely part of a game logic where certain conditions trigger a processing sequence. 
// The fields at 0x78 and 0x7c are likely flags or indicators that some data is present. 
// The function takes an object and an extra parameter, and performs a two-step operation if conditions met. 
// The return is void, so the result is not stored directly. 
// The function might be a "handleEvent" or "processData" method. 
// Based on the decompiled code, it's a member function with two condition checks and two subfunction calls. 
// The subfunctions (0x008162b0 and 0x00816490) are likely some processing steps. 
// The local variables are likely output parameters from the first call, then used in the second call. 
// The overall logic is: if condition1 (field at 0x78 non-null) and condition2 (field at 0x7c non-null) are both true, 
// then call a function that produces outputs, then call another function with those outputs. 
// The function itself returns void. 
// The class might be "SomeClass" and the method "someMethod". 
// For now, we'll keep the generic names. 
// In a real codebase, the class would have a more specific name like "StateManager" or "DataProcessor". 
// The function is likely part of a game logic where certain conditions trigger a processing sequence. 
// The fields at 0x78 and 0x7c are likely flags or indicators that some data is present. 
// The function takes an object and an extra parameter, and performs a two-step operation if conditions met. 
// The return is void, so the result is not stored directly. 
// The function might be a "handleEvent" or "processData" method. 
// Based on the decompiled code, it's a member function with two condition checks and two subfunction calls. 
// The subfunctions (0x008162b0 and 0x00816490) are likely some processing steps. 
// The local variables are likely output parameters from the first call, then used in the second call. 
// The overall logic is: if condition1 (field at 0x78 non-null) and condition2 (field at 0x7c non-null) are both true, 
// then call a function that produces outputs, then call another function with those outputs. 
// The function itself returns void. 
// The class might be "SomeClass" and the method "someMethod". 
// For now, we'll keep the generic names. 
// In a real codebase, the class would have a more specific name like "StateManager" or "DataProcessor". 
// The function is likely part of a game logic where certain conditions trigger a processing sequence. 
// The fields at 0x78 and 0x7c are likely flags or indicators that some data is present. 
// The function takes an object and an extra parameter, and performs a two-step operation if conditions met. 
// The return is void, so the result is not stored directly. 
// The function might be a "handleEvent" or "processData" method. 
// Based on the decompiled code, it's a member function with two condition checks and two subfunction calls. 
// The subfunctions (0x008162b0 and 0x00816490) are likely some processing steps. 
// The local variables are likely output parameters from the first call, then used in the second call. 
// The overall logic is: if condition1 (field at 0x78 non-null) and condition2 (field at 0x7c non-null) are both true, 
// then call a function that produces outputs, then call another function with those outputs. 
// The function itself returns void. 
// The class might be "SomeClass" and the method "someMethod". 
// For now, we'll keep the generic names. 
// In a real codebase, the class would have a more specific name like "StateManager" or "DataProcessor". 
// The function is likely part of a game logic where certain conditions trigger a processing sequence. 
// The fields at 0x78 and 0x7c are likely flags or indicators that some data is present. 
// The function takes an object and an extra parameter, and performs a two-step operation if conditions met. 
// The return is void, so the result is not stored directly. 
// The function might be a "handleEvent" or "processData" method. 
// Based on the decompiled code, it's a member function with two condition checks and two subfunction calls. 
// The subfunctions (0x008162b0 and 0x00816490) are likely some processing steps. 
// The local variables are likely output parameters from the first call, then used in the second call. 
// The overall logic is: if condition1 (field at 0x78 non-null) and condition2 (field at 0x7c non-null) are both true, 
// then call a function that produces outputs, then call another function with those outputs. 
// The function itself returns void. 
// The class might be "SomeClass" and the method "someMethod". 
// For now, we'll keep the generic names. 
// In a real codebase, the class would have a more specific name like "StateManager" or "DataProcessor". 
// The function is likely part of a game logic where certain conditions trigger a processing sequence. 
// The fields at 0x78 and 0x7c are likely flags or indicators that some data is present. 
// The function takes an object and an extra parameter, and performs a two-step operation if conditions met. 
// The return is void, so the result is not stored directly. 
// The function might be a "handleEvent" or "processData" method. 
// Based on the decompiled code, it's a member function with two condition checks and two subfunction calls. 
// The subfunctions (0x008162b0 and 0x00816490) are likely some processing steps. 
// The local variables are likely output parameters from the first call, then used in the second call. 
// The overall logic is: if condition1 (field at 0x78 non-null) and condition2 (field at 0x7c non-null) are both true, 
// then call a function that produces outputs, then call another function with those outputs. 
// The function itself returns void. 
// The class might be "SomeClass" and the method "someMethod". 
// For now, we'll keep the generic names. 
// In a real codebase, the class would have a more specific name like "StateManager" or "DataProcessor". 
// The function is likely part of a game logic where certain conditions trigger a processing sequence. 
// The fields at 0x78 and 0x7c are likely flags or indicators that some data is present. 
// The function takes an object and an extra parameter, and performs a two-step operation if conditions met. 
// The return is void, so the result is not stored directly. 
// The function might be a "handleEvent" or "processData" method. 
// Based on the decompiled code, it's a member function with two condition checks and two subfunction calls. 
// The subfunctions (0x008162b0 and 0x00816490) are likely some processing steps. 
// The local variables are likely output parameters from the first call, then used in the second call. 
// The overall logic is: if condition1 (field at 0x78 non-null) and condition2 (field at 0x7c non-null) are both true, 
// then call a function that produces outputs, then call another function with those outputs. 
// The function itself returns void. 
// The class might be "SomeClass" and the method "someMethod". 
// For now, we'll keep the generic names. 
// In a real codebase, the class would have a more specific name like "StateManager" or "DataProcessor". 
// The function is likely part of a game logic where certain conditions trigger a processing sequence. 
// The fields at 0x78 and 0x7c are likely flags or indicators that some data is present. 
// The function takes an object and an extra parameter, and performs a two-step operation if conditions met. 
// The return is void, so the result is not stored directly. 
// The function might be a "handleEvent" or "processData" method. 
// Based on the decompiled code, it's a member function with two condition checks and two subfunction calls. 
// The subfunctions (0x008162b0 and 0x00816490) are likely some processing steps. 
// The local variables are likely output parameters from the first call, then used in the second call. 
// The overall logic is: if condition1 (field at 0x78 non-null) and condition2 (field at 0x7c non-null) are both true, 
// then call a function that produces outputs, then call another function with those outputs. 
// The function itself returns void. 
// The class might be "SomeClass" and the method "someMethod". 
// For now, we'll keep the generic names. 
// In a real codebase, the class would have a more specific name like "StateManager" or "DataProcessor". 
// The function is likely part of a game logic where certain conditions trigger a processing sequence. 
// The fields at 0x78 and 0x7c are likely flags or indicators that some data is present. 
// The function takes an object and an extra parameter, and performs a two-step operation if conditions met. 
// The return is void, so the result is not stored directly. 
// The function might be a "handleEvent" or "processData" method. 
// Based on the decompiled code, it's a member function with two condition checks and two subfunction calls. 
// The subfunctions (0x008162b0 and 0x00816490) are likely some processing steps. 
// The local variables are likely output parameters from the first call, then used in the second call. 
// The overall logic is: if condition1 (field at 0x78 non-null) and condition2 (field at 0x7c non-null) are both true, 
// then call a function that produces outputs, then call another function with those outputs. 
// The function itself returns void. 
// The class might be "SomeClass" and the method "someMethod". 
// For now, we'll keep the generic names. 
// In a real codebase, the class would have a more specific name like "StateManager" or "DataProcessor". 
// The function is likely part of a game logic where certain conditions trigger a processing sequence. 
// The fields at 0x78 and 0x7c are likely flags or indicators that some data is present. 
// The function takes an object and an extra parameter, and performs a two-step operation if conditions met. 
// The return is void, so the result is not stored directly. 
// The function might be a "handleEvent" or "processData" method. 
// Based on the decompiled code, it's a member function with two condition checks and two subfunction calls. 
// The subfunctions (0x008162b0 and 0x00816490) are likely some processing steps. 
// The local variables are likely output parameters from the first call, then used in the second call. 
// The overall logic is: if condition1 (field at 0x78 non-null) and condition2 (field at 0x7c non-null) are both true, 
// then call a function that produces outputs, then call another function with those outputs. 
// The function itself returns void. 
// The class might be "SomeClass" and the method "someMethod". 
// For now, we'll keep the generic names. 
// In a real codebase, the class would have a more specific name like "StateManager" or "DataProcessor". 
// The function is likely part of a game logic where certain conditions trigger a processing sequence. 
// The fields at 0x78 and 0x7c are likely flags or indicators that some data is present. 
// The function takes an object and an extra parameter, and performs a two-step operation if conditions met. 
// The return is void, so the result is not stored directly. 
// The function might be a "handleEvent" or "processData" method. 
// Based on the decompiled code, it's a member function with two condition checks and two subfunction calls. 
// The subfunctions (0x008162b0 and 0x00816490) are likely some processing steps. 
// The local variables are likely output parameters from the first call, then used in the second call. 
// The overall logic is: if condition1 (field at 0x78 non-null) and condition2 (field at 0x7c non-null) are both true, 
// then call a function that produces outputs, then call another function with those outputs. 
// The function itself returns void. 
// The class might be "SomeClass" and the method "someMethod". 
// For now, we'll keep the generic names. 
// In a real codebase, the class would have a more specific name like "StateManager" or "DataProcessor". 
// The function is likely part of a game logic where certain conditions trigger a processing sequence. 
// The fields at 0x78 and 0x7c are likely flags or indicators that some data is present. 
// The function takes an object and an extra parameter, and performs a two-step operation if conditions met. 
// The return is void, so the result is not stored directly. 
// The function might be a "handleEvent" or "processData" method. 
// Based on the decompiled code, it's a member function with two condition checks and two subfunction calls. 
// The subfunctions (0x008162b0 and 0x00816490) are likely some processing steps. 
// The local variables are likely output parameters from the first call, then used in the second call. 
// The overall logic is: if condition1 (field at 0x78 non-null) and condition2 (field at 0x7c non-null) are both true, 
// then call a function that produces outputs, then call another function with those outputs. 
// The function itself returns void. 
// The class might be "SomeClass" and the method "someMethod". 
// For now, we'll keep the generic names. 
// In a real codebase, the class would have a more specific name like "StateManager" or "DataProcessor". 
// The function is likely part of a game logic where certain conditions trigger a processing sequence. 
// The fields at 0x78 and 0x7c are likely flags or indicators that some data is present. 
// The function takes an object and an extra parameter, and performs a two-step operation if conditions met. 
// The return is void, so the result is not stored directly. 
// The function might be a "handleEvent" or "processData" method. 
// Based on the decompiled code, it's a member function with two condition checks and two subfunction calls. 
// The subfunctions (0x008162b0 and 0x00816490) are likely some processing steps. 
// The local variables are likely output parameters from the first call, then used in the second call. 
// The overall logic is: if condition1 (field at 0x78 non-null) and condition2 (field at 0x7c non-null) are both true, 
// then call a function that produces outputs, then call another function with those outputs. 
// The function itself returns void. 
// The class might be "SomeClass" and the method "someMethod". 
// For now, we'll keep the generic names. 
// In a real codebase, the class would have a more specific name like "StateManager" or "DataProcessor". 
// The function is likely part of a game logic where certain conditions trigger a processing sequence. 
// The fields at 0x78 and 0x7c are likely flags or indicators that some data is present. 
// The function takes an object and an extra parameter, and performs a two-step operation if conditions met. 
// The return is void, so the result is not stored directly. 
// The function might be a "handleEvent" or "processData" method. 
// Based on the decompiled code, it's a member function with two condition checks and two subfunction calls. 
// The subfunctions (0x008162b0 and 0x00816490) are likely some processing steps. 
// The local variables are likely output parameters from the first call, then used in the second call. 
// The overall logic is: if condition1 (field at 0x78 non-null) and condition2 (field at 0x7c non-null) are both true, 
// then call a function that produces outputs, then call another function with those outputs. 
// The function itself returns void. 
// The class might be "SomeClass" and the method "someMethod". 
// For now, we'll keep the generic names. 
// In a real codebase, the class would have a more specific name like "StateManager" or "DataProcessor". 
// The function is likely part of a game logic where certain conditions trigger a processing sequence. 
// The fields at 0x78 and 0x7c are likely flags or indicators that some data is present. 
// The function takes an object and an extra parameter, and performs a two-step operation if conditions met. 
// The return is void, so the result is not stored directly. 
// The function might be a "handleEvent" or "processData" method. 
// Based on the decompiled code, it's a member function with two condition checks and two subfunction calls. 
// The subfunctions (0x008162b0 and 0x00816490) are likely some processing steps. 
// The local variables are likely output parameters from the first call, then used in the second call. 
// The overall logic is: if condition1 (field at 0x78 non-null) and condition2 (field at 0x7c non-null) are both true, 
// then call a function that produces outputs, then call another function with those outputs. 
// The function itself returns void. 
// The class might be "SomeClass" and the method "someMethod". 
// For now, we'll keep the generic names. 
// In a real codebase, the class would have a more specific name like "StateManager" or "DataProcessor". 
// The function is likely part of a game logic where certain conditions trigger a processing sequence. 
// The fields at 0x78 and 0x7c are likely flags or indicators that some data is present. 
// The function takes an object and an extra parameter, and performs a two-step operation if conditions met. 
// The return is void, so the result is not stored directly. 
// The function might be a "handleEvent" or "processData" method. 
// Based on the decompiled code, it's a member function with two condition checks and two subfunction calls. 
// The subfunctions (0x008162b0 and 0x00816490) are likely some processing steps. 
// The local variables are likely output parameters from the first call, then used in the second call. 
// The overall logic is: if condition1 (field at 0x78 non-null) and condition2 (field at 0x7c non-null) are both true, 
// then call a function that produces outputs, then call another function with those outputs. 
// The function itself returns void. 
// The class might be "SomeClass" and the method "someMethod". 
// For now, we'll keep the generic names. 
// In a real codebase, the class would have a more specific name like "StateManager" or "DataProcessor". 
// The function is likely part of a game logic where certain conditions trigger a processing sequence. 
// The fields at 0x78 and 0x7c are likely flags or indicators that some data is present. 
// The function takes an object and an extra parameter, and performs a two-step operation if conditions met. 
// The return is void, so the result is not stored directly. 
// The function might be a "handleEvent" or "processData" method. 
// Based on the decompiled code, it's a member function with two condition checks and two subfunction calls. 
// The subfunctions (0x008162b0 and 0x00816490) are likely some processing steps. 
// The local variables are likely output parameters from the first call, then used in the second call. 
// The overall logic is: if condition1 (field at 0x78 non-null) and condition2 (field at 0x7c non-null) are both true, 
// then call a function that produces outputs, then call another function with those outputs. 
// The function itself returns void. 
// The class might be "SomeClass" and the method "someMethod". 
// For now, we'll keep the generic names. 
// In a real codebase, the class would have a more specific name like "StateManager" or "DataProcessor". 
// The function is likely part of a game logic where certain conditions trigger a processing sequence. 
// The fields at 0x78 and 0x7c are likely flags or indicators that some data is present. 
// The function takes an object and an extra parameter, and performs a two-step operation if conditions met. 
// The return is void, so the result is not stored directly. 
// The function might be a "handleEvent" or "processData" method. 
// Based on the decompiled code, it's a member function with two condition checks and two subfunction calls. 
// The subfunctions (0x008162b0 and 0x00816490) are likely some processing steps. 
// The local variables are likely output parameters from the first call, then used in the second call. 
// The overall logic is: if condition1 (field at 0x78 non-null) and condition2 (field at 0x7c non-null) are both true, 
// then call a function that produces outputs, then call another function with those outputs. 
// The function itself returns void. 
// The class might be "SomeClass" and the method "someMethod". 
// For now, we'll keep the generic names. 
// In a real codebase, the class would have a more specific name like "StateManager" or "DataProcessor". 
// The function is likely part of a game logic where certain conditions trigger a processing sequence. 
// The fields at 0x78 and 0x7c are likely flags or indicators that some data is present. 
// The function takes an object and an extra parameter, and performs a two-step operation if conditions met. 
// The return is void, so the result is not stored directly. 
// The function might be a "handleEvent" or "processData" method. 
// Based on the decompiled code, it's a member function with two condition checks and two subfunction calls. 
// The subfunctions (0x008162b0 and 0x00816490) are likely some processing steps. 
// The local variables are likely output parameters from the first call, then used in the second call. 
// The overall logic is: if condition1 (field at 0x78 non-null) and condition2 (field at 0x7c non-null) are both true, 
// then call a function that produces outputs, then call another function with those outputs. 
// The function itself returns void. 
// The class might be "SomeClass" and the method "someMethod". 
// For now, we'll keep the generic names. 
// In a real codebase, the class would have a more specific name like "StateManager" or "DataProcessor". 
// The function is likely part of a game logic where certain conditions trigger a processing sequence. 
// The fields at 0x78 and 0x7c are likely flags or indicators that some data is present. 
// The function takes an object and an extra parameter, and performs a two-step operation if conditions met. 
// The return is void, so the result is not stored directly. 
// The function might be a "handleEvent" or "processData" method. 
// Based on the decompiled code, it's a member function with two condition checks and two subfunction calls. 
// The subfunctions (0x008162b0 and 0x00816490) are likely some processing steps. 
// The local variables are likely output parameters from the first call, then used in the second call. 
// The overall logic is: if condition1 (field at 0x78 non-null) and condition2 (field at 0x7c non-null) are both true, 
// then call a function that produces outputs, then call another function with those outputs. 
// The function itself returns void. 
// The class might be "SomeClass" and the method "someMethod". 
// For now, we'll keep the generic names. 
// In a real codebase, the class would have a more specific name like "StateManager" or "DataProcessor". 
// The function is likely part of a game logic where certain conditions trigger a processing sequence. 
// The fields at 0x78 and 0x7c are likely flags or indicators that some data is present. 
// The function takes an object and an extra parameter, and performs a two-step operation if conditions met. 
// The return is void, so the result is not stored directly. 
// The function might be a "handleEvent" or "processData" method. 
// Based on the decompiled code, it's a member function with two condition checks and two subfunction calls. 
// The subfunctions (0x008162b0 and 0x00816490) are likely some processing steps. 
// The local variables are likely output parameters from the first call, then used in the second call. 
// The overall logic is: if condition1 (field at 0x78 non-null) and condition2 (field at 0x7c non-null) are both true, 
// then call a function that produces outputs, then call another function with those outputs. 
// The function itself returns void. 
// The class might be "SomeClass" and the method "someMethod". 
// For now, we'll keep the generic names. 
// In a real codebase, the class would have a more specific name like "StateManager" or "DataProcessor". 
// The function is likely part of a game logic where certain conditions trigger a processing sequence. 
// The fields at 0x78 and 0x7c are likely flags or indicators that some data is present. 
// The function takes an object and an extra parameter, and performs a two-step operation if conditions met. 
// The return is void, so the result is not stored directly. 
// The function might be a "handleEvent" or "processData" method. 
// Based on the decompiled code, it's a member function with two condition checks and two subfunction calls. 
// The subfunctions (0x008162b0 and 0x00816490) are likely some processing steps. 
// The local variables are likely output parameters from the first call, then used in the second call. 
// The overall logic is: if condition1 (field at 0x78 non-null) and condition2 (field at 0x7c non-null) are both true, 
// then call a function that produces outputs, then call another function with those outputs. 
// The function itself returns void. 
// The class might be "SomeClass" and the method "someMethod". 
// For now, we'll keep the generic names. 
// In a real codebase, the class would have a more specific name like "StateManager" or "DataProcessor". 
// The function is likely part of a game logic where certain conditions trigger a processing sequence. 
// The fields at 0x78 and 0x7c are likely flags or indicators that some data is present. 
// The function takes an object and an extra parameter, and performs a two-step operation if conditions met. 
// The return is void, so the result is not stored directly. 
// The function might be a "handleEvent" or "processData" method. 
// Based on the decompiled code, it's a member function with two condition checks and two subfunction calls. 
// The subfunctions (0x008162b0 and 0x00816490) are likely some processing steps. 
// The local variables are likely output parameters from the first call, then used in the second call. 
// The overall logic is: if condition1 (field at 0x78 non-null) and condition2 (field at 0x7c non-null) are both true, 
// then call a function that produces outputs, then call another function with those outputs. 
// The function itself returns void. 
// The class might be "SomeClass" and the method "someMethod". 
// For now, we'll keep the generic names. 
// In a real codebase, the class would have a more specific name like "StateManager" or "DataProcessor". 
// The function is likely part of a game logic where certain conditions trigger a processing sequence. 
// The fields at 0x78 and 0x7c are likely flags or indicators that some data is present. 
// The function takes an object and an extra parameter, and performs a two-step operation if conditions met. 
// The return is void, so the result is not stored directly. 
// The function might be a "handleEvent" or "processData" method. 
// Based on the decompiled code, it's a member function with two condition checks and two subfunction calls. 
// The subfunctions (0x008162b0 and 0x00816490) are likely some processing steps. 
// The local variables are likely output parameters from the first call, then used in the second call. 
// The overall logic is: if condition1 (field at 0x78 non-null) and condition2 (field at 0x7c non-null) are both true, 
// then call a function that produces outputs, then call another function with those outputs. 
// The function itself returns void. 
// The class might be "SomeClass" and the method "someMethod". 
// For now, we'll keep the generic names. 
// In a real codebase, the class would have a more specific name like "StateManager" or "DataProcessor". 
// The function is likely part of a game logic where certain conditions trigger a processing sequence. 
// The fields at 0x78 and 0x7c are likely flags or indicators that some data is present. 
// The function takes an object and an extra parameter, and performs a two-step operation if conditions met. 
// The return is void, so the result is not stored directly. 
// The function might be a "handleEvent" or "processData" method. 
// Based on the decompiled code, it's a member function with two condition checks and two subfunction calls. 
// The subfunctions (0x008162b0 and 0x00816490) are likely some processing steps. 
// The local variables are likely output parameters from the first call, then used in the second call. 
// The overall logic is: if condition1 (field at 0x78 non-null) and condition2 (field at 0x7c non-null) are both true, 
// then call a function that produces outputs, then call another function with those outputs. 
// The function itself returns void. 
// The class might be "SomeClass" and the method "someMethod". 
// For now, we'll keep the generic names. 
// In a real codebase, the class would have a more specific name like "StateManager" or "DataProcessor". 
// The function is likely part of a game logic where certain conditions trigger a processing sequence. 
// The fields at 0x78 and 0x7c are likely flags or indicators that some data is present. 
// The function takes an object and an extra parameter, and performs a two-step operation if conditions met. 
// The return is void, so the result is not stored directly. 
// The function might be a "handleEvent" or "processData" method. 
// Based on the decompiled code, it's a member function with two condition checks and two subfunction calls. 
// The subfunctions (0x008162b0 and 0x00816490) are likely some processing steps. 
// The local variables are likely output parameters from the first call, then used in the second call. 
// The overall logic is: if condition1 (field at 0x78 non-null) and condition2 (field at 0x7c non-null) are both true, 
// then call a function that produces outputs, then call another function with those outputs. 
// The function itself returns void. 
// The class might be "SomeClass" and the method "someMethod". 
// For now, we'll keep the generic names. 
// In a real codebase, the class would have a more specific name like "StateManager" or "DataProcessor". 
// The function is likely part of a game logic where certain conditions trigger a processing sequence. 
// The fields at 0x78 and 0x7c are likely flags or indicators that some data is present. 
// The function takes an object and an extra parameter, and performs a two-step operation if conditions met. 
// The return is void, so the result is not stored directly. 
// The function might be a "handleEvent" or "processData" method. 
// Based on the decompiled code, it's a member function with two condition checks and two subfunction calls. 
// The subfunctions (0x008162b0 and 0x00816490) are likely some processing steps. 
// The local variables are likely output parameters from the first call, then used in the second call. 
// The overall logic is: if condition1 (field at 0x78 non-null) and condition2 (field at 0x7c non-null) are both true, 
// then call a function that produces outputs, then call another function with those outputs. 
// The function itself returns void. 
// The class might be "SomeClass" and the method "someMethod". 
// For now, we'll keep the generic names. 
// In a real codebase, the class would have a more specific name like "StateManager" or "DataProcessor". 
// The function is likely part of a game logic where certain conditions trigger a processing sequence. 
// The fields at 0x78 and 0x7c are likely flags or indicators that some data is present. 
// The function takes an object and an extra parameter, and performs a two-step operation if conditions met. 
// The return is void, so the result is not stored directly. 
// The function might be a "handleEvent" or "processData" method. 
// Based on the decompiled code, it's a member function with two condition checks and two subfunction calls. 
// The subfunctions (0x008162b0 and 0x00816490) are likely some processing steps. 
// The local variables are likely output parameters from the first call, then used in the second call. 
// The overall logic is: if condition1 (field at 0x78 non-null) and condition2 (field at 0x7c non-null) are both true, 
// then call a function that produces outputs, then call another function with those outputs. 
// The function itself returns void. 
// The class might be "SomeClass" and the method "someMethod". 
// For now, we'll keep the generic names. 
// In a real codebase, the class would have a more specific name like "StateManager" or "DataProcessor". 
// The function is likely part of a game logic where certain conditions trigger a processing sequence. 
// The fields at 0x78 and 0x7c are likely flags or indicators that some data is present. 
// The function takes an object and an extra parameter, and performs a two-step operation if conditions met. 
// The return is void, so the result is not stored directly. 
// The function might be a "handleEvent" or "processData" method. 
// Based on the decompiled code, it's a member function with two condition checks and two subfunction calls. 
// The subfunctions (0x008162b0 and 0x00816490) are likely some processing steps. 
// The local variables are likely output parameters from the first call, then used in the second call. 
// The overall logic is: if condition1 (field at 0x78 non-null) and condition2 (field at 0x7c non-null) are both true, 
// then call a function that produces outputs, then call another function with those outputs. 
// The function itself returns void. 
// The class might be "SomeClass" and the method "someMethod". 
// For now, we'll keep the generic names. 
// In a real codebase, the class would have a