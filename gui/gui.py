from PyQt5 import QtWidgets
from chess import Chess
class GUI:
    def __init__(self):
        self.app = QtWidgets.QApplication([])
        self.dlg = QtWidgets.QDialog()
        vbl = QtWidgets.QVBoxLayout(self.dlg)
        self.chess = Chess(self.callback)
        vbl.addWidget(self.chess)
        self.dlg.show()

    def bind(self, predict):
        self.predict = predict
    
    def start(self):
        self.app.exec_()
    
    def callback(self, map, color):
        if self.predict == None:
            return (-1, -1)
        else:
            return self.predict(map, color)

    def click(self, x, y):
        pass