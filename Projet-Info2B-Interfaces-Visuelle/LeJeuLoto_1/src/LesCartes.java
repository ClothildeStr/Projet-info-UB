import java.awt.Color;
import java.util.ArrayList;
import javax.swing.DefaultListModel;

/**
 *
 * @author strainchampsclothilde
 */
public class LesCartes {
    private ArrayList<CarteLoto> lst;
    
    public LesCartes(){
        lst = new ArrayList<CarteLoto>();
    }
    public int getTaille(){
        return this.lst.size();
    }
    public CarteLoto getCarte(int i){
        return this.lst.get(i);
    }
    public void ajouteCarte(CarteLoto c){
        this.lst.add(c); 
    }
    public void retireCarte(CarteLoto c){
        int ind=this.lst.indexOf(c);
        if (ind != -1)
            this.lst.remove(ind); 
    }
    public void retireCartes(){
        this.lst.clear();
    }
    public LesCartes rechCartes(int num){
        LesCartes ll= new LesCartes();
        for (int i=0; i<getTaille(); i++){
            CarteLoto c= getCarte(i);
            if(c.estDans(num)){
                ll.ajouteCarte(c);
            }
        }
        return ll;
    }
    public void initLesCartes(int n, int nbcol, int nbval){
        for(int i=0; i<n; i++){
            CarteLoto c = new CarteLoto(nbcol, nbval);
            ajouteCarte(c);
        }
    }
    public String toString(){
        String res="";
        for(int i=0; i<this.getTaille();i++){
            CarteLoto c = this.lst.get(i);
            res+="Carte n°"+(i+1)+"\n"+c.toString()+"\n";
	}
	return res;
    }
}
