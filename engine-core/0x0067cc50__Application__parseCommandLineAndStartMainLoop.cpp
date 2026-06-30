// FUNC_NAME: Application::parseCommandLineAndStartMainLoop
// Address: 0x0067cc50
// Role: Parse command-line arguments and start the appropriate main loop (frontend or game)

void __fastcall Application::parseCommandLineAndStartMainLoop(int *thisPtr)
{
    char cVar;
    int loopId;
    int argIdx;
    char *argStr;
    uint argCount;
    char *argStr2;
    uint tempIdx;
    char *pDefaultStr;
    char *pAnotherStr;
    int localArray1[3]; // used for function pointer pairing
    code *localFuncPtr1;
    int localArray2[3];
    code *localFuncPtr2;
    char saveGameBuffer[40]; // used with -playerspawn

    // Check for "FrontendMainLoop" and if it exists, call it via vtable
    loopId = FUN_00683280("FrontendMainLoop");
    if (FUN_006833d0(loopId) != 0) {
        (**(code **)(thisPtr[0] + 0x14))(loopId); // vtable call at offset +0x14
    }

    argIdx = 0;
    argCount = FUN_0067bf10(); // get argument count
    if (argCount != 0) {
        do {
            argStr = (char *)FUN_0067bf20(argIdx); // get argument string
            if (argStr == (char *)0x0) {
                loopId = 1; // null string -> treat as match? (or error)
            } else {
                loopId = __stricmp(argStr, "-mainloop");
            }
            if (loopId == 0) {
                // Found -mainloop flag, next argument is loop name
                tempIdx = FUN_0067bf10();
                if (argIdx + 1 < tempIdx) {
                    loopId = FUN_0067bf20(argIdx + 1);
                    loopId = FUN_00683280(loopId); // get loop ID
                    if (FUN_006833d0(loopId) != 0) {
                        (**(code **)(thisPtr[0] + 0x14))(loopId); // call the specified loop
                    }
                }
            } else {
                argStr2 = (char *)FUN_0067bf20(argIdx);
                if (argStr2 == (char *)0x0) {
                    loopId = 1;
                } else {
                    loopId = __stricmp(argStr2, "-playerspawn");
                }
                if (loopId == 0) {
                    // Found -playerspawn flag, next argument is the player spawn type
                    tempIdx = argIdx + 1;
                    argCount = FUN_0067bf10();
                    if (tempIdx < argCount) {
                        loopId = FUN_0067bf20(tempIdx);
                        FUN_004d8f00(loopId); // set player spawn mode
                        cVar = FUN_004d8f50(); // check if successful
                        argIdx = tempIdx;
                        if (cVar != '\0') {
                            // If spawn succeeded, load a save game name from buffer
                            loopId = FUN_004d8ce0(saveGameBuffer);
                            FUN_008111a0(loopId); // initialize with save game data
                        }
                    }
                } else {
                    // Check for -stream flag
                    if (argStr == (char *)0x0) {
                        loopId = 1;
                    } else {
                        loopId = __stricmp(argStr, "-stream");
                    }
                    if (loopId == 0) {
                        // Found -stream flag, arguments are stream file and packages
                        tempIdx = FUN_0067bf10();
                        if (argIdx + 2 < tempIdx) {
                            argIdx = argIdx + 1; // move to stream file arg
                            loopId = FUN_0067bf20(argIdx);
                            FUN_004d3d90(loopId); // set stream file
                            loopId = FUN_0067bf10();
                            if (argIdx < loopId - 1U) {
                                do {
                                    argIdx = argIdx + 1;
                                    loopId = FUN_0067bf20(argIdx);
                                    FUN_004d4300(loopId); // add stream package
                                    FUN_004d44b0(0x20); // set buffer size? (0x20 = 32)
                                    loopId = FUN_0067bf10();
                                } while (argIdx < loopId - 1U);
                            }
                            FUN_004d53a0(0x20); // finalize streams
                            FUN_00411e40(); // probably some initialization
                            // Set default resource paths; use provided ones or fallback to a default
                            pAnotherStr = (char *)thisPtr[6]; // +0x18 (since int*)
                            if (pAnotherStr == (char *)0x0) {
                                pAnotherStr = &DAT_0120546e; // default string (maybe empty)
                            }
                            pDefaultStr = (char *)thisPtr[2]; // +0x08
                            if (pDefaultStr == (char *)0x0) {
                                pDefaultStr = &DAT_0120546e;
                            }
                            FUN_0067c9f0(pDefaultStr, pAnotherStr); // set resource paths
                            // Now start the GameMainLoop
                            loopId = thisPtr[0]; // vtable
                            loopId = FUN_00683280("GameMainLoop");
                            (**(code **)(loopId + 0x14))(loopId); // call vtable method
                        }
                    } else {
                        // Check for -juice flag
                        if (argStr == (char *)0x0) {
                            loopId = 1;
                        } else {
                            loopId = __stricmp(argStr, "-juice");
                        }
                        if (loopId != 0) {
                            // Check for -gameid flag
                            if (argStr == (char *)0x0) {
                                loopId = 1;
                            } else {
                                loopId = __stricmp(argStr, "-gameid");
                            }
                            if (loopId == 0) {
                                // Found -gameid flag, next argument is game ID, parse into two function pointers?
                                argIdx = argIdx + 1;
                                loopId = FUN_0067bf20(argIdx);
                                FUN_004d3bc0(loopId); // copy string?
                                FUN_004d3e20(localArray1); // parse into pair
                                if (localArray1[0] != 0) {
                                    (*localFuncPtr1)(localArray1[0]); // call first function
                                }
                                FUN_004d3bc0(loopId);
                                FUN_004d3e20(localArray2);
                                if (localArray2[0] != 0) {
                                    (*localFuncPtr2)(localArray2[0]); // call second function
                                }
                            } else if (argStr != (char *)0x0) {
                                __stricmp(argStr, "-autoconnect"); // -autoconnect handled, no action?
                            }
                        }
                    }
                }
            }
            argIdx = argIdx + 1;
            argCount = FUN_0067bf10();
        } while (argIdx < argCount);
    }
    // Clear the flag indicating we are in frontend mode?
    DAT_0110ae75 = 0;
    return;
}