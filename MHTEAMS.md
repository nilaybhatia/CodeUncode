*MegaHard Teams* is a famous software in Chefland for conducting online meetings and lectures. As a Software Engineer on the team, you are tasked with implementing 2 new *independent* features.

#### **1st feature (for the first 2 subtasks):**
In its current implementation, when the internet connection of the professor temporarily disappears, the data packets can't reach even one of the students who are attending the lectures in real time. Instead, the data packets generated from the professor's side are temporarily buffered in their computer and as soon as the connection is restored, they are sent out immediately. That is why you can sometimes hear your prof. speak too fast after an unstable internet connection, while in reality they are the buffered packets arriving late.

You are given an array $A$ containing elements $A_{1}, A_{2}, A_{3} \cdots A_{N}$ denoting the size of the data packets that are generated at the prof's computer every unit of time (say, a microsecond).
You are also given $Q$ **disjoint** intervals. Each interval is of the form $[l, r]$, and the prof. has no internet connection from $l$ to $r$ units of time, both inclusive. The total size of packets generated in this
interval must be sent as soon as the connection is restored.

The network has a capacity $K$. So, in one unit of time, the total size of packets leaving the prof's router cannot exceed $K$. You may assume that you can split the packets; i.e. if the buffered packet sizes are $[2, 3, 5]$, their 
total sum is $10$ and you can send them as $[1, 1, 8]$ as soon as the connection is restored. Note that when the connection is restored, you'll have to also send the generated packets, in addition to these late buffered packets.

A lecture is said to go on **_smoothly_**, if either:
1. The prof. never loses their connection. OR
2. For each time the prof. loses their connection, the buffered packets are transferred before they lose their connection again (or before the lecture ends in the case when they lose the connection for the last time).  

You have to report whether the lecture went on **_smoothly_**.

#### **2nd feature (for the last subtask):**

In this task, we'll be looking at MegaHard's central server design. Also, all meeting attendees are considered equivalent and there is no "one important speaker". Any of the people in the meeting can lose their connection at any time. So, unlike the previous task, the intervals can be **overlapping** in this one. The data packets are broadcasted to everyone, so if let's say if one person loses their connection in $[2, 6]$ and the other in $[4, 9]$, the sizes of packets in range $[4, 6]$ will have to be considered twice. In general, a packet size will be considered for buffering as many times as the number of intervals it occurs in.

You are given an array $A$ of the packets generated overall, across all attendees. You are also given $Q$ overlapping intervals each of the form $[l, r]$. From $[l, r]$ no broadcasting can take place and the central server is 
as good as dead. As before, the packets can be split. In this problem, the capacity $K$ is independent, meaning that sending buffered packets of one interval does not reduce the unuitilised capacity. See the samples to understand better.

A meeting is said to go on _**smoothly**_ if:
1. Not a single person loses their connection throughout the meeting. OR
2. When the server can't broadcast, it must send all buffered packets (considering frequency count) before it can't broadcast again (or before the meeting ends in case it's the last time).

You have to report whether the meeting went on **_smoothly_**.

### Input:

- The first line will contain $T$, the number of testcases. The description of $T$ testcases follows.
- The first line of each test case contains 3 integers, $N$, $K$ and $feature$. 
- The second line contains $N$ space-separated integers denoting the packet size at each instant of time.
- The third line of each test case contains the integer $Q$, denoting the number of times the internet connection is lost (by the prof. in 1st feature and by anyone in the 2nd)
- Each of the next $Q$ lines contains $2$ integers $l$ and $r$, denoting an internet loss from time $l$ to $r$, both inclusive. These pairs might not necessarily be in increasing order.

### Output:
For each testcase, output "YES" if the lecture or meeting was conducted **_smoothly_**, and "NO" otherwise.

### Constraints 
- $1 \leq T \leq 10$
- $1 \leq N \leq 10^6$
- $1 \leq K \leq 10^9$
- $1 \leq feature \leq 2$
- $1 \leq A_{i} \leq K$
- $1 \leq Q \leq N$
- $1 \leq l \leq r \leq N$


### Subtasks

#### **Subtask 1 (20 points):**
- $feature == 1$
- $N \leq 10^3$
- $K \leq 10^5$

#### **Subtask 2 (30 points):**
- $feature == 1$
- $N \leq 10^6$
- $K \leq 10^9$

#### **Subtask 3 (50 points):**
- $feature == 2$
- $N \leq 10^6$
- $K \leq 10^9$

### Example Input:
    3
    10 10 1
    1 4 2 5 3 7 8 2 1 3
    2
    8 9
    3 5
    10 10 1
    1 4 1 1 3 7 8 2 1 3
    2
    8 9
    3 5
    11 10 2
    1 4 2 5 3 7 8 2 1 3 1
    3
    2 4
    3 5
    9 10


### Example Output:
	NO
    YES
    YES

	
### Explanation:
**Example case 1:** The total buffered size from $[3, 5]$ is $2 + 5 + 3 = 10$.
The unutilised bandwidth of index 6 is 3 and that of index 7 is 2. We can send only $3+2=5$ total size of data packets, then after that the connection is lost again.

**Example case 2:** The total buffered size from $[3, 5]$ is $1 + 1 + 3 = 5$.
We can send this total size of $5$ before the connection is lost again.

**Example case 3:** The unitilised capacities for all indices are $[9, 6, 8, 5, 7, 3, 2, 8, 9, 7, 9]$. The total size of data packets in $[2, 4]$ is $11$ and can be sent starting from index $6$ as $[3, 2, 6]$. The total size of data packets in $[3, 5]$ is $10$ and can be sent starting from index $6$ as $[3, 2, 5]$. Note that since capacities are independent in the 2nd feature, sending packets of the 1st interval did not reduce the unutilised capacity and we could send packets of the 2nd interval using the same indices too. The last interval's packets can be easily sent as well.
