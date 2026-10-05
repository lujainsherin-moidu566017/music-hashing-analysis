# Academic Conclusion: Suitability of Hashing for the Music Application

**Course / Project Title:** Music Application – Hashing and Search Performance Analysis  
**Topic:** Hash Table Implementation using Division Method with Linear Probing vs Linear Search

---

## 1. Main Conclusion

> **Hashing is a suitable and more efficient approach for the given music application. In the experiment, hashing required 12 total comparisons compared with 21 for linear search, giving better observed search performance. Hashing provides $O(1)$ average-case search performance, while worst-case performance can be $O(N)$ due to collisions. The experiment also showed that the load factor of 0.80 and clustering increased the number of probes. Therefore, for this dataset and the tested searches, hashing is the more suitable approach, provided that an appropriate table size and collision-resolution strategy are used.**

---

## 2. Evidence from Experimental Results

### A. Search Comparison Summary
During the experimental execution of the C program on the 4 test cases (`105`, `420`, `840`, and `500`):
* **Hashing Search:** Required a total of **12 comparisons / probes** across all 4 searches, with an **average of 3.00 comparisons**.
* **Linear Search:** Required a total of **21 comparisons**, with an **average of 5.25 comparisons**.
* **Observed Reduction:** Hashing achieved a **42.86% reduction** in search comparisons relative to linear search on this dataset.
* In individual searches:
  * For `105`: Both methods required 1 comparison (tie).
  * For `420`: Hashing required 2 comparisons vs. 4 for linear search.
  * For `840`: Hashing required 4 comparisons vs. 8 for linear search.
  * For `500` (unsuccessful search): Hashing terminated after 5 comparisons (reaching an empty slot), whereas linear search checked all 8 elements.

### B. Impact of Collisions and Load Factor
* With 8 song IDs and a table size of $M = 10$, the load factor was:
  $$\alpha = \frac{8}{10} = 0.80 \quad (80\%)$$
* Because all 8 song IDs are multiples of 105, their modulo 10 values mapped strictly to indices 0 and 5, resulting in **6 collisions during the 8 insertions**.
* This created two primary clusters (slots 0–3 and slots 5–8), which elevated the probe counts for later insertions and searches.
* Despite this clustering and the relatively high load factor of 0.80, hashing still required fewer comparisons overall than sequentially scanning the array.

---

## 3. Complexity Summary

| Metric | Linear Search | Hash Table (Linear Probing) |
| :--- | :---: | :---: |
| **Best-Case Search** | $O(1)$ | $O(1)$ |
| **Average-Case Search** | $O(N)$ | $O(1)$ |
| **Worst-Case Search** | $O(N)$ | $O(N)$ |
| **Space Complexity** | $O(1)$ auxiliary | $O(M)$ table space |
| **Experimental Average (4 searches)** | 5.25 comparisons | 3.00 comparisons |

---

## 4. Final Recommendation

For this dataset and the tested searches, **hashing is the more suitable approach** due to its lower comparison count and $O(1)$ average-case potential. To maintain efficient search performance as a dataset grows, care should be taken to select an appropriate table size (preferably prime) and keep the load factor within moderate bounds to limit collision clustering.
