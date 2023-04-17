#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
date: 08-06-21
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
from scipy.integrate import odeint
import matplotlib as mpl
plt.style.use('seaborn')

FONTSIZE = 20
LEGEND_FONTSIZE = 15
SAVE_PATH = os.path.join(os.getcwd(), "ej1_Resultados")
os.makedirs(SAVE_PATH, exist_ok=True)

plt.style.use("seaborn")
mpl.rcParams.update(
    {
        "font.size": 18,
        "axes.labelsize": 18,
        "axes.titlesize": 18,
        "legend.fontsize": 15,
        "xtick.labelsize": 15,
        "ytick.labelsize": 15,
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
    Funcion de represion para el modelo de Goodwin
    """
    return a / (b + c * np.power(p, h))

def goodwinModel(z, t, alphas, betas, param, h):
    """
    Modelo de Goodwin
    """
    m, e, p = z
    alpha_m, alpha_e, alpha_p = alphas
    beta_m, beta_e, beta_p = betas
    a, b, c = param

    dmdt = alpha_m * g_R(p, a, b, c, h) - beta_m*m
    dedt = alpha_e * m - beta_e * e
    dpdt = alpha_p * e - beta_p * p

    return [dmdt, dedt, dpdt]

alphas = alpha_m, alpha_e, alpha_p = 1, 1, 1
betas = beta_m, beta_e, beta_p = 0.1, 0.1, 0.1
param = a, b, c = 1, 1, 1

z0 =  [0.5, 0.5, 0.5]
t = np.linspace(0,750, 10001)

m_h = []
e_h = []
p_h = []

for h in range(15):
    z = odeint(goodwinModel, z0, t, args=(alphas, betas, param, h))

    fig, ax = plt.subplots()
    ax.set_title(r"$h={}$".format(h))
    ax.plot(t, z[:,0], label = r'$m$')
    ax.plot(t, z[:,1], label = r'$e$')
    ax.plot(t, z[:,2], label = r'$p$')
    ax.set_xlabel(r'$t$', fontsize=FONTSIZE)
    ax.set_ylabel('Concentraciones', fontsize=FONTSIZE)
    plt.legend(fontsize=LEGEND_FONTSIZE)
    plt.tight_layout()
    plt.savefig(os.path.join(SAVE_PATH, "h={}_Concentraciones.pdf".format(h)), bbox_inches='tight')
    # plt.show()
    # plt.pause(1)
    plt.close()

    m_h.append(z[:,0])
    e_h.append(z[:,1])
    p_h.append(z[:,2])

ESTACIONARIO = 3335
fig, ax = plt.subplots()
ax.plot(t[:-ESTACIONARIO], m_h[7][:-ESTACIONARIO], label = r'$h=7$')
ax.plot(t[:-ESTACIONARIO], m_h[8][:-ESTACIONARIO], label = r'$h=8$')
ax.plot(t[:-ESTACIONARIO], m_h[10][:-ESTACIONARIO], label = r'$h=10$')
ax.plot(t[:-ESTACIONARIO], m_h[14][:-ESTACIONARIO], label = r'$h=14$')
ax.set_xlabel(r'$t$', fontsize=FONTSIZE)
ax.set_ylabel('m(t)', fontsize=FONTSIZE)
plt.legend(loc='upper right', fontsize=LEGEND_FONTSIZE)
plt.tight_layout()
plt.savefig(os.path.join(SAVE_PATH, "m.pdf".format(h)), bbox_inches='tight')
plt.show()

fig, ax = plt.subplots()
ax.plot(t[-ESTACIONARIO:], m_h[7][-ESTACIONARIO:], label = r'$h=7$')
ax.plot(t[-ESTACIONARIO:], m_h[8][-ESTACIONARIO:], label = r'$h=8$')
ax.plot(t[-ESTACIONARIO:], m_h[10][-ESTACIONARIO:], label = r'$h=10$')
ax.plot(t[-ESTACIONARIO:], m_h[14][-ESTACIONARIO:], label = r'$h=14$')
ax.set_xlabel(r'$t$', fontsize=FONTSIZE)
ax.set_ylabel('m(t)', fontsize=FONTSIZE)
plt.legend(loc='upper right', fontsize=LEGEND_FONTSIZE)
plt.tight_layout()
plt.savefig(os.path.join(SAVE_PATH, "m_estacionario.pdf".format(h)), bbox_inches='tight')
plt.show()

fig, ax = plt.subplots()
ax.plot(t[:-ESTACIONARIO], e_h[7][:-ESTACIONARIO], label = r'$h=7$')
ax.plot(t[:-ESTACIONARIO], e_h[8][:-ESTACIONARIO], label = r'$h=8$')
ax.plot(t[:-ESTACIONARIO], e_h[10][:-ESTACIONARIO], label = r'$h=10$')
ax.plot(t[:-ESTACIONARIO], e_h[14][:-ESTACIONARIO], label = r'$h=14$')
ax.set_xlabel(r'$t$', fontsize=FONTSIZE)
ax.set_ylabel('e(t)', fontsize=FONTSIZE)
plt.legend(loc='upper right', fontsize=LEGEND_FONTSIZE)
plt.tight_layout()
plt.savefig(os.path.join(SAVE_PATH, "e.pdf".format(h)), bbox_inches='tight')
plt.show()

fig, ax = plt.subplots()
ax.plot(t[-ESTACIONARIO:], e_h[7][-ESTACIONARIO:], label = r'$h=7$')
ax.plot(t[-ESTACIONARIO:], e_h[8][-ESTACIONARIO:], label = r'$h=8$')
ax.plot(t[-ESTACIONARIO:], e_h[10][-ESTACIONARIO:], label = r'$h=10$')
ax.plot(t[-ESTACIONARIO:], e_h[14][-ESTACIONARIO:], label = r'$h=14$')
ax.set_xlabel(r'$t$', fontsize=FONTSIZE)
ax.set_ylabel('e(t)', fontsize=FONTSIZE)
plt.legend(loc='upper right', fontsize=LEGEND_FONTSIZE)
plt.tight_layout()
plt.savefig(os.path.join(SAVE_PATH, "e_estacionario.pdf".format(h)), bbox_inches='tight')
plt.show()

fig, ax = plt.subplots()
ax.plot(t[:-ESTACIONARIO], p_h[7][:-ESTACIONARIO], label = r'$h=7$')
ax.plot(t[:-ESTACIONARIO], p_h[8][:-ESTACIONARIO], label = r'$h=8$')
ax.plot(t[:-ESTACIONARIO], p_h[10][:-ESTACIONARIO], label = r'$h=10$')
ax.plot(t[:-ESTACIONARIO], p_h[14][:-ESTACIONARIO], label = r'$h=14$')
ax.set_xlabel(r'$t$', fontsize=FONTSIZE)
ax.set_ylabel('p(t)', fontsize=FONTSIZE)
plt.legend(loc='upper right', fontsize=LEGEND_FONTSIZE)
plt.tight_layout()
plt.savefig(os.path.join(SAVE_PATH, "p.pdf".format(h)), bbox_inches='tight')
plt.show()

fig, ax = plt.subplots()
ax.plot(t[-ESTACIONARIO:], p_h[7][-ESTACIONARIO:], label = r'$h=7$')
ax.plot(t[-ESTACIONARIO:], p_h[8][-ESTACIONARIO:], label = r'$h=8$')
ax.plot(t[-ESTACIONARIO:], p_h[10][-ESTACIONARIO:], label = r'$h=10$')
ax.plot(t[-ESTACIONARIO:], p_h[14][-ESTACIONARIO:], label = r'$h=14$')
ax.set_xlabel(r'$t$', fontsize=FONTSIZE)
ax.set_ylabel('p(t)', fontsize=FONTSIZE)
plt.legend(loc='upper right', fontsize=LEGEND_FONTSIZE)
plt.tight_layout()
plt.savefig(os.path.join(SAVE_PATH, "p_estacionario.pdf".format(h)), bbox_inches='tight')
plt.show()


"""
Solo falta el barrido en beta
"""
m_b = []
e_b = []
p_b = []

h = 10

for beta in [0.1, 0.5, 1]:
    z = odeint(goodwinModel, z0, t, args=(alphas, [beta,beta,beta], param, h))

    fig, ax = plt.subplots()
    ax.set_title(r"$\beta_i={}$".format(beta))
    ax.plot(t, z[:,0], label = r'$m$')
    ax.plot(t, z[:,1], label = r'$e$')
    ax.plot(t, z[:,2], label = r'$p$')
    ax.set_xlabel(r'$t$', fontsize=FONTSIZE)
    ax.set_ylabel('Concentraciones', fontsize=FONTSIZE)
    plt.legend(fontsize=LEGEND_FONTSIZE)
    plt.tight_layout()
    plt.savefig(os.path.join(SAVE_PATH, "b={}_Barrido.pdf".format(beta)), bbox_inches='tight')
    # plt.show()
    # plt.pause(1)
    plt.show()

    m_b.append(z[:,0])
    e_b.append(z[:,1])
    p_b.append(z[:,2])


ESTACIONARIO = 3335
fig, ax = plt.subplots()
ax.plot(t[:-ESTACIONARIO], m_b[0][:-ESTACIONARIO], label = r'$\beta_i=0.1$')
ax.plot(t[:-ESTACIONARIO], m_b[1][:-ESTACIONARIO], label = r'$\beta_i=0.5$')
ax.plot(t[:-ESTACIONARIO], m_b[2][:-ESTACIONARIO], label = r'$\beta_i=1$')
ax.set_xlabel(r'$t$', fontsize=FONTSIZE)
ax.set_ylabel('m(t)', fontsize=FONTSIZE)
plt.legend(fontsize=LEGEND_FONTSIZE)
plt.tight_layout()
plt.savefig(os.path.join(SAVE_PATH, "m_B_.pdf".format(h)), bbox_inches='tight')
plt.show()

fig, ax = plt.subplots()
ax.plot(t[-ESTACIONARIO:], m_b[0][-ESTACIONARIO:], label = r'$\beta_i=0.1$')
ax.plot(t[-ESTACIONARIO:], m_b[1][-ESTACIONARIO:], label = r'$\beta_i=0.5$')
ax.plot(t[-ESTACIONARIO:], m_b[2][-ESTACIONARIO:], label = r'$\beta_i=1$')
ax.set_xlabel(r'$t$', fontsize=FONTSIZE)
ax.set_ylabel('m(t)', fontsize=FONTSIZE)
plt.legend(fontsize=LEGEND_FONTSIZE)
plt.tight_layout()
plt.savefig(os.path.join(SAVE_PATH, "m_B_estacionario.pdf".format(h)), bbox_inches='tight')
plt.show()


ESTACIONARIO = 3335
fig, ax = plt.subplots()
ax.plot(t[:-ESTACIONARIO], e_b[0][:-ESTACIONARIO], label = r'$\beta_i=0.1$')
ax.plot(t[:-ESTACIONARIO], e_b[1][:-ESTACIONARIO], label = r'$\beta_i=0.5$')
ax.plot(t[:-ESTACIONARIO], e_b[2][:-ESTACIONARIO], label = r'$\beta_i=1$')
ax.set_xlabel(r'$t$', fontsize=FONTSIZE)
ax.set_ylabel('e(t)', fontsize=FONTSIZE)
plt.legend(fontsize=LEGEND_FONTSIZE)
plt.tight_layout()
plt.savefig(os.path.join(SAVE_PATH, "e_B_.pdf".format(h)), bbox_inches='tight')
plt.show()

fig, ax = plt.subplots()
ax.plot(t[-ESTACIONARIO:], m_b[0][-ESTACIONARIO:], label = r'$\beta_i=0.1$')
ax.plot(t[-ESTACIONARIO:], m_b[1][-ESTACIONARIO:], label = r'$\beta_i=0.5$')
ax.plot(t[-ESTACIONARIO:], m_b[2][-ESTACIONARIO:], label = r'$\beta_i=1$')
ax.set_xlabel(r'$t$', fontsize=FONTSIZE)
ax.set_ylabel('e(t)', fontsize=FONTSIZE)
plt.legend(fontsize=LEGEND_FONTSIZE)
plt.tight_layout()
plt.savefig(os.path.join(SAVE_PATH, "e_B_estacionario.pdf".format(h)), bbox_inches='tight')
plt.show()


ESTACIONARIO = 3335
fig, ax = plt.subplots()
ax.plot(t[:-ESTACIONARIO], p_b[0][:-ESTACIONARIO], label = r'$\beta_i=0.1$')
ax.plot(t[:-ESTACIONARIO], p_b[1][:-ESTACIONARIO], label = r'$\beta_i=0.5$')
ax.plot(t[:-ESTACIONARIO], p_b[2][:-ESTACIONARIO], label = r'$\beta_i=1$')
ax.set_xlabel(r'$t$', fontsize=FONTSIZE)
ax.set_ylabel('p(t)', fontsize=FONTSIZE)
plt.legend(fontsize=LEGEND_FONTSIZE)
plt.tight_layout()
plt.savefig(os.path.join(SAVE_PATH, "p_B_.pdf".format(h)), bbox_inches='tight')
plt.show()

fig, ax = plt.subplots()
ax.plot(t[-ESTACIONARIO:], p_b[0][-ESTACIONARIO:], label = r'$\beta_i=0.1$')
ax.plot(t[-ESTACIONARIO:], p_b[1][-ESTACIONARIO:], label = r'$\beta_i=0.5$')
ax.plot(t[-ESTACIONARIO:], p_b[2][-ESTACIONARIO:], label = r'$\beta_i=1$')
ax.set_xlabel(r'$t$', fontsize=FONTSIZE)
ax.set_ylabel('p(t)', fontsize=FONTSIZE)
plt.legend(fontsize=LEGEND_FONTSIZE)
plt.tight_layout()
plt.savefig(os.path.join(SAVE_PATH, "p_B_estacionario.pdf".format(h)), bbox_inches='tight')
plt.show()

