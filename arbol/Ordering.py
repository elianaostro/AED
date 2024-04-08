from Tree import BinaryTree, Node

def visitTreeInOrder(node, fn):
    # arbol izquierdo, despues raiz y despues derecho
    if node is None:
        return
    visitTreeInOrder(node.getLeftTree(),fn)
    fn(node.getValue())
    visitTreeInOrder(node.getRightTree(),fn)

def visitTreePreOrder(node, fn):
    # raiz,arbol izquierdo despues el derecho
    if node is None:
        return
    fn(node.getValue())
    visitTreePreOrder(node.getLeftTree(),fn)
    visitTreePreOrder(node.getRightTree(),fn)


def visitTreePostOrder(node, fn):
    # arbol izquierdo, despues derecho y raiz
    if node is None:
        return
    visitTreePostOrder(node.getLeftTree(),fn)
    visitTreePostOrder(node.getRightTree(),fn)
    fn(node.getValue())


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

print("PRE ORDER")
visitTreePreOrder(tree.getRoot(), print)
print("IN ORDER")
visitTreeInOrder(tree.getRoot(), print)
print("POST ORDER")
visitTreePostOrder(tree.getRoot(), print)