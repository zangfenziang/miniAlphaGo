from PyQt5 import QtWidgets
from PyQt5 import QtCore
import copy
class Cell(QtWidgets.QPushButton):
    def __init__(self, x, y, listen):
        QtWidgets.QPushButton.__init__(self, "")
        self.clicked.connect(lambda: listen(x, y))
        self.setFixedWidth(80)
        self.setFixedHeight(80)
        self.setIconSize(QtCore.QSize(60, 60))
        self.setFocusPolicy(0)