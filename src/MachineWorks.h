/* MachineWorks.h */

#include "li/li.h"

/* Initialise MachineWorks */
#define MWINIT_OPTIONED /* turn on new system of LiInitialise */

/* Start up journaling for debug builds */
/*
#ifdef _DEBUG
#define MWINIT_JOURNAL_FILE "c:/temp/mworks_journal.lwc"
#endif
#define MWINIT_MESSAGES_ENV_VAR "LI_DIAG_MESSAGE_FILE"
#define MWINIT_DIAGNOSTIC_HANDLER_PARAMETER
*/

/* LiInitialise will take a second parameter */
/* which will be the diagnostic handler */
#include "li/mwinit.h"

#ifdef _DEBUG // debug
#define CDT_DEBUG _DEBUG
#else // optimized
#define CDT_DEBUG 0
#endif

/*
 * A simple implementation that just calls malloc/realloc/free
 */
static LtGenericPtr MemAllocate(LtSize size) {
    LtGenericPtr result;

    result = malloc(size);

    return result;
}

static LtGenericPtr MemReallocate(LtGenericPtr ptr, LtSize new_size) {
    LtGenericPtr result;

    if (ptr)
        result = realloc(ptr, new_size);
    else
        result = malloc(new_size);

    return result;
}

static void MemDeallocate(LtGenericPtr ptr) {
    if (ptr)
        free(ptr);
}

/// Nothing but LiInitialise() and LiTerminate();
void initialize_mw();
void terminate_mw();