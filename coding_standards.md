# CS 302 - C++ Coding Standards

These standards apply to **every project** in this course. Code quality is graded in every assignment. Standards are not optional extras; they are part of what it means to write correct, professional code.

---

## Why Standards Matter

- **Readability**: Code is read far more than it is written. Standards make it easy for any reader to understand unfamiliar code.
- **Fewer Bugs**: Consistent naming, initialization rules, and `const` usage eliminate entire categories of C++ undefined behavior.
- **Collaboration**: Standards remove style debates so code reviews focus on logic and correctness.
- **Career Readiness**: Every professional engineering team enforces coding standards. Apple, Google, Meta, and Microsoft all do.

---

## Standard 1: Naming Conventions

| Element | Convention | Example |
|---|---|---|
| Classes and types | `PascalCase` | `Train`, `MusicLibrary` |
| Functions and methods | `camelCase` | `getWeight()`, `insertSong()` |
| Variables | `camelCase` | `totalWeight`, `count` |
| Constants | `ALL_CAPS` | `MAX_CAPACITY`, `DEFAULT_FARE` |

Names must be **self-documenting**. A reader should understand what something does without reading its implementation.

```cpp
// Not Good:
class train_data {
    int N;
    void LOAD(int x);
};
const int max = 100;

// GOOD:
class Train {
    int count;
    void load(int item);
};
const int MAX_CAPACITY = 100;
```

---

## Standard 2: Indentation and Bracing

- Indent with **3 or 4 spaces**; be consistent throughout the file
- **Never mix tabs and spaces**
- **Always use braces `{}`** even for single-line control structures
- Choose one brace style (Allman or K&R) and use it consistently throughout the project. Do not mix styles. See the Project 5 update below.

```cpp
// Not Good:
if (count > 0)
    unload();
else unload(); unload();

// GOOD (Allman):
if (count > 0)
{
    unload();
}
else
{
    unload();
}
```

---

## Standard 3: Meaningful Comments

- Every **class** gets a header comment explaining its purpose
- Every **public method** gets a header comment explaining what it does, its parameters, and what it returns
- Inline comments explain **why**, not **what**; the code already says what

```cpp
// Not Good:
// Set i to 0
int i = 0;
// Loop
while (i < count) { arr[i] = 0; i++; }

// GOOD:
// Reset all cargo slots before loading new items
// to prevent stale data from a previous trip.
int i = 0;
while (i < count)
{
    arr[i] = 0;
    i++;
}
```

---

## Standard 4: `const` Correctness

- **Accessor methods** (getters) that do not modify the object must be marked `const`
- **Reference parameters** that are not modified must be `const`
- Applying `const` correctly prevents bugs and clearly signals intent to the caller

```cpp
// Not Good:
class Cargo {
    string getType();           // Looks like it might modify the object
    void print(Cargo& c);       // Looks like it might modify c
};

// GOOD:
class Cargo {
    string getType() const;         // Clearly read-only
    void print(const Cargo& c);     // Clearly c is not modified
};
```

---

## Standard 5: Header Guards

Every `.h` file **must** include a header guard to prevent multiple inclusion.

```cpp
// Not Good: breaks when included more than once
template <class T>
class Train {
    // ...
};

// GOOD: safe against multiple inclusion
#ifndef TRAIN_H
#define TRAIN_H

template <class T>
class Train {
    // ...
};

#endif
```

The guard name should be recognizable from the filename. Common conventions include the filename in `ALL_CAPS` with `_H` appended, or a readable variant that clearly maps back to the file:
- `Train.h` becomes `TRAIN_H`
- `MusicLibrary.h` becomes `MUSICLIBRARY_H` or `MUSIC_LIBRARY_H`

---

## Summary

| # | Standard | One-Line Rule |
|---|---|---|
| 1 | Naming | Classes `PascalCase`, functions/variables `camelCase`, constants `ALL_CAPS` |
| 2 | Bracing | Always `{}`, consistent indentation, one brace style throughout |
| 3 | Comments | Header comments on classes and methods; explain *why* not *what* |
| 4 | `const` | Accessors and non-mutating parameters marked `const` |
| 5 | Header Guards | Every `.h` file uses `#ifndef` / `#define` / `#endif` |

Code that does not follow these standards **will lose points** in every project, regardless of whether the program compiles and runs correctly.

---

## Update for Project 5: Brace Style

Both Allman style and K&R style are accepted. Choose one and use it
consistently throughout the entire project. Do not mix styles.

```cpp
// Allman style: opening brace on its own line
void foo()
{
    // body
}

// K&R style: opening brace on the same line
void foo() {
    // body
}
```
