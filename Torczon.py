import numpy as np
from tkinter import *
import math
import random
from matplotlib import *
from matplotlib import pyplot
import matplotlib.pyplot as plt
#creer une première fenêtre
window = Tk()

#personnaliser cette fenêtre
window.title("Torczon")
window.geometry("1080x720")
window.config(background = '#B398D3')
canvas = Canvas(window, width = 1000, height = 700, bg = "white", highlightthickness = 0)
canvas.pack(pady = 20)


def function(x):
    #return x[0] ** 2 + x[1]** 2
    return 100 * (x[1] - (x[0] ** 2)) ** 2 + (1 - x[0]) ** 2 #rosenbrock
    #return 2*x[0]*x[1]*math.exp(-(4*(x[0]**2)+x[1])/8)
    #return 6*x[0]**2+x[1]+x[1]**2

def function2(x):
    return 2 * x[0] * x[1] * math.exp(-(4 * (x[0] ** 2) + x[1]) / 8)

def F(fct ,ensemble):
    f_S = np.zeros(3)
    for i in range(0, 3):
        f_S[i] = fct(ensemble[i])
    return f_S


def reflexion(S0):
    Sr = np.zeros((3, 2))
    Sr[0] = S0[0]
    for i in range(1, 3):
        Sr[i] = 2 * S0[0] - S0[i]
    return Sr


def expension(S0):
    Se = np.zeros((3, 2))
    Se[0] = S0[0]
    for i in range(1, 3):
        Se[i] = 3 * S0[0] - 2 * S0[i]
    return Se


def contraction(S0):
    Sc = np.zeros((3, 2))
    Sc[0] = S0[0]
    for i in range(1, 3):
        Sc[i] = 0.5 * (S0[0] + S0[i])
    return Sc



#simplexe = np.array([[1, 1], [(1+math.sqrt(33))/8, (1-math.sqrt(33))/8], [0, 0]])
simplexe = np.array([[9, 0], [1, 0], [0, 1]])

#algo de torczon
def Torczon(simplexe, fct, epsilon):
    norm = 1  # initialiser norm à 1 pour rentrer dans l'algo
    eps = epsilon  # precision de l'algo
    S0 = simplexe
    canvas.create_line(S0[0][0] * 100 + (200), S0[0][1] * 100 + (200), S0[1][0] * 100 + (200),
                       S0[1][1] * 100 + (200),
                       S0[2][0] * 100 + (200), S0[2][1] * 100 + (200), S0[0][0] * 100 + (200),
                       S0[0][1] * 100 + (200), fill="black", width = 4)
    while (norm > eps):
        # etape 1
        Sr = reflexion(S0)
        #canvas.create_line(Sr[0][0] + (100), Sr[0][1]+(100), S0[1][0]+(100), S0[1][1] + (100), S0[2][0] + (100), S0[2][1]+ (100), Sr[0][0] + (100), Sr[0][1]+(100),fill="pink")
        FSr = F(fct, Sr)
        FS0 = F(fct, S0)
        minFSr = np.min(FSr)
        minFx1 = np.min(FS0)
        if (minFSr < minFx1):
            # etape 2.a)
            Se = expension(S0)
            #canvas.create_line(Se[0][0] * (100), Se[0][1] * (100), Se[1][0] * (100), Se[1][1] * (100), Se[2][0] * (100),
                              #Se[2][1] * (100), Se[0][0] * (100), Se[0][1]*(100),fill="pink")
            FSe = F(fct, Se)
            minFSe = np.min(FSe)
            if (minFSe < minFSr):
                # etape 2.b)
                S0 = Se
                canvas.create_line(S0[0][0] * 100 + (200), S0[0][1] * 100 + (200), S0[1][0] * 100 + (200),
                                   S0[1][1] * 100 + (200),
                                   S0[2][0] * 100 + (200), S0[2][1] * 100 + (200), S0[0][0] * 100 + (200),
                                   S0[0][1] * 100 + (200),fill="red", width = 4)
            else:
                # etape 2.c)
                S0 = Sr
                canvas.create_line(S0[0][0] * 100 + (200), S0[0][1] * 100 + (200), S0[1][0] * 100 + (200),
                       S0[1][1] * 100 + (200),
                       S0[2][0] * 100 + (200), S0[2][1] * 100 + (200), S0[0][0] * 100 + (200),
                       S0[0][1] * 100 + (200), fill="pink", width = 4)
        else:
            # etape 3
            S0 = contraction(S0)
            canvas.create_line(S0[0][0] * 100 + (200), S0[0][1] * 100 + (200), S0[1][0] * 100 + (200),
                               S0[1][1] * 100 + (200),
                               S0[2][0] * 100 + (200), S0[2][1] * 100 + (200), S0[0][0] * 100 + (200),
                               S0[0][1] * 100 + (200), fill="blue", width = 4)
        # etape 4
        S1 = S0.copy()

        # etape 5
        FS0 = F(fct, S0)
        minFS0 = np.min(FS0)
        indicemin = np.where(FS0 == minFS0)
        maxFS0 = np.max(FS0)
        indicemax = np.where(FS0 == maxFS0)
        indiceinter = np.where((FS0 != minFS0) & (FS0 != maxFS0))
        S0[0] = S1[indicemin[0][0]]
        S0[2] = S1[indicemax[0][0]]
        if (len(indiceinter[0]) == 0):
            S0[1] = S1[indicemin[0][0]]
        else:
            S0[1] = S1[indiceinter[0][0]]
        norm = np.linalg.norm(S0[2] - S0[1])# recalcul du critère d'arrêt
        #norm => c'est la norme des deux pts extreme du simplexe

        print("x = [%.8f,%.8f]  F(x) = %.8f  norme = %.8f \n" % (S0[0][0],S0[0][1], fct(S0[0]), norm))
    return S0[0]

'''
from time import time

temps = np.zeros((2, 100))
mult_function=[function, function2]

j = 0
for function in mult_function:
    for i in range(100):
        t1 = time()
        Torczon(simplexe, function,10**(-6))
        t2 = time()
        temps[j][i] = t2-t1
    j += 1

y1 = temps[0]
y2 = temps[1]


plt.plot(range(100), y1)#profile de temps d'execution en seconde
plt.plot(range(100), y2)

# la complexite de l'algo change en fct de la fontion à étudier choisit , donc le temps de calcul aussi
# on ne peut donc pas vraiment savoir la complexité de l'algo

plt.show()

'''



print("Vecteur x* = ", Torczon(simplexe, function,10**(-6)))




"""
def tester() :
	#tableau= [ random.randint( 0, 10*n) for i in range(0, n)]
	tdebut= time()
	Torczon(simplexe, 10**(-6))
	tfin = time()
	return tfin - tdebut

x=[ 2**i for i in range( 0, 20) ]
y=[ tester() for i in range( 0, len(x)) ]

plt.plot(x,y, "bo-",  label="Torczon: abcisse n, ordonnée T(n)")
plt.xlabel( "n")
plt.ylabel( "T(n)")
plt.legend()
plt.show()

logx= [ math.log( x[i])/math.log(2.) for i in range( 0, len(x))]
logy= [ math.log( y[i])/math.log(2.) for i in range( 0, len(y))]
plt.plot(logx,logy, "ro-",  label='Torczon: abcisse log(n), ordonnée log( T(n))')
plt.axis( "equal")
plt.xlabel( "log n")
plt.ylabel( "log T(n)")
plt.legend()
#plt.xlim( ...,...)
#plt.ylim( ...,...)
plt.show()


#print("Minimum de la fonction: f(x*) = ", function(Torczon(simplexe, 10**(-6))))
"""
#l'afficher
window.mainloop()

