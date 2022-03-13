# pwguesstimator

## Summary

Calculates roughly how long an optimized password cracking tool would take to crack a provided password.
Then, attempts to crack the password using a very naive brute-force algorithm and provides timing results
if successful.

## Password Strength Methodology

To compute roughly how long it would take an optimized tool to crack a password, the following equation is used.

```text
total_possibilites = 0
for i in [min_length, password_length]
  total_possibilities += character_pool_size ^ i
endfor

// Rough estimate based on numbers from Hashcat (https://hashcat.net/).
// A Hashcat official twitter post claims a cracking speed of 100GH/s
// for NTLM-hashed passwords using hashcat 6.0.0 on a single NVIDIA
// 2080Ti GPU. (https://twitter.com/hashcat/status/1095807014079512579)
//
// Note that the brute_force function included in this library will be
// significantly slower than hashcat. This number is used for guesstimating
// how quickly a password could be brute-forced in the real world.
guesses_per_second = 100,000,000,000

duration_s = total_possibilities / guesses_per_second
```

## Password Cracking Methodology

To attempt to crack a given password, a naive brute-force approach is used.
The program simply iterates through every possible permutation of legal
characters until the answer is found.

## Disclaimers

This tool should not be used for evil, not that it would be very good at it anyway.

Absolutely **no** guarantees are made that the estimates provided by this tool are accurate.
This tool provides an extremely rough upper bound on how long it would take to crack a password.
There are many factors to consider when estimating the strength of a password, and this tool only
considers a very small subset of them. See the [Resources](#resources) section to get started on
learning more about password security.

## Resources

- [Security.org](https://www.security.org/how-secure-is-my-password/)
- [Hashcat.net](https://hashcat.net/hashcat/)
  - [Wiki](https://hashcat.net/wiki/)
  - [Source Code](https://github.com/hashcat)
