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

        # self.semaforo_fila = threading.Semaphore(datos[0])
        # self.dep_ocupado = threading.Semaphore(1)
        # self.semaforo_depto = threading.Semaphore(datos[2])
        # self.lock = threading.Lock()
        # self.fila = []
        # self.actual_fila = 0
        # self.condicion_grupo = threading.Condition()
        # self.personas_fila_menor = threading.Condition()
        # self.personas_en_depto = 0

        ####
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
        persona[1] = f"{persona[1]}{nombre_deptos[persona[2][persona[-1]+1]-1]},{tiempo}"
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
        self.dfis = departamentos(datos=deptos['dfis'], nombre = nombre_deptos[2])
        self.dquim = departamentos(datos=deptos['dquim'], nombre = nombre_deptos[3])
        self.defider = departamentos(datos=deptos['defider'], nombre = nombre_deptos[4])
        self.dmec = departamentos(datos=deptos['dmec'], nombre = nombre_deptos[5])
        self.dmin = departamentos(datos=deptos['dmin'], nombre = nombre_deptos[6])
        self.alumnos = []
        self.condicion = threading.Condition()
        tiempo = datetime.now().strftime("%H:%M:%S.%f")[:-3]
        self.max_lamp = 100
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
        # print(persona[2])
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
        # if self.actual_lamparas == 0:
            # self.last_call()
            # self.deptos_2()

        ### Notificar para que se ejecute la 2da vuelta solo que hay que enviar la ultima señal para que 
        ### pasen a realizar la consulta
        with self.lock:
            self.actual_lamparas +=1
        with self.condicion:
            if self.actual_lamparas == self.max_lamp:
                self.condicion.notify_all()
            else:
                self.condicion.wait()
        self.patio_cola_2(persona)
    
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