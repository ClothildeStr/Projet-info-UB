
import java.awt.Color;
import javax.swing.JColorChooser;


/**
 *
 * @author strainchampsclothilde
 */
public class AjoutJoueurDlg extends javax.swing.JDialog {
    
    private Joueur nj;// le nouveau joueur 
    private boolean ok;// pour la fermeture
    
    public AjoutJoueurDlg(java.awt.Frame parent, boolean modal) {
        super(parent, modal);// appel du constructeur de la classe ancêtre ici JDilaog
        initComponents();// construction de l’interface faite par l’EDI
        this.nj= new Joueur();// on crée un joueur par défaut, appel du constructeur par défaut
        this.ok= false;// par défaut fermeture par Annuler
    }
    //On laisse les attributs en private -> on fait des accesseurs 
    public boolean getOk(){
        return this.ok;
    }
    public Joueur getJoueur(){
        return this.nj;
    }
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        PanTitre = new javax.swing.JPanel();
        LTitre = new javax.swing.JLabel();
        PanSaisie = new javax.swing.JPanel();
        jPanel1 = new javax.swing.JPanel();
        LPseudo = new javax.swing.JLabel();
        LCouleur = new javax.swing.JLabel();
        LSolde = new javax.swing.JLabel();
        jPanel2 = new javax.swing.JPanel();
        Pseudo = new javax.swing.JTextField();
        PanChoixCoul = new javax.swing.JPanel();
        BCouleur = new javax.swing.JButton();
        PanCouleur = new javax.swing.JPanel();
        Solde = new javax.swing.JLabel();
        PanBouton = new javax.swing.JPanel();
        BAnnuler = new javax.swing.JButton();
        BValider = new javax.swing.JButton();

        setDefaultCloseOperation(javax.swing.WindowConstants.DISPOSE_ON_CLOSE);

        LTitre.setFont(new java.awt.Font("Nadeem", 0, 24)); // NOI18N
        LTitre.setText("Saisie d'un nouveau joueur");
        PanTitre.add(LTitre);

        getContentPane().add(PanTitre, java.awt.BorderLayout.NORTH);

        PanSaisie.setLayout(new java.awt.GridLayout(1, 2));

        jPanel1.setLayout(new java.awt.GridLayout(4, 0));

        LPseudo.setFont(new java.awt.Font("Lucida Grande", 0, 18)); // NOI18N
        LPseudo.setText("Pseudo");
        jPanel1.add(LPseudo);

        LCouleur.setFont(new java.awt.Font("Lucida Grande", 0, 18)); // NOI18N
        LCouleur.setText("Couleur");
        jPanel1.add(LCouleur);

        LSolde.setFont(new java.awt.Font("Lucida Grande", 0, 18)); // NOI18N
        LSolde.setText("Solde");
        jPanel1.add(LSolde);

        PanSaisie.add(jPanel1);

        jPanel2.setLayout(new java.awt.GridLayout(4, 0));

        Pseudo.setFont(new java.awt.Font("Lucida Grande", 0, 14)); // NOI18N
        jPanel2.add(Pseudo);

        PanChoixCoul.setLayout(new java.awt.GridLayout(1, 2));

        BCouleur.setFont(new java.awt.Font("Lucida Grande", 0, 14)); // NOI18N
        BCouleur.setText("Choisir couleur");
        BCouleur.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                BCouleurActionPerformed(evt);
            }
        });
        PanChoixCoul.add(BCouleur);

        javax.swing.GroupLayout PanCouleurLayout = new javax.swing.GroupLayout(PanCouleur);
        PanCouleur.setLayout(PanCouleurLayout);
        PanCouleurLayout.setHorizontalGroup(
            PanCouleurLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 170, Short.MAX_VALUE)
        );
        PanCouleurLayout.setVerticalGroup(
            PanCouleurLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 103, Short.MAX_VALUE)
        );

        PanChoixCoul.add(PanCouleur);

        jPanel2.add(PanChoixCoul);

        Solde.setFont(new java.awt.Font("Lucida Grande", 0, 14)); // NOI18N
        Solde.setText("20.0 €");
        jPanel2.add(Solde);

        PanSaisie.add(jPanel2);

        getContentPane().add(PanSaisie, java.awt.BorderLayout.CENTER);

        PanBouton.setLayout(new java.awt.GridLayout(1, 2));

        BAnnuler.setFont(new java.awt.Font("Lucida Grande", 0, 18)); // NOI18N
        BAnnuler.setText("Annuler");
        BAnnuler.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                BAnnulerActionPerformed(evt);
            }
        });
        PanBouton.add(BAnnuler);

        BValider.setFont(new java.awt.Font("Lucida Grande", 0, 18)); // NOI18N
        BValider.setText("Valider");
        BValider.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                BValiderActionPerformed(evt);
            }
        });
        PanBouton.add(BValider);

        getContentPane().add(PanBouton, java.awt.BorderLayout.SOUTH);

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void BCouleurActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_BCouleurActionPerformed
        // TODO add your handling code here:
        JColorChooser diag = new JColorChooser();// JColorChooser -> boite de dilaogue pour le choix d’une couleur
        Color coul = diag.showDialog(this,"Couleur",Color.red);
        // this désigne la fenêtre qui gère la boite ici la JFrame.
        // « couleur » -> titre de la boite (au dessus)
        // on récupère par la méthode showDialog la couleur sélectionnée
        if (coul != null){// coul = null si la boite a été fermée par Cancel
            nj.setCouleur(coul);// on affecte au joueur la couleur sélectionnée
            PanCouleur.setBackground(coul);// on colorie le panneau PanCouleur
        }
    }//GEN-LAST:event_BCouleurActionPerformed

    private void BValiderActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_BValiderActionPerformed
        // TODO add your handling code here:
        this.nj.setPseudo(Pseudo.getText());// on récupère le pseudo, on l’affecte au joueur
        this.nj.setSolde(20.0);// on fixe la solde du joueur à 20 par défault 
        this.ok=true;// on indique qu’on clique sur Valider
        this.setVisible(false);// on ferme la fenêtre
        this.dispose();// optimise la récupération d’espace
    }//GEN-LAST:event_BValiderActionPerformed

    private void BAnnulerActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_BAnnulerActionPerformed
        // TODO add your handling code here:
        setVisible(false);// ferme la boite
        dispose(); // optimise la récupération d’espace
    }//GEN-LAST:event_BAnnulerActionPerformed

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
            java.util.logging.Logger.getLogger(AjoutJoueurDlg.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(AjoutJoueurDlg.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(AjoutJoueurDlg.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(AjoutJoueurDlg.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>

        /* Create and display the dialog */
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                AjoutJoueurDlg dialog = new AjoutJoueurDlg(new javax.swing.JFrame(), true);
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
    private javax.swing.JButton BAnnuler;
    private javax.swing.JButton BCouleur;
    private javax.swing.JButton BValider;
    private javax.swing.JLabel LCouleur;
    private javax.swing.JLabel LPseudo;
    private javax.swing.JLabel LSolde;
    private javax.swing.JLabel LTitre;
    private javax.swing.JPanel PanBouton;
    private javax.swing.JPanel PanChoixCoul;
    private javax.swing.JPanel PanCouleur;
    private javax.swing.JPanel PanSaisie;
    private javax.swing.JPanel PanTitre;
    private javax.swing.JTextField Pseudo;
    private javax.swing.JLabel Solde;
    private javax.swing.JPanel jPanel1;
    private javax.swing.JPanel jPanel2;
    // End of variables declaration//GEN-END:variables
}
