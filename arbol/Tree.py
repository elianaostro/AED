class Node:
    def __init__(self, value):
        self.value = value
        self.leftTree = None
        self.rightTree = None
    
    def setLeftTree(self, left):
        self.leftTree = left
    
    def setRightTree(self, right):
        self.rightTree = right
    
    def setValue(self, value):
        self.value = value
    
    def getLeftTree(self):
        return self.leftTree
    
    def getRightTree(self):
        return self.rightTree
    
    def getValue(self):
        return self.value

class BinaryTree:
    def __init__(self, root):
        self.root = root
    def getRoot(self):
        return self.root
