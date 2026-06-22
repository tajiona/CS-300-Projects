# Project One

## Runtime Analysis of Data Structures

In Project One, I analyzed three data structures: a vector, a hash table, and a binary search tree (BST). Each structure was evaluated based on its efficiency when loading course data, searching for a course, and printing a sorted course list.

### Runtime Comparison

| Data Structure     | Load Data  | Search       | Print Sorted List |
| ------------------ | ---------- | ------------ | ----------------- |
| Vector             | O(n)       | O(n)         | O(n log n)        |
| Hash Table         | O(n)       | O(1) average | O(n log n)        |
| Binary Search Tree | O(n log n) | O(log n)     | O(n)              |

### Recommendation

I recommended the Binary Search Tree because it maintains data in sorted order and allows an in-order traversal to print courses alphabetically without requiring an additional sorting step. This provides an effective balance between search performance and the ability to generate sorted output.
