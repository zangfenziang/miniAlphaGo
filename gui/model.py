import os
def predict(map, color):
    if color != 1:
        for x in map:
            for y in x:
                if y != 0:
                    y = 3 - y

    str = 'ai.exe'
    for x in map:
        for y in x:
            str += ' %d'%(y)
    
    print(str)

    res = os.popen(str)
    data = (int(x[0:-1]) for x in res.readlines())
    return data