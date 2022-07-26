var heuresDiv = document.querySelector('.heures');
var dateDiv = document.querySelector('.date');

var affichageHeure = function()
	{	var today, annee, listeMois, mois, listeJour, jourNumero, jourNom,
		heures, minutes, secondes, deuxChiffres;

		//récupération de la date actuelle
		today = new Date();

		//récupération de l'année
		annee = today.getFullYear();

		//récupération du mois
		listeMois = ["Janvier", "Février", "Mars", "Avril", "Mai", "Juin",
		"Juillet", "Août", "Septembre", "Octobre", "Novembre", "Décembre"];
		mois = listeMois[today.getMonth()];

		//récupération du numéro du jour du mois
		jourNumero = today.getDate();

		//récupération du jour
		listeJour = ["Dimanche", "Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi"];
		jourNom = listeJour[today.getDay()];

		//Affighage des heures, minutes et secondes (avec deux chiffres)
		deuxChiffres = function(element)
			{	if(element < 10)
					{return element = "0"+ element;}
				else
					{return element;}
			}

		//récupération des heures
		heures = deuxChiffres(today.getHours());

		//récupération des minutes
		minutes = deuxChiffres(today.getMinutes());

		//récupération des secondes
		secondes = deuxChiffres(today.getSeconds());

		//Affichache dans nos balise DIV du HTML
		heuresDiv.textContent = heures + ":" + minutes + ":" + secondes;
		dateDiv.textContent = jourNom + " " + jourNumero + " " + mois + " " + annee;

		//lancer la fonction affichage heure toutes les 1000ms, soit toute les secondes
		setTimeout(affichageHeure, 1000);
	}

//lancer la fontion une fois au début
affichageHeure();




