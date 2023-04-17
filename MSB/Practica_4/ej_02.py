#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
date: 08-06-21
File: ej_02.py
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
from scipy.integrate import odeint
plt.style.use('seaborn')

FONTSIZE = 18
LEGEND_FONTSIZE = 15
SAVE_PATH = os.path.join(os.getcwd(), "ej2_Resultados")
os.makedirs(SAVE_PATH, exist_ok=True)

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

def g_R(p, a, b, c, h):
    """
    Funcion de represion para el modelo de Goodwin.
    """
    return a / (b + c * np.power(p, h))

def g_R_der(p, a, b, c, h):
    """
    Derivada de la funcion de represion.
    """
    return (-a*h*c*np.power(p, h-1)) / np.power((b + c * np.power(p, h)), 2)

def geneticSwitchModel(z, t, alphas, betas, param, h):
    """
    Modelo de Swich genetico
    """
    m1, m2, p1, p2 = z
    alpha_m, alpha_p = alphas
    beta_m, beta_p = betas
    a, b, c = param

    dm1dt = alpha_m * g_R(p2,a,b,c,h) - beta_m * m1
    dm2dt = alpha_m * g_R(p1,a,b,c,h) - beta_m * m2
    dp1dt = alpha_p * m1 - beta_p * p1
    dp2dt = alpha_p * m2 - beta_p * p2

    return [dm1dt, dm2dt, dp1dt, dp2dt]

def geneticSwitchSimplyfiedModel(p, t, alphas, betas, param, h):
    """
    Modelo simplificado del Switch generico, tomado beta_m >> beta_p
    """
    p1, p2 = p
    alpha_m, alpha_p = alphas
    beta_m, beta_p = betas
    a, b, c = param

    dp1dt = (alpha_p * alpha_m) / beta_m * g_R(p2,a,b,c,h) - beta_p * p1
    dp2dt = (alpha_p * alpha_m) / beta_m * g_R(p1,a,b,c,h) - beta_p * p2

    return [dp1dt, dp2dt]

def nullclinesSimplifiedModel(p, alphas, betas, param, h):
    a, b, c = param
    return np.prod(alphas) / np.prod(betas) * g_R(p,a,b,c,h)

def inverseNullcline(p, alphas, betas, param, h):
    a, b, c = param
    return (((np.prod(alphas)*a) / (np.prod(betas)*p) - b)/c)**(1/h)

"""
Voy a graficar la funcion de represion para distintos valores de b y c, pero
solo porque todo el mundo lo hace
TODO Cambiar y fijar h = 3, que es lo que todo el mundo hizo
"""
bs = np.linspace(2,10,5)
a, c = 5, 2
h = 4

for h in range(1,6):
    fig, axs = plt.subplots(1,2)
    fig.suptitle(r"$h={}$".format(h))
    x = np.linspace(0,10,1000)
    for b in bs:
        axs[0].plot(x, g_R(x, a, b, c, h), label=r"b={}".format(b))
        axs[1].plot(x, g_R_der(x, a, b, c, h), label=r"b={}".format(b))
    axs[0].set_xlabel(r"$p$", fontsize=FONTSIZE)
    axs[1].set_xlabel(r"$p$", fontsize=FONTSIZE)
    axs[0].set_ylabel(r"$g_R(p)$", fontsize=FONTSIZE)
    axs[1].set_ylabel(r"$g_{R}^{\prime}(p)$", fontsize=FONTSIZE)
    plt.legend(fontsize=LEGEND_FONTSIZE)
    plt.tight_layout()
    plt.savefig(os.path.join(SAVE_PATH, "b_barrido_h={}.pdf".format(h)), bbox_inches='tight')
    # plt.show()
    plt.close()

cs = np.linspace(2,10,5)
a, b = 5, 2
h = 4

for h in range(1,6):
    fig, ax = plt.subplots(1,2)
    x = np.linspace(0,10,1000)
    for c in cs:
        axs[0].plot(x, g_R(x, a, b, c, h), label=r"c={}".format(c))
        axs[1].plot(x, g_R_der(x, a, b, c, h), label=r"c={}".format(c))
    axs[0].set_xlabel(r"$p$", fontsize=FONTSIZE)
    axs[1].set_xlabel(r"$p$", fontsize=FONTSIZE)
    axs[0].set_ylabel(r"$g_R(p)$", fontsize=FONTSIZE)
    axs[1].set_ylabel(r"$g_{R}^{\prime}(p)$", fontsize=FONTSIZE)
    plt.legend(fontsize=LEGEND_FONTSIZE)
    plt.tight_layout()
    plt.savefig(os.path.join(SAVE_PATH, "c_barrido_h={}.pdf".format(h)), bbox_inches='tight')
    # plt.show()
    plt.close()

"""
Hay que usar la simplificacion, pero igual voy a simular el sistema pelado
"""

alphas = alpha_m, alpha_p = 1, 1
betas = beta_m, beta_p = 0.1, 0.3
param = a, b, c = 1, 1, 1

z0 =  [0.5, 0.4, 0.2, 0.7]
t = np.linspace(0,1000, 10001)

m1_h = []
m2_h = []
p1_h = []
p2_h = []

for h in range(15):
    z = odeint(geneticSwitchModel, z0, t, args=(alphas, betas, param, h))

    fig, axs = plt.subplots(1,2)
    fig.suptitle(r"$h={}$".format(h))
    axs[0].plot(t, z[:,0], label = r'$m1$')
    axs[0].plot(t, z[:,1], label = r'$m2$')
    axs[1].plot(t, z[:,2], label = r'$p1$')
    axs[1].plot(t, z[:,3], label = r'$p2$')
    axs[0].set_xlabel(r'$t$', fontsize=FONTSIZE)
    axs[1].set_xlabel(r'$t$', fontsize=FONTSIZE)
    axs[0].set_ylabel(r'$m$', fontsize=FONTSIZE)
    axs[1].set_ylabel(r'$p$', fontsize=FONTSIZE)
    plt.legend(fontsize=LEGEND_FONTSIZE)
    plt.tight_layout()
    plt.savefig(os.path.join(SAVE_PATH, "h={}_Concentraciones.pdf".format(h)), bbox_inches='tight')
    # plt.show()
    # plt.pause(1)
    plt.close()

    m1_h.append(z[:,0])
    m2_h.append(z[:,1])
    p1_h.append(z[:,2])
    p2_h.append(z[:,3])

"""
Hacemos el barrido en b.
"""

alphas = alpha_m, alpha_p = 1, 1
betas = beta_m, beta_p = 1, 0.001
param = a, b, c = 1, 1, 1
h = 3

p_range = np.linspace(0,20, 100000)

from shapely.geometry import LineString
# Bifurcacion cerca de b = 150
for b in [1,10,20,30,40,50,60,70,80,90,100,150,160,170,180,190,200,300,400,500]:
    param = a, b, c
    p1 = nullclinesSimplifiedModel(p_range, alphas, betas, param, h)
    p2 = nullclinesSimplifiedModel(p_range, alphas, betas, param, h)
    
    P1, P2 = np.meshgrid(np.linspace(0,20,100), np.linspace(0,20,100))
    u, v = np.zeros(P1.shape), np.zeros(P2.shape)
    NI, NJ = P1.shape

    for i in range(NI):
        for j in range(NJ):
            point = [P1[i,j], P2[i,j]] 
            dp = geneticSwitchSimplyfiedModel(point, 0, alphas, betas, param, h)
            u[i,j], v[i,j] = dp

    norm = np.sqrt(u*u + v*v)

    fig, ax = plt.subplots()
    ax.plot(p_range, p2, label=r"Nulclina $p_{2}=0$")
    ax.plot(p1, p_range, label=r"Nulclina $p_{1}=0$")

    #* Stream plot
    lw = 1.5* norm / norm.max() + 0.5
    # stream_points = np.array(np.meshgrid(np.arange(0,20), np.arange(0,20))).T.reshape(-1,2)
    # ax.streamplot(P1, P2, u, v, start_points=stream_points, density=2, linewidth=lw, maxlength=50.0)
    ax.streamplot(P1, P2, u, v, density=1.5, linewidth=lw, maxlength=50.0)

    line1 = LineString(np.column_stack((p_range, p2)))
    line2 = LineString(np.column_stack((p1, p_range)))
    intersection = line1.intersection(line2)

    if intersection.geom_type == 'MultiPoint':
        ax.plot(*LineString(intersection).xy, 'o')
    elif intersection.geom_type == 'Point':
        ax.plot(*intersection.xy, 'o')

    ax.set_xlim(0,20)
    ax.set_ylim(0,20)
    ax.set_title(r"$b={}$".format(b))
    ax.set_xlabel(r"$p_{1}$", fontsize=FONTSIZE)
    ax.set_ylabel(r"$p_{2}$", fontsize=FONTSIZE)
    box = ax.get_position()
    ax.set_position([box.x0, box.y0 + box.height * 0.1,box.width, box.height * 0.9])
    ax.legend(loc='upper center', bbox_to_anchor=(0.5, -0.1), ncol=2, fontsize=LEGEND_FONTSIZE)

    # plt.tight_layout()
    plt.savefig(os.path.join(SAVE_PATH, "StreamPlot_b={}.pdf".format(b)), bbox_inches='tight')
    # plt.savefig(os.path.join(SAVE_PATH, "StreamPlot_b={}.png".format(b)), bbox_inches='tight')
    # plt.pause(1)
    plt.close()
    # plt.show()

