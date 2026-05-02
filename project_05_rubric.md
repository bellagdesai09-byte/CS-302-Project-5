# Project 5 Rubric: Word Frequency Analyzer
**Total: 100 points**

| Section                            |  Points |
|------------------------------------|--------:|
| 1. Project Structure and Build     |      10 |
| 2. Hash Functions                  |      20 |
| 3. `HashTable<K, V>`               |      35 |
| 4. Driver and Output               |      10 |
| 5. Memory Management               |       5 |
| 6. ADT Design Document             |       5 |
| 7. Coding Standards                |       5 |
| 8. Design Decisions and Submission |      10 |
| **Total**                          | **100** |

---

## 1. Project Structure and Build (10 points)

**Makefile (4 pts)**
- Builds successfully using `make`
- Uses required flags (`-std=c++17 -Wall -Wextra -pedantic`)
- `make clean` removes all generated files
- `make run` builds and runs the program

**Directory Structure (3 pts)**
- All `.h` files in `include/`
- All `.cpp` files in `src/`
- All compiled `.o` files and executable output to `build/`

**File Organization (3 pts)**
- `HashTable.h` contains the complete template (declaration and definition)
- `hashFunctions.h` contains both hash function templates
- Provided files included unmodified

---

## 2. Hash Functions (20 points)

**Section 0 Verification (10 pts)**
- All six modHash values correct and printed with PASS **(5 pts)**
- All six hornerHash values correct and printed with PASS **(5 pts)**

**Implementation Correctness (10 pts)**
- `modHash`: correctly sums ASCII values and applies mod **(4 pts)**
- `hornerHash`: correctly applies Horner's method with base 31 and per-step mod **(6 pts)**

Partial credit awarded per function. A hash function that produces correct Section 0 values but incorrect values on other inputs earns partial credit.

---

## 3. `HashTable<K, V>` (35 points)

**Template and Structure (5 pts)**
- `HashTable<K, V>` is a proper class template, no hardcoded types **(2 pts)**
- Inherits from `HashTableInterface<K, V>` with correct syntax **(1 pt)**
- Constructor takes table size parameter **(1 pt)**
- Internal structure uses appropriate standard library containers **(1 pt)**

**`insert()` (10 pts)**
- Correctly hashes key to determine bucket **(3 pts)**
- If key not present, adds entry with value 1 **(3 pts)**
- If key present, increments existing value by 1 **(4 pts)**

**`find()` (5 pts)**
- Correctly hashes key and searches the appropriate bucket **(3 pts)**
- Returns 0 for keys not in the table **(2 pts)**

**Diagnostic Methods (10 pts)**
- `getLoadFactor()`: total entries divided by table size **(2 pts)**
- `getLongestChain()`: correct maximum chain length **(3 pts)**
- `getShortestChain()`: correct minimum non-empty chain length **(2 pts)**
- `getAverageChainLength()`: correct average over non-empty chains **(3 pts)**

**`getAllEntries()` (5 pts)**
- Returns all key-value pairs correctly **(3 pts)**
- Driver can use this to produce top 20 and bottom 20 correctly **(2 pts)**

---

## 4. Driver and Output (10 points)

**Section 0 (3 pts)**
- All 12 hash function verification values printed with correct PASS labels

**Section A: Mod-Based Analysis (3.5 pts)**
- All table statistics printed correctly **(1.5 pts)**
- Top 20 words by frequency printed in descending order **(1 pt)**
- Bottom 20 words by frequency printed in ascending order **(1 pt)**

**Section B: Horner Hash Analysis (3.5 pts)**
- Same requirements as Section A **(3.5 pts)**

All output must be clearly labeled. Unlabeled output receives no credit.

---

## 5. Memory Management (5 points)

- No memory leaks detected when running with valgrind **(3 pts)**
- Destructor correctly cleans up all dynamically allocated memory, if any **(2 pts)**

Note: if you use only standard library containers with no raw pointers, this section is largely handled for you. A brief explanation in `Design_Decisions.md` of why this is the case earns full credit.

---

## 6. ADT Design Document (5 points)

`ADT_Design.md` must include:

- Clear statement of purpose, what the dictionary ADT solves **(1 pt)**
- Logical data model described abstractly, no mention of implementation details **(1 pt)**
- All interface operations documented with behavior and preconditions **(2 pts)**
- Explanation of what a hash function does at the ADT level **(1 pt)**

---

## 7. Coding Standards (5 points)

All CS 302 coding standards apply. See `coding_standards.md`.

**Naming Conventions (1 pt)**
- Classes use PascalCase, functions and variables use camelCase, constants use ALL_CAPS
- Names are self-documenting

**Indentation and Bracing (1 pt)**
- Consistent 3 or 4 space indentation throughout
- Braces used consistently: either Allman style or K&R style, not mixed

**Comments (1 pt)**
- Every class has a header comment
- Every public method has a header comment
- Inline comments explain why, not what

**`const` Correctness (1 pt)**
- All accessor methods marked `const`
- All non-mutating reference parameters marked `const`

**Header Guards (1 pt)**
- Every `.h` file has a proper `#ifndef` / `#define` / `#endif` guard
- Guard names recognizable from the filename

---

## 8. Design Decisions and Submission (10 points)

**`Design_Decisions.md` (8 pts)**

*Design choices (3.5 pts)*
- Internal container choice explained and justified **(1.5 pts)**
- Prime table size rationale explained using the anagram example **(1 pt)**
- Real collision found in own output and explained: identifies words that collide under `modHash`, explains why they collide, and checks whether `hornerHash` separates them **(1 pt)**

*Analysis (4.5 pts)*
- Diagnostic numbers from both Section A and Section B included **(1 pt)**
- Interpretation: explains *why* the distributions differ, not just *that* they differ. Connects longest chain and average chain length to lookup performance. Tells the story the numbers tell **(2.5 pts)**
- Interesting observations about word frequencies **(1 pt)**

**`README.md` (1 pt)**
- Project title, author, build instructions, sample output, known issues

**Submission (1 pt)**
- ZIP named correctly (`project_05_lastname.zip`)
- No compiled files, `build/` directory, or IDE artifacts
- `make clean` run before submission

---

# Grading Philosophy

This project emphasizes practical design and evidence-based analysis. The hash table mechanics are not the hardest thing you have built this semester. The intellectual work is in the comparison: two functions, the same data, different distributions. The diagnostic numbers are your evidence; `Design_Decisions.md` is where you interpret that evidence.

A student who implements both functions, produces correct output, finds a real collision, and writes a thoughtful analysis explaining *why* the numbers differ has done exactly what this project asks. Reporting numbers without interpretation earns partial credit. Telling the story the numbers tell earns full credit.

Section 0 is your safety net. If your hash functions pass all twelve verification checks, your table analysis will be correct. If they do not, fix them before moving on.

Code that does not follow the CS 302 Coding Standards will lose points regardless of whether the program compiles and runs correctly.
