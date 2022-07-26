
import java.util.ArrayList;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author strainchampsclothilde
 */
public class LesLots {
    
    private ArrayList<Lot> lstL;//attribut de type arraylist
    
    public LesLots(){
        lstL = new ArrayList<Lot>();
    }
    
    public Lot getLot(int i){
        return this.lstL.get(i);
    }
    public int getNbLot(){
        return this.lstL.size();
    }
    public void ajouteLot(Lot l){
        this.lstL.add(l); //on ajoute le lot à lstL
    }
    public void supprimeLot(Lot l){
        int ind = this.lstL.indexOf(l);// on prend l'idice du lot l
        if(ind!= -1)//si ind est différent de -1
            this.lstL.remove(ind);//on efface le joueur de la liste lstL
    }
    public Lot rechLotNiv(int l){
           for(int i=0; i<getNbLot(); i++){//on parcourt la liste
               if(this.getLot(i).getNiveau() == l) //si nos deux niveau de lot sont égaux
                   return this.getLot(i); //on retourne le lot
               else 
                   return null;//sinon rien
           }
        return null;
    }
}
