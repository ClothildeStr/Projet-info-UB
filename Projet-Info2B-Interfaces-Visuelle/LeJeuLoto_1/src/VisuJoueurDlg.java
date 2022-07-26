
import javax.swing.JFrame;

/**
 *
 * @author strainchampsclothilde
 */
public class VisuJoueurDlg extends javax.swing.JDialog {

    private Joueur lejoueur;// le joueur à visualiser
    
    // on ajoute un paramètre au constructeur généré par défaut dans l’EDI, qui est de type Joueur, pour passer en paramètre le joueur à afficher
    public VisuJoueurDlg(java.awt.Frame parent, boolean modal, Joueur j) {
        super(parent, modal);// appel du constructeur de la classe ancêtre ici JDilaog
        initComponents();// construction de l’interface faite par l’EDI
        this.lejoueur=j;// on initialise l’attribut lejoueur avecle paramètre passé j
        initInfos();// appel de la méthode qui affiche les informations du joueur
    }

    private VisuJoueurDlg(JFrame jFrame, boolean b) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }
    private void initInfos(){
        // attribut lejoueur est de type Joueur ; 
        Pseudo.setText(lejoueur.getPseudo());// on affiche le pseudo
        PCouleur.setBackground(lejoueur.getCouleur());// on colorie le panneau
        Solde.setText(""+lejoueur.getSolde());//on affiche le solde
        Photo.setIcon(lejoueur.getPhoto());// affiche la photo du joueur sous forme d’icone sur le bouton
//        Edition.setText("Le joueur s'appelle "+lejoueur.getPseudo()+"\n\n");// on affihce les informations du joueur dans la zone d’édition
//        Edition.append("Il aime la couleur : "+lejoueur.getCouleur().toString()+"\n\n");// ajoute sans effacer sa couleur en RVB
//        Edition.append("Il dispose de la somme de "+lejoueur.getSolde()+"\n\n");//ajoute sans effacer son solde
        Edition.setText("Aucun lot gagné");//on affiche "Aucun lot gagné" dans la zone d'édition.
        Edition.setEnabled(false);// on fait ensorte de pas pouvoir modifié le text de la zone dédition 
    }
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        PanTitreVisual = new javax.swing.JPanel();
        LTitreVisual = new javax.swing.JLabel();
        PanInfoVisual = new javax.swing.JPanel();
        jPanel1 = new javax.swing.JPanel();
        LPseudo = new javax.swing.JLabel();
        Pseudo = new javax.swing.JLabel();
        LCouleur = new javax.swing.JLabel();
        PCouleur = new javax.swing.JPanel();
        LSolde = new javax.swing.JLabel();
        Solde = new javax.swing.JLabel();
        jPanel2 = new javax.swing.JPanel();
        jScrollPane1 = new javax.swing.JScrollPane();
        Edition = new javax.swing.JTextArea();
        Photo = new javax.swing.JButton();
        PanBoutonVisual = new javax.swing.JPanel();
        jButton1 = new javax.swing.JButton();
        BFermer = new javax.swing.JButton();

        setDefaultCloseOperation(javax.swing.WindowConstants.DISPOSE_ON_CLOSE);

        LTitreVisual.setFont(new java.awt.Font("Lucida Grande", 0, 18)); // NOI18N
        LTitreVisual.setText("Informations relatives à un joueur");
        PanTitreVisual.add(LTitreVisual);

        getContentPane().add(PanTitreVisual, java.awt.BorderLayout.NORTH);

        PanInfoVisual.setLayout(new java.awt.GridLayout(1, 2));

        jPanel1.setLayout(new java.awt.GridLayout(3, 2));

        LPseudo.setText("Pseudo");
        jPanel1.add(LPseudo);
        jPanel1.add(Pseudo);

        LCouleur.setText("Couleur");
        jPanel1.add(LCouleur);

        javax.swing.GroupLayout PCouleurLayout = new javax.swing.GroupLayout(PCouleur);
        PCouleur.setLayout(PCouleurLayout);
        PCouleurLayout.setHorizontalGroup(
            PCouleurLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 160, Short.MAX_VALUE)
        );
        PCouleurLayout.setVerticalGroup(
            PCouleurLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 157, Short.MAX_VALUE)
        );

        jPanel1.add(PCouleur);

        LSolde.setText("Solde");
        jPanel1.add(LSolde);
        jPanel1.add(Solde);

        PanInfoVisual.add(jPanel1);

        jPanel2.setLayout(new java.awt.GridLayout(1, 2));

        Edition.setColumns(20);
        Edition.setRows(5);
        jScrollPane1.setViewportView(Edition);

        jPanel2.add(jScrollPane1);
        jPanel2.add(Photo);

        PanInfoVisual.add(jPanel2);

        getContentPane().add(PanInfoVisual, java.awt.BorderLayout.CENTER);

        PanBoutonVisual.setLayout(new java.awt.GridLayout(1, 2));
        PanBoutonVisual.add(jButton1);

        BFermer.setText("Fermer");
        BFermer.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                BFermerActionPerformed(evt);
            }
        });
        PanBoutonVisual.add(BFermer);

        getContentPane().add(PanBoutonVisual, java.awt.BorderLayout.SOUTH);

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void BFermerActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_BFermerActionPerformed
        // TODO add your handling code here:
        setVisible(false);// ferme la boite
        dispose(); // optimise la récupération d’espace
    }//GEN-LAST:event_BFermerActionPerformed

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
            java.util.logging.Logger.getLogger(VisuJoueurDlg.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(VisuJoueurDlg.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(VisuJoueurDlg.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(VisuJoueurDlg.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>

        /* Create and display the dialog */
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                VisuJoueurDlg dialog = new VisuJoueurDlg(new javax.swing.JFrame(), true);
                dialog.setVisible(true);
            }
        });
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton BFermer;
    private javax.swing.JTextArea Edition;
    private javax.swing.JLabel LCouleur;
    private javax.swing.JLabel LPseudo;
    private javax.swing.JLabel LSolde;
    private javax.swing.JLabel LTitreVisual;
    private javax.swing.JPanel PCouleur;
    private javax.swing.JPanel PanBoutonVisual;
    private javax.swing.JPanel PanInfoVisual;
    private javax.swing.JPanel PanTitreVisual;
    private javax.swing.JButton Photo;
    private javax.swing.JLabel Pseudo;
    private javax.swing.JLabel Solde;
    private javax.swing.JButton jButton1;
    private javax.swing.JPanel jPanel1;
    private javax.swing.JPanel jPanel2;
    private javax.swing.JScrollPane jScrollPane1;
    // End of variables declaration//GEN-END:variables
}
