#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
date: 09-10-2020
File: ej_02_XOR_a.py
Author : Facundo Martin Cabrera
Email: cabre94@hotmail.com facundo.cabrera@ib.edu.ar
GitHub: https://github.com/cabre94
GitLab: https://gitlab.com/cabre94
Description:
"""

import os
import numpy as np
from matplotlib import pyplot as plt
import matplotlib as mpl
mpl.rcParams.update({
	'font.size': 20,
	'figure.figsize': [8, 6],
	'figure.autolayout': True,
	'font.family': 'serif',
	'font.sans-serif': ['Palatino']})

# Script propio para pasar argumentos por linea de comandos
from CLArg import lr, rf, epochs, batch_size, description

import tensorflow as tf
from tensorflow import keras
from tensorflow.keras import layers, activations, regularizers
from tensorflow.keras import losses, metrics, optimizers

# Datos que no son datos
x_train = np.array([[-1, -1], [-1, 1], [1, -1], [1, 1]])
y_train = np.array([[1], [-1], [-1], [1]])

# Arquitectura de la red
inputs = layers.Input(shape=(x_train.shape[1], ), name="Input")

layer_1 = layers.Dense(2, name='Hidden_1', activation=activations.tanh)(inputs)

outputs = layers.Dense(1, name='Output', activation=activations.tanh)(layer_1)

model = keras.models.Model(inputs=inputs,
                           outputs=outputs,
                           name='XOR_Arquitectura_1')


# Defino accuracy para el problema de XOR
def my_acc(y_true, y_pred):
    acc = tf.reduce_mean(
        tf.cast(tf.less_equal(tf.abs(y_true - y_pred), 0.1), tf.float32))
    return acc


model.compile(optimizer=keras.optimizers.Adam(lr),
              loss=losses.MSE,
              metrics=[my_acc])

model.summary()

hist = model.fit(x_train, y_train, epochs=epochs, verbose=2)

# Guardo los datos
data_folder = os.path.join('Datos', '2_XOR_A')
if not os.path.exists(data_folder):
    os.makedirs(data_folder)
model.save(os.path.join(data_folder, '{}.h5'.format(description)))
np.save(os.path.join(data_folder, '{}.npy'.format(description)), hist.history)

# Guardo las imagenes
img_folder = os.path.join('Figuras', '2_XOR_A')
if not os.path.exists(img_folder):
    os.makedirs(img_folder)

# Grafico
plt.plot(hist.history['loss'], label="Loss")
plt.xlabel("Epocas")
plt.ylabel("Loss")
plt.legend(loc='best')
plt.tight_layout()
plt.savefig(os.path.join(img_folder, 'Loss_{}.png'.format(description)),
            format="png",
            bbox_inches="tight")
plt.close()

plt.plot(hist.history['my_acc'], label="Accuracy")
plt.xlabel("Epocas")
plt.ylabel("Accuracy")
plt.legend(loc='best')
plt.tight_layout()
plt.savefig(os.path.join(img_folder, 'Acc_{}.png'.format(description)),
            format="png",
            bbox_inches="tight")
plt.close()