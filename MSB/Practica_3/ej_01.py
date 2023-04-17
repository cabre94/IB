#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
date: 31-05-21
File: ej_01.py
Author : Facundo Martin Cabrera
Email: cabre94@hotmail.com facundo.cabrera@ib.edu.ar
GitHub: https://github.com/cabre94
GitLab: https://gitlab.com/cabre94
Description: 
https://jakevdp.github.io/blog/2012/08/18/matplotlib-animation-tutorial/
https://holypython.com/how-to-save-matplotlib-animations-the-ultimate-guide/
"""

import os
from matplotlib.colors import Colormap
import numpy as np
from scipy.stats import binom
import matplotlib.pyplot as plt
from matplotlib import animation
import matplotlib as mpl
from matplotlib.animation import FuncAnimation

plt.style.use("seaborn")
mpl.rcParams.update(
    {
        "font.size": 18,
        "axes.labelsize": 16,
        "axes.titlesize": 18,
        "legend.fontsize": 15,
        "xtick.labelsize": 12,
        "ytick.labelsize": 12,
        "figure.figsize": [11, 6.5],
        "figure.autolayout": True,
        "font.family": "serif",
        "font.sans-serif": ["Helvetica"],
        "savefig.format": 'pdf',
        "savefig.bbox": 'tight'
    }
)


d = 0.1     # Probabilidad de morir

N0 = 100            # Tamaño de la poblacion
N_ITR = 50          # Numero de iteraciones
N_SAMPLES = 1000   # Numero de poblaciones simuladas
HIST_BINS = np.linspace(0, N0, N0+1)    # Bines para el histograma

SAVE_PATH = os.path.join(os.getcwd(), "ej1_Resultados")
os.makedirs(SAVE_PATH, exist_ok=True)

def prepare_animation(bar_container, line, n):
    """
    Funcion para hacer la animacion.
    """
    def animate(i):
        ax.set_title(r"$t = {}$".format(i))
        # Calculamos el histograma a tiempo t = i y actualizamos el histograma
        counts, _ = np.histogram(n[i, :], HIST_BINS, density=True)
        for count, rect in zip(counts, bar_container.patches):
            rect.set_height(count)
        # Ahora la binomial exacta
        x = np.arange(N0+1)
        bin_dist = binom.pmf(x,N0,(1-d)**(i))
        line.set_ydata(bin_dist)
        # return bar_container.patches
    return animate

n0 = np.full(N_SAMPLES, N0, dtype=int)

P_d = []


for idx, d in enumerate([0.1, 0.3, 0.5, 0.7, 0.9]):
    print(d)

    n = []
    n.append(n0)

    for _ in range(N_ITR):
        print(_, end='\r')

        n_new = [(np.random.rand(n[-1][i]) > d).sum() for i in range(len(n0))]
        n.append(n_new)
        
    n = np.array(n)

    # --- Animacion --- #
    fig, ax = plt.subplots()
    # _, _, bar_container = ax.hist(n[0, :], HIST_BINS, lw=1, ec="yellow", fc="green", alpha=0.5, density=True)
    _, _, bar_container = ax.hist(n[0, :], HIST_BINS, alpha=0.7, density=True, align='left')
    line = ax.plot(np.arange(N0+1), np.zeros(N0+1), 'k--o', markersize=3, lw=0.5, alpha=0.7)[0]

    ax.set_title(r"$t = 0$")
    ax.set_xlabel("Población")
    ax.set_ylabel(r"$P(n,t)$")

    ani = animation.FuncAnimation(fig, prepare_animation(bar_container, line, n), interval=500, frames=N_ITR)
    
    # plt.draw()
    plt.tight_layout()
    ani.save(os.path.join(SAVE_PATH,'d={:.0e}.gif'.format(d)), writer=animation.PillowWriter())
    plt.close()

    # --- Ahora los graficos con imshow --- #


    P_t = np.array([np.histogram(n_t, HIST_BINS, density=True)[0] for n_t in n])

    P_d.append(P_t)
    # P_t = np.array([np.histogram(n_t, HIST_BINS)[0] for n_t in n])

"""
"""
N_SAMPLES = 100000
d = 0.3
n0 = np.full(N_SAMPLES, N0, dtype=int)
n = []
n.append(n0)

fig, ax = plt.subplots()
for j in range(8):
    n_new = [(np.random.rand(n[-1][i]) > d).sum() for i in range(len(n0))]
    n.append(n_new)

    color = next(ax._get_lines.prop_cycler)['color']

    ax.hist(n_new, HIST_BINS, lw=1, alpha=0.4, density=True,color = color, align='left', label='t={}'.format(j+1))
    x = np.arange(N0+1)
    bin_dist = binom.pmf(x,N0,(1-d)**(j+1))

    ax.plot(np.arange(N0+1),bin_dist, '--o', markersize=3, lw=0.5,color = color, alpha=1)[0]

ax.set_title("d={}".format(d))
ax.set_xlabel("Población")
ax.set_ylabel(r"$P(n,t)$")
ax.legend(loc='best')
plt.savefig(os.path.join(SAVE_PATH, "Evolucion"))
plt.show()

"""    # fig, axs = plt.subplots(nrows=1, ncols=4, sharex=True,figsize=(12, 8))
    # fig, axs = plt.subplots(nrows=1, ncols=4)
    ax2 = axs[idx]
    # fig, ax = plt.subplots()
    # plt.imshow(P_t.T[::-1], cmap='seismic')
    ax2.set_title(r"d = {}".format(d))
    im = ax2.imshow(P_t.T[::-1], cmap='nipy_spectral')
    if(idx == 0):
        ax2.set_yticks(np.linspace(N0,0, 6, dtype=int))
        ax2.set_yticklabels(np.linspace(N0,0, 6, dtype=int)[::-1])
    ax2.grid(False)
    # plt.colorbar(im, cax=cax)
    # asi esta bien la evolucion pero tengo que poner manualmente los label





fig2, axs = plt.subplots(nrows=1, ncols=5, sharey=True, figsize=(8, 5))

# fig2.subplots_adjust(right=0.8)
# cbar_ax = fig2.add_axes([0.85, 0.15, 0.05, 0.7])
# fig2.colorbar(im, cax=cbar_ax)

# cbar = fig.colorbar(im, ax=axs.ravel().tolist(), shrink=0.95)
# fig2.colorbar(im, ax=axs.ravel().tolist())
# plt.tight_layout()
fig2.savefig("kk.png", bbox_inches='tight')
plt.close()"""