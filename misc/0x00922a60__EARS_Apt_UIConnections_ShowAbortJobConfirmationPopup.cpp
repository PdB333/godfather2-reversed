// Xbox PDB: EARS_Apt_UIConnections_ShowAbortJobConfirmationPopup
// FUNC_NAME: PauseJobConfirmDelete::constructor
// 0x00922a60: Creates a new PauseJobConfirmDelete object (confirm delete job) in the pause menu.
// Allocates 0xF0 bytes, initializes base PauseJob, registers a string, and sets job fields.
void PauseJobConfirmDelete::constructor() {
    // Allocate memory for the object (size 0xF0 = 240 bytes)
    PauseJobConfirmDelete* this = static_cast<PauseJobConfirmDelete*>(operatorNew(0xF0));
    if (this != nullptr) {
        // Call base class (PauseJob) constructor with parameter 0 (likely job type flag)
        PauseJob::constructor(0);
    }
    // Register the confirmation delete string for UI lookup
    registerString("$pause_job_confirm_delete");

    // Initialize specific fields (offsets relative to this)
    this->m_typeId = 2;                        // +0x0C: job type identifier
    this->m_hash1 = 0xB9754031;               // +0x20: first magic hash
    this->m_hash2 = 0x997DEE17;               // +0x1C: second magic hash
    this->m_callback = (void (*)())0x00922850; // +0x14: callback function (confirm delete handler)

    // Finalize construction (e.g., register job with manager, post event)
    finalizeConstruction();
}