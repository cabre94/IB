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
No me estaba dando bien bien, asi que cambie 
"""

import os
import numpy as np
import matplotlib.pyplot as plt
import matplotlib as mpl
plt.style.use('seaborn')
mpl.rcParams.update(
    {
        "font.size": 22,
        "axes.labelsize": 16,
        "axes.titlesize": 18,
        "legend.fontsize": 18,
        "xtick.labelsize": 16,
        "ytick.labelsize": 16,
        "figure.figsize": [9, 6.5],
        # "figure.autolayout": True,
        "font.family": "serif",
        "font.sans-serif": ["Helvetica"],
        # "savefig.format": 'pdf',
        # "savefig.bbox": 'tight'
    }
)

FONTSIZE = 22
LEGEND_FONTSIZE = 18
SAVE_PATH = os.path.join(os.getcwd(), "ej3_Resultados")
os.makedirs(SAVE_PATH, exist_ok=True)



class Gillespie():
    """
    Algoritmo de Gillespie para resolver el modelo de competencia intraespecifica.
    Las reacciones son:
    A -> A + A con tasa b
    A + A -> A con tasa d
    !En clase redefinimos las tasas como b = b/N y d = d/N. No estoy seguro cual habria que usar aca.
    ! Por el momento voy a dejarlas sin normalizar
    """
    def __init__(self, b, d, A0):
        self.K = [b, d]     # Tasas de las reacciones
        self.A = [A0]       # Poblacion
        self.t = [0]        # Tiempo
        self.h = [None] * len(self.K)   
        self.a = [None] * len(self.K)   # propensities
        self.a0 = None
        self.extincion = False      # Variable para chequear si la poblacion se extinguio
        self.itr = 1

        self.updatePropensitiesAndH()
    
    def updatePropensitiesAndH(self):
        self.h[0] = self.A[-1]      # A*E son todas las posibles combinaciones de K1
        # self.h[1] = (self.A[-1] * (self.A[-1]-1))/2 # Aca no se bien que poner, estoy asumiendo que A1A2 es lo mismo que A2A1
        self.h[1] = self.A[-1]**2 # Aca no se bien que poner, estoy asumiendo que A1A2 es lo mismo que A2A1
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

        self.updatePropensitiesAndH()
        if self.A[-1] == 0:
            self.extincion = True
    
    def simulate(self, t_max):
        while self.t[-1] < t_max and (not self.extincion):
            print("{} - {:.2f}".format(self.itr, self.t[-1]), end='\r')
            tau, reaction = self.nextReaction()     # Obtengo el tiempo de la siguiente reaccion y que reaccion sucede

            self.t.append(self.t[-1] + tau)     # Actualizo el tiempo
            self.updateSystem(reaction)
        
        return [self.t, self.A]
    
    def reset(self):
        aux = self.itr + 1
        self.__init__(self.K[0], self.K[1], self.A[0])
        self.itr = aux

def sol_exacta(t, b, d, phi_0):
    """
    Creo que los valores de r y s cambian en este ejemplo respecto a lo que hicimos en clase. Me los robe
    """
    r = b
    s = d
    c = s - r/phi_0
    phi = r / (s - c * np.exp(-r * t))
    xi = np.full_like(phi, np.sqrt(d/(2*b)))
    return [phi, xi]


b = 0.1
d = 0.001
A0 = 40
N_SAMPLES = 100
T_MAX = 100

system = Gillespie(b=b, d=d, A0=A0)
for itr in range(N_SAMPLES):
    t, A = system.simulate(T_MAX)
    plt.plot(t, A,'b', alpha=0.1, lw=1)
    system.reset()

t = np.linspace(0, 100, 10000)
phi, xi = sol_exacta(t, b, d, A0)
plt.plot(t, phi, 'k-', lw=2, label="Logistica")
# plt.plot(t, phi+xi, 'k-', lw=2)
# plt.plot(t, phi-xi, 'k-', lw=2)
plt.legend(fontsize=16)
plt.ylabel(r'$A(t)$',fontsize=FONTSIZE)
plt.xlabel(r'$t$',fontsize=FONTSIZE)
plt.legend(fontsize=LEGEND_FONTSIZE)
plt.tight_layout()
plt.savefig(os.path.join(SAVE_PATH, "Evolucion_Oscilatorio.pdf"), bbox_inches='tight')
plt.close()

"""
Ahora paso a calcular la distribucion de probabilidad alcanzado un estacionario
"""

P = []

for itr in range(10000):
    _, A = system.simulate(T_MAX)
    system.reset()
    P.append(A[-1])
P = np.array(P)

MAX = P.max()
MIN = P.min()
NUM_BINS = int(MAX)-int(MIN)+2
HIST_BINS = np.linspace(int(MIN), int(MAX)+1, NUM_BINS)    # Bines para el histograma

hist, bins = np.histogram(P, HIST_BINS, density=True)
center = (HIST_BINS[:-1] + HIST_BINS[1:]) / 2
width = 0.7 * (bins[1] - bins[0])

fig, ax = plt.subplots()
# plt.bar(center, hist, align='center', width=width)
container = ax.bar(center, hist, align='edge', alpha=0.7)
ax.vlines(phi[-1], 0, max([patch.get_height() for patch in container]), color='k', linestyle='--', alpha=0.8)
# ax.set_xlim(-2,MAX+2)
ax.set_xlabel(r'$n$', fontsize=FONTSIZE)
ax.set_ylabel(r'$P(n)$', fontsize=FONTSIZE)
plt.legend(fontsize=LEGEND_FONTSIZE)
# plt.tight_layout()
plt.savefig(os.path.join(SAVE_PATH, "Dist_probabilidad.pdf"), bbox_inches='tight')
plt.show()

"""
Ahora vamos a ver el caso en donde la poblacion se exxtingue
"""

b = 0.1
d = 0.2
A0 = 10
N_SAMPLES = 1000
T_MAX = 100

t_extincion = []

system = Gillespie(b=b, d=d, A0=A0)
for itr in range(N_SAMPLES):
    t, A = system.simulate(T_MAX)
    plt.plot(t, A,'b', alpha=0.1, lw=1)
    system.reset()

t = np.linspace(0, 100, 10000)
phi, xi = sol_exacta(t, b, d, A0)
# plt.plot(t, phi, 'k-', lw=2, label="Logistica")
# plt.plot(t, phi+xi, 'k-', lw=2)
# plt.plot(t, phi-xi, 'k-', lw=2)
plt.legend(fontsize=16)
plt.ylabel(r'$A(t)$',fontsize=FONTSIZE)
plt.xlabel(r'$t$',fontsize=FONTSIZE)
# plt.legend(fontsize=LEGEND_FONTSIZE)
plt.tight_layout()
plt.savefig(os.path.join(SAVE_PATH, "Evolucion_Extincion.pdf"), bbox_inches='tight')
plt.show()

"""
Ahora paso a calcular la distribucion de probabilidad del tiempo de extincion
"""

P_t = []

for itr in range(10000):
    t, A = system.simulate(T_MAX)
    system.reset()
    if A[-1] == 0:
        P_t.append(t[-1])
P_t = np.array(P_t)

MAX = P_t.max()
MIN = P_t.min()
NUM_BINS = int(MAX)-int(MIN)+2
HIST_BINS = np.linspace(int(MIN), int(MAX)+1, NUM_BINS)    # Bines para el histograma

hist, bins = np.histogram(P_t, HIST_BINS, density=True)
center = (HIST_BINS[:-1] + HIST_BINS[1:]) / 2
width = 0.7 * (bins[1] - bins[0])

fig, ax = plt.subplots()
# plt.bar(center, hist, align='center', width=width)
container = ax.bar(center, hist, align='edge', alpha=0.7)
# ax.set_xlim(-2,MAX+2)
ax.set_xlabel(r'$t_{ext}$', fontsize=FONTSIZE)
ax.set_ylabel(r'$P(t_{ext})$', fontsize=FONTSIZE)
plt.legend(fontsize=LEGEND_FONTSIZE)
# plt.tight_layout()
plt.savefig(os.path.join(SAVE_PATH, "Dist_tiempo_extincion.pdf"), bbox_inches='tight')
plt.show()
