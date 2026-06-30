// FUNC_NAME: DonControlGadget::displayOptions
// Address: 0x0068ef90
// This function displays available options in the Don Control menu.
// It checks visibility (bit 1 of flags at +0x08) and state < 3.
// Uses an option provider (from +0x0C) to get up to 2 options.
// For each option, checks availability, builds text + callback, displays it.
// If no option found and state is 0, shows "no options" string.

void DonControlGadget::displayOptions(int param_2) // param_2 likely controller index or input ID
{
    // member offsets:
    // +0x00: vtable
    // +0x04: state (int)
    // +0x08: flags (byte), bit 1 = visible/active
    // +0x0C: optionProviderId (handle for FUN_004973e0)
    // +0x10: displayActive (byte)
    // +0x14: currentOptionIndex or limit (-1 for all)

    // Check visibility and state < 3
    if ((*(byte*)(this + 0x08) & 2) != 0 && *(int*)(this + 0x04) < 3)
    {
        // Get option provider from manager using the stored ID
        void* provider = (void*)getOptionProvider(*(int*)(this + 0x0C));
        if (provider != nullptr)
        {
            // Provider data: assumed two ints
            int providerVal1 = *(int*)provider;          // +0x00
            int providerVal2 = *(int*)(provider + 4);    // +0x04

            uint optionIndex = 0;
            while (true)
            {
                int maxIndex = *(int*)(this + 0x14);
                if (maxIndex != -1 && (int)optionIndex >= maxIndex)
                    break;
                if (optionIndex >= 2)
                    break;

                // Check if option is available
                char isAvailable = isOptionAvailable(providerVal1, providerVal2, optionIndex);
                if (isAvailable != 0)
                {
                    // Build option data into local buffer (text + callback)
                    int optionBuffer[3]; // struct: { const char* text, void (*callback)(int), ? }
                    void* result = buildOptionData(optionBuffer, isAvailable, param_2);
                    const char* text = *(const char**)result;
                    if (text == nullptr)
                        text = (const char*)0x0120546e; // empty string constant
                    drawText(text);
                    *(byte*)(this + 0x10) = 1; // mark display active

                    // Callback (if present) – decompiler introduced local_4 incorrectly.
                    // Assume optionBuffer[0] is function pointer, called with optionIndex.
                    if (optionBuffer[0] != 0)
                    {
                        ((void (*)(int))optionBuffer[0])(optionIndex);
                    }

                    // Update state to 2 (option selected/displayed)
                    if ((*(byte*)(this + 0x08) & 2) != 0 && *(int*)(this + 0x04) < 3)
                    {
                        *(int*)(this + 0x04) = 2;
                    }
                    *(uint*)(this + 0x14) = optionIndex;
                    return;
                }
                optionIndex++;
            }

            // No option found and state is 0 -> show default empty message
            if (*(int*)(this + 0x04) == 0)
            {
                int defaultString = getLocalizedString(0x33371f37); // hash for "no options"
                drawText(defaultString);
                *(byte*)(this + 0x10) = 1;
                if ((*(byte*)(this + 0x08) & 2) != 0 && *(int*)(this + 0x04) < 3)
                {
                    *(int*)(this + 0x04) = 2;
                }
            }
        }
    }
}