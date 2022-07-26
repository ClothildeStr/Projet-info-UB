/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Serveur;
import java.io.*;
import java.util.*;
import java.util.regex.*;

/**
 *
 * @author strainchampsclothilde
 */
public class Traitement {
    //attribut
    public Hashtable<String, ArrayList<Integer>> joueurs;
    public Hashtable<String, Integer> parties;
    public Hashtable<String, Integer> ouvertures;
    public Hashtable<String, Integer> joueursActif;
    public ArrayList<String> plusOuvertures;
    public ArrayList<String> plusJoueurs;
    
    //constructeur standard
    public Traitement(){
        this.joueurs = new Hashtable<String, ArrayList<Integer>>();
        this.parties = new Hashtable<String, Integer>();
        this.ouvertures = new Hashtable<String, Integer>();
        this.joueursActif = new Hashtable<String, Integer>();
        this.plusOuvertures = new ArrayList<String>();
        this.plusJoueurs = new ArrayList<String>();
        try {
            chargementTables(Serveur.fichier);  
            maxOuverture();
            joueurActif();
        } catch (Exception e) {
            e.printStackTrace();
        }
        
    }
    // méthode remplissant nos hashtables   
    public void chargementTables(String fichier)throws IOException{
        //initialisation des hashtables
        String ligne, joueur1, joueur2, partie, ouverture;
        ArrayList<Integer> ligneCite = new ArrayList<Integer>();

        //lecture du fichier et remplissage des tables
        BufferedReader f=new BufferedReader(new FileReader(fichier));
        int comptLigne = 0;
        while ((ligne=f.readLine())!=null)
        {   
            comptLigne =comptLigne + 1;
            //pour prendre les lignes des joueurs
            Pattern pJoueurBlanc = Pattern.compile("White "+"\\\""+".*"+"\\\"");
            Matcher mJoueurBlanc = pJoueurBlanc.matcher(ligne);
            Pattern pJoueurNoir = Pattern.compile("Black "+"\\\""+".*"+"\\\"");
            Matcher mJoueurNoir = pJoueurNoir.matcher(ligne);
            
            //pour prendre les lignes des débuts de partie
            Pattern pSite = Pattern.compile("Site "+"\\\""+"https://lichess.org/"+"[a-zA-Z_0-9]*"+"\\\"");
            Matcher mSite = pSite.matcher(ligne);

            // pour l'ouverture
            Pattern pOuverture = Pattern.compile("Opening " + "\\\"" + ".*" + "\\\"");
            Matcher mOuverture = pOuverture.matcher(ligne);
            
            while(mJoueurBlanc.find())
            {
                joueur1 = mJoueurBlanc.group().substring(7, mJoueurBlanc.group().length()-1);
                if (joueurs.containsKey(joueur1)) 
                {    
                    joueurs.get(joueur1).add(comptLigne-2);
                } else 
                {
                    ArrayList<Integer> lignesJoueurs = new ArrayList<Integer>(Arrays.asList(comptLigne-2));
                    joueurs.put(joueur1, lignesJoueurs);
                }
                if (joueursActif.containsKey(joueur1)) 
                {   
                    int rep = joueursActif.get(joueur1);
                    rep = rep +1;
                    joueursActif.remove(joueur1);
                    joueursActif.put(joueur1, rep);
                } else{
                    joueursActif.put(joueur1, 1);
                }
            }

            while(mJoueurNoir.find())
            {
                joueur2 = mJoueurNoir.group().substring(7, mJoueurNoir.group().length()-1);     
                if (joueurs.containsKey(joueur2)) 
                {
                    joueurs.get(joueur2).add(comptLigne-3);
                } else 
                {
                    ArrayList<Integer> lignesJoueurs = new ArrayList<Integer>(Arrays.asList(comptLigne-3));
                    joueurs.put(joueur2, lignesJoueurs);
                }
                if (joueursActif.containsKey(joueur2)) 
                {   
                    int rep = joueursActif.get(joueur2);
                    rep = rep +1;
                    joueursActif.remove(joueur2);
                    joueursActif.put(joueur2, rep);
                } else{
                    joueursActif.put(joueur2, 1);
                }
            }

            
            while(mSite.find())
            {
                partie = mSite.group().substring(26, mSite.group().length()-1);       
                if (parties.containsKey(partie)) 
                {
                    parties.get(partie);
                } else{
                    parties.put(partie, comptLigne);
                }
            }
            while(mOuverture.find()) 
            {
                ouverture = mOuverture.group().substring(9, mOuverture.group().length() - 1);
                if (ouvertures.containsKey(ouverture)) 
                {   
                    int rep = ouvertures.get(ouverture);
                    rep = rep +1;
                    ouvertures.remove(ouverture);
                    ouvertures.put(ouverture, rep);
                } else{
                    ouvertures.put(ouverture, 1);
                }
            }
        }
        f.close(); 
    }
    
    //méthode remplissant notre attribut plusOuverture avec l'ouverture la plus jouée
    public void maxOuverture(){
        int maxValue = 0;
        for(Map.Entry<String,Integer> entry : ouvertures.entrySet()) {
            if(entry.getValue() > maxValue) {
               plusOuvertures.clear(); // New max remove all current keys 
               plusOuvertures.add(entry.getKey());
               maxValue = entry.getValue();
            }
            else if(entry.getValue() == maxValue)
            {
               plusOuvertures.add(entry.getKey());
            }
       }  
    }

    //méthode remplissant notre attribut plusJoueurs avec le nom du joueur qui a joué le plus de parties
    public void joueurActif(){
        int maxValue = 0;
        for(Map.Entry<String,Integer> entry : joueursActif.entrySet()) {
            if(entry.getValue() > maxValue) {
                plusJoueurs.clear(); // New max remove all current keys 
                plusJoueurs.add(entry.getKey());
                maxValue = entry.getValue();
            }
            else if(entry.getValue() == maxValue)
            {
                plusJoueurs.add(entry.getKey());
            }
       }
    }

}   
