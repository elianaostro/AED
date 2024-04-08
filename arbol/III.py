from Tree import BinaryTree, Node

def isLeaf(node):
    return node.getRightTree() == None and node.getLeftTree() == None

def ejericioIII(node):
    if node is None:
        return 0
    if isLeaf(node):
        return 1
    rama_izq = ejericioIII(node.getLeftTree())
    rama_der = ejericioIII(node.getRightTree())
    return 1 + max(rama_der,rama_izq)


root = Node(1)
node_2 = Node(2)
node_3 = Node(3)
root.setLeftTree(node_2)
root.setRightTree(node_3)
node_4 = Node(4)
node_2.setLeftTree(node_4)


tree = BinaryTree(root)

print(ejericioIII(tree.getRoot()))
