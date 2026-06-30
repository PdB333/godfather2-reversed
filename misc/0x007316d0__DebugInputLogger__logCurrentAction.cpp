// FUNC_NAME: DebugInputLogger::logCurrentAction
void __fastcall DebugInputLogger::logCurrentAction(int this) {
    uint32_t actionFlags;
    char pressed;
    uint32_t actionHash;
    char actionString[20];
    void *somePointer;

    // Initialize logging state
    FUN_00892af0(0);
    FUN_00892ce0(this, 0);

    actionFlags = *(uint32_t *)(this + 0x2188); // +0x2188: bitfield of active inputs/states

    if ((actionFlags >> 9 & 1) == 0) {
        if ((actionFlags >> 3 & 1) == 0) {
            if ((actionFlags >> 4 & 1) == 0) {
                if ((actionFlags >> 5 & 1) == 0) {
                    if ((actionFlags >> 6 & 1) == 0) {
                        pressed = isActionActive(0x3e); // Check action ID 0x3e
                        if (pressed == 0) {
                            pressed = isActionActive(0x38);
                            if (pressed == 0) {
                                pressed = isActionActive(0x10);
                                if (pressed == 0) {
                                    pressed = isActionActive(0x11);
                                    if (pressed == 0) {
                                        pressed = isActionActive(0x1d);
                                        if (pressed == 0) {
                                            pressed = isActionActive(0x1e);
                                            if (pressed == 0) {
                                                pressed = isActionActive(0x1f);
                                                if (pressed == 0) {
                                                    pressed = isActionActive(0x20);
                                                    if (pressed == 0) {
                                                        pressed = isActionActive(0x21);
                                                        if (pressed == 0) {
                                                            pressed = isActionActive(0x22);
                                                            if (pressed == 0) {
                                                                pressed = isActionActive(0x23);
                                                                if (pressed == 0) {
                                                                    pressed = isActionActive(0x24);
                                                                    if (pressed == 0) {
                                                                        pressed = isActionActive(0x25);
                                                                        if (pressed == 0) {
                                                                            pressed = isActionActive(0x26);
                                                                            if (pressed == 0) {
                                                                                pressed = isActionActive(0x19);
                                                                                if (pressed == 0) {
                                                                                    pressed = isActionActive(0x1a);
                                                                                    if (pressed == 0) {
                                                                                        pressed = isActionActive(0x27);
                                                                                        if (pressed == 0) {
                                                                                            pressed = isActionActive(0x28);
                                                                                            if (pressed == 0) {
                                                                                                pressed = isActionActive(0x2b);
                                                                                                if (pressed == 0) {
                                                                                                    pressed = isActionActive(0x2c);
                                                                                                    if (pressed == 0) {
                                                                                                        pressed = isActionActive(0x29);
                                                                                                        if (pressed == 0) {
                                                                                                            pressed = isActionActive(0x2a);
                                                                                                            if (pressed == 0) {
                                                                                                                pressed = isActionActive(0x2d);
                                                                                                                if (pressed == 0) {
                                                                                                                    pressed = isActionActive(0x2e);
                                                                                                                    if (pressed == 0) {
                                                                                                                        pressed = isActionActive(0x2f);
                                                                                                                        if (pressed == 0) {
                                                                                                                            pressed = isActionActive(0x30);
                                                                                                                            if (pressed == 0) {
                                                                                                                                pressed = isActionActive(0x31);
                                                                                                                                if (pressed == 0) {
                                                                                                                                    pressed = isActionActive(0x32);
                                                                                                                                    if (pressed == 0) {
                                                                                                                                        pressed = isActionActive(0x1b);
                                                                                                                                        if (pressed == 0) {
                                                                                                                                            pressed = isActionActive(0x1c);
                                                                                                                                            if (pressed == 0) {
                                                                                                                                                pressed = isActionActive(0xc);
                                                                                                                                                if (pressed == 0) {
                                                                                                                                                    pressed = isActionActive(0xa);
                                                                                                                                                    if (pressed == 0) {
                                                                                                                                                        pressed = isActionActive(0xb);
                                                                                                                                                        if (pressed == 0) {
                                                                                                                                                            pressed = isActionActive(0x37);
                                                                                                                                                            if (pressed == 0) {
                                                                                                                                                                pressed = isActionActive(0x39);
                                                                                                                                                                if (pressed == 0) {
                                                                                                                                                                    pressed = isActionActive(0x33);
                                                                                                                                                                    if ((((pressed == 0) &&
                                                                                                                                                                          (pressed = isActionActive(0x34), pressed == 0)) &&
                                                                                                                                                                         (pressed = isActionActive(0x35), pressed == 0)) &&
                                                                                                                                                                        (pressed = isActionActive(0x36), pressed == 0)) {
                                                                                                                                                                        pressed = isActionActive(7);
                                                                                                                                                                        if (pressed == 0) {
                                                                                                                                                                            pressed = isActionActive(8);
                                                                                                                                                                            if (pressed == 0) {
                                                                                                                                                                                pressed = isActionActive(0xd);
                                                                                                                                                                                if (pressed == 0) {
                                                                                                                                                                                    pressed = isActionActive(0xf);
                                                                                                                                                                                    if (pressed == 0) {
                                                                                                                                                                                        pressed = isActionActive(0x18);
                                                                                                                                                                                        if (pressed == 0) {
                                                                                                                                                                                            pressed = isActionActive(0xe);
                                                                                                                                                                                            if (pressed == 0)
                                                                                                                                                                                                goto NoActionFound;
                                                                                                                                                                                            actionHash = 0x6c7c1322;
                                                                                                                                                                                        } else {
                                                                                                                                                                                            actionHash = 0x2e853277;
                                                                                                                                                                                        }
                                                                                                                                                                                    } else {
                                                                                                                                                                                        actionHash = 0xc9bb805a;
                                                                                                                                                                                    }
                                                                                                                                                                                } else {
                                                                                                                                                                                    actionHash = 0xd26b49b0;
                                                                                                                                                                                }
                                                                                                                                                                            } else {
                                                                                                                                                                                actionHash = 0x8b569ac8;
                                                                                                                                                                            }
                                                                                                                                                                            goto LogAction;
                                                                                                                                                                        }
                                                                                                                                                                    } else {
                                                                                                                                                                        logDebugHash(0xa25cd9e5, actionString);
                                                                                                                                                                    }
                                                                                                                                                                    actionHash = 0x65876022;
                                                                                                                                                                } else {
                                                                                                                                                                    actionHash = 0xbb8031b;
                                                                                                                                                                }
                                                                                                                                                            } else {
                                                                                                                                                                setDebugFlag(this, 1);
                                                                                                                                                                actionHash = 0x2cfa515e;
                                                                                                                                                            }
                                                                                                                                                        } else {
                                                                                                                                                            actionHash = 0xa6ace4fb;
                                                                                                                                                        }
                                                                                                                                                    } else {
                                                                                                                                                        actionHash = 0x729b4cda;
                                                                                                                                                    }
                                                                                                                                                } else {
                                                                                                                                                    actionHash = 0xa17ee79b;
                                                                                                                                                }
                                                                                                                                            } else {
                                                                                                                                                actionHash = 0x169ca58;
                                                                                                                                            }
                                                                                                                                        } else {
                                                                                                                                            actionHash = 0xbd2bd105;
                                                                                                                                        }
                                                                                                                                    } else {
                                                                                                                                        actionHash = 0xbab58bda;
                                                                                                                                    }
                                                                                                                                } else {
                                                                                                                                    actionHash = 0x76779287;
                                                                                                                                }
                                                                                                                            } else {
                                                                                                                                actionHash = 0xbab58bda;
                                                                                                                            }
                                                                                                                        } else {
                                                                                                                            actionHash = 0x76779287;
                                                                                                                        }
                                                                                                                    } else {
                                                                                                                        actionHash = 0xa90ce6b5;
                                                                                                                    }
                                                                                                                } else {
                                                                                                                    actionHash = 0x64ceed62;
                                                                                                                }
                                                                                                            } else {
                                                                                                                actionHash = 0x52d9b0f6;
                                                                                                            }
                                                                                                        } else {
                                                                                                            actionHash = 0xe9bb7a3;
                                                                                                        }
                                                                                                    } else {
                                                                                                        actionHash = 0x78a7606b;
                                                                                                    }
                                                                                                } else {
                                                                                                    actionHash = 0x34696718;
                                                                                                }
                                                                                            } else {
                                                                                                actionHash = 0x374c1cba;
                                                                                            }
                                                                                        } else {
                                                                                            actionHash = 0xf30e2367;
                                                                                        }
                                                                                    } else {
                                                                                        actionHash = 0x45e21006;
                                                                                    }
                                                                                } else {
                                                                                    actionHash = 0x1a416b3;
                                                                                }
                                                                            } else {
                                                                                actionHash = 0xe8de0e00;
                                                                            }
                                                                        } else {
                                                                            actionHash = 0xa4a014ad;
                                                                        }
                                                                    } else {
                                                                        actionHash = 0x93d85d69;
                                                                    }
                                                                } else {
                                                                    actionHash = 0x4f9a6416;
                                                                }
                                                            } else {
                                                                actionHash = 0xfb8a7686;
                                                            }
                                                        } else {
                                                            actionHash = 0xb74c7d33;
                                                        }
                                                    } else {
                                                        actionHash = 0x7670f28;
                                                    }
                                                } else {
                                                    actionHash = 0xc32915d5;
                                                }
                                            } else {
                                                actionHash = 0xbc66f1e2;
                                            }
                                        } else {
                                            actionHash = 0x7828f88f;
                                        }
                                    } else {
                                        actionHash = 0xfe60dc0f;
                                    }
                                } else {
                                    actionHash = 0x387365c3;
                                }
                            } else {
                                setDebugFlag(this, 1);
                                actionHash = 0x1e097179;
                            }
                        } else {
                            actionHash = 0xc5150eb3;
                        }
                    } else {
                        actionHash = 0x28110bb4;
                    }
                } else {
                    actionHash = 0xc7f4ab7b;
                }
            } else {
                setDebugFlag(this, 1);
                actionHash = 0xa7b6f219;
            }
        } else {
            setDebugFlag(this, 1);
            actionHash = 0xab2cf25a;
        }
    } else {
        actionHash = 0xc49663d;
    }

LogAction:
    logDebugHash(actionHash, actionString);

NoActionFound:
    if ((*(uint32_t *)(this + 0x2188) >> 0x12 & 1) != 0) {
        logDebugHash(0xb603c6dc, actionString);
    }
    if ((*(uint32_t *)(this + 0x2188) >> 0x13 & 1) != 0) {
        logDebugHash(0x16646068, actionString);
    }
    if ((*(uint32_t *)(this + 0x2188) >> 0x14 & 1) != 0) {
        logDebugHash(0x91339333, actionString);
    }
    if ((*(uint32_t *)(this + 0x2188) >> 0x15 & 1) != 0) {
        logDebugHash(0x3641fe77, actionString);
    }
    if ((*(uint32_t *)(this + 0x2188) >> 0x16 & 1) != 0) {
        logDebugHash(0xc696e948, actionString);
    }
    if ((*(uint32_t *)(this + 0x2188) >> 0x17 & 1) != 0) {
        logDebugHash(0x3250a1ea, actionString);
    }

    if (somePointer != 0) {
        freeDebugBuffer(somePointer);
    }
    return;
}