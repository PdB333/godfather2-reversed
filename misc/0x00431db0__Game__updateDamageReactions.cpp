// FUNC_NAME: Game::updateDamageReactions

void Game::updateDamageReactions(Game *this)
{
    // Global phase flags – set once per frame
    DAT_0110b598 = 1;   // start damage reaction processing
    DAT_0110b599 = 0;
    DAT_0110b59a = 0;
    DAT_0110b5a4 = 0;
    DAT_0110b59c = 0;
    DAT_0110b5a0 = 0;
    DAT_0110b5a8 = 0;
    _DAT_0110b5ac = 0;

    // Pointer to the array of character pointers (starting at +0x3a74)
    int *characterPtrArray = (int *)(this + 0x3a74);
    int characterCount = *(int *)(this + 0x3af4);

    int *currentCharacterSlot = characterPtrArray;
    int *endCharacterSlot = characterPtrArray + characterCount;

    while (currentCharacterSlot != endCharacterSlot)
    {
        Character *character = (Character *)*currentCharacterSlot;

        // vtable+0x44: isCharacterAlive()
        if (character->isAlive())
        {
            // The character has 3 body‑part slots (head, torso, legs?).
            // Slot pointers are at character+4, character+5, character+6.
            int *slot = (int *)((char *)character + 4);
            int slotCount = 3;

            do
            {
                // Traverse the linked list of body parts for this slot.
                BodyPart *bodyPart = (BodyPart *)*slot;
                while (bodyPart != 0)
                {
                    // Check if body part is active (bit 1 of flags at +0x38 clear)
                    if (((*(byte *)(bodyPart + 0x38) & 2) == 0) &&
                        // vtable+0x14: canApplyEffect(BodyPart*)
                        character->canApplyEffect(bodyPart))
                    {
                        // Access a game timer or global state via FS segment
                        // (likely a thread‑local storage pointer to the game instance)
                        uint timerValue = *(uint *)(*(int *)(**(int **)(unaff_FS_OFFSET + 0x2c) + 8) + 0x7c +
                                                    *(int *)(bodyPart + 0x18));
                        // vtable+0x40: getInvincibilityFlag()
                        byte invincibleFlag = character->getInvincibilityFlag();
                        // Compare bit 11 of timer with the invincibility flag
                        if (((byte)(timerValue >> 0xb) & 1) == invincibleFlag)
                        {
                            // Search the 3 active reaction slots (global table at DAT_012233b0+0x30)
                            int reactionSlotIndex = 0;
                            uint reactionDataID = 0;
                            void *reactionDataPtr = 0;
                            int *reactionSlotArray = (int *)(DAT_012233b0 + 0x30);
                            bool found = false;

                            for (int i = 0; i < 3; i++)
                            {
                                if (reactionSlotArray[i] == (int)bodyPart)
                                {
                                    reactionDataID = *(uint *)(0x01163834 + i * 0x84);  // some data ID array
                                    reactionDataPtr = (void *)(0x01163650 + i * 0x210); // associated data structure
                                    found = true;
                                    break;
                                }
                            }

                            // vtable+0x3c: isCurrentlyReacting()
                            bool isReacting = character->isCurrentlyReacting();

                            if (found == isReacting)
                            {
                                FUN_0041c210(reactionDataID, reactionDataPtr);
                            }
                        }
                    }
                    bodyPart = (BodyPart *)*(int *)((char *)bodyPart + 0x10); // next link
                }
                slot++;     // move to next slot pointer
                slotCount--;
            } while (slotCount != 0);
        }
        currentCharacterSlot++;
    }

    // Post‑update cleanup
    FUN_0041c2d0();
}