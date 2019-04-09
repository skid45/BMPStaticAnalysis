# coding: utf-8
from matplotlib import pyplot as plt


#4b
f_R = open('C:/Users/akopo/source/repos/misoi1/misoi1/R_corr_coef', 'r')
f_G = open('C:/Users/akopo/source/repos/misoi1/misoi1/G_corr_coef', 'r')
f_B = open('C:/Users/akopo/source/repos/misoi1/misoi1/B_corr_coef', 'r')

array_R = []
array_G = []
array_B = []

for line in f_R:
    array_R.append([float(x) for x in line.split()])
for line in f_G:
    array_G.append([float(x) for x in line.split()])
for line in f_B:
    array_B.append([float(x) for x in line.split()])


mult = 4


plt.figure()
plt.plot(range(0, len(array_R[0]) * mult, mult), array_R[0], label="y = -10")
plt.plot(range(0, len(array_R[1]) * mult, mult), array_R[1], label="y = -5")
plt.plot(range(0, len(array_R[2]) * mult, mult), array_R[2], label="y = 0")
plt.plot(range(0, len(array_R[3]) * mult, mult), array_R[3], label="y = 5")
plt.plot(range(0, len(array_R[4]) * mult, mult), array_R[4], label="y = 10")
plt.title("R")
plt.xlabel('Значения Х')
plt.ylabel('Значения корреляции')
plt.legend()


plt.figure()
plt.plot(range(0, len(array_G[0]) * mult, mult), array_G[0], label="y = -10")
plt.plot(range(0, len(array_G[1]) * mult, mult), array_G[1], label="y = -5")
plt.plot(range(0, len(array_G[2]) * mult, mult), array_G[2], label="y = 0")
plt.plot(range(0, len(array_G[3]) * mult, mult), array_G[3], label="y = 5")
plt.plot(range(0, len(array_G[4]) * mult, mult), array_G[4], label="y = 10")
plt.title("G")
plt.xlabel('Значения Х')
plt.ylabel('Значения корреляции')
plt.legend()


plt.figure()
plt.plot(range(0, len(array_B[0]) * mult, mult), array_B[0], label="y = -10")
plt.plot(range(0, len(array_B[1]) * mult, mult), array_B[1], label="y = -5")
plt.plot(range(0, len(array_B[2]) * mult, mult), array_B[2], label="y = 0")
plt.plot(range(0, len(array_B[3]) * mult, mult), array_B[3], label="y = 5")
plt.plot(range(0, len(array_B[4]) * mult, mult), array_B[4], label="y = 10")
plt.title("B")
plt.xlabel('Значения Х')
plt.ylabel('Значения корреляции')
plt.legend()



#12
f_hist12R = open('C:/Users/akopo/source/repos/misoi1/misoi1/histogramR', 'r')
f_hist12G = open('C:/Users/akopo/source/repos/misoi1/misoi1/histogramG', 'r')
f_hist12B = open('C:/Users/akopo/source/repos/misoi1/misoi1/histogramB', 'r')
f_hist12Y = open('C:/Users/akopo/source/repos/misoi1/misoi1/histogramY', 'r')
f_hist12Cb = open('C:/Users/akopo/source/repos/misoi1/misoi1/histogramCb', 'r')
f_hist12Cr = open('C:/Users/akopo/source/repos/misoi1/misoi1/histogramCr', 'r')

array_hist12R = []
array_hist12G = []
array_hist12B = []
array_hist12Y = []
array_hist12Cb = []
array_hist12Cr = []

for line in f_hist12R:
    array_hist12R.append([int(x) for x in line.split()])
for line in f_hist12G:
    array_hist12G.append([int(x) for x in line.split()])
for line in f_hist12B:
    array_hist12B.append([int(x) for x in line.split()])
for line in f_hist12Y:
    array_hist12Y.append([int(x) for x in line.split()])
for line in f_hist12Cb:
    array_hist12Cb.append([int(x) for x in line.split()])
for line in f_hist12Cr:
    array_hist12Cr.append([int(x) for x in line.split()])


plt.figure()
plt.hist(array_hist12R[0], alpha=0.6, color='r', bins=range(0, 256), label="R")
plt.hist(array_hist12G[0], alpha=0.6, color='g', bins=range(0, 256), label="G")
plt.hist(array_hist12B[0], alpha=0.6, color='b', bins=range(0, 256), label="B")
plt.title("Гистограммы R, G и B")
plt.legend()


plt.figure()
plt.hist(array_hist12Y[0], alpha=0.6, color='y', bins=range(0, 256), label="Y")
plt.hist(array_hist12Cb[0], alpha=0.6, color='c', bins=range(0, 256), label="Cb")
plt.hist(array_hist12Cr[0], alpha=0.6, color='m', bins=range(0, 256), label="Cr")
plt.title("Гистограммы Y, Cb и Cr")
plt.legend()


f_hist15R1 = open('C:/Users/akopo/source/repos/misoi1/misoi1/DR1', 'r')
f_hist15R2 = open('C:/Users/akopo/source/repos/misoi1/misoi1/DR2', 'r')
f_hist15R3 = open('C:/Users/akopo/source/repos/misoi1/misoi1/DR3', 'r')
f_hist15R4 = open('C:/Users/akopo/source/repos/misoi1/misoi1/DR4', 'r')
f_hist15G1 = open('C:/Users/akopo/source/repos/misoi1/misoi1/DG1', 'r')
f_hist15G2 = open('C:/Users/akopo/source/repos/misoi1/misoi1/DG2', 'r')
f_hist15G3 = open('C:/Users/akopo/source/repos/misoi1/misoi1/DG3', 'r')
f_hist15G4 = open('C:/Users/akopo/source/repos/misoi1/misoi1/DG4', 'r')
f_hist15B1 = open('C:/Users/akopo/source/repos/misoi1/misoi1/DB1', 'r')
f_hist15B2 = open('C:/Users/akopo/source/repos/misoi1/misoi1/DB2', 'r')
f_hist15B3 = open('C:/Users/akopo/source/repos/misoi1/misoi1/DB3', 'r')
f_hist15B4 = open('C:/Users/akopo/source/repos/misoi1/misoi1/DB4', 'r')
f_hist15Y1 = open('C:/Users/akopo/source/repos/misoi1/misoi1/DY1', 'r')
f_hist15Y2 = open('C:/Users/akopo/source/repos/misoi1/misoi1/DY2', 'r')
f_hist15Y3 = open('C:/Users/akopo/source/repos/misoi1/misoi1/DY3', 'r')
f_hist15Y4 = open('C:/Users/akopo/source/repos/misoi1/misoi1/DY4', 'r')
f_hist15Cb1 = open('C:/Users/akopo/source/repos/misoi1/misoi1/DCb1', 'r')
f_hist15Cb2 = open('C:/Users/akopo/source/repos/misoi1/misoi1/DCb2', 'r')
f_hist15Cb3 = open('C:/Users/akopo/source/repos/misoi1/misoi1/DCb3', 'r')
f_hist15Cb4 = open('C:/Users/akopo/source/repos/misoi1/misoi1/DCb4', 'r')
f_hist15Cr1 = open('C:/Users/akopo/source/repos/misoi1/misoi1/DCR1', 'r')
f_hist15Cr2 = open('C:/Users/akopo/source/repos/misoi1/misoi1/DCR2', 'r')
f_hist15Cr3 = open('C:/Users/akopo/source/repos/misoi1/misoi1/DCr3', 'r')
f_hist15Cr4 = open('C:/Users/akopo/source/repos/misoi1/misoi1/DCr4', 'r')


array_hist15R1 = []
array_hist15R2 = []
array_hist15R3 = []
array_hist15R4 = []
array_hist15G1 = []
array_hist15G2 = []
array_hist15G3 = []
array_hist15G4 = []
array_hist15B1 = []
array_hist15B2 = []
array_hist15B3 = []
array_hist15B4 = []
array_hist15Y1 = []
array_hist15Y2 = []
array_hist15Y3 = []
array_hist15Y4 = []
array_hist15Cb1 = []
array_hist15Cb2 = []
array_hist15Cb3 = []
array_hist15Cb4 = []
array_hist15Cr1 = []
array_hist15Cr2 = []
array_hist15Cr3 = []
array_hist15Cr4 = []


for line in f_hist15R1:
    array_hist15R1.append([int(x) for x in line.split()])
for line in f_hist15R2:
    array_hist15R2.append([int(x) for x in line.split()])
for line in f_hist15R3:
    array_hist15R3.append([int(x) for x in line.split()])
for line in f_hist15R4:
    array_hist15R4.append([int(x) for x in line.split()])

for line in f_hist15G1:
    array_hist15G1.append([int(x) for x in line.split()])
for line in f_hist15G2:
    array_hist15G2.append([int(x) for x in line.split()])
for line in f_hist15G3:
    array_hist15G3.append([int(x) for x in line.split()])
for line in f_hist15G4:
    array_hist15G4.append([int(x) for x in line.split()])

for line in f_hist15B1:
    array_hist15B1.append([int(x) for x in line.split()])
for line in f_hist15B2:
    array_hist15B2.append([int(x) for x in line.split()])
for line in f_hist15B3:
    array_hist15B3.append([int(x) for x in line.split()])
for line in f_hist15B4:
    array_hist15B4.append([int(x) for x in line.split()])

for line in f_hist15Y1:
    array_hist15Y1.append([int(x) for x in line.split()])
for line in f_hist15Y2:
    array_hist15Y2.append([int(x) for x in line.split()])
for line in f_hist15Y3:
    array_hist15Y3.append([int(x) for x in line.split()])
for line in f_hist15Y4:
    array_hist15Y4.append([int(x) for x in line.split()])

for line in f_hist15Cb1:
    array_hist15Cb1.append([int(x) for x in line.split()])
for line in f_hist15Cb2:
    array_hist15Cb2.append([int(x) for x in line.split()])
for line in f_hist15Cb3:
    array_hist15Cb3.append([int(x) for x in line.split()])
for line in f_hist15Cb4:
    array_hist15Cb4.append([int(x) for x in line.split()])

for line in f_hist15Cr1:
    array_hist15Cr1.append([int(x) for x in line.split()])
for line in f_hist15Cr2:
    array_hist15Cr2.append([int(x) for x in line.split()])
for line in f_hist15Cr3:
    array_hist15Cr3.append([int(x) for x in line.split()])
for line in f_hist15Cr4:
    array_hist15Cr4.append([int(x) for x in line.split()])

plt.figure()
plt.hist(array_hist15R1[0], color='r', bins=range(-100, 100), label="R")
plt.hist(array_hist15G1[0], rwidth=0.75, color='g', bins=range(-100, 100), label="G")
plt.hist(array_hist15B1[0], rwidth=0.5, color='b', bins=range(-100, 100), label="B")
plt.title("Гистограммы массивов разностей компонент R, G и B для правила 1")
plt.legend()

plt.figure()
plt.hist(array_hist15Y1[0], color='y', bins=range(-100, 100), label="Y")
plt.hist(array_hist15Cb1[0], rwidth=0.75, color='c', bins=range(-100, 100), label="Cb")
plt.hist(array_hist15Cr1[0], rwidth=0.5, color='m', bins=range(-100, 100), label="Cr")
plt.title("Гистограммы массивов разностей компонент Y, Cb и Cr для правила 1")
plt.legend()


plt.figure()
plt.hist(array_hist15R2[0], color='r', bins=range(-100, 100), label="R")
plt.hist(array_hist15G2[0], rwidth=0.75, color='g', bins=range(-100, 100), label="G")
plt.hist(array_hist15B2[0], rwidth=0.5, color='b', bins=range(-100, 100), label="B")
plt.title("Гистограммы массивов разностей компонент R, G и B для правила 2")
plt.legend()

plt.figure()
plt.hist(array_hist15Y2[0], color='y', bins=range(-100, 100), label="Y")
plt.hist(array_hist15Cb2[0], rwidth=0.75, color='c', bins=range(-100, 100), label="Cb")
plt.hist(array_hist15Cr2[0], rwidth=0.5, color='m', bins=range(-100, 100), label="Cr")
plt.title("Гистограммы массивов разностей компонент Y, Cb и Cr для правила 2")
plt.legend()


plt.figure()
plt.hist(array_hist15R3[0], color='r', bins=range(-100, 100), label="R")
plt.hist(array_hist15G3[0], rwidth=0.75, color='g', bins=range(-100, 100), label="G")
plt.hist(array_hist15B3[0], rwidth=0.5, color='b', bins=range(-100, 100), label="B")
plt.title("Гистограммы массивов разностей компонент R, G и B для правила 3")
plt.legend()

plt.figure()
plt.hist(array_hist15Y3[0], color='y', bins=range(-100, 100), label="Y")
plt.hist(array_hist15Cb3[0], rwidth=0.75, color='c', bins=range(-100, 100), label="Cb")
plt.hist(array_hist15Cr3[0], rwidth=0.5, color='m', bins=range(-100, 100), label="Cr")
plt.title("Гистограммы массивов разностей компонент Y, Cb и Cr для правила 3")
plt.legend()


plt.figure()
plt.hist(array_hist15R4[0], color='r', bins=range(-100, 100), label="R")
plt.hist(array_hist15G4[0], rwidth=0.75, color='g', bins=range(-100, 100), label="G")
plt.hist(array_hist15B4[0], rwidth=0.5, color='b', bins=range(-100, 100), label="B")
plt.title("Гистограммы массивов разностей компонент R, G и B для правила 4")
plt.legend()

plt.figure()
plt.hist(array_hist15Y4[0], color='y', bins=range(-100, 100), label="Y")
plt.hist(array_hist15Cb4[0], rwidth=0.75, color='c', bins=range(-100, 100), label="Cb")
plt.hist(array_hist15Cr4[0], rwidth=0.5, color='m', bins=range(-100, 100), label="Cr")
plt.title("Гистограммы массивов разностей компонент Y, Cb и Cr для правила 4")
plt.legend()


plt.show()
