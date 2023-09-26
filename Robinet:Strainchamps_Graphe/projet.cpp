#include <cstdlib>
#include <iostream>
#include <cmath>
#include <new>

using namespace std;

int n; // nombre de sommets
int **adj; //[n][n];  // matrice d'adjacence du graphe
int *couleur1; //[n];  // couleurs des sommets pour l'agorithme exact
int *couleur2; //[n]; // couleurs pour DSATUR
int *DSAT; //[n]; // degr�s de saturation
int *Degre; //[n]; // degr�s des sommets
bool trouve=false; // permet de stopper l'algorithme exact
                   // quand une coloration  a ete trouvee
int nbK; //degré d'impropreté
int **sommets;


void initialiseTab(){
  adj=new int*[n]; 
    for (int i = 0; i < n; i++)
      adj[i] = new int[n]; 
    couleur1= new int[n]; couleur2 = new int[n];
    DSAT = new int[n]; Degre = new int[n];
}


void genere(int p) // genere un graphe non orient� de n sommets et probabilit� p d'ar�te entre toute paire de sommets
{
  srand(time(NULL));
  for(int i=0;i<n-1;i++)
  {
    for(int j=i+1;j<n;j++)
     if(rand()%101 <=p)
      adj[i][j]=adj[j][i]=1;
     else adj[i][j]=adj[j][i]=0;
  }
  /*for(int i=0;i<n;i++)
  { cout << "sommet " << i << " : ";
    for(int j=0;j<n;j++)
      if(adj[i][j]) cout << j << " ";
    cout << endl;
  }*/
}


bool convient(int x, int c) // teste si la couleur c peut �tre donnee au sommet x (elle n'est pas utilisee par un de ses voisins)
{
     for(int i=0;i<x;i++)
      if(adj[x][i] && (couleur1[i]==c)) return false;
     return true;
}


//utilisé pour on vérifie que le sommet x à au plus k voisins de couleur c
bool valide(int x, int c, int k){
	int cpt = 0;
	for(int j = 0; j<n; j++){
		if(adj[x][j] && (couleur2[j]==c)){ //si j est un voisin de couleur c de i
			cpt++;
			if(cpt > k) return false;
		}
	}
	return true;
} 

bool convientDSAT2(int x, int c, int k){ // teste si la couleur c peut etre donnee au sommet x - version pour DSATURk-impropre
if(!valide(x,c,k)) return false; //on vérifie que le sommet x à au plus k voisins de couleur c
else{    
     for(int i=0;i<n;i++)
        if(adj[x][i] && couleur2[i]==c && !valide(i,c,k-1)) return false; //on vérifie que les voisins de couleur c de x ont au plus k-1 voisins de couleur c
     return true;
  }
}

bool convientDSAT(int x, int c) // teste si la couleur c peut �tre donnee au sommet x - version pour DSATUR
{
     for(int i=0;i<n;i++)
      if(adj[x][i] && couleur2[i]==c) return false;
     return true;
}

void colorRR(int x, int k) // fonction recursive pour tester toutes les couleurs possible pour le sommet x
{ 
     if(x==n)
     { cout << "Coloration en " << k << " couleurs trouv�e" << endl;
       for(int i=0;i<n;i++) cout << "couleur de " << i << " : " << couleur1[i] << endl; //int z;cin >> z;
       trouve=true;
     }
     else
     for(int c=1;c<=k;c++)
      if(convient(x,c)) 
	      {couleur1[x]=c;
         colorRR(x+1,k);
	       if(trouve) return;}
}



void colorexact(int k) // teste si le graphe possede une coloration en k couleurs en essayant toutes les combinaisons
{
    for(int i=0;i<n;i++)
     couleur1[i]=0;
     colorRR(0,k);
}



int nbChromatique(int d) // calcule le nombre chromatique en testant � partir de d couleurs et diminuant k tant que c'est possible
{
  int k=d+1;
  do {
      k--;
      trouve=false;
      colorexact(k);
     }
  while(trouve);
  return k+1;
}



int dsatMax()
{
  int maxDeg=-1,maxDSAT=-1,smax=0;
  for(int i=0;i<n;i++)
  if(couleur2[i]==0 && (DSAT[i]>maxDSAT || (DSAT[i]==maxDSAT && Degre[i]>maxDeg)))
   { maxDSAT=DSAT[i]; maxDeg=Degre[i]; smax=i;}
  return smax;
}

/********************************************************************************/
/****************************************Exercice 1******************************/
/********************************************************************************/

int DSATUR(int k){
  int nb=0,c,x,cmax=0;
  for(int i=0;i<n;i++)
  {
    couleur2[i]=0; DSAT[i]=0; Degre[i]=0;
    for(int j=0;j<n;j++)
     if(adj[i][j]) Degre[i]++;
    DSAT[i]=Degre[i];
  }

  while(nb<n)  // tant qu'on a pas colori� tous les sommets
  {
    c=1;
    x=dsatMax(); // on choisit le sommet de DSAT max non encore colori�
    //cout << "x: " << x <<endl;
    while(!convientDSAT2(x,c,k)) c++; // on cherche la plus petite couleur disponible pour ce sommet
    for(int j=0; j<n;j++) // mise � jour des DSAT
     {
       if(adj[x][j] && convientDSAT(j,c)) DSAT[j]++; 
     }
    couleur2[x]=c;
    if(cmax<c) cmax=c;
    nb++;
  }
  
  return cmax;
}

/******************************************************************************/
/************************************Exercice 2********************************/
/******************************************************************************/

//DSATUR impropre où le degré de saturation représente le nombre de couleurs c pour lesquelles moins de k voisins sont de couleur c
int DSATUR2(int k)
{
  int nb=0,c,x,cmax=0,cpt_couleur,cpt_voisins;
  for(int i=0;i<n;i++)
  {
    couleur2[i]=0; DSAT[i]=0; Degre[i]=0;
    for(int j=0;j<n;j++)
     if(adj[i][j]) Degre[i]++;
    DSAT[i]=Degre[i];
  }

  while(nb<n)  // tant qu'on a pas colori� tous les sommets
  {
    c=1;
    x=dsatMax(); // on choisit le sommet de DSAT max non encore colori�
    while(!convientDSAT2(x,c,k)) c++; // on cherche la plus petite couleur disponible pour ce sommet
    couleur2[x]=c;
    if(cmax<c) cmax=c;
    for(int i=0; i<n; i++){ //on parcourt chaque sommet
      cpt_couleur = 0;
      for(int j=1; j <= cmax; j++){ //on teste le nombre de voisin du sommet i de même couleur pour chaque couleur
         cpt_voisins = 0;
         for (int m=0; m<n; m++){
            if(adj[i][m] && couleur2[m]==j) cpt_voisins++;
         }
         if(cpt_voisins < k) cpt_couleur++;
      }
      DSAT[i]=cpt_couleur;
    }
    nb++;
  }
  
  return cmax;
}

//DSATUR impropre où le degré de saturation représente le nombre de couleurs c pour lesquelles plus de k voisins sont de couleur c
int DSATUR3(int k)
{
  int nb=0,c,x,cmax=0,cpt_couleur,cpt_voisins;
  for(int i=0;i<n;i++)
  {
    couleur2[i]=0; DSAT[i]=0; Degre[i]=0;
    for(int j=0;j<n;j++)
     if(adj[i][j]) Degre[i]++;
    DSAT[i]=Degre[i];
  }

  while(nb<n)  // tant qu'on a pas colorié tous les sommets
  {
    c=1;
    x=dsatMax(); // on choisit le sommet de DSAT max non encore colorié
    while(!convientDSAT2(x,c,k)) c++; // on cherche la plus petite couleur disponible pour ce sommet
    couleur2[x]=c;
    if(cmax<c) cmax=c;
    for(int i=0; i<n; i++){
      cpt_couleur = 0;
      for(int j=1; j <= cmax; j++){
         cpt_voisins = 0;
         for (int m=0; m<n; m++){
            if(adj[i][m] && couleur2[m]==j) cpt_voisins++;
         }
         if(cpt_voisins > k) cpt_couleur++;
      }
      DSAT[i]=cpt_couleur;
    }
    nb++;
  }
  
  return cmax;
}

double ameliorationMoy(int n, int p, int k){
  int somme = 0;
  int dsat = 0;
  int dsat2 = 0;
  for (int i = 0; i < 100 ; i++)
  {
    initialiseTab();

    genere(p);
    dsat = DSATUR(k);
    dsat2 = DSATUR2(k); //tu peux changer en DSATUR3(k) pour tester la éieme version de calcule du degre de saturation
    somme += dsat - dsat2;
  }
  return somme/100;
}

/****************************************************************/
/************************Exercice 3******************************/
/****************************************************************/

int degmoy()
{
	int result=0;

  //fait le calcul du degré des sommets
	for(int i=0; i<n; i++)
	{
    Degre[i]=0;
		for(int j=0;j<n;j++)
     if(adj[i][j]) Degre[i]++;
    result+=Degre[i];
	}
	return result/n;
}

/******************************************************************/
/*************************Exercice 4*******************************/
/******************************************************************/

bool valideExactImpropre(int i, int c, int k, int x){
	int cpt = 0;
	for(int j = 0; j<x; j++){
		if(adj[i][j] && (couleur1[j]==c)){ //si j est un voisin de couleur c de i
			cpt++;
			if(cpt > k) {
        return false;
      }
		}
	}
	return true;
} 

bool convientExactImpropre(int x, int c, int i) // teste si la couleur c peut être donnee au sommet x (elle n'est pas utilisee par un de ses voisins)
{
    if(!valideExactImpropre(x,c,i,x)){
      return false; //on vérifie que le sommet x à au plus k voisins de couleur c
    } 
    
    else{    
          for(int j=0;j<x;j++){
              if(adj[x][j] && couleur1[j]==c && !valideExactImpropre(j,c,i-1,x)){
                return false; //on vérifie que les voisins de couleur c de x ont au plus k-1 voisins de couleur c
              }
          } 
     return true;
  }
}

void colorRRImpropre(int x, int k, int i) // fonction recursive pour tester toutes les couleurs possible pour le sommet x avec un degré d'impropreté de i
{ 

     if(x==n)
     { cout << "Coloration en " << k << " couleurs trouvée" << endl;
       for(int i=0;i<n;i++) cout << "couleur de " << i << " : " << couleur1[i] << endl; //int z;cin >> z;
       trouve=true;
     }
     else
     for(int c=1;c<=k;c++)
      if(convientExactImpropre(x,c,i)) 
	      {couleur1[x]=c;//cout << "=>couleur de " << x << " : " << couleur[x] << endl;
         colorRRImpropre(x+1,k,i);
	       if(trouve) return;}
}

void colorexactImpropre(int k, int i) // teste si le graphe possede une coloration en k couleurs avec une impropreté i en essayant toutes les combinaisons
{
    for(int i=0;i<n;i++)
     couleur1[i]=0;
    colorRRImpropre(0,k,i);
}

int nbChromatiqueI(int d, int i) // calcule le nombre chromatique i impropre en testant à partir de d couleurs et diminuant k tant que c'est possible
{
  int k=d+1;
  do {
      k--;
      trouve=false;
      colorexactImpropre(k,i);
     }
  while(trouve);
  return k+1;
}

/*******************************************************************************/
/*******************************Exercice 5**************************************/
/*******************************************************************************/

void construitSommets(int h, int l){
  srand(time(NULL));
  sommets = new int*[n];
  for (int i = 0; i < n; i++){
      sommets[i] = new int[2];
      sommets[i][0] = rand()%l; //position aléatoire en x
      sommets[i][1] = rand()%h; //position aléatoire en y
  }
}

/*indique si deux disques s'intersectent*/
bool intersection(int i, int j, int diametre){
  return sqrt(pow(sommets[i][0]-sommets[j][0],2)+pow(sommets[i][1]-sommets[j][1],2)) <= diametre; //si la distance entre les deux sommets est supérieure au diamètre des disques, alors pas d'intersection 
}

/*construit la matrice d'adjancence du graphe de disque*/
void construitGraphe(int d){
  adj=new int*[n]; 
  for (int i = 0; i < n; i++)
      adj[i] = new int[n]; 

  for(int i=0;i<n-1;i++)
  {
    for(int j=i+1;j<n;j++)
     if(intersection(i,j,d))
      adj[i][j]=adj[j][i]=1;
     else adj[i][j]=adj[j][i]=0;
  }
}

/*******************************************************************************/
/*************************Fonctions tests***************************************/
/*******************************************************************************/

/*
 * permet de répondre à la question 2 en affichant les résultats de dsat selon 
 * la proba d'arrête et l'impropreté
 */
void testExercice1(){
    int k;
    initialiseTab();
    for (int proba = 10; proba < 100; proba+=10)
      {
        genere(proba);
        for (int improprete = 0; improprete < 6; improprete++)
          {
            k=DSATUR(improprete);
            cout << "proba: "<< proba << " impropreté: " << improprete << " nb coul dsat: " << k << endl;
         }
      } 
}

void testExercice2(){
  int k;
  initialiseTab(); 
  for (int i = 10; i < 100; i+=10)
  {
    for (int improprete = 0; improprete < 6; improprete++)
    {
      k = ameliorationMoy(n,i,improprete);
      cout << "proba: "<< i << " impropreté: " << improprete << " amélioration moy: " << k << endl;
    }
  }
}

void testExercice3(){
  for(int i = 10; i < 100; i+=10) {
    n = i;
    initialiseTab();
    for(int j = 10; j < 100; j+=10){
      genere(j);
      cout << "nb sommet: "<< i << "proba: " << j << " degré moy: " << degmoy() << " nb coul: " << DSATUR(degmoy())<< endl;
      //cout << "nb sommet: "<< i << "proba: " << j << " degré moy: " << degmoy() << " nb coul: " << DSATUR2(degmoy())<< endl;
    }
  }
}


void testExercice4(){
  int resultat_dsatur, nbcImpropre;
  initialiseTab();
  for (int nbSommet = 5; nbSommet< 20; nbSommet+=5)
  {
    n = nbSommet;
    for (int proba = 10; proba < 100; proba+=10)
    {
      genere(proba);
      for(int improprete = 0; improprete < 5; improprete++){
        resultat_dsatur = DSATUR2(improprete);
        nbcImpropre = nbChromatiqueI(resultat_dsatur,improprete);
        cout << "nbSommets: "<< nbSommet << " proba: " << proba << " impropreté: " << improprete << " nb color exact impropre: " << nbcImpropre << " nb coul dsat: "<< resultat_dsatur <<endl;
      }
    }
  }
}

void testExercice5(){
  int h = 100; //hauteur
  int l = 100; //largeur
  for(n = 10; n < 100; n+=10){ //nbSommets
    initialiseTab();
    construitSommets(h,l);
      for(int d=5; d<90; d+=10){ //diamètre
          construitGraphe(d);
          //cout << "nb sommets: " << n << " diametre: " << d  << " nb coul dsat1: " << DSATUR(1) << " nb coul dsat2: "<< DSATUR2(1) << " nb coul dsat3: "<< DSATUR3(1) << endl;
          cout << "nb sommets: " << n << " diametre: " << d  << " nb coul dsat1: " << DSATUR(5) << " nb coul dsat2: "<< DSATUR2(5) << " nb coul dsat3: "<< DSATUR3(5) << endl;
      }
  }
  
}



int main()
{

 n=70;
 testExercice5();

  return 0;
}

