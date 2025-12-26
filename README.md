# Algorithms

This repository is dedicated to exploring Computer Science fundamentals, mastering algorithms, and implementing data structures from scratch.

## Implemented Topics:
### Trees (Self-balancing & Search)
* **Binary Search Tree (BST)**
* **AVL Tree** (Height-balanced)
* **Red-Black Tree** (Node-colored balancing)
### Sorting Algorithms
* **Bubble Sort** (O(n²) complexity)
### Algorithms timer
"I’ve added algorithms_timer.h to the repository for measuring the asymptotic complexity of algorithms and data structures. This helps to visualize how execution time scales with the volume of data.
Below are the performance measurements for algorithms and data structures obtained using this timer:"
{content: }
### Red-Black Tree: Handling the "NIL Brother" Edge Case during Removal
In my implementation, there is no explicit check for whether a "brother" node is NIL-leaf. This design choice was made because, in a valid Red-Black Tree, it is impossible for a node being balanced to have no brother (i.e., its brother cannot be a NIL-leaf).

If a brother (an internal node with a value) were missing, it would violate the fundamental property: every path from a node to any of its descendant NIL leaves must contain the same number of black nodes.

As shown in the images below, the "missing brother" scenario (where only a NIL-node exists) results in an invalid black height, regardless of the parent's color:
![nil_brother_redparent.png](images/nil_brother_redparent.png)
![nil_brother_blackparent.png](images/nil_brother_blackparent.png)

This is a reason why my method "fixup_remove_iterative()" assumes that brother is always not-NIl leaf. If the brother node does not exist even as a NIL-leaf, it means that the double black node is the root.
## Extra:
* **Language:** C++ (C++20)
* **IDE:** Visual Studio 2022
