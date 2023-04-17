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

import matplotlib.pyplot as plt
import matplotlib as mpl
# import plt.style.use("seaborn")
mpl.rcParams.update(
    {
        "font.size": 18,
        "axes.labelsize": 16,
        "axes.titlesize": 18,
        "legend.fontsize": 15,
        "xtick.labelsize": 12,
        "ytick.labelsize": 12,
        "figure.figsize": [9, 6.5],
        # "figure.autolayout": True,
        "font.family": "serif",
        "font.sans-serif": ["Helvetica"],
        "savefig.format": 'pdf',
        "savefig.bbox": 'tight'
    }
)

from egtplot import plot_static
C = 3
G = 1

payoff_entries = [
    [(G-C)*0.5],    [G],        [G],
    [0],            [G*0.5],    [0],
    [0],            [G],        [G*0.5]
]
labels = ['Halcones (x)','Palomas (y)','Bravucones (z)']
simplex = plot_static(payoff_entries, background=False,vert_labels=labels,display_parameters=False)
simplex.savefig("Bravucones.pdf")


payoff_entries = [
    [(G-C)*0.5],    [G],        [(G-C)*0.5],
    [0],            [G*0.5],    [G*0.5],
    [(G-C)*0.5],    [G*0.5],    [G*0.5]
]
labels = ['Halcones (x)','Palomas (y)','Vengativos (z)']
simplex = plot_static(payoff_entries, background=False,vert_labels=labels,display_parameters=False)
simplex.savefig("Vengativos.pdf")

