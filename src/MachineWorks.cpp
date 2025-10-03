#include "MachineWorks.h"

// -----------------------------------------------------------------------------------------------------------------------------
void initialize_mw() {

    LtStatus status;
    /* Setup the memory callbacks to the static functions (before LiInitialize) */
#if LI_OS == LI_OS_NT
    status = LiMemorySetCallbacks(MemAllocate, MemDeallocate, MemReallocate, MemSize);
    // status = LiMemorySetCallbacks(LiAllocate, LiDeallocate, LiReallocate, MemSize);
#else
    /* The LtFuncMemorySize callback is optional */
    status =
        LiMemorySetCallbacks(MemAllocate, MemDeallocate, MemReallocate, (LtFuncMemorySize)NULL);
#endif

    /* Initialise the MachineWorks system: This call is found in mwinit */
    status = LiInitialise();

    LtData data;
    if (LiStatusFail(status)) {
        fprintf(stderr, "\nERROR: Failed to initialise MachineWorks\n");
    } else {
        // Get MachineWorks version info.
        LiControlGet(LI_CONTROL_VERSION_NUMBER, &data);
        LtNat32 version = LiDataGetNat32(&data);
        fprintf(stdout, "\n============================================\n");
        fprintf(stdout, "MachineWorks is initialised\n");
        printf("    Major Version: %d\n", LiVersionGetMajor(version));
        printf("    Minor Version: %d\n", LiVersionGetMinor(version));
        printf("    Build Version: %d\n", LiVersionGetBuild(version));
        fprintf(stdout, "\n============================================\n");
    }

#if CDT_DEBUG
    /* Diagnostic function to check for clashes */
    default_diagnostic = (LtFuncDiagnostic)LiCallBackGet(LI_CALL_DIAGNOSTIC);
    status = LiCallBackSet(LI_CALL_DIAGNOSTIC, (LtFunc)my_diagnostic_handler);
    if (LiStatusFail(status)) {
        fprintf(stderr, "\nERROR: Failed to set the diagnostic call back in MachineWorks\n");
    } else {
        fprintf(stdout, "\n============================================\n");
        fprintf(stdout, "Diagnostic call back is set");
        fprintf(stdout, "\n============================================\n");
    }

    // Check that the LI_DIR environment variable is set up correctly, so that
    // MachineWorks has found the 'LI_DIR'/messages/english/diagnos file, to
    // translate diagnostic code numbers to english text
    LiControlGet(LI_CONTROL_MESSAGES_FILE, &data);
    if (!LiDataGetGenericPtr(&data)) {
        DISPLAY_TEXT("To get nicely formatted diagnostic messages, should set "
                     "the environment variable LI_DIR to point to the directory "
                     "MachineWorks is installed in\n");
    }

    // start journaling if in DEBUG mode
    _journal_fp = LiFileOpen("mw_journal.lwc", LI_FILE_WRITE);
    LiDataSetGenericPtr(&_journal_data, _journal_fp);
    LiControlSet(LI_CONTROL_JOURNAL_FILE, &_journal_data);
    LiDataSetBitfield(&_journal_data, LI_JOURNAL_TEXT);
    LiControlSet(LI_CONTROL_JOURNALING, &_journal_data);

    query_memory_usage("after initialisation");
#endif
}

// -----------------------------------------------------------------------------------------------------------------------------
void terminate_mw() {
#if CDT_DEBUG
    LiDataSetBitfield(&_journal_data, LI_JOURNAL_OFF);
    LiControlSet(LI_CONTROL_JOURNALING, &_journal_data);
    LiFileClose(_journal_fp);
#endif

    /* Terminate the MachineWorks system: This call is found in mwinit */
    LtStatus status = LiTerminate();
    if (LiStatusFail(status)) {
        fprintf(stderr, "\nERROR: Failed to terminate MachineWorks\n");
    } else {
        fprintf(stdout, "\n============================================\n");
        fprintf(stdout, "MachineWorks is terminated");
        fprintf(stdout, "\n============================================\n");
    }
}