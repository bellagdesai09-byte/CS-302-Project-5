# Design Decisions

## Internal Structure
To implement separate chaining, I built the hash table using a `std::vector` of `std::list<HashTableEntry<K, V>>`. I approached this design much like setting up a rack of test tubes. The `std::vector` acts as the rack itself: it allocates a fixed, contiguous block of memory that allows for instant $O(1)$ random access to any specific bucket. However, because an array cannot dynamically expand at a single index if multiple items land there, I placed a `std::list` inside each vector slot. The linked list handles the collisions gracefully, dynamically adding new nodes as needed without disturbing the rest of the table or requiring a full table resize.

## Prime Table Size
I used 19,997 for the table size because it is a prime number. When using modulo arithmetic (`% tableSize`) to map hash values to table indices, prime numbers are essential for preventing clustering. If the table size was an even number or shared common factors with the data (like standard ASCII sequences), the math would force many different keys into the exact same buckets. A prime number acts as a mathematical safeguard to ensure the data is distributed as uniformly as possible across the entire array.

## Finding a Real Collision
A real collision in my `modHash` table occurred with the words **"stop"** and **"pots"** (both of which appear in the text). Both words contain the exact same letters. Because `modHash` simply adds up the ASCII values (115 + 116 + 111 + 112 = 454), both words sum to 454. Addition is commutative, so `modHash` ignores the order of the letters and collapses them into the exact same bucket. 

When I checked the `hornerHash` table, it placed them in entirely different buckets. Because Horner's method multiplies the running total by 31 at each step, the positional order of the characters fundamentally changes the math, giving anagrams completely distinct mathematical signatures.

## Hash Function Comparison
The diagnostic data from processing all 156,943 words clearly shows why the hashing formula is the most critical part of the ADT. Both tables had the exact same load factor of 0.3758, meaning they held the exact same 7,515 unique words, but the distribution of those words was vastly different. 

* `modHash` completely ignores the position of characters, leading to heavy clustering. It produced an average chain length of **5.95** and a massive longest chain of **33**. 
* `hornerHash` accounts for character position using polynomial evaluation (base 31), which produced a highly even distribution. The average chain dropped down to **1.20**, and the longest chain was only **5**. 

Because of this, `hornerHash` produced a significantly more even distribution. We can see the real-world impact in the worst-case buckets: under `modHash`, lookup performance degrades heavily because the program has to sequentially search through a linked list of 33 items. By keeping the absolute longest chain at 5, `hornerHash` ensures that lookup performance remains incredibly fast and close to the $O(1)$ ideal.

## Interesting Observations
One of the most interesting things I noticed was the sheer dominance of specific words in the English language. Out of the 156,943 total words processed, the word "the" appeared 12,966 times, making up a massive percentage of the text. It was also satisfying to see the alphabetical tie-breaker lambda working perfectly in the bottom 20 list; seeing all the frequency-1 words perfectly sorted from "aa" to "accountant" proved that the sorting logic in the driver was executing exactly as planned.