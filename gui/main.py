from gui import GUI
from model import predict
app = GUI()
app.bind(predict)
app.start()