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

import threading
import time
from datetime import datetime

class departamentos:

    def __init__(self, datos, nombre):
        self.max_fila = datos[0]
        self.duracion_consulta = datos[1]
        self.max_dep = datos[2]
        self.semaforo = threading.Semaphore(datos[0])
        self.dep_ocupado = threading.Semaphore(1)
        self.lock = threading.Lock()
        self.nombre = nombre
        self.fila = []
        self.actual_fila = 0

    def entrar_fila(self, persona):
        #mando a todas las personas de la fila a la consulta y las saco de la fila
        with self.semaforo:
            self.fila.append(persona)
            self.actual_fila += 1

            if self.actual_fila == self.max_dep:
                tiempo = datetime.now().strftime("%H:%M:%S.%f")[:-3]

                personas_a_entrar = self.fila[:self.max_dep]
                for i in personas_a_entrar:
                    i[0] = f"{i[2][0]},{tiempo}"
                self.fila = self.fila[self.max_dep:]
                self.actual_fila = 0

                return self.go_dep(personas_a_entrar)
            

    def go_dep(self, personas):
        #toma un semaforo para q este ocupado
        self.dep_ocupado.acquire()
        #self lock para q no se interrumpa a la hebra :p
                
        #tiempo de consulta
        time.sleep(self.duracion_consulta)
        tiempo = datetime.now().strftime("%H:%M:%S.%f")[:-3]
        with self.lock:
            with open(f"{self.nombre}.txt","a") as archivo:
                for i in personas:
                    archivo.write(f"{i[0]},{tiempo},{i[-1]+1}\n")

        for persona in personas:
            if persona[3] == 1:
                with self.lock:
                    with open("salida.txt","a") as archivo:
                        archivo.write(f"{persona[2][0]},{tiempo}\n")
            else:
                with self.lock:
                    persona[3]+=1
        #libera el semaforo
        self.dep_ocupado.release()
        return  personas


    def last_call(self):
        tiempo = datetime.now().strftime("%H:%M:%S.%f")[:-3]

        personas_a_entrar = self.fila[:self.max_dep]
        for i in personas_a_entrar:
            i[0] = f"{i[2][0]},{tiempo}"
        self.fila = self.fila[self.max_dep:]
        self.actual_fila = 0

        return self.go_dep(personas_a_entrar)
        return




class lamparas():
    hilos_personas = []
    hilos_2personas = []


    def __init__(self):
        self.dmat = departamentos(datos=deptos['dmat'], nombre = nombre_deptos[0])
        self.dinf = departamentos(datos=deptos['dinf'], nombre = nombre_deptos[1])
        self.dfis = departamentos(datos=deptos['dfis'], nombre = nombre_deptos[1])
        self.dquim = departamentos(datos=deptos['dquim'], nombre = nombre_deptos[1])
        self.defider = departamentos(datos=deptos['defider'], nombre = nombre_deptos[1])
        self.dmec = departamentos(datos=deptos['dmec'], nombre = nombre_deptos[1])
        self.dmin = departamentos(datos=deptos['dmin'], nombre = nombre_deptos[1])
        self.alumnos = []
        tiempo = datetime.now().strftime("%H:%M:%S.%f")[:-3]
        self.actual_lamparas = 10
        self.lock = threading.Lock()
        for i in range(1,self.actual_lamparas+1):
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

        for i in self.hilos_personas:
            i.join()

        return                
    
    def last_call(self):
        self.dmat.go_dep(self.dmat.last_call())
        self.dinf.go_dep(self.dinf.last_call())
        self.dfis.go_dep(self.dfis.last_call())
        self.dquim.go_dep(self.dquim.last_call())
        self.dmec.go_dep(self.dmec.last_call())
        self.defider.go_dep(self.defider.last_call())
        self.dmin.go_dep(self.dmin.last_call())

# sample = ["",f"Persona{i},{tiempo }," ,("Persona{}".format(i),a,b),0] # 
    def patio_cola(self,persona):
        self.alumnos.append(persona)
        # tiempo = datetime.now().strftime("%H:%M:%S.%f")[:-3]
        # persona[1] = f"{persona[1]}{nombre_deptos[int(persona[2][1]-1)]},{tiempo}"        
        # self.hilos_2personas.append(persona)
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

        if self.actual_lamparas == 0:
            self.last_call()
            self.deptos_2()
    
    def deptos_2(self):
        for i in self.hilos_2personas:
            self.patio_cola_2(i)
        
    def patio_cola_2(self,persona):
        # tiempo = datetime.now().strftime("%H:%M:%S.%f")[:-3]
        # persona[1] = f"{persona[1]}{nombre_deptos[int(persona[2][2]-1)]},{tiempo},"        
        # with open("PdLamparas.txt","a") as archivo:
        #     archivo.write(f"{persona[1]}\n")
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
        # if self.actual_lamparas == 0:
        #     self.last_call()
           
            

    # def patio(self):


archivos(nombre_deptos)
lampara = lamparas()
lampara.ready()
print(lampara.alumnos)