function ID(id) {
	return document.getElementById(id);
}

function validForm() {
	var nom =  unescape(ID("nom").value);
	var prenom =  unescape(ID("prenom").value);
	var tel =  ID("tel").value;
	var email1 =  ID("email1").value;
	var email2 =  ID("email2").value;
	var msg =  ID("msg").value;
	var mes

	if (!(nom) || !(prenom) || !(tel) || !(email1) || !(email2) || !(msg)){
		mes = "Veuillez renseigner tous les champs";
	}
	else{
		var emailReg = new RegExp(/^[A-Za-z0-9]+\.+[A-Za-z0-9]+\@+[A-Za-z0-9]+\.+[A-Za-z]{2,}/i);
		var valid = emailReg.test(email1);
		if (!valid) {
			alert("Veuillez donner un email valide");
		}
		else{
			if (email1 != email2) {
				mes = "Les deux addresses E-mail sont différentes"
			}
			else{
				alert("Formulaire envoyer !");
			}
		}
	}
	
	ID("mes").innerHTML = mes;
}

