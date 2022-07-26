<?php
    $message=$_POST['nom'].' '.$_POST['prenom'].' '.$_POST['tel'].' '.$_POST['email1'].' '.$_POST['msg'];
    $retour = mail('clothilde.strainchamps@gmail.com', 'Envoi depuis la page Contact', $message, 'From : clothilde.strainchamps@gmail.com');
    if ($retour) {
        echo '<p>Votre message a bien été envoyé.</p>';
    }
?>