import math as m
import pygame


interation_MAX = 200# nombre d'itérations maximales avant de considérer que la suite converge

# bornes du repère
XMIN = -1.25
XMAX = 1.25
YMIN = -1.25
YMAX = 1.25

# taille de la fenêtre en pixels
LARGEUR= 500
HAUTEUR = 500

#fonction pour calculer le module d'un nombre complexe
def module(x, y):
    return m.sqrt(x**2 + y**2)

# Initialisation et création d'une fenêtre aux dimensions spécifiéés munie d'un titre
pygame.init()
screen = pygame.display.set_mode((LARGEUR, HAUTEUR))
pygame.display.set_caption("Fractale de Julia")

a = -0.5
b =  0.6
for x in range(LARGEUR):
    for y in range(HAUTEUR):
        # Les deux lignes suivantes permettent d'associer à chaque pixel de l'écran de coordonnées (x;y)
        i = 0
        xn = ((XMIN+y) * (XMAX-XMIN)) /LARGEUR + XMIN
        yn = ((XMIN-x) * (YMAX - YMIN)) / HAUTEUR +YMAX

        while module(xn, yn)<=2 and i<=interation_MAX:
            tmp = xn
            xn = xn**2 - yn**2 + a
            yn = 2*tmp*yn + b
            i+=1
        if module(xn, yn)<=2 and i>interation_MAX:
            screen.set_at((x, y), (0, 0, 0))  # On colore le pixel en noir -> code RGB : (0,0,0)
        else:
            screen.set_at((x, y), (255, 255, 255))  # On colore le pixel en blanc -> code RGB : (255,255,255)
            #screen.set_at((x, y), ((9 * i) % 256, (9 * i) % 256, (10 * i) % 256))

pygame.display.flip()  # Mise à jour et rafraîchissement de la fenêtre graphique pour affichage
# Boucle infinie permettant d'afficher à l'écran la fenêtre graphique
# Sans ça, la fenêtre apparaît et disparaît aussitôt
loop = True
while loop:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:  # Pour quitter l'application en fermant la fenêtre
            loop = False
pygame.quit()