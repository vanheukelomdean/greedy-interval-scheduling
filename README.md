# greedy-interval-scheduling

A solution to hackerrank problem [`Attending Workshops`](https://www.hackerrank.com/challenges/attending-workshops/problem)

### Problem
  
  Maximize the numeber of workshops someone can attend given a list of workshop start times and durations.
  
### Algorithm Pseudocode

```
 - Build candidate and attending workshop sets.

 - While there still exists dandidate workshops:

     - Find the workshop element with the earliest conclusion.

     - Add the element to the attending set, remove from the candidate set.

     - Remove all elements from the canditate set which intersect the recently added attending workshop.
```
