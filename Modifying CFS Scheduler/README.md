# Modifying CFS Scheduler with 
The Linux CFS scheduler is a non-realtime scheduler, with non-realtime guarantees being given to processes. 

My modification is as follows
I add a soft real-time requirement to a process - say something like each process, that requires soft real-time guarantees must receive atleast x units of time-slice. Every time the scheduler is called, I check if the real-time guarantees of process with soft-realtime requirements are being met or not. I would give higher priority to a processes soft-realtime requirement compared to the vruntime that is normally considered.

So I modified the scheduler in such a way that everytime a process is selected through the RB-tree, I compare to all other process with soft-realtime requirements and see which one of those require the CPU more urgently than the one selected through the regular RB-tree. The one that urgently requires CPU time needs to be scheduled before the one selected through CFS. 

I additionally created a system call called rtnice to modify the tasks soft-realtime requirements, which takes PID and the realtime guarantees needed as argument. 

To test the correct functionality of the modified scheduler, I ran tasks requiring realtime guarantees and set the guarantees through test.c I then show the execution time of the process with and without the soft realtime guarantees to demonstrate if the modified scheduler is functioning or not.

Note: Linux/kernel v5.9 distribution was used for this assignment