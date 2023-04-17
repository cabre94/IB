#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
date: 14-06-21
File: ej_02.py
Author : Facundo Martin Cabrera
Email: cabre94@hotmail.com facundo.cabrera@ib.edu.ar
GitHub: https://github.com/cabre94
GitLab: https://gitlab.com/cabre94
Description: 
"""

import os
import numpy as np
import pandas as pd
from scipy import signal, optimize
import matplotlib.pyplot as plt

import matplotlib as mpl

plt.style.use("seaborn")
mpl.rcParams.update(
    {
        "font.size": 20,
        "axes.labelsize": 20,
		"legend.fontsize": 15,
        "xtick.labelsize": 18,
        "ytick.labelsize": 18,
        "figure.figsize": [9, 6.5],
        "figure.autolayout": True,
        "font.family": "serif",
        "font.sans-serif": ["Helvetica"],
        "savefig.format": 'pdf',
        "savefig.bbox": 'tight'
    }
)


FONTSIZE = 14
LEGEND_FONTSIZE = 12
SAVE_PATH = os.path.join(os.getcwd(), "ej2_Resultados")
os.makedirs(SAVE_PATH, exist_ok=True)

#@title 
# def sech_sir(t,a,b,c):
#     return a*np.power(np.cosh(b*t+c),-2)

def sech_sir(x,a,b,c):
	y = a*((np.cosh(b*x+c))**(-2))
	return y

headers = ["Date", "infected", "UTI", "dead", "tests"]
df = pd.read_csv(
    "2021-tp05-covid19.csv",
    converters={"Date": str},
    names=headers,
    skiprows=1,
    error_bad_lines=False,
)

Date, infected, UTI, dead, tests = df.to_numpy()[:-11].T

"""Corrijo valores chotos"""
infected[infected == '#REF!'] = 0
infected = infected.astype(float)
UTI = UTI.astype(float)
dead = dead.astype(float)
tests = tests.astype(float)
UTI = np.nan_to_num(UTI, copy=True, nan=0)
tests = np.nan_to_num(tests, copy=True, nan=0)


fig, ax = plt.subplots()
ax.plot(infected)
ax.set_xlabel("Fecha")
ax.set_ylabel("Infectados reportados")
x = np.arange(0,len(Date),28)
ax.set_xticks(x)
ax.set_xticklabels(Date[x], rotation=40)
plt.savefig(os.path.join(SAVE_PATH, "Infectados"))
plt.show()

fig, ax = plt.subplots()
ax.plot(UTI)
ax.set_xlabel("Fecha")
ax.set_ylabel("UTI")
x = np.arange(0,len(Date),28)
ax.set_xticks(x)
ax.set_xticklabels(Date[x], rotation=40)
plt.savefig(os.path.join(SAVE_PATH, "UTI"))
plt.show()

fig, ax = plt.subplots()
ax.plot(dead)
ax.set_xlabel("Fecha")
ax.set_ylabel("Muertes reportadas")
x = np.arange(0,len(Date),28)
ax.set_xticks(x)
ax.set_xticklabels(Date[x], rotation=40)
plt.savefig(os.path.join(SAVE_PATH, "Muertes"))
plt.show()

fig, ax = plt.subplots()
ax.plot(tests)
ax.set_xlabel("Fecha")
ax.set_ylabel("Tests realizados")
x = np.arange(0,len(Date),28)
ax.set_xticks(x)
ax.set_xticklabels(Date[x], rotation=40)
plt.savefig(os.path.join(SAVE_PATH, "Tests"))
plt.show()

"""
Primero quiero suavisar la señal
"""

infected_filt = signal.savgol_filter(infected,7,1)

fig, ax = plt.subplots()
ax.plot(infected, 'k-', label='Datos')
ax.plot(infected_filt,linewidth=4, label='Suavizado')
ax.set_xlabel("Fecha")
ax.set_ylabel("Infectados reportados")
ax.legend(loc='best')
x = np.arange(0,len(Date),28)
ax.set_xticks(x)
ax.set_xticklabels(Date[x], rotation=40)
plt.savefig(os.path.join(SAVE_PATH, "Infectados_suavizado"))
plt.show()

"""
Ahora que esto ya esta suavizado, pruebo hacer el ajuste usando distinta cantidad de dias
"""

infec_1st_peak = infected_filt[:280]
date_1st_peak = Date[:280]

peak_idx = np.argmax(infec_1st_peak)

fig, ax = plt.subplots()
ax.plot(infec_1st_peak)
ax.vlines(peak_idx,0, infec_1st_peak[peak_idx],color='r',linestyle='--')
ax.annotate(date_1st_peak[peak_idx]+' (Día {})'.format(peak_idx+1), (peak_idx,0), color='red',fontsize=10, textcoords="offset points", xytext=(8,0), ha='left')
ax.set_xlabel("Dias")
# ax.set_xlabel("Fecha")
ax.set_ylabel("Infectados reportados (suavizado)")
# ax.legend(loc='best')
# x = np.arange(0,len(date_1st_peak),28)
# ax.set_xticks(x)
# ax.set_xticklabels(date_1st_peak[x], rotation=40)
plt.savefig(os.path.join(SAVE_PATH, "Pico_infectados"))
plt.show()

"""
Ahora hacemos el ajuste barriendo la cantidad de datos usados para ajustar
"""
# kk = infec_1st_peak[:200]
# dias = np.arange(len(kk))
# p0 = 5000,0.01,-1
# popt, pcov = optimize.curve_fit(sech_sir, dias, kk,p0)
# res = sech_sir(np.arange(300), *popt)
# plt.plot(np.arange(300), res), plt.show()

predicted_peaks = []

fit_result_folder = os.path.join(SAVE_PATH, "fit_results")
os.makedirs(fit_result_folder, exist_ok=True)

t0 = 120

for t_fit in np.arange(t0,len(infec_1st_peak)):
	print(t_fit, end='\r')
	infec2fit = infec_1st_peak[:t_fit]
	days = np.arange(t_fit)
	# p0 = [300, 0.02, -4]
	p0 = 5000,0.01,-1

	# Obtenemos los parametros del ajuste
	popt, pcov = optimize.curve_fit(sech_sir, days, infec2fit, p0, maxfev=10000)

	fitted_curve = sech_sir(np.arange(len(infec_1st_peak)), *popt)
	peak_pred = np.argmax(fitted_curve)
	predicted_peaks.append(peak_pred)

	fig, ax = plt.subplots()
	ax.set_title(r"$t_f = {}$".format(t_fit))
	ax.plot(infec_1st_peak, 'b', label="Datos filtrados")
	ax.vlines(peak_idx,0, infec_1st_peak[peak_idx], color='k',linestyle='--')
	ax.plot(fitted_curve, 'r', label="Ajuste")
	ax.vlines(peak_pred,0, fitted_curve[peak_pred], color='k',linestyle='--')
	ax.set_xlabel("Dias")
	# ax.set_xlabel("Fecha")
	ax.set_ylabel("Infectados reportados (suavizado)")
	ax.legend(loc='best')
	plt.savefig(os.path.join(fit_result_folder, "Ajuste_tfit={}".format(t_fit)))
	plt.close()

ts_fit = np.arange(t0,len(infec_1st_peak))
# days = np.arange(len(infec_1st_peak))
fig, ax = plt.subplots()
ax.plot(ts_fit, np.array(predicted_peaks),  'r--', label="Picos predichos")
ax.plot(ts_fit,np.full_like(ts_fit,peak_idx),'--b',label='Pico real')

ax.set_ylim(-2, 300)
ax.set_xlabel(r"$t_{fit}$")
ax.set_ylabel("Dia picos de infectados")
ax.legend(loc='best')
plt.savefig(os.path.join(SAVE_PATH, "Pico_infectados_ajuste"))
plt.show()