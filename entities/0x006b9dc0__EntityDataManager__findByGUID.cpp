// FUNC_NAME: EntityDataManager::findByGUID
int __thiscall EntityDataManager::findByGUID(EntityDataManager *this, int *guid)
{
    // Flags at +0x80; check if bit 2 is set (networked lookup path)
    if (((*(uint *)((int)this + 0x80) >> 2) & 1) == 0)
    {
        // Non‑networked path – verify the GUID is not a known sentinel value
        if ((*guid != 0xBBDBDBBA) || 
            (guid[1] != 0xBEEFBEEF) || 
            (guid[2] != 0xEAC15A55) || 
            (guid[3] != 0x91100911))
        {
            // Also reject an all‑zero GUID
            if ((*guid != 0) || (guid[1] != 0) || (guid[2] != 0) || (guid[3] != 0))
            {
                // Look up in the local hash table (FUN_00446100 is guidTableLookup)
                int *base = (int *)guidTableLookup(guid, 0);
                if (base != 0)
                {
                    // Entity data is at base+0x50
                    return (int)base + 0x50;
                }
            }
        }
    }
    else
    {
        // Networked path: use the net session to find the object
        NetSession *session = (NetSession *)FUN_0078e110();   // likely NetSession::getInstance
        if (session != 0)
        {
            // FUN_0078dbb0 is probably NetSession::findObjectByGUID
            return (int)FUN_0078dbb0();
        }
    }
    return 0;
}