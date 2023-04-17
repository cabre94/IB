#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
date: 22-10-2020
File: ej_10_AlexNet.py
Author : Facundo Martin Cabrera
Email: cabre94@hotmail.com facundo.cabrera@ib.edu.ar
GitHub: https://github.com/cabre94
GitLab: https://gitlab.com/cabre94
Description: 
https://machinelearningmastery.com/how
-to-configure-image-data-augmentation-when-training
-deep-learning-neural-networks/
"""

import argparse
import os
import numpy as np
from matplotlib import pyplot as plt

# Script propio para pasar argumentos por linea de comandos
from CLArg import lr, rf, epochs, batch_size, description
from CLArg import dataset

from sklearn.model_selection import train_test_split
from tensorflow.keras.datasets import cifar10, cifar100

import tensorflow as tf
from tensorflow import keras
from tensorflow.keras import layers, activations, regularizers
from tensorflow.keras import losses, metrics, optimizers
from tensorflow.keras.regularizers import l2

from tensorflow.keras.preprocessing.image import ImageDataGenerator

# Importo los datos
if dataset == 'cifar10':
    (x_train, y_train), (x_test, y_test) = cifar10.load_data()
    n_classes = 10
elif dataset == 'cifar100':
    (x_train, y_train), (x_test, y_test) = cifar100.load_data()
    n_classes = 100

# Los junto porque quiero splitearlos distinto
x_train, y_train = np.vstack((x_train, x_test)), np.vstack((y_train, y_test))
# Separo los datos de test
x_train, x_test, y_train, y_test = train_test_split(x_train,
                                                    y_train,
                                                    test_size=9000,
                                                    stratify=y_train)
# Ahora separo entre training y validacion
x_train, x_val, y_train, y_val = train_test_split(x_train,
                                                  y_train,
                                                  test_size=9000,
                                                  stratify=y_train)

# Normalizacion
media = x_train.mean(axis=0)
sigma = x_train.std(axis=0)

x_train = x_train - media
x_train /= sigma
x_test = x_test - media
x_test /= sigma
x_val = x_val - media
x_val /= sigma

# Paso los labels a one-hot encoded
y_train = keras.utils.to_categorical(y_train, n_classes)
y_test = keras.utils.to_categorical(y_test, n_classes)
y_val = keras.utils.to_categorical(y_val, n_classes)

# Arquitectura de la mini-AlexNet
model = keras.models.Sequential(name='Mini-VGG16')

model.add(layers.Input(shape=(32, 32, 3)))

model.add(layers.Conv2D(64, 3, strides=1, activation='relu', padding='same'))
model.add(layers.BatchNormalization())
model.add(layers.Conv2D(64, 3, strides=1, activation='relu', padding='same'))
model.add(layers.BatchNormalization())

model.add(layers.MaxPool2D(2, strides=2))

model.add(layers.Conv2D(128, 3, strides=1, activation='relu', padding='same'))
model.add(layers.BatchNormalization())
model.add(layers.Conv2D(128, 3, strides=1, activation='relu', padding='same'))
model.add(layers.BatchNormalization())

model.add(layers.MaxPool2D(2, strides=2))

model.add(layers.Conv2D(256, 3, strides=1, activation='relu', padding='same'))
model.add(layers.BatchNormalization())
model.add(layers.Conv2D(256, 3, strides=1, activation='relu', padding='same'))
model.add(layers.BatchNormalization())
model.add(layers.Conv2D(256, 3, strides=1, activation='relu', padding='same'))
model.add(layers.BatchNormalization())

model.add(layers.MaxPool2D(2, strides=1))

model.add(layers.Conv2D(512, 3, strides=1, activation='relu', padding='same'))
model.add(layers.BatchNormalization())
model.add(layers.Conv2D(512, 3, strides=1, activation='relu', padding='same'))
model.add(layers.BatchNormalization())
model.add(layers.Conv2D(512, 3, strides=1, activation='relu', padding='same'))
model.add(layers.BatchNormalization())

model.add(layers.MaxPool2D(2, strides=1))

model.add(layers.Conv2D(512, 3, strides=1, activation='relu', padding='same'))
model.add(layers.BatchNormalization())
model.add(layers.Conv2D(512, 3, strides=1, activation='relu', padding='same'))
model.add(layers.BatchNormalization())
model.add(layers.Conv2D(512, 3, strides=1, activation='relu', padding='same'))
model.add(layers.BatchNormalization())

model.add(layers.MaxPool2D(2, strides=1))

model.add(layers.Flatten())
model.add(layers.Dropout(0.3))
model.add(layers.BatchNormalization())
model.add(layers.Dense(1024, activation='relu', kernel_regularizer=l2(rf)))
model.add(layers.Dropout(0.3))
model.add(layers.BatchNormalization())
model.add(layers.Dense(512, activation='relu', kernel_regularizer=l2(rf)))
model.add(layers.Dropout(0.3))
model.add(layers.BatchNormalization())
model.add(layers.Dense(512, activation='relu', kernel_regularizer=l2(rf)))
model.add(layers.Dense(n_classes, activation='linear'))


model.summary()

model.compile(optimizer=optimizers.Adam(learning_rate=lr),
              loss=losses.CategoricalCrossentropy(from_logits=True),
              metrics=[metrics.CategoricalAccuracy(name='CAcc')])

IDG = ImageDataGenerator(
    rotation_range=45,  # Ang max de rotaciones
    width_shift_range=5,    # Cant de pixeles que puede trasladarse, sepuede pasar una
    height_shift_range=5,   # fraccion de la dimension en vez de un entero
    # brightness_range=[0.5, 1.5],  # Cuanto puede variar el brillo, si lo uso todo da mal
    shear_range=0.,     # No entendi que es
    zoom_range=0.,      # Por lo que vi, queda re feo asi que no lo uso
    fill_mode='nearest',    # Estrategia para llenar los huecos
    horizontal_flip=True,   # Reflexion horizontal b -> d
    vertical_flip=False,    # Reflexion vertical   ! -> ¡
    # Con esto alcanza creo, el resto no tengo tan claro como funciona
    # y prefiero dejarlo asi
)

# Only required if featurewise_center or featurewise_std_normalization
# or zca_whitening are set to True.
# IDG.fit(x_train)

hist = model.fit(IDG.flow(x_train, y_train, batch_size=batch_size),
                 epochs=epochs,
                 steps_per_epoch=len(x_train) / batch_size,
                 validation_data=(x_val, y_val),
                 verbose=2)

# Calculo la loss y Accuracy para los datos de test
test_loss, test_Acc = model.evaluate(x_test, y_test)

data_folder = os.path.join('Datos', '10_VGG16_' + dataset)
if not os.path.exists(data_folder):
    os.makedirs(data_folder)
model.save(os.path.join(data_folder, '{}.h5'.format(description)))
np.save(os.path.join(data_folder, '{}.npy'.format(description)), hist.history)

# Guardo las imagenes
img_folder = os.path.join('Figuras', '10_VGG16_' + dataset)
if not os.path.exists(img_folder):
    os.makedirs(img_folder)

# Grafico
plt.plot(hist.history['loss'], label="Loss Training")
plt.plot(hist.history['val_loss'], label="Loss Validation")
plt.title("Acc Test: {:.3f}".format(test_Acc))
plt.xlabel("Epocas", fontsize=15)
plt.ylabel("Loss", fontsize=15)
plt.legend(loc='best')
plt.tight_layout()
plt.savefig(os.path.join(img_folder, 'Loss_{}.png'.format(description)),
            format="png",
            bbox_inches="tight")
plt.close()

plt.plot(hist.history['CAcc'], label="Acc. Training")
plt.plot(hist.history['val_CAcc'], label="Acc. Validation")
plt.title("Acc Test: {:.3f}".format(test_Acc))
plt.xlabel("Epocas", fontsize=15)
plt.ylabel("Accuracy", fontsize=15)
plt.legend(loc='best')
plt.tight_layout()
plt.savefig(os.path.join(img_folder, 'Acc_{}.png'.format(description)),
            format="png",
            bbox_inches="tight")
plt.close()
