// FUNC_NAME: CryptoEngine::processBlock

int __thiscall CryptoEngine::processBlock(void)
{
    uint8_t block1[16];
    uint8_t block2[16];
    uint8_t block3[16];
    uint8_t block4[16];
    uint8_t block5[16];
    uint8_t block6[16];
    uint8_t block7[16];
    uint8_t block8[16];
    uint8_t block9[16];
    int result;
    uint32_t size;

    size = this->m_size; // +0x00: some size value
    result = initializeTransform(block1, block6, block8, block7, block4, block2, block5, block3, block9, 0);
    if (result == 0) {
        int halfSize = size / 3;
        result = allocateBuffer(halfSize * 28);
        if (result == 0) {
            result = checkPrecondition();
            if (result == 0) {
                doSubTransform(halfSize);
                allocateBuffer(halfSize * 28);
                result = checkPrecondition();
                if (result == 0) {
                    doSubTransform(halfSize * 2);
                    result = xorBlocks(block2, block1);
                    if (result == 0) {
                        result = xorBlocks(block3, block4);
                        if (result == 0) {
                            result = multiplyBlocks(block2, block9);
                            if (result == 0) {
                                result = hashBlock(block9);
                                if (result == 0) {
                                    result = multiplyBlocks(block9, block9);
                                    if (result == 0) {
                                        result = hashBlock(block9);
                                        if (result == 0) {
                                            result = xorBlocks(block9, block6);
                                            if (result == 0) {
                                                result = multiplyBlocks(block3, block9);
                                                if (result == 0) {
                                                    result = hashBlock(block9);
                                                    if (result == 0) {
                                                        result = multiplyBlocks(block9, block9);
                                                        if (result == 0) {
                                                            result = hashBlock(block9);
                                                            if (result == 0) {
                                                                result = xorBlocks(block9, block7);
                                                                if (result == 0) {
                                                                    result = hashBlock(block3);
                                                                    if (result == 0) {
                                                                        result = hashBlock(block9);
                                                                        if (result == 0) {
                                                                            result = xorBlocks(block9, block8);
                                                                            if (result == 0) {
                                                                                result = addBlocks(block6, block4);
                                                                                if (result == 0) {
                                                                                    result = addBlocks(block7, block1);
                                                                                    if (result == 0) {
                                                                                        result = rotateBlock(block6);
                                                                                        if (result == 0) {
                                                                                            result = rotateBlock(block7);
                                                                                            if (result == 0) {
                                                                                                result = addBlocks(block8, block1);
                                                                                                if (result == 0) {
                                                                                                    result = addBlocks(block8, block4);
                                                                                                    if (result == 0) {
                                                                                                        result = addBlocks(block6, block8);
                                                                                                        if (result == 0) {
                                                                                                            result = addBlocks(block7, block8);
                                                                                                            if (result == 0) {
                                                                                                                result = processWithConstant3(3);
                                                                                                                if (result == 0) {
                                                                                                                    result = addBlocks(block6, block9);
                                                                                                                    if (result == 0) {
                                                                                                                        result = processWithConstant3(3);
                                                                                                                        if (result == 0) {
                                                                                                                            result = addBlocks(block7, block9);
                                                                                                                            if (result == 0) {
                                                                                                                                result = combineBlock(block8, 3, block8);
                                                                                                                                if (result == 0) {
                                                                                                                                    result = addBlocks(block8, block6);
                                                                                                                                    if (result == 0) {
                                                                                                                                        result = addBlocks(block8, block7);
                                                                                                                                        if (result == 0) {
                                                                                                                                            result = addBlocks(block6, block8);
                                                                                                                                            if (result == 0) {
                                                                                                                                                result = addBlocks(block7, block8);
                                                                                                                                                if (result == 0) {
                                                                                                                                                    result = setBlock(block6, block6, 0);
                                                                                                                                                    if (result == 0) {
                                                                                                                                                        result = setBlock(block7, block7, 0);
                                                                                                                                                        if (result == 0) {
                                                                                                                                                            result = processKey(halfSize);
                                                                                                                                                            if (result == 0) {
                                                                                                                                                                result = processKey(halfSize * 2);
                                                                                                                                                                if (result == 0) {
                                                                                                                                                                    result = processKey(halfSize * 3);
                                                                                                                                                                    if (result == 0) {
                                                                                                                                                                        result = processKey(halfSize * 4);
                                                                                                                                                                        if (result == 0) {
                                                                                                                                                                            result = hashBlock(block1);
                                                                                                                                                                            if (result == 0) {
                                                                                                                                                                                result = hashBlock(block8);
                                                                                                                                                                                if (result == 0) {
                                                                                                                                                                                    result = hashBlock(block4);
                                                                                                                                                                                    if (result == 0) {
                                                                                                                                                                                        result = hashBlock(block9);
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
        cleanupTransform(block1, block6, block8, block7, block4, block2, block5, block3, block9, 0);
    }
    return result;
}