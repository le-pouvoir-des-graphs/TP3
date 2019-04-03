#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <climits>


using namespace std;

struct Node {
    int tache, dur, pred;
};

Node createNode(int t, int d, int p)
{
    Node n;
    n.tache = t;
    n.dur = d;
    n.pred = p;
    return n;
}

class Graph {
    int taille;
    vector<Node> arcs;

    public:
        Graph(string nomFichier)
        {
            arcs = graphepotentieltache(nomFichier);
        }
        
        vector<Node> graphepotentieltache(string nomFichier) {
            cout << "Création du graph : " << endl;
            vector<Node> nodes;
	        ifstream fichier(nomFichier);
	        if(fichier.is_open())
	        {
		        taille = 0;
		        string ligne;
		        while(getline(fichier, ligne))
		        {
                    istringstream iss(ligne);
                    string buffer;
                    int count = 0;
                    int tache, dur, pred;
                    while(getline(iss, buffer, ' ')) {  
				        if(count == 0)
                        {
                            tache = stoi(buffer);
                        }
                        else if(count == 1)
                        {
                            dur = stoi(buffer);
                        }
                        else
                        {
                            istringstream iss2(buffer);
                            string buffer2;
                            while(getline(iss2, buffer2, ',')) {
                                pred = stoi(buffer2);
                                nodes.insert(nodes.end(),createNode(tache,dur,pred));
                                cout << "insert : " << tache << " " << dur << " " << pred << endl ;
                            }
                        }
                        count++;
                    }
                    taille++;
                }
		        fichier.close();
                //taille;
                return nodes;
	        }
	        else
	        {
		        cerr << "ERREUR le fichier " << nomFichier << " n'existe pas" << endl;
                return nodes;
	        }
        }

        int maxDistance(int dist[]) {   
	        int max = INT_MIN, max_index; 
	        for (int i = 0; i < taille; i++) 
		        if (dist[i] >= max) 
			        max = dist[i], max_index = i; 
	        return max_index; 
        }

        void earlierStartingDate()
        {
            int esd[taille];
            int pere[taille];
	        
	        for (int i = 0; i < taille; i++) {
		        esd[i], pere[i] = INT_MIN, -1;
            }
            pere[0] = -1;
	        esd[0] = 0; 

	        for (int cpt = 0; cpt < taille; cpt++) { 
                int i = maxDistance(esd); 
                int u = arcs.at(cpt).pred; 
		        int v = arcs.at(cpt).tache; 
		        int duration = arcs.at(cpt).dur; 
		        for (int j = 0; j < taille; j++) 
			        if (esd[i] + duration > esd[j]) {
				        esd[v] = esd[u] + duration; 
				        pere[v] = u;
			        }
	        }
            
            cout << "Earlier Starting Date \n" << endl;
	        for (int i = 0; i < taille; i++) 
		        cout << "sommet " << i << " : early => " << esd[i] << endl; 
	        cout << endl;
            
        }

        void latestStartingDate()
        {
            int esd[taille];
            int pere[taille];
	        
	        for (int i = 0; i < taille; i++) {
		        esd[i], pere[i] = INT_MIN, -1;
            }
            pere[0] = -1;
	        esd[0] = 0; 

	        for (int cpt = 0; cpt < taille; cpt++) {
                int i = maxDistance(esd); 
                int u = arcs.at(cpt).pred; 
		        int v = arcs.at(cpt).tache; 
		        int duration = arcs.at(cpt).dur; 
		        for (int j = 0; j < taille; j++) 
			        if (esd[i] + duration > esd[j]) {
				        esd[v] = esd[u] + duration; 
				        pere[v] = u;
			        }
	        }
            int lsd[taille];
	        for (int cpt = taille-1; cpt >= 0; cpt--) {	 
                int u = arcs.at(cpt).pred; 
		        int v = arcs.at(cpt).tache; 
		        int w = arcs.at(cpt).dur; 	
		        lsd[u] = esd[v]-w;
	        }
	        lsd[0] = esd[0];
	        lsd[taille-1] = esd[taille-1];
            cout << "Latest Starting Date \n" << endl;
	        for (int i = 0; i < taille; i++) 
		        cout << "sommet " << i << " : latest => " << lsd[i] << endl; 
	        cout << endl;
        }
        
        void criticalPath()
        {
            int esd[taille];
            int pere[taille];
	        
	        for (int i = 0; i < taille; i++) {
		        esd[i], pere[i] = INT_MIN, -1;
            }
            pere[0] = -1;
	        esd[0] = 0; 

	        for (int cpt = 0; cpt < taille; cpt++) { 
                int i = maxDistance(esd); 
                int u = arcs.at(cpt).pred; 
		        int v = arcs.at(cpt).tache; 
		        int duration = arcs.at(cpt).dur; 
		        for (int j = 0; j < taille; j++) 
			        if (esd[i] + duration > esd[j]) {
				        esd[v] = esd[u] + duration; 
				        pere[v] = u;
			        }
	        }
            int lsd[taille];
	        for (int cpt = taille-1; cpt >= 0; cpt--) {	 
                int u = arcs.at(cpt).pred; 
		        int v = arcs.at(cpt).tache; 
		        int w = arcs.at(cpt).dur; 	
		        lsd[u] = esd[v]-w;
	        }
            cout << "Critical Path \n" << endl;
	        for (int i = 0; i < taille; i++) {
		        if(esd[i]-lsd[i]==0)
			        cout << i << "->";
            }
            cout <<endl;
        }
        
};



int main() { 	
	Graph g = Graph("matrice2");
    g.earlierStartingDate();
    g.latestStartingDate();
    g.criticalPath();
	return 0; 
}
