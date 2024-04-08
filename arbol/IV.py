from Tree import BinaryTree, Node

def sum(root):
    if root is None:
        return 0
    if (root.getRightTree() == None and root.getLeftTree() == None):
        return root.getValue()
    return sum(root.getLeftTree()) + sum(root.getRightTree())

def isSumTree(root):
    if sum(root) != root.getValue():
        return False
    if (root.getRightTree() == None and root.getLeftTree() == None):
        return True
    return isSumTree(root.getRightTree()) and isSumTree(root.getLeftTree())
    
root = Node(1)
node_2 = Node(2)
node_3 = Node(3)
root.setLeftTree(node_2)
root.setRightTree(node_3)
node_4 = Node(4)
node_2.setLeftTree(node_4)

tree = BinaryTree(root)



root_2 = Node(10)
node_2_2 = Node(3)
node_3_2 = Node(4)
root.setLeftTree(node_2_2)
root.setRightTree(node_3_2)
node_4_2 = Node(2)
node_5_2 = Node(1)
node_2_2.setLeftTree(node_4_2)
node_2_2.setLeftTree(node_5_2)


tree_2 = BinaryTree(root_2)

print(isSumTree(tree.getRoot()))
print(isSumTree(tree_2.getRoot()))
