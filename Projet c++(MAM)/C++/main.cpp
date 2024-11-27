#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include "Tache.h"
#include <algorithm>
#include <sstream>
// Prototypes des fonctions
void afficherMenu();
void ajouterTache(std::list<Tache>& taches);
void modifierTache(std::list<Tache>& taches);
void modifierStatutTache(std::list<Tache>& taches); // Nouvelle fonction
void supprimerTache(std::list<Tache>& taches);
void afficherTaches(const std::list<Tache>& taches, Tache::Statut statut = Tache::Statut::EN_COURS, bool toutes = true);
void rechercherTache(const std::list<Tache>& taches);
void sauvegarderTaches(const std::list<Tache>& taches);
void chargerTaches(std::list<Tache>& taches);

const std::string FICHIER_TACHES = "taches.txt";

int main() {
    std::list<Tache> taches;

    // Charger les tâches depuis le fichier
    chargerTaches(taches);

    int choix;
    do {
        afficherMenu();
        std::cout << "Entrez votre choix : ";
        std::cin >> choix;
        std::cin.ignore(); // Nettoyer le buffer

        switch (choix) {
            case 1: ajouterTache(taches); break;
            case 2: modifierTache(taches); break;
            case 3: supprimerTache(taches); break;
            case 4: afficherTaches(taches, Tache::Statut::TERMINE, false); break;
            case 5: afficherTaches(taches, Tache::Statut::EN_COURS, false); break;
            case 6: afficherTaches(taches, Tache::Statut::EN_ATTENTE, false); break;
            case 7: afficherTaches(taches); break;
            case 8: rechercherTache(taches); break;
            case 9: modifierStatutTache(taches); break; 
            case 0: 
                sauvegarderTaches(taches);
                std::cout << "Sauvegarde terminée. Au revoir !\n";
                break;
            default: std::cout << "Choix invalide, réessayez.\n";
        }
    } while (choix != 0);

    return 0;
}
//dECLARATION DES FOCNTION

void afficherMenu() {
    std::cout << "\n============#######     BIENVENU SUR PLANIFICATEUR DE TACHE PERSONNELE     #######=============\n";
    std::cout << "\n=============== MENU ===================\n";
    std::cout << "1. Ajouter une tâche\n";
    std::cout << "2. Modifier une tâche\n";
    std::cout << "3. Supprimer une tâche\n";
    std::cout << "4. Afficher toutes les tâches terminées\n";
    std::cout << "5. Afficher toutes les tâches en cours\n";
    std::cout << "6. Afficher toutes les tâches en attente\n";
    std::cout << "7. Afficher toutes les tâches\n";
    std::cout << "8. Rechercher une tâche par mot-clé\n";
    std::cout << "9. Modifier le statut d'une tâche\n"; 
    std::cout << "0. Quitter\n";
}

void ajouterTache(std::list<Tache>& taches) { //Fonction pour l'ajout d'une tache
    std::string titre, description, deadline;
    int priorite, statut;

    std::cout << "Entrez le titre : ";
    std::getline(std::cin, titre);
    std::cout << "Entrez la description : ";
    std::getline(std::cin, description);
    std::cout << "Entrez la priorité (0: Basse, 1: Moyenne, 2: Élevée) : ";
    std::cin >> priorite;
    std::cin.ignore();
    std::cout << "Entrez la date limite : ";
    std::getline(std::cin, deadline);
    std::cout << "Entrez le statut (0: En cours, 1: En attente, 2: Terminé) : ";
    std::cin >> statut;
    std::cin.ignore();

    Tache nouvelleTache(titre, description, static_cast<Tache::Priorite>(priorite), deadline, static_cast<Tache::Statut>(statut));
    taches.push_back(nouvelleTache);
    sauvegarderTaches(taches);
    std::cout << "Tâche ajoutée avec succès !\n";
}

void modifierTache(std::list<Tache>& taches) { //Fonction pour la modification d'une tache
    std::string titre;
    std::cout << "Entrez le titre de la tâche à modifier : ";
    std::getline(std::cin, titre);

    for (auto& tache : taches) {
        if (tache.getTitre() == titre) {
            std::string newTitre, newDescription, newDeadline;
            int newPriorite, newStatut;

            std::cout << "Entrez le nouveau titre (laisser vide pour ne pas changer) : ";
            std::getline(std::cin, newTitre);
            if (!newTitre.empty()) tache.setTitre(newTitre);

            std::cout << "Entrez la nouvelle description (laisser vide pour ne pas changer) : ";
            std::getline(std::cin, newDescription);
            if (!newDescription.empty()) tache.setDescription(newDescription);

            std::cout << "Entrez la nouvelle priorité (0: Basse, 1: Moyenne, 2: Élevée, -1 pour ne pas changer) : ";
            std::cin >> newPriorite;
            std::cin.ignore();
            if (newPriorite != -1) tache.setPriorite(static_cast<Tache::Priorite>(newPriorite));

            std::cout << "Entrez la nouvelle date limite (laisser vide pour ne pas changer) : ";
            std::getline(std::cin, newDeadline);
            if (!newDeadline.empty()) tache.setDeadline(newDeadline);

            std::cout << "Entrez le nouveau statut (0: En cours, 1: En attente, 2: Terminé, -1 pour ne pas changer) : ";
            std::cin >> newStatut;
            std::cin.ignore();
            if (newStatut != -1) tache.setStatut(static_cast<Tache::Statut>(newStatut));

            sauvegarderTaches(taches);
            std::cout << "Tâche modifiée avec succès !\n";
            return;
        }
    }
    std::cout << "Tâche non trouvée.\n";
}

void modifierStatutTache(std::list<Tache>& taches) {//Fonction ppour la modification de statut d'une tache
    std::string titre;
    std::cout << "Entrez le titre de la tâche dont vous souhaitez modifier le statut : ";
    std::getline(std::cin, titre);

    for (auto& tache : taches) {
        if (tache.getTitre() == titre) {
            int newStatut;
            std::cout << "Entrez le nouveau statut (0: En cours, 1: En attente, 2: Terminé) : ";
            std::cin >> newStatut;
            std::cin.ignore();

            tache.setStatut(static_cast<Tache::Statut>(newStatut));
            sauvegarderTaches(taches);
            std::cout << "Statut modifié avec succès !\n";
            return;
        }
    }
    std::cout << "Tâche non trouvée.\n";
}

void supprimerTache(std::list<Tache>& taches) { //Focntion pour la suppression d'une tache
    std::string titre;
    std::cout << "Entrez le titre de la tâche à supprimer : ";
    std::getline(std::cin, titre);

    auto it = std::find_if(taches.begin(), taches.end(), [&](const Tache& tache) {
        return tache.getTitre() == titre;
    });

    if (it != taches.end()) {
        taches.erase(it);
        sauvegarderTaches(taches);
        std::cout << "Tâche supprimée avec succès !\n";
    } else {
        std::cout << "Tâche non trouvée.\n";
    }
}

// fonctions pour afficher une tache

void afficherTaches(const std::list<Tache>& taches, Tache::Statut statut, bool toutes) {
    if (toutes) {
        std::cout << "\n--- Toutes les tâches ---\n";
        for (const auto& tache : taches) {
            tache.afficher();
        }
    } else {
        std::cout << "\n--- Tâches filtrées ---\n";
        for (const auto& tache : taches) {
            if (tache.getStatut() == statut) {
                tache.afficher();
            }
        }
    }
}

void rechercherTache(const std::list<Tache>& taches) { //Pour la recherche dune tache
    std::string motCle;
    std::cout << "Entrez le mot-clé pour la recherche : ";
    std::getline(std::cin, motCle);

    std::cout << "\n--- Résultats de la recherche ---\n";
    for (const auto& tache : taches) {
        if (tache.getTitre().find(motCle) != std::string::npos ||
            tache.getDescription().find(motCle) != std::string::npos) {
            tache.afficher();
        }
    }
}

void sauvegarderTaches(const std::list<Tache>& taches) { //pour le sauvegarde dune tache
    std::ofstream fichier(FICHIER_TACHES);
    for (const auto& tache : taches) {
        fichier << tache.getTitre() << ";"
                << tache.getDescription() << ";"
                << static_cast<int>(tache.getPriorite()) << ";"
                << tache.getDeadline() << ";"
                << static_cast<int>(tache.getStatut()) << "\n";
    }
}

void chargerTaches(std::list<Tache>& taches) { //pour le chargement d'une tache
    std::ifstream fichier(FICHIER_TACHES);
    std::string ligne;
    while (std::getline(fichier, ligne)) {
        std::stringstream ss(ligne);
        std::string titre, description, deadline;
        int priorite, statut;

        std::getline(ss, titre, ';');
        std::getline(ss, description, ';');
        ss >> priorite;
        ss.ignore(); // ignorer le point-virgule
        std::getline(ss, deadline, ';');
        ss >> statut;

        taches.push_back(Tache(titre, description, static_cast<Tache::Priorite>(priorite), deadline, static_cast<Tache::Statut>(statut)));
    }
}
