Author: Kyle Chan
Email: kchan21@csu.fullerton.edu

I did not implement the extra credit.

Execution time of serial.cpp:
real    0m2.112s
user    0m0.072s
sys     0m0.030s

Execution time of parallel.cpp:
real    0m0.466s
user    0m0.070s
sys     0m0.109s

1. In the output of time, what is the difference between real, user, and sys times?
Real time refers to the real time that has passed. This includes other possible processes that also may be running at the game time. User time refers to the CPU time that was used while executing the process. Sys time refers to the amount of CPU time spent in the kernel within the process.
2. Which is longer: user time or sys time? Use your knowledge to explain why.
User time will be greater than sys time since user time refers to the time the CPU spends outside the kernel.
3. When fetching all of the locations in the file, which fetcher finishes faster? Why do you think that is?
parallel.cpp finishes faster since instead of waiting for each child to terminate, this program creates multiple children to do the same task at the same time.
4. Suppose one of the fetcher children crashes. Will this affect other children? Explain. What is your conclusion regarding the benefits or disadvantages of isolating each fetch task within a different process?
If a fetcher child crashes, it will not affect the other children. This is because the child is independent from the other children. Creating children is beneficial since it can prevent the whole program from crashing.