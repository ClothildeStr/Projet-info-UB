import math as m
import pygame


interation_MAX = 50# nombre d'itérations maximales avant de considérer que la suite converge

# bornes du repère
XMIN = -2
XMAX = 0.5
YMIN = -1.25
YMAX = 1.25


# test pour utilisés pour différents affichage pour créer la vidéo
#XMIN, XMAX, YMIN, YMAX = -2, 0.5, -1.25, 1.25
#XMIN, XMAX, YMIN, YMAX = -2, 0.25, -1, 1
#XMIN, XMAX, YMIN, YMAX = -2, 0, -0.75, 0.75
#XMIN, XMAX, YMIN, YMAX = -2, -0.25, -0.5, 0.5
#XMIN, XMAX, YMIN, YMAX = -2, -0.5, -0.25, 0.25
#XMIN, XMAX, YMIN, YMAX = -2, -1, -0.25, 0.25
#XMIN, XMAX, YMIN, YMAX = -2, -1.25, -0.25, 0.25
#XMIN, XMAX, YMIN, YMAX = -2, -1.5, -0.25, 0.25
#XMIN, XMAX, YMIN, YMAX = -2, -1.5, -0.2, 0.2
#XMIN, XMAX, YMIN, YMAX = -2, -1.6, -0.15, 0.15
#XMIN, XMAX, YMIN, YMAX = -1.9, -1.65, -0.1, 0.1
#XMIN, XMAX, YMIN, YMAX = -1.8, -1.7, -0.05, 0.05
#XMIN, XMAX, YMIN, YMAX = -1.82, -1.72, -0.03, 0.03
#XMIN, XMAX, YMIN, YMAX = -1.82, -1.72, -0.02, 0.02



# taille de la fenêtre en pixels
LARGEUR= 500
HAUTEUR = 500

# Initialisation et création d'une fenêtre aux dimensions spécifiéés munie d'un titre
pygame.init()
screen = pygame.display.set_mode((LARGEUR, HAUTEUR))
pygame.display.set_caption("Fractale de Mandelbrot")


#fonction pour calculer le module d'un nombre complexe
def module(x, y):
    return m.sqrt(x**2 + y**2)

# Création de l'ensemble de Mandelbrot
# Principe : on balaye l'écran pixel par pixel en convertissant le pixel en un point du plan de notre repère
# Si la suite converge, le point appartient à l'ensemble de Mandelbrot et on colore le pixel en noir
# Sinon la suite diverge, le point n'appartient pas à l'ensemble et on colore le pixel en blanc

def Mandelbrot(XMIN, XMAX, YMIN, YMAX, HAUTEUR, LARGEUR):
    for x in range(LARGEUR):
        for y in range(HAUTEUR):
            # Les deux lignes suivantes permettent d'associer à chaque pixel de l'écran de coordonnées (x;y)
            # un point C du plan de coordonnées (x;y) dans le repère défini par XMIN:XMAX et YMIN:YMAX
            cx = ((x * (XMAX - XMIN)) / (LARGEUR) + XMIN)
            cy = ((y * (YMIN - YMAX)) / (HAUTEUR) + YMAX)
            xn = 0
            yn = 0
            n = 0

            while module(xn, yn)<2 and n<interation_MAX:
                tmp_x = xn
                tmp_y = yn
                xn = tmp_x * tmp_x - tmp_y * tmp_y + cx
                yn = 2 * tmp_x * tmp_y + cy
                n = n + 1

            if n == interation_MAX:
                screen.set_at((x, y), (0, 0, 0))  # On colore le pixel en noir -> code RGB : (0,0,0)
            else:
                #screen.set_at((x, y), (255, 255, 255))
                # On colore le pixel en blanc -> code RGB : (255,255,255)
                # on colore en couleur
                screen.set_at((x, y), ((3 * n) % 256, (1 * n) % 256, (10 * n) % 256))

    pygame.display.flip()  # Mise à jour et rafraîchissement de la fenêtre graphique pour affichage

# Boucle infinie permettant d'afficher à l'écran la fenêtre graphique
# Sans ça, la fenêtre apparaît et disparaît aussitôt

Mandelbrot(XMIN, XMAX, YMIN, YMAX, HAUTEUR, LARGEUR)

loop = True
while loop:
  for event in pygame.event.get():
    if event.type == pygame.QUIT: # Pour quitter l'application en fermant la fenêtre
      loop = False
    elif event.type == pygame.MOUSEBUTTONDOWN:
      p = pygame.mouse.get_pos()
      px = (p[0] * (XMAX - XMIN) / LARGEUR + XMIN)
      py = (p[1] * (YMIN - YMAX) / HAUTEUR + YMAX)
      print("({};{})".format(px,py))
pygame.quit()