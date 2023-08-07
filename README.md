## matrixpath

### How to use
```
<path/to>/matrixpath    <path/to/tab-delimited/child-parent/file>    [<path/to/out/folder>]
```
If an *out folder* is not provided it defaults to the *input folder* of the *tab-delimited file*.  

#### Tab delimited file
TSV file (tab separated) containing 2 columns, describing *child node/parent node* relationships:  
Node id in column 1 and its respective Parent id in column 2.  
column 1: Node id (int)  
column 2: Parent id (int). If root, Parent id == Node id  
  
Example:  
```
6	6
9	6
3	6
2	3
11	3
10	3
5	2
12	2
7	2
13	10
4	10
1	13
8	13
```
### How to use the test

```
<path/to>/matrixpath test/test_tree.tsv
```
Outputs:  
test_tree_matrix.tsv  
test_tree_score_matrix.tsv  
test_tree_scores.tsv  

### Output formats

The matrices are organized *row x col* as *child x parent* ids.  Any value outside the diagonal represents a connection between parent-child.  
On the *tree_matrix.tsv* the diagonal merely represents that the child/parent is connected to itself.  
On the *tree_score_matrix.tsv* the diagonal is the score, aka, the amount of children connected to each parent node plut itself (+1).  
The *tree_scores.tsv* is table similar to the input tree in format, but column 1 contains Node id and column 2 its respective score (connections + 1).  
