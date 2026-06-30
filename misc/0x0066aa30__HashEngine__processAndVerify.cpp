// FUNC_NAME: HashEngine::processAndVerify
int HashEngine::processAndVerify(int* param_1)
{
    // Local buffers for state and intermediate hashes (16 bytes each, except 20 for hashOut)
    char state1[16];
    char state2[16];
    char state3[16];
    char state4[16];
    char state5[16];
    char state6[16];
    char state7[16];
    char state8[16];
    char state9[16];
    char state10[16];
    char state11[16];
    char state12[16];
    char state13[16];
    char finalHash[20]; // 20 bytes (SHA-1 size)

    int result;

    // Initialize all state buffers with zero or initial constants
    result = stateInit(finalHash, state5, state3, state4, state8, state11, state6, state9, state10, state7, state12, state2, state1, 0);
    if (result == 0) {
        int maxSize = *this; // this pointer likely points to a size/capability value
        int inputSize = *param_1;
        int roundCount = (inputSize < maxSize) ? (inputSize / 3) : (maxSize / 3);
        int blockSize = roundCount * 0x1c; // 28 bytes per block

        result = checkAlloc(blockSize); // Ensure allocation for block data
        if (result == 0) {
            result = processRound(); // Perform a processing round
            if (result == 0) {
                updateState(roundCount);        // Update state with input count
                checkAlloc(blockSize);
                result = processRound();
                if (result == 0) {
                    updateState(roundCount * 2); // Double count
                    checkAlloc(blockSize);
                    result = processRound();
                    if (result == 0) {
                        updateState(roundCount);
                        checkAlloc(blockSize);
                        result = processRound();
                        if (result == 0) {
                            updateState(roundCount * 2);
                            // Combine states
                            result = combineStates(state11, state10, finalHash);
                            if (result == 0) {
                                result = combineStates(state9, state12, state8);
                                if (result == 0) {
                                    result = copyState(state11, state2);
                                    if (result == 0) {
                                        result = hashState(state2);
                                        if (result == 0) {
                                            result = copyState(state2, state2);
                                            if (result == 0) {
                                                result = hashState(state2);
                                                if (result == 0) {
                                                    result = copyState(state10, state1);
                                                    if (result == 0) {
                                                        result = hashState(state1);
                                                        if (result == 0) {
                                                            result = copyState(state1, state1);
                                                            if (result == 0) {
                                                                result = hashState(state1);
                                                                if (result == 0) {
                                                                    result = combineStates(state2, state1, state5);
                                                                    if (result == 0) {
                                                                        result = copyState(state9, state2);
                                                                        if (result == 0) {
                                                                            result = hashState(state2);
                                                                            if (result == 0) {
                                                                                result = copyState(state2, state2);
                                                                                if (result == 0) {
                                                                                    result = hashState(state2);
                                                                                    if (result == 0) {
                                                                                        result = copyState(state12, state1);
                                                                                        if (result == 0) {
                                                                                            result = hashState(state1);
                                                                                            if (result == 0) {
                                                                                                result = copyState(state1, state1);
                                                                                                if (result == 0) {
                                                                                                    result = hashState(state1);
                                                                                                    if (result == 0) {
                                                                                                        result = combineStates(state2, state1, state4);
                                                                                                        if (result == 0) {
                                                                                                            result = hashState(state9);
                                                                                                            if (result == 0) {
                                                                                                                result = hashState(state2);
                                                                                                                if (result == 0) {
                                                                                                                    result = hashState(state12);
                                                                                                                    if (result == 0) {
                                                                                                                        result = hashState(state1);
                                                                                                                        if (result == 0) {
                                                                                                                            result = combineStates(state2, state1, state3);
                                                                                                                            if (result == 0) {
                                                                                                                                result = xorStates(state5, state8);
                                                                                                                                if (result == 0) {
                                                                                                                                    result = xorStates(state4, finalHash);
                                                                                                                                    if (result == 0) {
                                                                                                                                        result = rotateState(state5);
                                                                                                                                        if (result == 0) {
                                                                                                                                            result = rotateState(state4);
                                                                                                                                            if (result == 0) {
                                                                                                                                                result = xorStates(state3, finalHash);
                                                                                                                                                if (result == 0) {
                                                                                                                                                    result = xorStates(state3, state8);
                                                                                                                                                    if (result == 0) {
                                                                                                                                                        result = xorStates(state5, state3);
                                                                                                                                                        if (result == 0) {
                                                                                                                                                            result = xorStates(state4, state3);
                                                                                                                                                            if (result == 0) {
                                                                                                                                                                result = setConstant(3);
                                                                                                                                                                if (result == 0) {
                                                                                                                                                                    result = xorStates(state5, state2);
                                                                                                                                                                    if (result == 0) {
                                                                                                                                                                        result = setConstant(3);
                                                                                                                                                                        if (result == 0) {
                                                                                                                                                                            result = xorStates(state4, state2);
                                                                                                                                                                            if (result == 0) {
                                                                                                                                                                                result = mixState(state3, 3, state3);
                                                                                                                                                                                if (result == 0) {
                                                                                                                                                                                    result = xorStates(state3, state5);
                                                                                                                                                                                    if (result == 0) {
                                                                                                                                                                                        result = xorStates(state3, state4);
                                                                                                                                                                                        if (result == 0) {
                                                                                                                                                                                            result = xorStates(state5, state3);
                                                                                                                                                                                            if (result == 0) {
                                                                                                                                                                                                result = xorStates(state4, state3);
                                                                                                                                                                                                if (result == 0) {
                                                                                                                                                                                                    result = zeroState(state5, state5, 0);
                                                                                                                                                                                                    if (result == 0) {
                                                                                                                                                                                                        result = zeroState(state4, state4, 0);
                                                                                                                                                                                                        if (result == 0) {
                                                                                                                                                                                                            result = processBlock(roundCount);
                                                                                                                                                                                                            if (result == 0) {
                                                                                                                                                                                                                result = processBlock(roundCount * 2);
                                                                                                                                                                                                                if (result == 0) {
                                                                                                                                                                                                                    result = processBlock(roundCount * 3);
                                                                                                                                                                                                                    if (result == 0) {
                                                                                                                                                                                                                        result = processBlock(roundCount * 4);
                                                                                                                                                                                                                        if (result == 0) {
                                                                                                                                                                                                                            result = hashState(finalHash);
                                                                                                                                                                                                                            if (result == 0) {
                                                                                                                                                                                                                                result = hashState(state3);
                                                                                                                                                                                                                                if (result == 0) {
                                                                                                                                                                                                                                    result = hashState(state8);
                                                                                                                                                                                                                                    if (result == 0) {
                                                                                                                                                                                                                                        result = hashState(state2);
                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                                }
                                                                                                                                                                                                                            }
                                                                                                                                                                                                                        }
                                                                                                                                                                                                                    }
                                                                                                                                                                                                                }
                                                                                                                                                                                                            }
                                                                                                                                                                                                        }
                                                                                                                                                                                                    }
                                                                                                                                                                                                }
                                                                                                                                                                                            }
                                                                                                                                                                                        }
                                                                                                                                                                                    }
                                                                                                                                                                                }
                                                                                                                                                                            }
                                                                                                                                                                        }
                                                                                                                                                                    }
                                                                                                                                                                }
                                                                                                                                                            }
                                                                                                                                                        }
                                                                                                                                                    }
                                                                                                                                                }
                                                                                                                                            }
                                                                                                                                        }
                                                                                                                                   }
                                                                                                                                }
                                                                                                                            }
                                                                                                                        }
                                                                                                                    }
                                                                                                                }
                                                                                                            }
                                                                                                        }
                                                                                                    }
                                                                                                }
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        // Cleanup state buffers
        stateCleanup(finalHash, state5, state3, state4, state8, state11, state6, state9, state10, state7, state12, state2, state1, 0);
    }
    return result;
}