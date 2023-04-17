#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
date: 06-06-21
File: ej_03.py
Author : Facundo Martin Cabrera
Email: cabre94@hotmail.com facundo.cabrera@ib.edu.ar
GitHub: https://github.com/cabre94
GitLab: https://gitlab.com/cabre94
Description: 
Estoy en duda si en el ejercicio hay que usar que A + E = N = cte.
Voy a asumir que si y despues de ultima lo cambio.
"""

import os
import numpy as np
import matplotlib.pyplot as plt
plt.style.use('seaborn')

FONTSIZE = 15
LEGEND_FONTSIZE = 10
SAVE_PATH = os.path.join(os.getcwd(), "ej3_Resultados")
os.makedirs(SAVE_PATH, exist_ok=True)



class Gillespie():
    """
    Algoritmo de Gillespie para resolver el modelo de competencia intraespecifica.
    Las reacciones son:
    A -> A + A con tasa b
    A + A -> A con tasa d
    Asumo que lo que tenemos como recurso limitado es la cantidad de slots, o sea que tenemos
    espacios vacios E de tal forma que A + E = N y las reacciones serian como
    A + E -> A + A
    A + A -> A + E
    !En clase redefinimos las tasas como b = b/N y d = d/N. No estoy seguro cual habria que usar aca.
    ! Por el momento voy a dejarlas sin normalizar
    """
    def __init__(self, b, d, A0, N):
        assert(A0 <= N)
        self.K = [b/N, d]     # Tasas de las reacciones
        self.A = [A0]       # Poblacion
        self.E = [N-A0]     # Numero de slots vacios
        self.t = [0]        # Tiempo
        self.N = N          # Slots totales
        self.h = [None] * len(self.K)   
        self.a = [None] * len(self.K)   # propensities
        self.a0 = None
        self.extincion = False      # Variable para chequear si la poblacion se extinguio

        self.updatePropensitiesAndH()
    
    def updatePropensitiesAndH(self):
        self.h[0] = self.A[-1] * self.E[-1]   # A*E son todas las posibles combinaciones de K1
        self.h[1] = (self.A[-1] * (self.A[-1]-1))/2 # Aca no se bien que poner, estoy asumiendo que A1A2 es lo mismo que A2A1
        # self.h[1] = self.A[-1] # Aca no se bien que poner, estoy asumiendo que A1A2 es lo mismo que A2A1
        self.a = [self.h[i]*self.K[i] for i in range(len(self.K))]
        self.a0 = sum(self.a)
    
    def timeNextReaction(self):
        rand = np.random.random()
        return -np.log(rand)/self.a0
    
    def whichReaction(self):
        rand = self.a0 * np.random.random()
        reaction = 0
        while self.a[reaction] < rand:
            rand -= self.a[reaction]
            reaction += 1
        return reaction
    
    def nextReaction(self):
        tau = self.timeNextReaction()
        reaction = self.whichReaction()
        return [tau, reaction]
    
    def updateSystem(self, reaction):
        if reaction == 0:
            self.A.append(self.A[-1]+1)
        elif reaction == 1:
            self.A.append(self.A[-1]-1)
        else:
            raise Exception('No existe esta reaccion')
        self.E.append(self.N - self.A[-1])

        self.updatePropensitiesAndH()
        if self.A[-1] == 0:
            self.extincion = True

    
    def simulate(self, t_max):
        while self.t[-1] < t_max and (not self.extincion):
            print("{:.2f}".format(self.t[-1]), end='\r')
            tau, reaction = self.nextReaction()     # Obtengo el tiempo de la siguiente reaccion y que reaccion sucede

            self.t.append(self.t[-1] + tau)     # Actualizo el tiempo
            self.updateSystem(reaction)
        
        return [self.t, self.A]


b = 0.1
d = 0.001
N = 100
A0 = 10

# system = Gillespie(0.1, 0.001, 40, 200)
system = Gillespie(b=b, d=d, A0=A0, N=N)
t, A = system.simulate(100)

plt.plot(t, A)
plt.show()