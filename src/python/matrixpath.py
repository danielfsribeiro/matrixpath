import matrixpath_py


def _flatten_tree(tree: list) -> list:
    flat_list = []
    for row in tree:
        flat_list.extend(row)
    
    return flat_list


def _make_neat(flat_list: list,
               row_size: int = 2) -> list:
    new_list = []
    row = []
    i = 0
    s = 0
    while i < len(flat_list):
        while s < row_size:
            row.append(flat_list[i])
            i += 1
            s += 1
        # After while ends
        new_list.append(row)
        row = []
        s = 0
    
    return new_list


def matrixpath(tree: list,
               neat: bool = False  # Return as 2D matix
               ) -> list:
    if isinstance(tree[0], list):
        tree = _flatten_tree(tree)
    
    result = matrixpath_py.matrixpath(tree)
    if neat:
        result = _make_neat(result)
    
    return result


def run_tests() -> None:
    from tests import good_tree, good_tree2, big_tree, bad_tree
    print("good_tree:", matrixpath(good_tree))
    print("good_tree2:", matrixpath(good_tree2))
    print("good_tree2, neat:", matrixpath(good_tree2, True))
    print("big_tree, neat:", matrixpath(big_tree, True))
    print("bad_tree:", matrixpath(bad_tree))
