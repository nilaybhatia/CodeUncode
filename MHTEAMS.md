*MegaHard Teams* is a famous software in Chefland for conducting online meetings and lectures. As a Software Engineer on the team, you are tasked with implementing 2 new *independent* features.

#### **1st feature (for the first 2 subtasks):**
In its current implementation, when the internet connection of the professor temporarily disappears, the data packets can't reach even one of the students who are attending the lectures in real time. Instead, the data packets generated from the professor's side are temporarily buffered in their computer and as soon as the connection is restored, they are sent out immediately. That is why you can sometimes hear your prof. speak too fast after an unstable internet connection, while in reality they are the buffered packets arriving late.

You are given an array $A$ containing the size of the data packets that are generated at the prof's computer every unit of time (say, a microsecond).
You are also given $Q$ **disjoint** intervals. Each interval is of the form $[l, r]$, and the prof. has no internet connection from $l$ to $r$ units of time, both inclusive. The total size of packets generated in this
interval must be sent as soon as the connection is restored.

The network has a capacity $K$. So, in one unit of time, the total size of packets leaving the prof's router cannot exceed $K$. You may assume that you can split the packets; i.e. if the buffered packets are $[2, 3, 5]$, their 
total sum is $10$ and you can send them as $[1, 1, 8]$ as soon as the connection is restored. Note that when the connection is restored, you'll have to also send the generated packets, in addition to these late buffered packets.

A lecture is said to go on **_smoothly_**, if either:
1. The prof. never loses their connection. OR
2. For each time the prof. loses their connection, the buffered packets are transferred before they lose their connection again (or before the lecture ends in the case when they lose the connection for the last time).  



#### **2nd feature (for the last subtask):**

In this task, we'll be looking at MegaHard's central server design. Also, all meeting attendees are considered equivalent and there is no "one important speaker". Any of the people in the meeting can lose their connection at any time. So, unlike the previous task, the intervals can be **overlapping** in this one. The data packets are broadcasted to everyone, so if let's say if one person loses their connection in $[2, 6]$ and the other in $[4, 9]$, the sizes of packets in range $[4, 6]$ will have to be considered twice. In general, a packet size will be considered for buffering as many times as the number of intervals it occurs in.

You are given an array $A$ of the packets generated overall, across all attendees. You are also given $Q$ overlapping intervals each of the form $[l, r]$. From $[l, r]$ no broadcasting can take place and the central server is 
as good as dead. As before, the network has capacity $K$, and the packets can be split.

A meeting is said to go on _**smoothly**_ if:
1. Not a single person loses their connection throughout the meeting. OR
2. When the server can't broadcast, it must send all buffered packets (considering frequency count) before it can't broadcast again (or before the meeting ends in case it's the last time).

### Input:

- The first line will contain $T$, the number of testcases. The description of $T$ testcases follows.
- The first line of each test case contains 3 integers, $N$, $K$ and $feature$. 
- The second line contains $N$ space-separated integers denoting the packet size at each instant of time.
- The third line of each test case contains the integer $Q$, denoting the number of times the internet connection is lost (by the prof. in 1st feature and by anyone in the 2nd)
- Each of the next $Q$ lines contains $2$ integers $l$ and $r$, denoting an internet loss from time $l$ to $r$, both inclusive.

### Output:
For each testcase, output "YES" if the lecture or meeting was conducted **_smoothly_**, and "NO" otherwise.

### Constraints 
- $1 \leq T \leq 10$
- $2 \leq M \leq 10^9$

### Subtasks
- 30 points : $1 \leq R \leq 10000$
- 70 points : $1 \leq R \leq 10^9$

$M$ is a prime number

### Sample Input:
	1
	2 2

### Sample Output:
	1
	
### EXPLANATION:
This list is :
$[1,8,27,64,125..] -> [7,19,37,61..] -> [12,18,24..] -> [6,6,6..]$. Number of times 2 divides 6 is 1. Hence the answer is 1.
