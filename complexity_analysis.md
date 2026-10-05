# Complexity Analysis: Hashing vs Linear Search

This document provides a detailed theoretical and practical time and space complexity analysis of the Hash Table (Division Method with Linear Probing) and Linear Search algorithms implemented for the Music Application.

---

## 1. Load Factor Calculation

The **Load Factor** ($\alpha$ or $\lambda$) represents the ratio of the number of occupied slots to the total capacity of the hash table:

$$\alpha = \frac{n}{m}$$

Where:
* $n$ = Number of elements stored = $8$
* $m$ = Total number of slots in the hash table = $10$

$$\alpha = \frac{8}{10} = 0.80 \quad (80\% \text{ table occupancy})$$

### Academic Significance of $\alpha = 0.80$
* In open addressing with linear probing, performance begins to degrade sharply when $\alpha > 0.70 - 0.75$.
* At $\alpha = 0.80$, unoccupied slots become scarce (only 2 out of 10 slots remain free).
* Contiguous blocks of occupied slots ("clusters") quickly merge into longer clusters, increasing the average number of probes required for both insertion and search operations.

---

## 2. Hashing (Division Method with Linear Probing)

### A. Time Complexity of Insertion

1. **Best-Case Complexity: $O(1)$**
   * **Condition:** The initial hash index $h(\text{key}) = \text{key} \pmod m$ maps directly to an empty slot.
   * **Operations:** Exactly $1$ probe. No collisions occur.
   * **Observed Example in Experiment:**
     * Song ID `105`: $h(105) = 5$ (Slot 5 was empty $\rightarrow 1$ probe).
     * Song ID `210`: $h(210) = 0$ (Slot 0 was empty $\rightarrow 1$ probe).

2. **Average-Case Complexity: $O(1)$ or $O\left(\frac{1}{1 - \alpha}\right)$**
   * Under the Uniform Hashing Assumption (SUHA), when collisions are resolved via linear probing, Donald Knuth derived the expected number of probes for an insertion (unsuccessful search) as:
     $$E[\text{Probes}_{\text{insert}}] \approx \frac{1}{2} \left(1 + \frac{1}{(1 - \alpha)^2}\right)$$
   * For moderate load factors ($\alpha \le 0.5 - 0.7$), this evaluates to a small constant, maintaining an average runtime of **$O(1)$**.
   * In our experiment ($\alpha = 0.80$), average insertion probes were:
     $$\text{Average Insertion Checks} = \frac{1 + 1 + 2 + 2 + 3 + 3 + 4 + 4}{8} = \frac{20}{8} = 2.50 \text{ checks}$$

3. **Worst-Case Complexity: $O(n)$ or $O(m)$**
   * **Condition:** Severe clustering occurs where all keys hash to the same initial index or all preceding slots are full.
   * **Operations:** The algorithm must linearly traverse through all occupied slots before finding an empty slot. If the table is nearly full ($n \approx m$), this requires traversing $n$ elements, yielding **$O(n)$** runtime.

---

### B. Time Complexity of Search

1. **Best-Case Complexity: $O(1)$**
   * **Condition:** The requested song ID is stored at its primary hash address $h(\text{key})$.
   * **Operations:** A single array access and comparison ($1$ probe).
   * **Observed Example:**
     * Song ID `105`: Hashed to index 5 and found immediately in $1$ probe.

2. **Average-Case Complexity: $O(1)$**
   * Under uniform distribution assumptions, linear probing provides $O(1)$ average search time. In theoretical open addressing models, the expected number of probes grows as the load factor $\alpha$ increases.
   * **Observed Experimental Average:** 3.00 comparisons. This is consistent with the average-case constant-time behavior expected from hashing, although the exact number of probes depends on the key distribution and collision pattern.
   * In this experiment, the load factor of $\alpha = 0.80$ and the clustering of multiples of 105 increased the number of probes compared to an ideal uniform hash distribution.

3. **Worst-Case Complexity: $O(n)$**
   * **Condition:** When extensive collisions occur or elements form long contiguous clusters, or when an unsuccessful search must scan the cluster up to the first empty slot.
   * **Operations:** Probing through the cluster takes $O(n)$ steps.

---

### C. Space Complexity: $O(m)$
* The hash table allocates a fixed array of size $m$ ($m = 10$).
* Total space complexity is **$O(m)$**, where $m$ is the table size.
* Additional auxiliary memory is $O(1)$ (temporary loop indices and probe counters).

---

## 3. Linear Search

Linear search operates sequentially across an unindexed array of size $n = 8$.

1. **Best-Case Complexity: $O(1)$**
   * **Condition:** The target item is located at the very first position (index 0).
   * **Operations:** $1$ comparison.
   * **Observed Example:**
     * Song ID `105`: Located at index 0 $\rightarrow 1$ comparison.

2. **Average-Case Complexity: $O(n)$**
   * For successful searches uniformly distributed across the array:
     $$\text{Average Comparisons} = \frac{n + 1}{2} = \frac{8 + 1}{2} = 4.5 \text{ comparisons}$$
   * For a mix of successful and unsuccessful searches, average comparisons rise towards $n$.
   * **Observed Experimental Average:** **$5.25$ comparisons**.

3. **Worst-Case Complexity: $O(n)$**
   * **Condition:** The target item is at the very last index ($n-1$) or is not present in the array.
   * **Operations:** The algorithm must examine all $n$ items.
   * **Observed Example:**
     * Song ID `840` (at index 7) $\rightarrow 8$ comparisons.
     * Song ID `500` (not present) $\rightarrow 8$ comparisons.

4. **Space Complexity: $O(1)$ Auxiliary Space**
   * Operates directly on the sequential storage array with no additional memory overhead ($O(1)$ auxiliary memory).

---

## 4. Comprehensive Complexity Summary Table

| Algorithm | Operation | Best Case | Average Case | Worst Case | Space Complexity |
| :--- | :--- | :---: | :---: | :---: | :---: |
| **Hash Table (Linear Probing)** | **Search** | $O(1)$ | $O(1)$ | $O(n)$ | $O(m)$ (where $m$ is table size) |
| **Hash Table (Linear Probing)** | **Insert** | $O(1)$ | $O(1)$ | $O(n)$ | $O(m)$ (where $m$ is table size) |
| **Hash Table (Linear Probing)** | **Delete** | $O(1)$ | $O(1)$ | $O(n)$ | $O(m)$ (where $m$ is table size) |
| **Linear Search** | **Search** | $O(1)$ | $O(n)$ | $O(n)$ | $O(1)$ (auxiliary space) |

* **Actual Experimental Averages:**
  * **Hashing Search:** $3.00$ comparisons / probes
  * **Linear Search:** $5.25$ comparisons
* **Observed Load Factor Impact:** The load factor of $\alpha = 0.80$ ($8/10$) combined with clustering from multiples of 105 increased the number of probes needed during linear probing resolution and search.

---

## 5. Effect of Collisions on Linear Probing

Linear probing resolves collisions using the recurrence relation:

$$\text{index}_i = (h(\text{key}) + i) \pmod m, \quad i = 0, 1, 2, \dots$$

### 1. Primary Clustering Phenomenon
* When a collision occurs, the colliding key is placed in the next immediately adjacent free slot.
* This creates contiguous blocks of occupied cells known as **primary clusters**.
* Any new key that hashes to *any* slot within an existing cluster will systematically traverse the entire length of the cluster before finding an empty slot, thereby extending the cluster even further.
* **In our music application dataset:**
  * All 8 IDs are multiples of 105 ($105, 210, 315, 420, 525, 630, 735, 840$).
  * Under modulo 10, their units digit is either 5 or 0.
  * This concentrated 100% of the keys into only two starting points ($h=0$ and $h=5$).
  * Slots 0, 1, 2, 3 merged into one continuous block of 4 elements.
  * Slots 5, 6, 7, 8 merged into another continuous block of 4 elements.
  * This elevated probe counts from 1 up to 4 for later insertions (Song ID 735 and 840).

### 2. Impact on Search Performance
* **Successful Searches:** Must traverse the same probe path taken during insertion. Keys inserted late into a cluster (e.g., `840`) require more comparisons ($4$ probes).
* **Unsuccessful Searches:** Must probe sequentially through the entire cluster until reaching the first `EMPTY` slot. For `500` ($h=0$), it probed $0 \rightarrow 1 \rightarrow 2 \rightarrow 3$ and stopped at empty slot $4$ (5 probes total).

### 3. Mitigation Strategies for Production Systems
1. **Use Prime Table Sizes:** If $m = 11$ had been chosen instead of $10$:
   * $105 \pmod{11} = 6$, $210 \pmod{11} = 1$, $315 \pmod{11} = 7$, $420 \pmod{11} = 2$, $525 \pmod{11} = 8$, $630 \pmod{11} = 3$, $735 \pmod{11} = 9$, $840 \pmod{11} = 4$.
   * Result: **0 collisions!** Every single search would take exactly $1$ comparison ($O(1)$).
2. **Quadratic Probing or Double Hashing:** Eliminates primary clustering by varying the step size between probes.
3. **Dynamic Rehashing:** Automatically resize the table (e.g., double table capacity to next prime) whenever $\alpha > 0.70$.
