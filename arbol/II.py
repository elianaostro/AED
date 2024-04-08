from Tree import BinaryTree, Node

def isLeaf(node):
    return node.getRightTree() == None and node.getLeftTree() == None


def ejericioII(node):
    if node is None:
        return
    if isLeaf(node):
        print(node.getValue())
    ejericioII(node.getLeftTree())
    ejericioII(node.getRightTree())



root = Node(1)
node_2 = Node(2)
node_3 = Node(3)
root.setLeftTree(node_2)
root.setRightTree(node_3)
node_4 = Node(4)
node_5 = Node(5)
node_2.setLeftTree(node_4)
node_2.setRightTree(node_5)
node_6 = Node(6)
node_7 = Node(7)
node_3.setLeftTree(node_6)
node_3.setRightTree(node_7)

tree = BinaryTree(root)

ejericioII(tree.getRoot())
