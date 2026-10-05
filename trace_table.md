# Trace Tables: Music Application Hashing & Search Analysis

This document provides step-by-step trace tables detailing the execution of the hash table insertion, collision resolution using linear probing, hashing search, and linear search. All values precisely correspond to the actual execution of [hashing_music.c](file:///c:/Users/HP/OneDrive/Desktop/dsamusicproject/hashing_music.c).

---

## 1. Hash Table Insertion Trace

* **Hash Function:** $h(\text{key}) = \text{key} \pmod{10}$
* **Collision Resolution Policy:** Linear Probing: $\text{index} = (h(\text{key}) + i) \pmod{10}$ for $i = 0, 1, 2, \dots$
* **Initial State:** All 10 slots initialized to `EMPTY` (represented as `-`).

| Step | Song ID | Hash Value ($h = \text{key} \% 10$) | Collision? | Positions Checked | Final Position | Hash Table State (Indices 0 to 9) |
| :---: | :---: | :---: | :---: | :---: | :---: | :--- |
| **0** | *Initial* | - | - | - | - | `[ - , - , - , - , - , - , - , - , - , - ]` |
| **1** | **105** | $105 \pmod{10} = 5$ | No | `[5]` | **5** | `[ - , - , - , - , - , 105, - , - , - , - ]` |
| **2** | **210** | $210 \pmod{10} = 0$ | No | `[0]` | **0** | `[ 210, - , - , - , - , 105, - , - , - , - ]` |
| **3** | **315** | $315 \pmod{10} = 5$ | Yes (Index 5) | `[5, 6]` | **6** | `[ 210, - , - , - , - , 105, 315, - , - , - ]` |
| **4** | **420** | $420 \pmod{10} = 0$ | Yes (Index 0) | `[0, 1]` | **1** | `[ 210, 420, - , - , - , 105, 315, - , - , - ]` |
| **5** | **525** | $525 \pmod{10} = 5$ | Yes (Index 5) | `[5, 6, 7]` | **7** | `[ 210, 420, - , - , - , 105, 315, 525, - , - ]` |
| **6** | **630** | $630 \pmod{10} = 0$ | Yes (Index 0) | `[0, 1, 2]` | **2** | `[ 210, 420, 630, - , - , 105, 315, 525, - , - ]` |
| **7** | **735** | $735 \pmod{10} = 5$ | Yes (Index 5) | `[5, 6, 7, 8]` | **8** | `[ 210, 420, 630, - , - , 105, 315, 525, 735, - ]` |
| **8** | **840** | $840 \pmod{10} = 0$ | Yes (Index 0) | `[0, 1, 2, 3]` | **3** | `[ 210, 420, 630, 840, - , 105, 315, 525, 735, - ]` |

### Detailed Step-by-Step Breakdown

1. **Insert 105:**
   * $h(105) = 105 \pmod{10} = 5$.
   * Slot 5 is empty (`-`).
   * Insert `105` at index 5. (0 collisions, 1 check).
2. **Insert 210:**
   * $h(210) = 210 \pmod{10} = 0$.
   * Slot 0 is empty (`-`).
   * Insert `210` at index 0. (0 collisions, 1 check).
3. **Insert 315:**
   * $h(315) = 315 \pmod{10} = 5$.
   * Slot 5 is occupied by `105` $\rightarrow$ **Collision!**
   * Probe next slot: $(5 + 1) \pmod{10} = 6$.
   * Slot 6 is empty. Insert `315` at index 6. (1 collision, 2 checks).
4. **Insert 420:**
   * $h(420) = 420 \pmod{10} = 0$.
   * Slot 0 is occupied by `210` $\rightarrow$ **Collision!**
   * Probe next slot: $(0 + 1) \pmod{10} = 1$.
   * Slot 1 is empty. Insert `420` at index 1. (1 collision, 2 checks).
5. **Insert 525:**
   * $h(525) = 525 \pmod{10} = 5$.
   * Slot 5 is occupied (`105`), Slot 6 is occupied (`315`) $\rightarrow$ **Collision!**
   * Probe next slot: $(6 + 1) \pmod{10} = 7$.
   * Slot 7 is empty. Insert `525` at index 7. (2 probe steps, 3 checks).
6. **Insert 630:**
   * $h(630) = 630 \pmod{10} = 0$.
   * Slot 0 is occupied (`210`), Slot 1 is occupied (`420`) $\rightarrow$ **Collision!**
   * Probe next slot: $(1 + 1) \pmod{10} = 2$.
   * Slot 2 is empty. Insert `630` at index 2. (2 probe steps, 3 checks).
7. **Insert 735:**
   * $h(735) = 735 \pmod{10} = 5$.
   * Slot 5 (`105`), Slot 6 (`315`), and Slot 7 (`525`) are occupied $\rightarrow$ **Collision!**
   * Probe next slot: $(7 + 1) \pmod{10} = 8$.
   * Slot 8 is empty. Insert `735` at index 8. (3 probe steps, 4 checks).
8. **Insert 840:**
   * $h(840) = 840 \pmod{10} = 0$.
   * Slot 0 (`210`), Slot 1 (`420`), and Slot 2 (`630`) are occupied $\rightarrow$ **Collision!**
   * Probe next slot: $(2 + 1) \pmod{10} = 3$.
   * Slot 3 is empty. Insert `840` at index 3. (3 probe steps, 4 checks).

---

## 2. Hash Search Trace

For hash search, an item is hashed to its initial slot. If not found, sequential probing checks contiguous slots until either the key is found (Success) or an `EMPTY` slot is reached (Failure, proving the key was never inserted into this probe cluster).

| Search ID | Initial Hash Index ($h = \text{key} \% 10$) | Positions Checked (Probe Sequence) | Comparisons / Probes | Search Result |
| :---: | :---: | :--- | :---: | :--- |
| **105** | $5$ | `[5]` (Found `105`) | **1** | **Found at Index 5** (Successful) |
| **420** | $0$ | `[0]` (contains 210) $\rightarrow$ `[1]` (Found `420`) | **2** | **Found at Index 1** (Successful) |
| **840** | $0$ | `[0]` (210) $\rightarrow$ `[1]` (420) $\rightarrow$ `[2]` (630) $\rightarrow$ `[3]` (Found `840`) | **4** | **Found at Index 3** (Successful) |
| **500** | $0$ | `[0]` (210) $\rightarrow$ `[1]` (420) $\rightarrow$ `[2]` (630) $\rightarrow$ `[3]` (840) $\rightarrow$ `[4]` (`EMPTY`) | **5** | **Not Found** (Terminated at empty slot 4) |

* **Total Hashing Comparisons:** $1 + 2 + 4 + 5 = 12$
* **Average Hashing Comparisons:** $\frac{12}{4} = 3.00$

---

## 3. Linear Search Trace

Linear search scans the sequential array of inserted song IDs:
`arr = [105, 210, 315, 420, 525, 630, 735, 840]` ($N = 8$).

| Search ID | Elements Checked (Sequential Index Order) | Comparisons | Search Result |
| :---: | :--- | :---: | :--- |
| **105** | `[105]` (at index 0) | **1** | **Found at Index 0** (Successful) |
| **420** | `[105, 210, 315, 420]` (indices 0 to 3) | **4** | **Found at Index 3** (Successful) |
| **840** | `[105, 210, 315, 420, 525, 630, 735, 840]` (indices 0 to 7) | **8** | **Found at Index 7** (Successful) |
| **500** | `[105, 210, 315, 420, 525, 630, 735, 840]` (all 8 items) | **8** | **Not Found** (Reached end of array) |

* **Total Linear Search Comparisons:** $1 + 4 + 8 + 8 = 21$
* **Average Linear Search Comparisons:** $\frac{21}{4} = 5.25$

---

## 4. Key Takeaways from the Trace

1. **Clustering Pattern:** Because all 8 IDs are multiples of $105$, they strictly end in either digit `5` or `0`. This forces all keys into two primary clusters:
   * Cluster A (Originating at index 5): Slots 5, 6, 7, 8.
   * Cluster B (Originating at index 0): Slots 0, 1, 2, 3.
2. **Early Termination in Hashing Search:** When searching for `500` ($h = 0$), hashing search only inspected slots 0, 1, 2, 3, and 4 (5 checks). As soon as slot 4 was found to be `EMPTY`, it terminated immediately without checking the remaining slots (5, 6, 7, 8, 9). Conversely, linear search had to inspect all 8 elements.
