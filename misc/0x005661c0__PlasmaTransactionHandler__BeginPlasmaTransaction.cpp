// FUNC_NAME: PlasmaTransactionHandler::BeginPlasmaTransaction
void __thiscall PlasmaTransactionHandler::BeginPlasmaTransaction(
    uint32_t param_2, uint32_t param_3, uint32_t param_4,
    uint32_t param_5, uint32_t param_6, uint32_t param_7, uint32_t param_8)
{
    // Offsets: this+0x8044 = m_pTransactionContext (pointer to a transaction context object)
    //          this+0x8004 = m_pTransactionBuffer (buffer for transaction data)
    if (this->m_pTransactionContext != nullptr)
    {
        // Initialize the Plasma system (global call)
        Plasma_Initialize();

        // Get the Plasma service provider (singleton)
        PlasmaServiceProvider* pServiceProvider = Plasma_GetServiceProvider();
        if (pServiceProvider != nullptr)
        {
            // VTable offset 0x48: GetTransactionManager
            PlasmaTransactionManager* pTransactionMgr = pServiceProvider->GetTransactionManager();
            if (pTransactionMgr != nullptr)
            {
                // VTable offset 0x28: BeginTransaction
                PlasmaTransaction* pTransaction = pTransactionMgr->BeginTransaction();
                if (pTransaction != nullptr)
                {
                    // VTable offset 0x08: IsTransactionReady (returns bool)
                    bool bReady = pTransaction->IsTransactionReady();
                    if (bReady)
                    {
                        // m_pTransactionContext->WriteTransactionData at VTable offset 0x2c
                        // This writes transaction parameters into m_pTransactionBuffer
                        this->m_pTransactionContext->WriteTransactionData(
                            this->m_pTransactionBuffer,
                            param_2,
                            1,
                            param_3,
                            param_4,
                            1,
                            0,
                            param_5,
                            param_6,
                            0);

                        // Check for Plasma errors after write
                        if (Plasma_IsError())
                        {
                            int errorCode = Plasma_GetLastError();
                            LogError(errorCode, "Error creating Plasma transaction");
                        }

                        // m_pTransactionContext->GetTransaction (VTable offset 0x00)
                        // returns another object
                        // then call its SetTimeout at VTable offset 0x10
                        IPlasmaTransaction* pTxInterface = this->m_pTransactionContext->GetTransaction();
                        pTxInterface->SetTimeout(
                            this->m_pTransactionBuffer,
                            param_7,
                            param_8,
                            10000);
                    }
                }
            }
        }
    }
}