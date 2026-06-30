// FUNC_NAME: ConsoleCommandHandler::processCommand
// Address: 0x005ad380
// Role: Handles execution of console commands with various routing based on command type and context

void ConsoleCommandHandler::processCommand(void* this, uint* pCommandContext, uint* pOptionalData, int bForceExecute, int bCheckAgain)
{
    char* commandString;
    char cVar2;
    bool bVar4;
    undefined4 uVar5;
    int iVar3;
    char local_1c[8]; // buffer for command name/path?
    undefined4 local_14; // probably a hash or result

    if (pOptionalData == (uint*)0x0)
    {
        return;
    }

    // Check if console mode is enabled
    cVar2 = isConsoleModeEnabled(0);
    if (cVar2 != '\0')
    {
        startConsoleInput();
        cVar2 = isConsoleInputActive();
        if (cVar2 != '\0')
        {
            return; // Already in console input mode, ignore
        }
    }

    commandString = *(char**)(pCommandContext + 8); // command string at offset +8

    // Check for special command prefixes: _r, _l, _ty, _x, _y, _sc, _wi, _he, _al
    if ((((*commandString != '_') || (cVar2 = commandString[1], cVar2 == 'r')) || (cVar2 == 'l')) ||
        ((((((cVar2 != 't' || (commandString[2] != 'y')) && ((cVar2 != 'x' || (commandString[2] != '\0')))) &&
           ((cVar2 != 'y' || (commandString[2] != '\0')))) && ((cVar2 != 's' || (commandString[2] != 'c')))) &&
         ((((cVar2 != 'w' || (commandString[2] != 'i')) && ((cVar2 != 'h' || (commandString[2] != 'e')))) &&
          ((cVar2 != 'a' || (commandString[2] != 'l'))))))))
    {
        // Not a special command prefix, set global flag to indicate command executed
        g_bCommandExecuted = true; // DAT_0103af70
    }

    // Check if bit 15 of pOptionalData is clear (i.e., not an internal command)
    if ((~(byte)(*pOptionalData >> 0xf) & 1) == 0)
    {
        cVar2 = isConsoleModeEnabled(0);
        if (cVar2 == '\0')
        {
            cVar2 = isConsoleCommandQueued();
            if (cVar2 == '\0')
            {
                cVar2 = isCommandBuiltIn();
                if (cVar2 != '\0')
                {
                    acknowledgeCommand();
                    captureCommandState(local_1c);
                    g_pCommandHandlerFunc(*(undefined4*)(pCommandContext + 8), local_14); // call function pointer
                    finalizeCommand();
                    return;
                }
                goto LAB_005ad4d8;
            }
            // Command is queued, fetch and process
            uVar5 = *(undefined4*)(pCommandContext + 8);
            queueCommandOutput();
            iVar3 = executeQueuedCommand(uVar5, pOptionalData);
        }
        else
        {
            // Console mode active, handle via console
            uVar5 = *(undefined4*)(pCommandContext + 8);
            startConsoleInput();
            prepareConsoleExecution();
            iVar3 = runConsoleCommand(pOptionalData, uVar5, pOptionalData);
        }

        if (iVar3 != 0)
        {
            return;
        }
    }

LAB_005ad4d8:
    if (bForceExecute == 0)
    {
        // Conditions based on internal counter at this+0x604
        if (0 < *(int*)(this + 0x604))
        {
            uVar5 = *(undefined4*)(pCommandContext + 8);
            iVar3 = fetchCommandHandler(uVar5, pOptionalData);
            processCommandRoutine(iVar3 + 4, uVar5, pOptionalData);
            return;
        }
        bVar4 = (pOptionalData == g_pCurrentCommandData); // compare to global pointer
    }
    else
    {
        if ((bCheckAgain != 0) && (0 < *(int*)(this + 0x604)))
        {
            uVar5 = *(undefined4*)(pCommandContext + 8);
            iVar3 = fetchCommandHandler(); // missing args? original code: FUN_005b1b90()
            iVar3 = checkCommandStream(iVar3 + 4, uVar5);
            if (iVar3 != 0)
            {
                uVar5 = *(undefined4*)(pCommandContext + 8);
                iVar3 = fetchCommandHandler(uVar5, pOptionalData);
                processCommandRoutine(iVar3 + 4, uVar5, pOptionalData);
                return;
            }
        }

        if (pOptionalData == (uint*)0x0)
        {
            bVar4 = true;
        }
        else
        {
            bVar4 = (bool)(~(byte)(*pOptionalData >> 0xf) & 1);
        }
    }

    // Final handling: send acknowledgment and try to execute from buffer
    sendCommandAcknowledgment(*(undefined4*)(pCommandContext + 8), bVar4);
    iVar3 = acquireCommandBufferSlot();
    if (iVar3 != 0)
    {
        processCommandRoutine(iVar3, *(undefined4*)(pCommandContext + 8), pOptionalData);
    }
}