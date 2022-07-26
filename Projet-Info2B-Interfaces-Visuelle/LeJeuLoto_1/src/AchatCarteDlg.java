
import java.awt.Dimension;
import java.awt.GridLayout;
import javax.swing.JButton;
import javax.swing.JFrame;


/**
 *
 * @author strainchampsclothilde
 */
public class AchatCarteDlg extends javax.swing.JDialog {

    private LesJoueurs ljc;// liste courante des joueurs
    private int nbCol, nbLig, nbNum;// nombre de lignes, colonnes et de numéros d'une carte de loto
    private Joueur jc;// le joueur courant
    private CarteLoto cc;// carte de loto courante
    private boolean achat;// indicateur pour savoir si un achat de carte a été réaliser
    private boolean ok;// indicateur pour la boîte de dialogue
    
    public AchatCarteDlg(java.awt.Frame parent, boolean modal, LesJoueurs lj, int ligne, int colonne, int numero) {
        super(parent, modal);// appel du constructeur de la classe ancêtre ici JDilaog
        initComponents();// construction de l’interface faite par l’EDI
        this.ljc = lj;// on initialise l’attribut ljc avec le paramètre passé lj
        this.nbLig = ligne;// on initialise l’attribut nbLig avec le paramètre passé ligne   
        this.nbCol = colonne;// on initialise l’attribut nbCol avec le paramètre passé colonne  
        this.nbNum = numero;// on initialise l’attribut nbNum avec le paramètre passé numero 
        this.achat = false;// par défaut on fixe l'achat d'une carte à false
        this.jc = ljc.getJoueur(0);// on fixe le joueur courant au premier joueur de la liste
        this.cc = new CarteLoto(colonne, numero);// on créer une carte de loto courante avec les paramètres du jeu
        this.ok = false;// on fixe la fermeture de la boîte de dialogue à false
        remplirListeJoueurs();// méthode pour remplir la JComboBox avec les noms des joueurs
        initCarte();// méthode pour intialiser une carte de loto
        afficheCarte();// méthode pour afficher cette carte de loto
    }
    // accesseurs en lecture
    public boolean getOk(){
        return this.ok;
    }
    public boolean getAchat(){
        return this.achat;
    }

    private AchatCarteDlg(JFrame jFrame, boolean b) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }
    
    public void remplirListeJoueurs(){// méthode pour remplir la comboBox
        for(int i = 0; i<ljc.getNbJoueur(); i++)// on fait une boucle sur la liste des joueurs        
            ComboJoueur.addItem(ljc.getJoueur(i).getPseudo());// on ajoute le joueur i à la liste déroulante
//        switch(ljc.getNbJoueur()){
//            case 1:{
//                ComboJoueur.addItem(ljc.getJoueur(0).getPseudo());
//            }
//            case 2:{
//                ComboJoueur.addItem(ljc.getJoueur(0).getPseudo());
//                ComboJoueur.addItem(ljc.getJoueur(1).getPseudo());
//            }
//            case 3:{
//                ComboJoueur.addItem(ljc.getJoueur(0).getPseudo());
//                ComboJoueur.addItem(ljc.getJoueur(1).getPseudo());
//                ComboJoueur.addItem(ljc.getJoueur(2).getPseudo());
//            }
//            case 4:{
//                ComboJoueur.addItem(ljc.getJoueur(0).getPseudo());
//                ComboJoueur.addItem(ljc.getJoueur(1).getPseudo());
//                ComboJoueur.addItem(ljc.getJoueur(2).getPseudo());
//                ComboJoueur.addItem(ljc.getJoueur(3).getPseudo());
//            }
//        }
    }
    
    public void initCarte(){
        Panneau.setLayout( new GridLayout(nbLig, nbCol));// on fixe le GridLayout pour le JPanel Panneau avec un GridLayout, pour nl lignes et nc colonnes
        for (int i=0 ; i<this.nbLig;i++){// on fait une double boucle sur les lignes 
            for (int j=0; j<this.nbCol; j++){// et les colonnes  
                JButton bouton=new JButton();// création d'un bouton
                bouton.setPreferredSize(new Dimension(50,50)); // on affecte une taille préférée au bouton
                Panneau.add(bouton);// on ajoute ce bouton au JPanel Panneau
            }
        }
    }
    
    private void afficheCarte(){
//        for (int i=0;i<this.nbLig; i++){  // boucle sur les lignes
//            for(int j=0; j<this.nbCol; j++){ // boucle sur les colonnes
//                // On récupère le bouton d’indice i*nl+j du Panneau
//		//le JPanel Panneau a un tableau à 1 dimension qui contient ses composants
//	        // getComponent(z) -> redonne le composant qui est à l’indice  z
//		//i*this.nl+j, donne l’indice de la case(i,j) dans le tableau des components
//		// le tableau est rempli ligne par ligne pour un GridLayout
//                JButton jb=(JButton)Panneau.getComponent(i*nbLig+j);
//		// on teste si case (I,j) de la carte d’indice k, vaut 0 ou non
//                if (cc.getCase(i, j) !=0) 
//                    jb.setText(""+cc.getCase(i, j));  // si != de 0, on affiche cette valeur sur le bouton
//                else 
//                    jb.setText("");
//            }
//        }
//    }
        
        // pour chaque case de la carte, on affiche sa valeur dans un bouton du Paneau
        for(int i = 0; i < nbLig; i++){
            for(int j=0; j < nbCol; j++){
                ((JButton) Panneau.getComponent(i*nbCol+j)).setText((cc.getCase(i, j) == 0 ? "" : "" + cc.getCase(i, j)));
            }
        }
    }

    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        PanTitre = new javax.swing.JPanel();
        LTitre = new javax.swing.JLabel();
        Panneau = new javax.swing.JPanel();
        PanBouton = new javax.swing.JPanel();
        PanAffichage = new javax.swing.JPanel();
        LInfo = new javax.swing.JLabel();
        jPanel1 = new javax.swing.JPanel();
        ComboJoueur = new javax.swing.JComboBox<>();
        BAutreChoix = new javax.swing.JButton();
        BAcheter = new javax.swing.JButton();
        BQuitter = new javax.swing.JButton();

        setDefaultCloseOperation(javax.swing.WindowConstants.DISPOSE_ON_CLOSE);

        LTitre.setFont(new java.awt.Font("Lucida Grande", 0, 18)); // NOI18N
        LTitre.setText("Acheter une ou plusieurs cartes");
        PanTitre.add(LTitre);

        getContentPane().add(PanTitre, java.awt.BorderLayout.NORTH);

        javax.swing.GroupLayout PanneauLayout = new javax.swing.GroupLayout(Panneau);
        Panneau.setLayout(PanneauLayout);
        PanneauLayout.setHorizontalGroup(
            PanneauLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 468, Short.MAX_VALUE)
        );
        PanneauLayout.setVerticalGroup(
            PanneauLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 429, Short.MAX_VALUE)
        );

        getContentPane().add(Panneau, java.awt.BorderLayout.CENTER);

        PanBouton.setLayout(new java.awt.BorderLayout());

        LInfo.setFont(new java.awt.Font("Lucida Grande", 0, 14)); // NOI18N
        LInfo.setText("Info");
        PanAffichage.add(LInfo);

        PanBouton.add(PanAffichage, java.awt.BorderLayout.NORTH);

        jPanel1.setLayout(new java.awt.GridLayout(1, 4));

        ComboJoueur.setModel(new javax.swing.DefaultComboBoxModel<>(new String[] { " " }));
        ComboJoueur.setSelectedIndex(-1);
        ComboJoueur.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                ComboJoueurActionPerformed(evt);
            }
        });
        jPanel1.add(ComboJoueur);

        BAutreChoix.setText("Autre choix");
        BAutreChoix.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                BAutreChoixActionPerformed(evt);
            }
        });
        jPanel1.add(BAutreChoix);

        BAcheter.setText("Acheter");
        BAcheter.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                BAcheterActionPerformed(evt);
            }
        });
        jPanel1.add(BAcheter);

        BQuitter.setText("Quitter");
        BQuitter.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                BQuitterActionPerformed(evt);
            }
        });
        jPanel1.add(BQuitter);

        PanBouton.add(jPanel1, java.awt.BorderLayout.CENTER);

        getContentPane().add(PanBouton, java.awt.BorderLayout.SOUTH);

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void ComboJoueurActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_ComboJoueurActionPerformed
        // TODO add your handling code here:
        int ind = ComboJoueur.getSelectedIndex();
        if (ind != -1){
            this.jc = ljc.getJoueur(ind-1);
            LInfo.setText("");
            LInfo.setText(jc.getPseudo()+" a un solde de "+String.valueOf(jc.getSolde())+ "€");
        }
    }//GEN-LAST:event_ComboJoueurActionPerformed

    private void BAcheterActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_BAcheterActionPerformed
        // TODO add your handling code here:
        if(jc.acheter(cc) == true){// si le joueur peu acheter la carte
            LInfo.setText(jc.getPseudo()+" a un solde de "+String.valueOf(jc.getSolde()) + "€");// on lui affiche son nouveau solde
            this.achat = true;// un achat de carte a été réaliser, achat est fixé à true
            Panneau.removeAll();// on efface tout les composent de Panneau
            cc = new CarteLoto(nbCol, nbNum);// on créer une nouvelle carte courante
            initCarte();// on l'initialise
            afficheCarte();// et on l'affiche
        }
        else// si le joueur ne peut pas l'acheter 
            LInfo.setText("Le solde du joueur est insufisant.");// on lui dit que sont solde est insufisant pour l'achat
    }//GEN-LAST:event_BAcheterActionPerformed

    private void BQuitterActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_BQuitterActionPerformed
        // TODO add your handling code here:
            this.ok = true;// on indique qu’on clique sur Quitter
            this.setVisible(false);// on ferme la fenêtre
            this.dispose();// optimise la récupération d’espace
    }//GEN-LAST:event_BQuitterActionPerformed

    private void BAutreChoixActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_BAutreChoixActionPerformed
        // TODO add your handling code here:
        Panneau.removeAll();// on efface la carte
        cc = new CarteLoto(nbCol, nbNum);
        initCarte();
        afficheCarte();
    }//GEN-LAST:event_BAutreChoixActionPerformed

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
            java.util.logging.Logger.getLogger(AchatCarteDlg.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(AchatCarteDlg.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(AchatCarteDlg.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(AchatCarteDlg.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>
        //</editor-fold>

        /* Create and display the dialog */
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                AchatCarteDlg dialog = new AchatCarteDlg(new javax.swing.JFrame(), true);
                dialog.addWindowListener(new java.awt.event.WindowAdapter() {
                    @Override
                    public void windowClosing(java.awt.event.WindowEvent e) {
                        System.exit(0);
                    }
                });
                dialog.setVisible(true);
            }
        });
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton BAcheter;
    private javax.swing.JButton BAutreChoix;
    private javax.swing.JButton BQuitter;
    private javax.swing.JComboBox<String> ComboJoueur;
    private javax.swing.JLabel LInfo;
    private javax.swing.JLabel LTitre;
    private javax.swing.JPanel PanAffichage;
    private javax.swing.JPanel PanBouton;
    private javax.swing.JPanel PanTitre;
    private javax.swing.JPanel Panneau;
    private javax.swing.JPanel jPanel1;
    // End of variables declaration//GEN-END:variables
}
