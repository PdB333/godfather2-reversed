// FUNC_NAME: JobRequest::submit
bool JobRequest::submit()
{
    // Check if any input parameters are set and we are not already processing a job
    if (((m_inputParams[0] != 0) || (m_inputParams[1] != 0) || (m_inputParams[2] != 0) || (m_inputParams[3] != 0)) &&
        (m_jobId == 0))
    {
        int jobSlot = allocateJobSlot();                // Get a free slot from the job manager
        int jobId = submitJob(this, jobSlot);            // Submit the request and obtain a job ID
        m_jobId = jobId;                                 // Store the job ID for later tracking
        if (jobId != 0)
        {
            setJobUserData(jobId, m_userData);           // Attach user data to the running job
        }
    }
    return m_jobId != 0;                                 // Return true if a job is now active
}