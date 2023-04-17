#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
date: 24-06-21
File: ej_01.py
Author : Facundo Martin Cabrera
Email: cabre94@hotmail.com facundo.cabrera@ib.edu.ar
GitHub: https://github.com/cabre94
GitLab: https://gitlab.com/cabre94
Description: 
"""


import os
import numpy as np
import matplotlib.pyplot as plt
from shapely.geometry import LineString
import matplotlib as mpl
from scipy.integrate import odeint
plt.style.use("seaborn")
mpl.rcParams.update(
    {
        "font.size": 18,
        "axes.labelsize": 16,
        "axes.titlesize": 18,
        "legend.fontsize": 15,
        "xtick.labelsize": 12,
        "ytick.labelsize": 12,
        "figure.figsize": [9, 6.5],
        "figure.autolayout": True,
        "font.family": "serif",
        "font.sans-serif": ["Helvetica"],
        "savefig.format": 'pdf',
        "savefig.bbox": 'tight'
    }
)

SAVE_PATH = os.path.join(os.getcwd(), "ej1_Resultados")
os.makedirs(SAVE_PATH, exist_ok=True)



def comensalismModel(u, t, a12, a21, rho):
    """
    Modelo comensalismo
    """
    u1, u2 = u

    du1dt = u1 * (1-u1+a12*u2)
    du2dt = u2 * (1-u2+a21*u1) * rho

    return [du1dt, du2dt]

def nulclina1(u1, a12):
    return -(1-u1)/a12

def nulclina2(u1, a21):
    return 1+a21*u1


def ejercicio(a12, a21, rho):
    u = np.linspace(-2,2,2000)
    # a12 = 0.5
    # a21 = 0.8
    # rho = 1

    null1 = nulclina1(u, a12)
    null2 = nulclina2(u, a21)

    P1, P2 = np.meshgrid(np.linspace(-2,2,101), np.linspace(-2,2,101))
    x, y = np.zeros(P1.shape), np.zeros(P2.shape)

    NI, NJ = P1.shape

    for i in range(NI):
        for j in range(NJ):
            point = [P1[i,j], P2[i,j]] 
            dp = comensalismModel(point, 0, a12, a21, rho)
            x[i,j], y[i,j] = dp

    norm = np.sqrt(x*x + y*y)
    lw = 1.5* norm / norm.max() + 0.5

    fig, ax = plt.subplots()
    ax.plot(u, null1, label=r"Nulclina $\dot{u_{1}}=0$")
    ax.plot(u, null2, label=r"Nulclina $\dot{u_{2}}=0$")

    #* Stream plot
    lw = 1.5* norm / norm.max() + 0.5
    # stream_points = np.array(np.meshgrid(np.arange(0,20), np.arange(0,20))).T.reshape(-1,2)
    # ax.streamplot(P1, P2, u, v, start_points=stream_points, density=2, linewidth=lw, maxlength=50.0)
    ax.streamplot(P1, P2, x, y, density=1.5, linewidth=lw, maxlength=50.0)

    line1 = LineString(np.column_stack((u, null1)))
    line2 = LineString(np.column_stack((u, null2)))
    intersection = line1.intersection(line2)

    print(intersection.geom_type)
    if intersection.geom_type == 'MultiPoint':
        ax.plot(*LineString(intersection).xy, 'o')
    elif intersection.geom_type == 'Point':
        ax.plot(*intersection.xy, 'o')

    ax.set_xlim(-2-0.01,2+0.01)
    ax.set_ylim(-2-0.01,2+0.01)
    ax.set_title(r"$a12={}, a21={}$".format(a12, a21))
    ax.set_xlabel(r"$u_{1}$")
    ax.set_ylabel(r"$u_{2}$")
    box = ax.get_position()
    ax.set_position([box.x0, box.y0 + box.height * 0.1,box.width, box.height * 0.9])
    ax.legend(loc='upper center', bbox_to_anchor=(0.5, -0.1), ncol=2)

    plt.savefig(os.path.join(SAVE_PATH, "StreamPlot_$a12={}_a21={}.pdf".format(a12,a21)), bbox_inches='tight')
    # plt.pause(1)
    # plt.close()
    plt.show()

ejercicio(0.1, 0.5, 1)
ejercicio(0.5, 2, 1)
ejercicio(3, 2, 1)

# ejercicio(-0.5, 0.8, 1)
# ejercicio(0.5, -0.8, 1)
# ejercicio(0.5, 2, 1)
# ejercicio(0.5, 3, 1)

# ejercicio(-0.5, -0.8, 1)