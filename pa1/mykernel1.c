/* mykernel1.c: your portion of the kernel
 *
 *	Below are routines that are called by other parts of the kernel. 
 *	Your ability to modify the kernel is via these routines.  You may
 *	modify the bodies of these routines, and add code outside or them,
 *	in any way you wish (however, you cannot change their interfaces).  
 * 
 */
#include <stdio.h>
#include <strings.h>
#include "aux.h"
#include "sys.h"
#include "mykernel1.h"
static CONTEXT processes[MAXPROCS];

/* NewContext (p, c) will be called by the kernel whenever a new process
 * is created.  This is essentially a notification (which you will make
 * use of) that this newly created process has an ID of p, and that its
 * initial context is pointed to by c.  Make sure you make a copy of the
 * contents of this context (i.e., don't copy the pointer, but the contents
 * pointed to by the pinter), as the pointer will become useless after this
 * routine returns.
 */

void NewContext (p, c)
	int p;				// ID of new process just created
	CONTEXT *c;			// initial context for this process
{
	/* your code here */
        if (p > MAXPROCS || p < 0) return;
        memcpy(&processes[p - 1], c, sizeof(CONTEXT));
}

/* MySwitchContext (p) should cause a context switch from the calling
 * process to process p. It should return the ID of the calling process.  
 * The ID of the calling process can be determined by calling GetCurProc (),
 * which returns the currently running process's ID.  The routine
 * SwitchContext (p) is an internal working version of context switching. 
 * This is provided so that the kernel works without modification, to
 * allow the other exercises to execute and to illustrate proper behavior.  
 * For Exercise F, the call to SwitchContext (p) MUST be removed.  
 */
 
int MySwitchContext (p)
	int p;				// process to switch to
{
        /* your code here */
        /*
        int currPID = GetCurProc( );
        CONTEXT ctxt = processes[ currPID - 1 ];
        //CONTEXT *c = &ctxt;
        CONTEXT newCtxt = processes[ p - 1 ];
        //CONTEXT *newC = &newCtxt;
        //last = GetCurProc( );
        */
        //if (p < 0 || p > MAXPROCS) return -1; 
        static int last = 1;
        int magic = 0;
        SaveContext(processes + GetCurProc() - 1);
        if (magic == 1) return last;    
        else magic = 1;
        //Printf( "Restoring to %d from %d\n", p, GetCurProc());
        last = GetCurProc();
        RestoreContext(processes + p - 1);
        
        //return (SwitchContext (p));	// remove call to SwitchContext (p)
}
