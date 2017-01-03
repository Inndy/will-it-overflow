# Will it overflow?

To overflow or not to overflow, that is the question.

This project demos how C input functions destoried your buffer!

## Sample Output

```
Round 0: scanf %s
Pwned: 41
Round 1: scanf %16s
Pwned: 00
Round 2: fgets
Safe
Round 3: fread
Safe
But vulerable to information leakage (Not ensure that NULL terminated)
Round 4: strcpy
Pwned: 41
Round 5: strncpy
Safe
But vulerable to information leakage (Not ensure that NULL terminated)
Round 6: read
Safe
But vulerable to information leakage (Not ensure that NULL terminated)
```
