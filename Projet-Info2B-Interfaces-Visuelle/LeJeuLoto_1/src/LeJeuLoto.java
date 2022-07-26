import javax.swing.ImageIcon;
import javax.swing.JPanel;

/**
 *
 * @author strainchampsclothilde
 */
public class LeJeuLoto extends javax.swing.JFrame {
    
    private int option;// attribut pour l'option choisie
    private int nbCol;// attribut pour le nombre de colonne d'une carte
    private int nbNum;// attribut pour le nombre de numéros d'une carte
    private LesJoueurs lstJ;// lstJ attribut de type LesJoueurs
    private LesJoueurs gagnants;
    private boolean carteAchetee;// attribut pour savoir si des cartes ont déjà été achetées par les joueurs
    private int boules[];// tableau représentant les boules sorties lors des tirages
    private final int  MAX = 90;// numéro max que les boules de tirage peuvent porter
    private Lot lc;
    private LesLots lstL;// lstL attribut de type LesLots
    
    public LeJeuLoto() {
        initComponents();// construction de l’interface faite par l’EDI
        this.option = 1;// par défaut l'option choisie est la 1 donc Quine
        LOption.setText("Option choisie : Quine");// on modifie le text du label LOption par...
        this.lstL = new LesLots();
        this.lc = null;
        initLots();

//       LCadeau.setText("Cadeau: Bon d'achat");
//        BCadeau.setIcon(lc.getPhoto());
        this.nbCol = 5;// on initialise l’attribut nbCol pardéfaut par 5 
        this.nbNum = 4;// on initialise l’attribut nbNum pardéfaut par 4
        this.lstJ = new LesJoueurs();// on créer une liste de joueurs
        this.gagnants = new LesJoueurs();
        this.carteAchetee = false;// au début aucune cartes n'est achetées donc false
        boules= new int [MAX];// on créer notre tableau d'entiers
        initBoules();// méthode pour initialiser notre tableau de boules
        BTirage.setEnabled(false);// on rend incliquable notre bouton de tirage
        BArreter.setEnabled(false);// on rend incliquable notre bouton arrêter
        ItemRecommencer.setEnabled(false);// on rend incliquable notre ittem de menu pour recomencer une partie
        
    }
    
    private void afficheCartes(){// méthode pour afficher les cartes achetées par chaque joueurs en face de son bouton
        int compt = 0;// on initialise un compteur à 0
        for(int i=0; i<lstJ.getNbJoueur(); i++){// on fait une boucle sur la liste des joueurs
            Joueur j = lstJ.getJoueur(i);// pour un joueur i
            int nbCarte = j.getMesCartes().getTaille();// on regade combien il a de cartes (1 ou 2)
            switch(nbCarte){
                case 0:{// si il n'a pas de cartes
                    compt +=2;// on ajoute 2 à compt
                    break;// on s'arrête pour ne pas passer au cas suivant
                }
                case 1:{// si il a une carte
                    j.getMesCartes().getCarte(0).dessineCarte((JPanel) LesCartons.getComponent(compt), j.getCouleur(), true);
                    // on affiche sa première carte à l'emplaçement de compt
                    compt +=2;// on ajoute 2 à compt
                    break;// on s'arrête pour ne pas passer au cas suivant
                }
                case 2:{// si il a deux cartes
                    for(int k=0; k<nbCarte;k++){// on fait une boucle sur le nb de carte
                        j.getMesCartes().getCarte(k).dessineCarte((JPanel) LesCartons.getComponent(compt), j.getCouleur(), true);
                        // pour chaque carte 0 et 1, on affiche les cartes à l'emplaçement de compt
                        compt +=1;// on ajoute 1 à compt
                    }
                }
            }
        }
    }
    
    public void initBoules(){
        for(int i=0; i<MAX-1; i++){
            boules[i] = 0; 
        }
    }
    
private void initLots() {
//        Cadeau l1=new Cadeau("Appareil à raclette",1);//initialisation du premier lot cadeau (niveau 1)
//        l1.setPhoto(new ImageIcon(getClass().getResource("/raclette.jpg")));//modification de la photo 
//        lstL.ajouteLot(l1);//ajout du lot l1 dans la liste lstL ( des lots )
        Cadeau l2=new Cadeau("Machine à laver",2);//initialisation du deuxième lot cadeau (niveau 2)
        l2.setPhoto(new ImageIcon(getClass().getResource("/machine_laver.jpeg")));//modification de la photo 
        lstL.ajouteLot(l2);//ajout du lot l2 dans la liste lstL ( des lots )
        Cadeau l3=new Cadeau("Twingo",3);//initialisation du troisième lot cadeau (niveau 3)
        l3.setPhoto(new ImageIcon(getClass().getResource("/twingo.jpeg")));//modification de la photo 
        lstL.ajouteLot(l3);//ajout du lot l3 dans la liste lstL ( des lots )
        BonAchat l4=new BonAchat("10 euros",1);//initialisation du premier lot bon d'achat (niveau 1)
        l4.setPhoto(new ImageIcon(getClass().getResource("/bon.png")));//modification de la photo 
        lstL.ajouteLot(l4);//ajout du lot l4 dans la liste lstL ( des lots )
        BonAchat l5=new BonAchat("50 euros",2);//initialisation du premier lot  (niveau 2)
        l5.setPhoto(new ImageIcon(getClass().getResource("/bon.png")));//modification de la photo 
        lstL.ajouteLot(l5);//ajout du lot l5 dans la liste lstL ( des lots )
        BonAchat l6=new BonAchat("100 euros",1);//initialisation du premier lot bon d'achat (niveau 3)
        l6.setPhoto(new ImageIcon(getClass().getResource("/bon.png")));//modification de la photo 
        lstL.ajouteLot(l6);//ajout du lot l6 dans la liste laG ( des lots à gagner)
    }
    
    public void partiePrete(){// métode qui vérifie si le jeu peut être lancé
        boolean cartesJ = true;// on initialise le boolean des cartes des joueurs en suposant qu'ils en ont tous acheté
        for(int i=0; i<lstJ.getNbJoueur(); i++){// on fait une boucle sur la liste des joueurs
            Joueur j = lstJ.getJoueur(i);// pour le joueurs i
            cartesJ &= j.getAchatCarte();// on regarde si c'est true donc acheté
        }
        if(cartesJ == true && lstJ.getNbJoueur()>0){// si tt les joueurs ont au mois acheté une carte
            BTirage.setEnabled(true);// on active le bouton de tirage 
            BArreter.setEnabled(true);//et d'arrêt
        }
        else// sinon 
            LNombreTirage.setText("Le jeu n'est pas prêt!");// on dit la ou s'affiche les boules tirées que le jeu n'est pas prêt
    }

    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        PanTitre = new javax.swing.JPanel();
        jLabel1 = new javax.swing.JLabel();
        PanInfos = new javax.swing.JPanel();
        PanCadeau = new javax.swing.JPanel();
        LCadeau = new javax.swing.JLabel();
        jPanel1 = new javax.swing.JPanel();
        jLabel3 = new javax.swing.JLabel();
        LOption = new javax.swing.JLabel();
        jPanel2 = new javax.swing.JPanel();
        jPanel4 = new javax.swing.JPanel();
        jScrollPane1 = new javax.swing.JScrollPane();
        HistoTirage = new javax.swing.JTextArea();
        BCadeau = new javax.swing.JButton();
        jPanel3 = new javax.swing.JPanel();
        BTirage = new javax.swing.JButton();
        LNombreTirage = new javax.swing.JLabel();
        BArreter = new javax.swing.JButton();
        PanJoueurs = new javax.swing.JPanel();
        BJoueur1 = new javax.swing.JButton();
        BJoueur2 = new javax.swing.JButton();
        BJoueur3 = new javax.swing.JButton();
        BJoueur4 = new javax.swing.JButton();
        LesCartons = new javax.swing.JPanel();
        Carte1 = new javax.swing.JPanel();
        Carte2 = new javax.swing.JPanel();
        Carte3 = new javax.swing.JPanel();
        Carte4 = new javax.swing.JPanel();
        Carte5 = new javax.swing.JPanel();
        Carte6 = new javax.swing.JPanel();
        Carte7 = new javax.swing.JPanel();
        Carte8 = new javax.swing.JPanel();
        jMenuBar1 = new javax.swing.JMenuBar();
        MAjout = new javax.swing.JMenu();
        ItemJoueur = new javax.swing.JMenuItem();
        ItemLot = new javax.swing.JMenuItem();
        MAction = new javax.swing.JMenu();
        ItemOption = new javax.swing.JMenuItem();
        ItemDemarrer = new javax.swing.JMenuItem();
        ItemAcheter = new javax.swing.JMenuItem();
        ItemContinuer = new javax.swing.JMenuItem();
        ItemRecommencer = new javax.swing.JMenuItem();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);

        jLabel1.setFont(new java.awt.Font("PT Sans", 0, 24)); // NOI18N
        jLabel1.setText("Voici les cartes dont vous disposez");
        PanTitre.add(jLabel1);

        getContentPane().add(PanTitre, java.awt.BorderLayout.NORTH);

        PanInfos.setLayout(new java.awt.BorderLayout());

        PanCadeau.add(LCadeau);

        PanInfos.add(PanCadeau, java.awt.BorderLayout.NORTH);

        jPanel1.setLayout(new java.awt.GridLayout(1, 2));

        jLabel3.setText("Historique du tirage des boules");
        jPanel1.add(jLabel3);

        LOption.setText("Option choisie :");
        jPanel1.add(LOption);

        PanInfos.add(jPanel1, java.awt.BorderLayout.CENTER);

        jPanel2.setLayout(new java.awt.GridLayout(1, 2));

        jPanel4.setLayout(new java.awt.GridLayout(1, 2));

        HistoTirage.setColumns(20);
        HistoTirage.setRows(5);
        jScrollPane1.setViewportView(HistoTirage);

        jPanel4.add(jScrollPane1);

        BCadeau.setText("Aperçu cadeau\n");
        jPanel4.add(BCadeau);

        jPanel2.add(jPanel4);

        jPanel3.setLayout(new java.awt.GridLayout(1, 3));

        BTirage.setText("Tirage");
        BTirage.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                BTirageActionPerformed(evt);
            }
        });
        jPanel3.add(BTirage);

        LNombreTirage.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        jPanel3.add(LNombreTirage);

        BArreter.setText("Arreter");
        BArreter.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                BArreterActionPerformed(evt);
            }
        });
        jPanel3.add(BArreter);

        jPanel2.add(jPanel3);

        PanInfos.add(jPanel2, java.awt.BorderLayout.SOUTH);

        getContentPane().add(PanInfos, java.awt.BorderLayout.SOUTH);

        PanJoueurs.setLayout(new java.awt.GridLayout(4, 0));

        BJoueur1.setText("Joueur 1");
        BJoueur1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                BJoueur1ActionPerformed(evt);
            }
        });
        PanJoueurs.add(BJoueur1);

        BJoueur2.setText("Joueur 2");
        BJoueur2.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                BJoueur2ActionPerformed(evt);
            }
        });
        PanJoueurs.add(BJoueur2);

        BJoueur3.setText("Joueur 3");
        BJoueur3.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                BJoueur3ActionPerformed(evt);
            }
        });
        PanJoueurs.add(BJoueur3);

        BJoueur4.setText("Joueur 4");
        BJoueur4.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                BJoueur4ActionPerformed(evt);
            }
        });
        PanJoueurs.add(BJoueur4);

        getContentPane().add(PanJoueurs, java.awt.BorderLayout.EAST);

        LesCartons.setLayout(new java.awt.GridLayout(4, 2));
        LesCartons.add(Carte1);
        LesCartons.add(Carte2);
        LesCartons.add(Carte3);
        LesCartons.add(Carte4);
        LesCartons.add(Carte5);
        LesCartons.add(Carte6);
        LesCartons.add(Carte7);
        LesCartons.add(Carte8);

        getContentPane().add(LesCartons, java.awt.BorderLayout.CENTER);

        MAjout.setText("Ajout");

        ItemJoueur.setText("Joueur");
        ItemJoueur.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                ItemJoueurActionPerformed(evt);
            }
        });
        MAjout.add(ItemJoueur);

        ItemLot.setText("Lot");
        ItemLot.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                ItemLotActionPerformed(evt);
            }
        });
        MAjout.add(ItemLot);

        jMenuBar1.add(MAjout);

        MAction.setText("Action");

        ItemOption.setText("Option Jeu");
        ItemOption.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                ItemOptionActionPerformed(evt);
            }
        });
        MAction.add(ItemOption);

        ItemDemarrer.setText("Démarrer Jeu");
        ItemDemarrer.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                ItemDemarrerActionPerformed(evt);
            }
        });
        MAction.add(ItemDemarrer);

        ItemAcheter.setText("Acheter cartes");
        ItemAcheter.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                ItemAcheterActionPerformed(evt);
            }
        });
        MAction.add(ItemAcheter);

        ItemContinuer.setText("Continuer");
        ItemContinuer.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                ItemContinuerActionPerformed(evt);
            }
        });
        MAction.add(ItemContinuer);

        ItemRecommencer.setText("Recommencer");
        ItemRecommencer.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                ItemRecommencerActionPerformed(evt);
            }
        });
        MAction.add(ItemRecommencer);

        jMenuBar1.add(MAction);

        setJMenuBar(jMenuBar1);

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void ItemOptionActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_ItemOptionActionPerformed
        // TODO add your handling code here:
        OptionsDlg diag= new OptionsDlg(this, true, carteAchetee, nbNum, nbCol);// on créer un objet OptionDlg avec ces paramètres
        diag.setSize(600, 500);// on fixe la taille
        diag.setLocation(100,100);// on peut la positionner
        diag.setVisible(true);// on affiche la boîte de dialogue
        if (diag.getOk() == true ){// on teste si on a fermé par Quitter (ok = true)      
            this.nbCol = diag.getNbCol();// on récupère le nombre de colonne
            this.nbNum = diag.getNbNum();// on récupère le nombre de ligne
            this.option = diag.getChoix();// on récupère l'option de jeu
            switch(this.option) {// en fonction de l'option choisie
                case 1: {// si l'option 1 est choisie
                    LOption.setText("Option choisie : Quine");// on afiche... dans le label de l'option
                    break;// on stop pour ne pas faire les cas suivant
                }
                case 2: {// si l'option 2 est choisie
                    LOption.setText("Option choisie : Double Quine");// on afiche... dans le label de l'option
                    break;
                }
                case 3: {// si l'option 3 est choisie
                    LCadeau.setText("Cadeau: " + lc.getDescription());
                }
            }
        }
    }//GEN-LAST:event_ItemOptionActionPerformed

    private void BJoueur1ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_BJoueur1ActionPerformed
        // TODO add your handling code here:
        Joueur j= lstJ.getJoueur(0);//on sélectionne le joueur d'indice 0 de notre liste de joueur
        VisuJoueurDlg diag= new VisuJoueurDlg(this, true, j);// on crée la boite, this --> désigne la JFrame, true met un mode bloquant
        // on passe le paramètre le joueur à afficher (ici j)
        diag.setSize(600, 500);// on fixe la taille
        diag.setLocation(100,100);// on peut la positionner
        diag.setVisible(true);// on affiche la boîte de dialogue

    }//GEN-LAST:event_BJoueur1ActionPerformed

    private void ItemJoueurActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_ItemJoueurActionPerformed
        // TODO add your handling code here:
        AjoutJoueurDlg diag= new AjoutJoueurDlg(this, true);// 2 paramètres «usuels »
        diag.setVisible(true);// on affiche la boite
        diag.setSize(600, 500);// on fixe la taille
        diag.setLocation(100,100);// on peut la positionner
        if (diag.getOk() == true && lstJ.getNbJoueur()<4){// on teste si on a fermé par Valider (ok = true) et que la liste des Joueur est inférieur à 4
            Joueur j = diag.getJoueur();// on récupère le joueur créé (avec l’accesseur getJoueur)
            lstJ.ajouteJoueur(j);// on ajoute le joueur à la liste qui est un objet "LesJoueurs"
        
            int ind = lstJ.getlistJoueur().indexOf(j);//on prend l'idice du joueur j que l'on vient d'ajouter
            switch(ind){
                case 0:{//si l'indice est de 0
                    BJoueur1.setText(j.getPseudo());//on modifie ce qui est écrit sur le bouton BJoueur1 par le pseudo du joueur j
                    BJoueur1.setBackground(j.getCouleur());//puis on modifie la couleur du bouton par celle du joueur j
                    break;// on met un break pour que les cas suivant de s'execute pas 
                }
                case 1:{//même principe pour des indices de joueur différent
                    BJoueur2.setText(j.getPseudo());
                    BJoueur2.setBackground(j.getCouleur());
                    break;
                }
                case 2:{
                    BJoueur3.setText(j.getPseudo());
                    BJoueur3.setBackground(j.getCouleur());
                    break;
                    }
                case 3:{
                    BJoueur4.setText(j.getPseudo());
                    BJoueur4.setBackground(j.getCouleur());
                    break;
                }
            }
        }
    }//GEN-LAST:event_ItemJoueurActionPerformed

    private void BJoueur2ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_BJoueur2ActionPerformed
        // TODO add your handling code here:
        //même principe pour tt les boutons de joueurs
        Joueur j= lstJ.getJoueur(1);
        VisuJoueurDlg diag= new VisuJoueurDlg(this, true, j);
        diag.setSize(600, 500);
        diag.setLocation(100,100);
        diag.setVisible(true);
    }//GEN-LAST:event_BJoueur2ActionPerformed

    private void BJoueur3ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_BJoueur3ActionPerformed
        // TODO add your handling code here:
        Joueur j= lstJ.getJoueur(2);
        VisuJoueurDlg diag= new VisuJoueurDlg(this, true, j);
        diag.setSize(600, 500);
        diag.setLocation(100,100);
        diag.setVisible(true);
    }//GEN-LAST:event_BJoueur3ActionPerformed

    private void BJoueur4ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_BJoueur4ActionPerformed
        // TODO add your handling code here:
        Joueur j= lstJ.getJoueur(3);
        VisuJoueurDlg diag= new VisuJoueurDlg(this, true, j);
        diag.setSize(600, 500);
        diag.setLocation(100,100);
        diag.setVisible(true);
    }//GEN-LAST:event_BJoueur4ActionPerformed

    private void ItemAcheterActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_ItemAcheterActionPerformed
        // TODO add your handling code here:
        AchatCarteDlg diag= new AchatCarteDlg(this, true, lstJ, 3, this.nbCol, this.nbNum);// on créer un objet achat.. avec ces paramètres
        diag.setVisible(true);// on affiche la boite
        diag.setSize(600, 500);// on fixe la taille
        diag.setLocation(100,100);// on peut la positionner
        if (diag.getOk() == true ){// on teste si on a fermé par Quitter (ok = true) 
            carteAchetee = diag.getAchat();// nous revoie si des cartes on été acheté
            afficheCartes();// affiche les cartes que les joueurs on achetées dans l'interface principale
        }
    }//GEN-LAST:event_ItemAcheterActionPerformed

    private void BTirageActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_BTirageActionPerformed
//        // TODO add your handling code here:
        int nb;// on déclare nb qui est un entier
        do{// on fait 
            nb = (int)(1+90*Math.random());//on génère un nombre aléatoire entre 1 et 90
        }while(boules[nb-1] == 1);// tant qu'il est dans notre tableau de boules donc déjà tiré dans le jeu on refait...
        boules[nb-1]=1;// si il n'y était pas on met 1 pour dire qu'il a été tiré une fois
        
        LNombreTirage.setText(String.valueOf(nb));// on modifie notre label pour afficher la boules tiré (nb)
        HistoTirage.append(nb + " - ");// on ajoute à notre historique nb    
        gagnants = new LesJoueurs();// on créer une liste de joueurs gagnants de type "lesJoueurs"
        for(int i=0; i<lstJ.getNbJoueur(); i++){// on fait une boucle sur la liste des joueurs
            Joueur j = lstJ.getJoueur(i);// pour le joueur i
            for(int k=0; k<j.getMesCartes().getTaille(); k++){// on fait une boucle sur la liste de ces cartes
                CarteLoto c = j.getMesCartes().getCarte(k);// on une carte k
                if(c.placePion(nb) == true){// si nb est dans la carte on place un pion 
                    if(c.cartonGagnantTD(option)){// on vérifie si sa carte est gagnante en fonction de l'option choisie
                        gagnants.ajouteJoueur(j);// si oui on ajoute notre joueur à notre liste de gagnant
                        switch(option){// en fontion de l'option
                            case 1:{// si 1
                                HistoTirage.append("\n" + j.getPseudo() + " a réalisé un Quine.");// on ajoute à l'histo de tirage que le joueur gagne et à réaliser...
                                break;// on met un break pour que les cas suivant de s'execute pas 
                            }
                            case 2:{// si 2
                                HistoTirage.append("\n" + j.getPseudo() + " a réalisé un Double Quine.");// on ajoute à l'histo de tirage que le joueur gagne et à réaliser...
                                break;// on met un break pour que les cas suivant de s'execute pas 
                            }
                            case 3:{// si 3
                                HistoTirage.append("\n" + j.getPseudo() + " a réalisé un Carton Plein.");// on ajoute à l'histo de tirage que le joueur gagne et à réaliser...
                            }
                        }
                    }
                }
            }
        }
        afficheCartes();// on rafraichi les cartes des joueurs dans l'interface principale
        if(gagnants.getNbJoueur() == 1){// si il n'y a que 1 gagnant
            Joueur j = gagnants.getJoueur(0);
            HistoTirage.append("\nLe gagnant de ce jeu du loto est: "
                                + "\nC'est " + j.getPseudo() + " qui repart avec le lot!");// on ajoute à notre histo de tirage que le joueur gagnat est ... et repart avec le lot
            BTirage.setEnabled(false);// on rend incliquable le bouton de tirage
            ItemContinuer.setEnabled(true);
        }
        else{// sinon
            if(gagnants.getNbJoueur() > 1){// si il y a plusieurs gagnants
                int nbg = (int)(0+gagnants.getNbJoueur()*Math.random());// on tire aléatoire un indice de joueur
                Joueur j = gagnants.getJoueur(nbg);//on prend le joueurs ... à la liste des gagnants
                HistoTirage.append("\nLes gagnants de ce jeu du loto sont: "
                                    + "\n" + gagnants.toString()
                                    + "\nMalheureusement seul un peu être vainqueur et repartir avec le lot,"
                                    + "\net c'est " + j.getPseudo() + " qui repart avec le lot!");// il devient gagnant du lot et du jeu
                BTirage.setEnabled(false);// on rend incliquable le bouton de tirage
                ItemContinuer.setEnabled(true);
            }
        }
    }//GEN-LAST:event_BTirageActionPerformed

    private void ItemDemarrerActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_ItemDemarrerActionPerformed
        partiePrete();// on vérifie si la partie peit être lancé
        ItemDemarrer.setEnabled(false);
        ItemRecommencer.setEnabled(true);// 
        int n;
        do{
            n=(int)(0+this.lstL.getNbLot()*Math.random());
        }while(lstL.getLot(n).getNiveau()!= this.option);      
        this.lc=this.lstL.getLot(n);
            if(this.lc instanceof Cadeau){
                Cadeau c=(Cadeau)this.lstL.getLot(n);
                BCadeau.setText("");
                BCadeau.setIcon(c.getPhoto());
                LCadeau.setText(c.toString());   
            }
            else
            {
                BonAchat b=(BonAchat)this.lstL.getLot(n);
                BCadeau.setIcon(null);
                BCadeau.setText(b.toString());
                LCadeau.setText(b.toString());
             
            }
    }//GEN-LAST:event_ItemDemarrerActionPerformed

    private void BArreterActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_BArreterActionPerformed
        // TODO add your handling code here:
        BTirage.setEnabled(false);
        ItemRecommencer.setEnabled(true);// 
    }//GEN-LAST:event_BArreterActionPerformed

    private void ItemRecommencerActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_ItemRecommencerActionPerformed
        // TODO add your handling code here:
        HistoTirage.setText("");
        LCadeau.setText("");
        this.option = 1;// par défaut l'option choisie est la 1 donc Quine
        LOption.setText("Option choisie : Quine");// on modifie le text du label LOption par...
        carteAchetee = false;
        for(int i=0; i<lstJ.getNbJoueur(); i++){
            Joueur j = lstJ.getJoueur(i);
            j.setSolde(20.0);
            j.getMesCartes().retireCartes();
        }
        
        Carte1.removeAll();
        Carte2.removeAll();
        Carte3.removeAll();
        Carte4.removeAll();
        Carte5.removeAll();
        Carte6.removeAll();
        Carte7.removeAll();
        Carte8.removeAll();
        
        LNombreTirage.setText("");
        BTirage.setEnabled(false);// on rend incliquable notre bouton de tirage
        BArreter.setEnabled(false);// on rend incliquable notre bouton arrêter
        ItemRecommencer.setEnabled(false);// on rend incliquable notre ittem de menu pour recomencer une partie
        ItemDemarrer.setEnabled(true);
        ItemContinuer.setEnabled(false);
        int n;
        do{
            n=(int)(0+this.lstL.getNbLot()*Math.random());
        }while(lstL.getLot(n).getNiveau()!= this.option);      
        this.lc=this.lstL.getLot(n);
            if(this.lc instanceof Cadeau){
                Cadeau c=(Cadeau)this.lstL.getLot(n);
                BCadeau.setText("");
                BCadeau.setIcon(c.getPhoto());
                LCadeau.setText(c.toString());   
            }
            else
            {
                BonAchat b=(BonAchat)this.lstL.getLot(n);
                BCadeau.setIcon(null);
                BCadeau.setText(b.toString());
                LCadeau.setText(b.toString());
             
            }
    }//GEN-LAST:event_ItemRecommencerActionPerformed

    private void ItemLotActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_ItemLotActionPerformed
        // TODO add your handling code here:
//        SaisieLotDlg diag= new SaisieLotDlg(this, true);// 2 paramètres «usuels »
//        diag.setVisible(true);// on affiche la boite
//        diag.setSize(600, 500);// on fixe la taille
//        diag.setLocation(100,100);// on peut la positionner
//        if (diag.getOk() == true)
    }//GEN-LAST:event_ItemLotActionPerformed

    private void ItemContinuerActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_ItemContinuerActionPerformed
        // TODO add your handling code here:
        if(gagnants.getNbJoueur() >= 0){
            if(option == 1 || option == 2){
                option += 1;
                switch(this.option) {// en fonction de l'option choisie
                    case 1: {// si l'option 1 est choisie
                        LOption.setText("Option choisie : Quine");// on afiche... dans le label de l'option
                        break;// on stop pour ne pas faire les cas suivant
                    }
                    case 2: {// si l'option 2 est choisie
                        LOption.setText("Option choisie : Double Quine");// on afiche... dans le label de l'option
                    }
                }
            }
            else{
                LNombreTirage.setText("Niveau de carton plein atteint");
            }
            int n;
        do{
            n=(int)(0+this.lstL.getNbLot()*Math.random());
        }while(lstL.getLot(n).getNiveau()!= this.option);      
        this.lc=this.lstL.getLot(n);
            if(this.lc instanceof Cadeau){
                Cadeau c=(Cadeau)this.lstL.getLot(n);
                BCadeau.setText("");
                BCadeau.setIcon(c.getPhoto());
                LCadeau.setText(c.toString());   
            }
            else
            {
                BonAchat b=(BonAchat)this.lstL.getLot(n);
                BCadeau.setIcon(null);
                BCadeau.setText(b.toString());
                LCadeau.setText(b.toString());
             
            }
            BTirage.setEnabled(true);// on rend cliquable notre bouton de tirage
            ItemDemarrer.setEnabled(false);
        }
            
            
    }//GEN-LAST:event_ItemContinuerActionPerformed

    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        /* Set the Nimbus look and feel */
        //<editor-fold defaultstate="collapsed" desc=" Look and feel setting code (optional) ">
        /* If Nimbus (introduced in Java SE 6) is not available, stay with the default look and feel.
         * For details see http://download.oracle.com/javase/tutorial/uiswing/lookandfeel/plaf.html 
         */
        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException ex) {
            java.util.logging.Logger.getLogger(LeJeuLoto.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(LeJeuLoto.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(LeJeuLoto.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(LeJeuLoto.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>

        /* Create and display the form */
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                LeJeuLoto lj = new LeJeuLoto();
                lj.setVisible(true);
                lj.setSize(800,600);
            }
        });
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton BArreter;
    private javax.swing.JButton BCadeau;
    private javax.swing.JButton BJoueur1;
    private javax.swing.JButton BJoueur2;
    private javax.swing.JButton BJoueur3;
    private javax.swing.JButton BJoueur4;
    private javax.swing.JButton BTirage;
    private javax.swing.JPanel Carte1;
    private javax.swing.JPanel Carte2;
    private javax.swing.JPanel Carte3;
    private javax.swing.JPanel Carte4;
    private javax.swing.JPanel Carte5;
    private javax.swing.JPanel Carte6;
    private javax.swing.JPanel Carte7;
    private javax.swing.JPanel Carte8;
    private javax.swing.JTextArea HistoTirage;
    private javax.swing.JMenuItem ItemAcheter;
    private javax.swing.JMenuItem ItemContinuer;
    private javax.swing.JMenuItem ItemDemarrer;
    private javax.swing.JMenuItem ItemJoueur;
    private javax.swing.JMenuItem ItemLot;
    private javax.swing.JMenuItem ItemOption;
    private javax.swing.JMenuItem ItemRecommencer;
    private javax.swing.JLabel LCadeau;
    private javax.swing.JLabel LNombreTirage;
    private javax.swing.JLabel LOption;
    private javax.swing.JPanel LesCartons;
    private javax.swing.JMenu MAction;
    private javax.swing.JMenu MAjout;
    private javax.swing.JPanel PanCadeau;
    private javax.swing.JPanel PanInfos;
    private javax.swing.JPanel PanJoueurs;
    private javax.swing.JPanel PanTitre;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JLabel jLabel3;
    private javax.swing.JMenuBar jMenuBar1;
    private javax.swing.JPanel jPanel1;
    private javax.swing.JPanel jPanel2;
    private javax.swing.JPanel jPanel3;
    private javax.swing.JPanel jPanel4;
    private javax.swing.JScrollPane jScrollPane1;
    // End of variables declaration//GEN-END:variables
}
