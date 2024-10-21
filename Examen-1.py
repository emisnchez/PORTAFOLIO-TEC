import JuegoBN as jbn  

class Examen(jbn.JuegoBN):
    def __init__(self):
        super().__init__()
        self.matriz[3][0] = "E"
        self.matriz[3][1] = "X"
        self.matriz[3][2] = "A"
        self.matriz[3][3] = "M"
        self.matriz[3][4] = "E"
        self.matriz[3][5] = "N"
        self.matriz[4][0] = "F"
        self.matriz[4][1] = "I"
        self.matriz[4][2] = "N"
        self.matriz[4][3] = "A"
        self.matriz[4][4] = "L"


obj_EXAMEN = Examen()
obj_EXAMEN.muestra_tablero()
obj_EXAMEN.descarga_matriz()


 