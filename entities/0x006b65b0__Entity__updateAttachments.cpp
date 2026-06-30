// FUNC_NAME: Entity::updateAttachments
// Address: 0x006b65b0
// Member function, __thiscall via ECX
void __fastcall Entity::updateAttachments(void* thisPtr) // param_1 = this
{
    // Offset 0x78: flag indicating whether to use attachment list or default processing
    int useAttachmentList = *(int*)((uintptr_t)thisPtr + 0x78);
    
    if (useAttachmentList == 0)
    {
        // Process default number of times (offset 0x68: defaultProcessCount)
        int defaultCount = *(int*)((uintptr_t)thisPtr + 0x68);
        for (int i = defaultCount; i != 0; i--)
        {
            // Process attachment slot 0 (default index)
            FUN_006b5c50(0); // processAttachment(0)
            
            // Increment processed count (offset 0x74)
            *(int*)((uintptr_t)thisPtr + 0x74) = *(int*)((uintptr_t)thisPtr + 0x74) + 1;
            
            // Check if this entity should use high-detail update
            float distThreshold = *(float*)((uintptr_t)thisPtr + 0x80); // +0x80: updateDistanceSq
            if ((gUpdateDistanceThreshold < distThreshold) ||
                ((*(uint*)((uintptr_t)thisPtr + 0x34) >> 0x1d & 1) != 0)) // bit 29 of flags
            {
                FUN_006b2f70(); // highDetailUpdate()
            }
            else
            {
                FUN_006b59f0(); // lowDetailUpdate()
            }
        }
    }
    else
    {
        // Process attachment list
        // Offset 0xac: number of attachments
        int attachmentCount = *(int*)((uintptr_t)thisPtr + 0xac);
        int iVar3 = attachmentCount - 1;
        if (iVar3 >= 0)
        {
            do
            {
                // Offset 0xa8: pointer to array of attachment indices (int)
                int* attachmentArray = *(int**)((uintptr_t)thisPtr + 0xa8);
                int attachmentIndex = attachmentArray[iVar3];
                
                // Validate attachment index
                char isValid = FUN_00791230(); // isValidAttachmentIndex(attachmentIndex) - but attachmentIndex not passed? Actually not, it's a global check? Based on decompile, it takes no parameters (or uses other context). We'll keep as is.
                // Note: The original call was FUN_00791230() with no args, but it might use a global state. We'll leave it.
                if (isValid != 0)
                {
                    FUN_006b5c50(attachmentIndex); // processAttachment(attachmentIndex)
                    
                    *(int*)((uintptr_t)thisPtr + 0x74) = *(int*)((uintptr_t)thisPtr + 0x74) + 1;
                    
                    float distThreshold = *(float*)((uintptr_t)thisPtr + 0x80);
                    if ((gUpdateDistanceThreshold < distThreshold) ||
                        ((*(uint*)((uintptr_t)thisPtr + 0x34) >> 0x1d & 1) != 0))
                    {
                        FUN_006b2f70();
                    }
                    else
                    {
                        FUN_006b59f0();
                    }
                }
                iVar3--;
            } while (iVar3 >= 0);
            return;
        }
    }
    return;
}