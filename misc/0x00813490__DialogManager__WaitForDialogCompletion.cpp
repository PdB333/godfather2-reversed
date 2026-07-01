// FUNC_NAME: DialogManager::WaitForDialogCompletion
void __thiscall DialogManager::WaitForDialogCompletion(uint resourceId)
{
    // Start the dialog resource
    StartDialog(resourceId);
    // Set a completion callback with a specific event hash
    SetCompletionCallback(resourceId, 0x85b01e7f);

    // Block until the dialog is finished
    while (!IsDialogFinished())
    {
        // Process pending messages/updates
        PumpDialogMessages();

        int state = GetDialogState();
        if (state == 0)
        {
            // Process again and retrieve result, then store in member at +0x50
            PumpDialogMessages();
            uint result = GetDialogResult();
            this->m_dialogResult = result; // offset +0x50
        }
        else if (state == 1)
        {
            // Process and retrieve result, then set it as response and mark complete
            PumpDialogMessages();
            uint result = GetDialogResult();
            SetDialogResponse(result);
            SetDialogComplete(1);
        }

        // Advance the dialog state/frame
        AdvanceDialogState();
    }
}