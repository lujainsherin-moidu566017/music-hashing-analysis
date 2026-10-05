# Performance Comparison: Hashing vs Linear Search

This document provides a comparative evaluation between **Hash Table Search (Division Method with Linear Probing)** and **Linear Search** based on the actual execution results of [hashing_music.c](file:///c:/Users/HP/OneDrive/Desktop/dsamusicproject/hashing_music.c).

---

## 1. Experimental Search Comparison Table

The table below reflects the exact operation counts recorded during the execution of the C program:

| Search ID | Query Nature | Initial Hash Index ($h = \text{key} \% 10$) | Hashing Comparisons (Probes) | Linear Search Comparisons | Faster Method | Operation Difference |
| :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| **105** | Successful (Present) | 5 | **1** | **1** | **Tie (Equal)** | 0 comparisons |
| **420** | Successful (Present) | 0 | **2** | **4** | **Hashing is Faster** | Hashing saved 2 checks (50% faster) |
| **840** | Successful (Present) | 0 | **4** | **8** | **Hashing is Faster** | Hashing saved 4 checks (50% faster) |
| **500** | Unsuccessful (Absent) | 0 | **5** | **8** | **Hashing is Faster** | Hashing saved 3 checks (37.5% faster) |
| **TOTAL** | - | - | **12** | **21** | **Hashing Won Overall** | **9 total comparisons saved** |
| **AVERAGE**| - | - | **3.00** | **5.25** | **Hashing Won Overall** | **42.86% overall speedup** |

---

## 2. In-Depth Comparative Dimensions

### A. Search Efficiency
* **Linear Search:** Examines elements strictly one by one in array index order ($0, 1, 2, \dots$). The search position depends entirely on where the song happened to be inserted into the playlist. For songs located near the end of the array (such as `840` at index 7), linear search must inspect every single preceding element ($8$ comparisons). For absent songs (`500`), it is forced to scan the entire collection ($8$ comparisons).
* **Hashing Search:** Uses the mathematical key to jump directly to the target bucket in $O(1)$ time. In our music application, `105` jumped straight to index 5 ($1$ comparison), and even after collision resolution, `420` required only $2$ checks and `840` required $4$ checks. Overall, hashing cut total search operations from $21$ down to $12$.

### B. Collision Effect
* **Linear Search:** Collisions do not exist in linear search because elements are simply appended sequentially.
* **Hashing:** Collisions cause degradation in probe count. In this specific dataset of multiples of 105, severe clustering formed two contiguous clusters (indices 0–3 and 5–8). Despite this deliberate worst-case clustering condition, hashing still outperformed linear search in 3 out of 4 test cases and tied in the 4th.

### C. Scalability
* **Linear Search ($O(N)$):** Comparison counts grow linearly with the number of stored elements. When searching towards the end of an array or for an absent element, all $N$ elements must be inspected.
* **Hashing ($O(1)$ Average):** Under appropriate load factors and collision handling, hashing offers average constant-time search performance, making it theoretically more scalable as the number of elements grows.

### D. Memory Usage
* **Linear Search:** Requires space only for the exact number of songs ($N$ elements). No empty slots are needed ($100\%$ space utilization).
* **Hash Table:** Requires extra capacity ($M = 10$ slots for $N = 8$ items), leaving slots 4 and 9 empty to prevent infinite probe loops and maintain reasonable load factors. There is a slight space-time tradeoff (trading extra memory for faster search performance).

### E. Algorithmic Complexity

| Metric | Linear Search | Hash Table (Linear Probing) |
| :--- | :---: | :---: |
| **Best Case Time** | $O(1)$ | $O(1)$ |
| **Average Case Time** | $O(N)$ | $O(1)$ |
| **Worst Case Time** | $O(N)$ | $O(N)$ |
| **Space Complexity** | $O(1)$ auxiliary | $O(M)$ table space |
| **Implementation Complexity** | Simple (Sequential scan) | Moderate (Hash function + collision probing + wrap-around) |

---

## 3. Suitability for the Music Application

For the given dataset, hashing required fewer comparisons than linear search (12 total vs. 21 total, averaging 3.00 vs. 5.25 comparisons). Therefore, hashing performed better in this experiment and is the more suitable approach for the given application.

This evaluation is based on the tested dataset and should not be taken as a universal benchmark across all possible workloads, but it demonstrates the operational advantage of hash-based lookups over linear scanning in this music application scenario.
