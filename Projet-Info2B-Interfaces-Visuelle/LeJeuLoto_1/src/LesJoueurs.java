
import java.util.ArrayList;

/**
 *
 * @author strainchampsclothilde
 */
public class LesJoueurs {
    
    private ArrayList<Joueur> lstJ;//attribut de type arraylist
    
    
    public LesJoueurs(){
        lstJ = new ArrayList<Joueur>();
    }
    public ArrayList<Joueur> getlistJoueur(){
        return this.lstJ;//accesseur de la liste
    }
    public Joueur getJoueur(int i){
        return this.lstJ.get(i);
    }
    public int getNbJoueur(){
        return this.lstJ.size();
    }
    public void ajouteJoueur(Joueur j){
        this.lstJ.add(j); //on ajoute le joueur à lstJ
    }
    public void supprimeJoueur(Joueur j){
        int ind = this.lstJ.indexOf(j);// on prend l'idice du joueur j
        if(ind!= -1)//si ind est différent de -1
            this.lstJ.remove(ind);//on efface le joueur de la liste lstJ
    }
    public Joueur rechJoueur(String ps){
        if(!ps.equals("")){//si le pseudo n'est pas null
           for(int i=0; i<getNbJoueur(); i++){//on parcourt la liste
               if(this.getJoueur(i).getPseudo().equals(ps)) //si nos deux chaine de caractère sont égales (pseudo)
                   return this.getJoueur(i); //on retourne le joueur
               else 
                   return null;//sinon rien
           }
        }
        return null;
    }
    public String toString(){
        String res="";
        for(int i=0; i<this.getNbJoueur();i++){
            Joueur j = this.lstJ.get(i);
            res+="Joueur n°"+(i+1)+j.toString()+"\n";
	}
	return res;
    }
}
