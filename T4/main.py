import threading
import random as rand
from datetime import datetime
import time

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


class departamentos:

    def __init__(self, datos, nombre):
        self.nombre = nombre
        self.max_fila = threading.Semaphore(datos[0])
        self.max_dep = threading.Semaphore(datos[2])
        self.condicion = threading.Condition()
        self.lock = threading.Lock()
        self.actual_fila = 0
        self.depto_ocupado = 0
        self.tope_dep = datos[2]
        self.dentro_dep = 0
        self.consulta = datos[1]
        ###

    def entrar_fila(self,persona):
        time.sleep(0.5)
        self.max_fila.acquire()
        self.lock.acquire()
        tiempo = datetime.now().strftime("%H:%M:%S.%f")[:-3]
        persona[0] = f"{persona[2][0]},{tiempo},"
        self.actual_fila += 1
        self.lock.release()
        with self.condicion:
            if self.actual_fila>= self.tope_dep and self.depto_ocupado == 0:
                self.condicion.notify()
        
        with self.condicion:
            self.condicion.wait()

        self.depto(persona)

    def depto(self,persona):
        self.max_dep.acquire()
        self.lock.acquire()
        self.actual_fila-=1
        self.max_fila.release()
        self.dentro_dep +=1
        if self.dentro_dep == self.tope_dep:
            self.depto_ocupado = 1
        tiempo = datetime.now().strftime("%H:%M:%S.%f")[:-3]
        with open(f"{self.nombre}.txt","a") as archivo:
            archivo.write(f"{persona[0]}{tiempo},{persona[-1]+1}\n")
        self.lock.release()
        time.sleep(self.consulta)

        self.lock.acquire()
        persona[-1] +=1
        self.dentro_dep -=1
        self.lock.release()
        with self.condicion:
            if self.dentro_dep == 0:
                self.depto_ocupado = 0
                self.condicion.notify_all()
        self.max_dep.release()


    def last_call(self):
        with self.condicion:
            self.condicion.notify_all()





class lamparas():
    hilos_personas = []

    def __init__(self):
        self.dmat = departamentos(datos=deptos['dmat'], nombre = nombre_deptos[0])
        self.dinf = departamentos(datos=deptos['dinf'], nombre = nombre_deptos[1])
        self.dfis = departamentos(datos=deptos['dfis'], nombre = nombre_deptos[2])
        self.dquim = departamentos(datos=deptos['dquim'], nombre = nombre_deptos[3])
        self.defider = departamentos(datos=deptos['defider'], nombre = nombre_deptos[4])
        self.dmec = departamentos(datos=deptos['dmec'], nombre = nombre_deptos[5])
        self.dmin = departamentos(datos=deptos['dmin'], nombre = nombre_deptos[6])
        self.alumnos = []
        self.condicion = threading.Condition()
        tiempo = datetime.now().strftime("%H:%M:%S.%f")[:-3]
        self.max_lamp = 500
        self.actual_lamparas = 0
        self.lock = threading.Lock()
        for i in range(1,self.max_lamp+1):
            a = rand.randint(1,7)
            b = rand.randint(1,7)
            while(a == b):
                b = rand.randint(1,7)
            sample = ["",f"Persona{i},{tiempo }," ,("Persona{}".format(i),a,b),0] # 
            # string para escribir en deptos, string para escribir en patio lamparas,( persona_numero, depto_1, depto_2 ),[ instancia de depto 0 si es el primero, 1 si es el 2do] 
            hilo = threading.Thread(target=self.patio_cola,args=(sample,))
            self.hilos_personas.append(hilo)
    
    def ready(self):
        for i in self.hilos_personas:
            
            i.start()

        for i in self.hilos_personas:
            i.join()

        return                
    

# sample = ["",f"Persona{i},{tiempo }," ,("Persona{}".format(i),a,b),0] # 
    def patio_cola(self,persona):
        self.alumnos.append(persona)
        tiempo = datetime.now().strftime("%H:%M:%S.%f")[:-3]
        self.lock.acquire()
        persona[1] = f"{persona[1]}{nombre_deptos[int(persona[2][1]-1)]},{tiempo},"        
        self.lock.release()
        if persona[2][1] == 1:
            self.dmat.entrar_fila(persona)
            self.lock.acquire()
            self.actual_lamparas -= 1
            self.lock.release()
        elif persona[2][1] == 2:
            self.dinf.entrar_fila(persona)
            self.lock.acquire()
            self.actual_lamparas -= 1
            self.lock.release()
        elif persona[2][1] == 3:
            self.dfis.entrar_fila(persona)
            self.lock.acquire()
            self.actual_lamparas -= 1
            self.lock.release()
        elif persona[2][1] == 4:
            self.dquim.entrar_fila(persona)
            self.lock.acquire()
            self.actual_lamparas -= 1
            self.lock.release()
        elif persona[2][1] == 5:
            self.defider.entrar_fila(persona)
            self.lock.acquire()
            self.actual_lamparas -= 1
            self.lock.release()
        elif persona[2][1] == 6:
            self.dmec.entrar_fila(persona)
            self.lock.acquire()
            self.actual_lamparas -= 1
            self.lock.release()
        elif persona[2][1] == 7:
            self.dmin.entrar_fila(persona)
            self.lock.acquire()
            self.actual_lamparas -= 1
            self.lock.release()
        self.patio_cola_2(persona)
    

        
    def patio_cola_2(self,persona):
        tiempo = datetime.now().strftime("%H:%M:%S.%f")[:-3]
        self.lock.acquire()
        persona[1] = f"{persona[1]}{nombre_deptos[int(persona[2][2]-1)]},{tiempo}"        
        with open("PdLamparas.txt","a") as archivo:
            archivo.write(f"{persona[1]}\n")
        self.lock.release()
        if persona[2][2] == 1:
            self.dmat.entrar_fila(persona)
            self.lock.acquire()
            self.actual_lamparas -= 1
            self.lock.release()
        elif persona[2][2] == 2:
            self.dinf.entrar_fila(persona)
            self.lock.acquire()
            self.actual_lamparas -= 1
            self.lock.release()
        elif persona[2][2] == 3:
            self.dfis.entrar_fila(persona)
            self.lock.acquire()
            self.actual_lamparas -= 1
            self.lock.release()
        elif persona[2][2] == 4:
            self.dquim.entrar_fila(persona)
            self.lock.acquire()
            self.actual_lamparas -= 1
            self.lock.release()
        elif persona[2][2] == 5:
            self.defider.entrar_fila(persona)
            self.lock.acquire()
            self.actual_lamparas -= 1
            self.lock.release()
        elif persona[2][2] == 6:
            self.dmec.entrar_fila(persona)
            self.lock.acquire()
            self.actual_lamparas -= 1
            self.lock.release()
        elif persona[2][2] == 7:
            self.dmin.entrar_fila(persona)
            self.lock.acquire()
            self.actual_lamparas -= 1
            self.lock.release()
        
        tiempo = datetime.now().strftime("%H:%M:%S.%f")[:-3]
        self.lock.acquire()
        with open("Salida.txt","a") as archivo:
            archivo.write(f"{persona[2][0]},{tiempo}\n")
        self.alumnos.pop()
        self.lock.release()
        if len(self.alumnos) < 10:
            self.defider.last_call()
            self.dfis.last_call()
            self.dmat.last_call()
            self.dinf.last_call()
            self.dmin.last_call()
            self.dquim.last_call()
            self.dmec.last_call()


            

archivos(nombre_deptos)
lampara = lamparas()
lampara.ready()