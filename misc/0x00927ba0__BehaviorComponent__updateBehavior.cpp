// FUNC_NAME: BehaviorComponent::updateBehavior

void __fastcall BehaviorComponent::updateBehavior(BehaviorComponent* thisPtr)
{
    // Global manager pointer (e.g., BehaviorManager*)
    BehaviorManager* mgr = reinterpret_cast<BehaviorManager*>(DAT_01129a74);
    
    // Get current update timestamp
    uint32_t timestamp = FUN_005bf370();
    
    // Local array used as an argument for some process
    uint32_t localArray[4]; // actually used as uint32_t[4] but only first element used?
    localArray[0] = timestamp;
    
    // Check flags: if not already doing a behavior transition and global flag allows
    if (thisPtr->field_325 == 0 && mgr->field_3c4 == 0)
    {
        thisPtr->field_325 = (uint8_t)timestamp; // Mark as transition in progress? (only low byte)
    }
    
    // If the manager is not in a blocking state
    if (mgr->field_3c7 == 0 || mgr->field_3c5 == 0)
    {
        // Compare the string at offset 0xd4 with string at offset 0x19c
        // FUN_00927910 likely resolves a string to a behavior vtable
        int cmpResult = strcmp(thisPtr->nextStateName, thisPtr->targetStateName);
        
        if (cmpResult == 0)
        {
            // Strings equal: if global flag allows and local transition pending
            if (mgr->field_3c4 != 0 && thisPtr->field_325 != 0 && thisPtr->targetStateName[0] != '\0')
            {
                // Enter the target state using vtable method at +0x48
                BehaviorVTable* vtable = (BehaviorVTable*)FUN_00927910(thisPtr->targetStateName);
                if (vtable != nullptr)
                {
                    vtable->enter(thisPtr->targetStateName,
                                  thisPtr->newStateParams[0],
                                  thisPtr->newStateParams[1],
                                  thisPtr->newStateParams[2],
                                  thisPtr->newStateParams[3]);
                }
                thisPtr->field_325 = 0; // Clear transition flags
                thisPtr->field_324 = 0;
            }
        }
        else 
        {
            // Strings differ: handle transition request
            if (mgr->field_3c4 != 0 || thisPtr->field_324 != 0)
            {
                // If there is a pending next state (at 0xd4), exit it
                if (thisPtr->nextStateName[0] != '\0')
                {
                    BehaviorVTable* vtable = (BehaviorVTable*)FUN_00927910(thisPtr->nextStateName);
                    if (vtable != nullptr)
                    {
                        vtable->exit(thisPtr->nextStateName,
                                     thisPtr->currentStateParams[0],
                                     thisPtr->currentStateParams[1],
                                     thisPtr->currentStateParams[2],
                                     thisPtr->currentStateParams[3]);
                    }
                }
                // If target state is non-empty and not already transitioning to it, enter it
                if (thisPtr->targetStateName[0] != '\0' && thisPtr->field_325 == 0)
                {
                    // Enter the target state
                    BehaviorVTable* vtable = (BehaviorVTable*)FUN_00927910(thisPtr->targetStateName);
                    if (vtable != nullptr)
                    {
                        vtable->enter(thisPtr->targetStateName,
                                      thisPtr->newStateParams[0],
                                      thisPtr->newStateParams[1],
                                      thisPtr->newStateParams[2],
                                      thisPtr->newStateParams[3]);
                    }
                    thisPtr->field_325 = 0;
                    thisPtr->field_324 = 0;
                }
            }
        }
    }
    
    // Now handle the actual state update logic (separate from transitions)
    if (mgr->field_3c7 == 0)
    {
        // Branch based on string at 0x25c (transition selector)
        if (mgr->field_3c5 == 0 ||
            (thisPtr->targetStateName[0] == '\0' && thisPtr->field_0c[0] == '\0') ||
            (vtable = (BehaviorVTable*)FUN_00927910(thisPtr->targetStateName[0] != '\0' ? thisPtr->targetStateName : thisPtr->field_0c), vtable == nullptr))
        {
            // Fall through to end
            goto LAB_00927f19;
        }
        
        // Compare with "0"
        if (strncmp(thisPtr->transitionString, "0", 2) == 0)
        {
            // This branch corresponds to transition "0" - do nothing special? Actually it falls through to LAB_00927f19
            goto LAB_00927f19;
        }
        // Compare with "1" - special handling
        if (strncmp(thisPtr->transitionString, "1", 2) == 0)
        {
            FUN_0098bf00(thisPtr->targetStateName, thisPtr->newStateParams); // Copy params to state data
            goto LAB_00927f19;
        }
        
        // Otherwise, call update method at +0x50
        vtable->update(thisPtr->targetStateName,
                       thisPtr->newStateParams[0],
                       thisPtr->newStateParams[1],
                       thisPtr->newStateParams[2],
                       thisPtr->newStateParams[3]);
    }
    else if (mgr->field_3c5 == 0)
    {
        // Another branch: if manager flag allows
        if (mgr->field_3c7 == 0 || mgr->field_3c5 != 0 ||
            (int* vtable = (int*)FUN_00927980(), vtable == nullptr)) // Some other registry
        {
            goto LAB_00927f19;
        }
        
        // Compare transition string with "1"
        if (strncmp(thisPtr->transitionString, "1", 2) == 0)
        {
            // Use target state name
            thisPtr->targetStateName = ??? Actually it's a pointer: in code it assigns puVar16 = param_1 + 0x19c
            // So just pass through
        }
        else
        {
            // Use a default global state name (DAT_00e2f044)
            // That likely is a global string like "idle" or something
            // For reconstruction, we can treat it as a char*
            char* defaultStateName = DAT_00e2f044;
            // Call some function with that state and new params
            bool result = FUN_0098d180(defaultStateName, thisPtr->newStateParams);
            if (result != 0)
            {
                // If returned true, check transition string with "0"
                if (strncmp(thisPtr->transitionString, "0", 2) == 0)
                {
                    // Continue to update
                    // Fill in params and call vtable method at +0x58
                    vtable = (BehaviorVTable*)FUN_00927980(); // Re-fetch? Actually code reuses piStack_18
                }
                else
                {
                    goto LAB_00927f19;
                }
            }
            else
            {
                goto LAB_00927f19;
            }
        }
        // Update call at +0x58 (different from +0x50)
        vtable->update(thisPtr->targetStateName,
                       thisPtr->newStateParams[0],
                       thisPtr->newStateParams[1],
                       thisPtr->newStateParams[2],
                       thisPtr->newStateParams[3]);
    }
    else
    {
        // Final branch: both flags set
        if ((thisPtr->targetStateName[0] == '\0' && thisPtr->field_0c[0] == '\0') ||
            (vtable = (BehaviorVTable*)FUN_00927910(thisPtr->targetStateName[0] != '\0' ? thisPtr->targetStateName : thisPtr->field_0c), vtable == nullptr))
        {
            goto LAB_00927f19;
        }
        // Use method at +0x54
        vtable->update(thisPtr->targetStateName,
                       thisPtr->newStateParams[0],
                       thisPtr->newStateParams[1],
                       thisPtr->newStateParams[2],
                       thisPtr->newStateParams[3]);
    }
    
LAB_00927f19:
    // After state update, check if we need to update further based on time and state ID
    bool continueUpdate = FUN_009276a0(mgr, localArray[0]);
    if (continueUpdate != 0 && thisPtr->field_32c == 4) // state ID 4
    {
        // Get an iterator over some list
        FUN_00926810(&someStackVar, localArray); // some pointer/array
        BehaviorIterator* iter = (BehaviorIterator*)FUN_005bec00();
        while (iter != nullptr && iter->check() == 0) // virtual function at +0x10
        {
            int result = iter->process(thisPtr->field_328, someStackVar, localArray[0]); // virtual at +0x5c
            if (result == 0)
            {
                iter = (BehaviorIterator*)FUN_005bec20(iter); // get next
            }
            else
            {
                break;
            }
        }
    }
    
    // If manager has a non-default interpolation factor
    if (mgr->interpolationFactor != 1.0f) // assuming 0x3cc is a float, DAT_00d577a0 is 1.0f maybe
    {
        // Check if we have a target state name (non-empty)
        int context = thisPtr->targetStateName[0] != '\0' ? thisPtr->targetStateName : thisPtr->field_0c;
        if (context != 0) // Actually points to either string
        {
            BehaviorVTable* vtable = (BehaviorVTable*)FUN_00927910(context);
            if (vtable != nullptr)
            {
                vtable->interpolate(thisPtr->targetStateName, mgr->interpolationFactor); // +0x60
            }
        }
    }
    
    // Copy current state data to next state data (for the next frame)
    if (thisPtr->nextStateName[0] != '\0')
    {
        // Copy params from current state to next state (backup)
        memcpy(thisPtr->savedParams, thisPtr->currentStateParams, sizeof(float) * 4); // 0xc0 = 192 bytes? Actually 0xc0 = 192, but we treat as 4 floats each 16 bytes? Better treat as Vec4? Offsets suggest 4 floats at 0x270-0x27c and 0x280-0x28c etc.
        // Actually the offsets: 0x270,274,278,27c are saved; 0x280,284,288,28c are current; 0x290,294,298,29c are new.
        // The function copies 0xc0 bytes? That's 192 bytes, which is 48 floats. That seems too large. Could be a matrix? But the offsets are only 4 floats each. Possibly a bug: decompiler misread the size? Actually memcpy param is 0xc0 which is 192 bytes. But the data at 0xc and 0xd4 are char strings? Wait, FUN_005c4660 is called with 0xc0 as size. That's 192 bytes. The offsets 0xc and 0xd4 are probably pointers to actual data buffers (like 192-byte structs). It's confusing.
        // Based on the later usage, it copies from 0xc to 0xd4? Actually FUN_005c4660(param_1 + 0xc, param_1 + 0xd4, 0xc0, 0) - that copies from 0xd4 to 0xc? No, the function signature in decompiler: param1=dest, param2=src, param3=size, param4=0? So it copies 0xc0 bytes from 0xd4 to 0xc.
        // Then later copies 0xc0 bytes from 0x19c to 0xd4.
        // The data at 0xc and 0xd4 are probably the same structure (192 bytes each) representing state data. But the string comparisons suggest they are strings. Maybe the struct at 0xc is starting with a string, but the full 192 bytes include other fields. However, the member offsets (0x25c, 0x270, etc.) suggest a structure layout.
        // To simplify, I'll treat the copy as moving state data buffers.
        memcpy(thisPtr + 0xc, thisPtr + 0xd4, 0xc0);
        // Then copy the current params (at 0x280-0x28c) to the saved params (0x270-0x27c)
        thisPtr->savedParams[0] = thisPtr->currentStateParams[0];
        thisPtr->savedParams[1] = thisPtr->currentStateParams[1];
        thisPtr->savedParams[2] = thisPtr->currentStateParams[2];
        thisPtr->savedParams[3] = thisPtr->currentStateParams[3];
    }
    
    // Now shift the new state data to current state data for next frame
    memcpy(thisPtr + 0xd4, thisPtr + 0x19c, 0xc0);
    // Copy new params to current params
    thisPtr->currentStateParams[0] = thisPtr->newStateParams[0];
    thisPtr->currentStateParams[1] = thisPtr->newStateParams[1];
    thisPtr->currentStateParams[2] = thisPtr->newStateParams[2];
    thisPtr->currentStateParams[3] = thisPtr->newStateParams[3];
    // Clear the target state name and new params
    memset(thisPtr->targetStateName, 0, 1); // set first byte to 0
    memset(thisPtr->newStateParams, 0, sizeof(float) * 4);
}
```