#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
date: 07-10-2020
File: ej_02_3.py
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

from tensorflow.keras.datasets import cifar10
from sklearn.model_selection import train_test_split

import tensorflow as tf
from tensorflow import keras
from tensorflow.keras import layers, activations, regularizers
from tensorflow.keras import losses, metrics, optimizers

# Cargo los datos
(x_train, y_train), (x_test, y_test) = cifar10.load_data()

# separo el training en train y validation manteniendo la distribucion (y mezclando)
x_train, x_val, y_train, y_val = train_test_split(x_train,
                                                  y_train,
                                                  test_size=0.2,
                                                  stratify=y_train)

# Hago el flatten de los datos
x_train = x_train.reshape(len(x_train), x_train[0].size).astype(np.float)
x_test = x_test.reshape(len(x_test), x_test[0].size).astype(np.float)
x_val = x_val.reshape(len(x_val), x_val[0].size).astype(np.float)

# Paso los labels a one-hot encoded
y_train = keras.utils.to_categorical(y_train, 10)
y_test = keras.utils.to_categorical(y_test, 10)
y_val = keras.utils.to_categorical(y_val, 10)

# Normalizacion
media = x_train.mean(axis=0)
sigma = x_train.std(axis=0)

x_train = x_train - media
x_train /= sigma
x_test = x_test - media
x_test /= sigma
x_val = x_val - media
x_val /= sigma

# Arquitectura de la red segun el ej3 TP2
inputs = layers.Input(shape=x_train.shape[1], name="Input")

l1 = layers.Dense(
    100,
    name='Hidden',
    activation=activations.sigmoid,
    kernel_regularizer=regularizers.l2(rf),
)(inputs)

output = layers.Dense(10,
                      name='Output',
                      activation=activations.linear,
                      kernel_regularizer=regularizers.l2(rf))(l1)

model = keras.models.Model(inputs=inputs, outputs=output, name='Ej3_TP2')

model.compile(optimizer=optimizers.Adam(lr),
              loss=losses.mean_squared_error,
              metrics=[metrics.CategoricalAccuracy(name="Acc")])

model.summary()

hist = model.fit(x_train,
                 y_train,
                 epochs=epochs,
                 validation_data=(x_val, y_val),
                 batch_size=batch_size,
                 verbose=2)

# Calculo la loss y Accuracy para los datos de test
test_loss, test_Acc = model.evaluate(x_test, y_test)

# Guardo los datos
data_folder = os.path.join('Datos', '2_EJ3_TP2')
if not os.path.exists(data_folder):
    os.makedirs(data_folder)
model.save(os.path.join(data_folder, '{}.h5'.format(description)))
np.save(os.path.join(data_folder, '{}.npy'.format(description)), hist.history)

# Grafico y guardo figuras
img_folder = os.path.join('Figuras', '2_EJ3_TP2')
if not os.path.exists(img_folder):
    os.makedirs(img_folder)

# Grafico
plt.plot(hist.history['loss'], label="Loss Training")
plt.plot(hist.history['val_loss'], label="Loss Validation")
plt.title("Acc Test: {:.3f}".format(test_Acc))
plt.xlabel("Epocas")
plt.ylabel("Loss")
plt.legend(loc='best')
plt.tight_layout()
plt.savefig(os.path.join(img_folder, 'Loss_{}.png'.format(description)),
            format="png",
            bbox_inches="tight")
plt.close()

plt.plot(hist.history['Acc'], label="Acc. Training")
plt.plot(hist.history['val_Acc'], label="Acc. Validation")
plt.title("Acc Test: {:.3f}".format(test_Acc))
plt.xlabel("Epocas")
plt.ylabel("Accuracy")
plt.legend(loc='best')
plt.tight_layout()
plt.savefig(os.path.join(img_folder, 'Acc_{}.png'.format(description)),
            format="png",
            bbox_inches="tight")
plt.close()