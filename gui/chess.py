import PyQt5
from PyQt5 import QtWidgets
from PyQt5 import QtSvg
from PyQt5 import QtGui
from cell import Cell
import copy
class Chess(QtWidgets.QDialog):
    def __init__(self, callback):
        QtWidgets.QDialog.__init__(self)
        self.callback = callback
        self.cells = []
        layout = QtWidgets.QGridLayout(self)
        layout.setSpacing(0)
        for x in range(8):
            tmp = []
            for y in range(8):
                cell = Cell(x, y, self.listen)
                tmp.append(cell)
                layout.addWidget(cell, x, y)
            self.cells.append(tmp)
        self.white = self._render('./img/white.svg')
        self.black = self._render('./img/black.svg')
        self.start()
        self.lock = False
        self.color = 2
    
    def _render(self, path):
        render = QtSvg.QSvgRenderer()
        render.load(path)
        img = QtGui.QPixmap(60, 60)
        img.fill(QtGui.QColor(255, 255, 255, 0))
        render.render(QtGui.QPainter(img))
        icon = QtGui.QIcon(img)
        return icon

    def start(self):
        self.map = [[0 for y in range(8)] for x in range(8)]
        self.map[3][3] = 1
        self.map[3][4] = 2
        self.map[4][3] = 2
        self.map[4][4] = 1
        self.showCell()
        
    def showCell(self):
        for x in range(8):
            for y in range(8):
                cell = self.cells[x][y]
                color = self.map[x][y]
                if color == 1:
                    cell.setIcon(self.white)
                elif color == 2:
                    cell.setIcon(self.black)
                else:
                    cell.setIcon(QtGui.QIcon())

    def listen(self, x, y):
        if self.check(x, y):
            if nextStep(self.map, x, y, self.color):
                self.map[x][y] = self.color
                self.showCell()
                self.clock = True
                if isNext(copy.deepcopy(self.map), 3 - self.color):
                    while True:
                        (x, y) = self.callback(self.map, 3 - self.color)
                        if self.check(x, y) and nextStep(self.map, x, y, 3 - self.color):
                            self.map[x][y] = 3 - self.color
                            self.showCell()
                            if isNext(copy.deepcopy(self.map), self.color):
                                break
                            elif not isNext(copy.deepcopy(self.map), 3 - self.color):
                                self.getResult()
                                break
                        else:
                            QtWidgets.QMessageBox.critical(None, 'AI error', 'at (%d, %d)'%(x, y))
                            self.start()
                            break
                elif not isNext(copy.deepcopy(self.map), self.color):
                    self.getResult()
                self.clock = False
    
    def check(self, x, y):
        if self.map[x][y] != 0:
            return False
        if self.lock:
            return False
        return True
    
    def getResult(self):
        white = sum([sum([1 if y == 1 else 0 for y in x]) for x in self.map])
        black = sum([sum([1 if y == 2 else 0 for y in x]) for x in self.map])
        QtWidgets.QMessageBox.about(None, 'Over', "score: %d - %d"%(white, black))
        self.start()
    
def isNext(map, color):
    for i in range(0, 8):
        for j in range(0, 8):
            if (map[i][j] == 0) and nextStep(map, i, j, color):
                return True
    return False

def nextStep(map, x, y, color):
    count = 0
    count += nextOneStep(map, x, y, color, [0, 1])
    count += nextOneStep(map, x, y, color, [1, 1])
    count += nextOneStep(map, x, y, color, [1, 0])
    count += nextOneStep(map, x, y, color, [0, -1])
    count += nextOneStep(map, x, y, color, [-1, 0])
    count += nextOneStep(map, x, y, color, [-1, -1])
    count += nextOneStep(map, x, y, color, [1, -1])
    count += nextOneStep(map, x, y, color, [-1, 1])
    return count != 0

def nextOneStep(map, x, y, color, addition):
    end_x = x
    end_y = y
    it_x = x
    it_y = y
    it_x += addition[0]
    it_y += addition[1]
    while (it_x in range(0, 8)) and (it_y in range(0, 8)):
        if map[it_x][it_y] == 0:
            break
        elif map[it_x][it_y] == color:
            end_x = it_x
            end_y = it_y
            break
        it_x += addition[0]
        it_y += addition[1]
    
    it_x = x
    it_y = y
    count = 0
    while (it_x != end_x) or (it_y != end_y):
        it_x += addition[0]
        it_y += addition[1]
        if map[it_x][it_y] != color:
            count += 1
            map[it_x][it_y] = color
    return count