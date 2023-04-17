#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
date: 03-06-21
File: ej_02_multiplicativo.py
Author : Facundo Martin Cabrera
Email: cabre94@hotmail.com facundo.cabrera@ib.edu.ar
GitHub: https://github.com/cabre94
GitLab: https://gitlab.com/cabre94
Description: 
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
        "xtick.labelsize": 18,
        "ytick.labelsize": 18,
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
SAVE_PATH = os.path.join(os.getcwd(), "ej2_Resultados", "Multiplicativo")
os.makedirs(SAVE_PATH, exist_ok=True)

# Funciones que hacen las iteraciones de sus respectivos modelos
def stepAdditiveNoise(x_t, a=1.05, sigma=0.2):
    z = np.random.normal(loc=0, scale=sigma, size=len(x_t))
    return a*x_t + z

def stepMultiplicativeNoise(x_t, a=1.05, sigma=0.2):
    z = np.random.normal(loc=0, scale=sigma, size=len(x_t))
    return a*x_t + z*x_t

x_t = []    # x_t[i] son los valores de cada trayectoria a tiempo i 
x_exacta = [1.0]

x0 = np.full(12, 1.0)   # 12 trayectorias a tiempo 0
x_t.append(x0)

for _ in range(50):
    x_t.append(stepMultiplicativeNoise(x_t[-1]))
    x_exacta.append(x_exacta[-1] * 1.05)

x_t = np.array(x_t) # x_t[i] son los valores de cada trayectoria a tiempo i 
x = np.copy(x_t.T)  # x[i] es la i-esima trayectoria simulada
x_exacta = np.array(x_exacta)

# Graficamos las 12 trayectorias
fig, ax = plt.subplots()
ax.plot(x_exacta, 'k-', label='Sin ruido')
for i in range(len(x)):
    ax.plot(x[i], '--', lw=1)

ax.set_xlabel(r"$t$", fontsize=FONTSIZE)
ax.set_ylabel(r"$x(t)$", fontsize=FONTSIZE)
plt.legend(loc='best', shadow=True, fancybox=True, fontsize=LEGEND_FONTSIZE)
plt.tight_layout()
plt.savefig(os.path.join(SAVE_PATH, "12_trayectorias.pdf"), bbox_inches='tight')
plt.show()

"""
Ahora voy a hacer estadistica con muchas trayectorias.
"""

NUM_SAMPLES = 10**5

x_t = []
x_exacta = [1.0]

x0 = np.full(NUM_SAMPLES, 1.0)
x_t.append(x0)

for _ in range(50):
    x_t.append(stepMultiplicativeNoise(x_t[-1]))
    x_exacta.append(x_exacta[-1] * 1.05)

x_t = np.array(x_t) # x_t[i] son los valores de cada trayectoria a tiempo i 
x = np.copy(x_t.T)  # x[i] es la i-esima trayextoria simulada
x_exacta = np.array(x_exacta)

"""
Primero graficamos el promedio para distintas cantidades de trayectorias,
commo para ver que el promedio se acerca a la evolucion sin ruido
"""
fig, ax = plt.subplots()
ax.plot(x_exacta, 'k-', label='Sin ruido')
prom = [10**i for i in range(5)]
for i in prom:
    ax.plot(x[:i].mean(axis=0), '--', lw=2, label='n = {}'.format(i))

ax.set_xlabel(r"$t$", fontsize=FONTSIZE)
ax.set_ylabel(r"$x(t)$", fontsize=FONTSIZE)
# ax.set_ylim(0, int(ax.get_ylim()[1])+1)
plt.legend(loc='best', shadow=True, fancybox=True, fontsize=LEGEND_FONTSIZE)
plt.tight_layout()
plt.savefig(os.path.join(SAVE_PATH, "Estadistica_promedio.pdf"), bbox_inches='tight')
plt.show()

"""
Grafico la distribucion de probabilidad P(x,t) a distintos tiempos
"""
MAX = x_t.max()
MIN = x_t.min()
NUM_BINS = int(MAX)-int(MIN)+2
HIST_BINS = np.linspace(int(MIN), int(MAX)+1, NUM_BINS)    # Bines para el histograma

P_t = np.array([np.histogram(x_i_t, HIST_BINS, density=True)[0] for x_i_t in x_t])

#
fig, ax = plt.subplots()
for t in np.linspace(0,50,6, dtype=int):
    ax.bar(HIST_BINS[:-1], P_t[t], label=r'$t={}$'.format(t), alpha=0.7)
ax.set_xlim(-2,40)
ax.set_xlabel(r'$x$', fontsize=FONTSIZE)
ax.set_ylabel(r'$t$', fontsize=FONTSIZE)
plt.legend(fontsize=LEGEND_FONTSIZE)
plt.tight_layout()
plt.savefig(os.path.join(SAVE_PATH, "Distintos_t.pdf"), bbox_inches='tight')
plt.show()

"""
y Ahora grafico la distribucion de probabilidad P(x,t) a distintos tiempos en 3D
"""
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
# for t in np.linspace(0,50,6, dtype=int):
for t in np.linspace(0,50,11, dtype=int):
    bar_container = ax.bar(HIST_BINS[:-1], P_t[t], zs=t, zdir='y', alpha=0.7)

ax.plot(x_exacta, np.arange(len(x_exacta)), [0]*len(x_exacta), label='Sin ruido')

ax.view_init(31, 65)
ax.set_xlim(-5,40)
ax.set_xlabel(r'$x$', fontsize=FONTSIZE)
ax.set_ylabel(r'$t$', fontsize=FONTSIZE)
ax.zaxis.set_rotate_label(False)  # disable automatic rotation
ax.set_zlabel(r"$P(x,t)$", rotation=90)
plt.legend()
# plt.tight_layout()
plt.savefig(os.path.join(SAVE_PATH, "3D.pdf"), bbox_inches='tight')
plt.show()


"""
Por ultimo graficamos el promedio y la evolucion de la desv standard
"""
fig, ax = plt.subplots()
std = x.std(axis=0)
ax.fill_between(np.arange(len(x[0])),x.mean(axis=0)-std, x.mean(axis=0)+std, alpha=0.3, label=r"$\sigma$" )
ax.plot(x.mean(axis=0), '--', lw=2, label=r'$\mu$')

ax.set_xlabel(r"$t$", fontsize=FONTSIZE)
ax.set_ylabel(r"$x(t)$", fontsize=FONTSIZE)
plt.legend(loc='upper left', shadow=True, fancybox=True, fontsize=LEGEND_FONTSIZE)
plt.tight_layout()
plt.savefig(os.path.join(SAVE_PATH, "MeanAndStd.pdf"), bbox_inches='tight')
plt.show()