import threading
import random as rand
from datetime import datetime

rand.seed(39)

def archivos(nombres):
    for i in nombres:        
        try:
            open(f"{i}.txt","w")
        except:
            pass

nombre_deptos = [
    "Departamento_de_Matematicas",
    "Departamento_de_Informatica",
    "Departamento_de_Fisica", 
    "Departamento_de_Quimica",
    "DEFIDER",
    "Departamento_de_Mecanica",
    "Departamento_de_Minas",
    "Salida",
    "PdLamparas"
]
#Departamentos : (capacidad fila, duracion consulta, capacidad del departamento)
deptos ={
    "dmat" : (20,9,10),
    "dinf" : (8,5,2),
    "dfis" : (15,7,5),
    "dquim" : (6,4,3),
    "defider" : (6,1,5),
    "dmec" : (9,4,4),
    "dmin" : (7,5,2)
}
claves = {
    1 : "dmat",
    2 : "dinf",
    3 : "dfis",
    4 : "dquim",
    5 : "defider",
    6 : "dmec",
    7 : "dmin"
}



class departamentos():

    def __init__(self,datos, nombre):
        self.max_fila = datos[0]
        self.duracion_consulta = datos[1]
        self.max_dep = datos[2]
        self.semaforo = threading.Semaphore(datos[0])
        # semaforo con la cantidad maxima de personas por fila para no sobrepasarlas
        self.lock = threading.Lock()
        # lock para asegurar el entrar bien al departamento correspondiente
        self.nombre = nombre
        self.fila = []
        self.actual_fila  = 0
    
    def entrar_fila(self,persona):
        with self.semaforo:
            self.fila.append(persona)
            self.actual_fila +=1

        if self.actual_fila == self.max_dep:
            tiempo = datetime.now().strftime("%H:%M:%S.%f")[:-3]
            
            #mandar a los n primeros a self.go_dep
        return
    
    def go_dep(self,personas):
        return

    def last_call(self):
        return    


class lamparas():
    hilos_personas = []
    hilos_2personas = []


    def __init__(self):
        self.dmat = departamentos(datos=deptos['dmat'], nombre = nombre_deptos[0])
        self.dinf = departamentos(datos=deptos['dinf'], nombre = nombre_deptos[1])
        self.alumnos = []
        tiempo = datetime.now().strftime("%H:%M:%S.%f")[:-3]
        for i in range(1,11):
            a = rand.randint(1,2)
            b = rand.randint(1,2)
            while(a == b):
                b = rand.randint(1,2)
            sample = ["",f"Persona{i},{tiempo }," ,("Persona{}".format(i),a,b),0] # 
            # string para escribir en deptos, string para escribir en patio lamparas,( persona_numero, depto_1, depto_2 ),[ instancia de depto 0 si es el primero, 1 si es el 2do] 
            hilo = threading.Thread(target=self.patio_cola,args=(sample,))
            self.hilos_personas.append(hilo)
    
    def ready(self):
        for i in self.hilos_personas:
            i.start()

        return                

    def patio_cola(self,persona):
        self.alumnos.append(persona)
        print(persona[2])
        return
        
    def patio_cola_2(self):
        return

    # def patio(self):


archivos(nombre_deptos)
lampara = lamparas()
lampara.ready()
