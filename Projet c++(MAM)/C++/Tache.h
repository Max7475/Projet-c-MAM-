#ifndef TACHE_H
#define TACHE_H

#include <string>

class Tache {
public:
    enum Priorite { BASSE, MOYENNE, ELEVEE };
    enum Statut { EN_COURS, EN_ATTENTE, TERMINE };

private:
    std::string titre;
    std::string description;
    Priorite priorite;
    std::string deadline;
    Statut statut;

public:
    // Constructeur
    Tache(const std::string& titre, const std::string& description, Priorite priorite, const std::string& deadline, Statut statut);

    // Getters
    std::string getTitre() const;
    std::string getDescription() const;
    Priorite getPriorite() const;
    std::string getDeadline() const;
    Statut getStatut() const;

    // Setters
    void setTitre(const std::string& titre);
    void setDescription(const std::string& description);
    void setPriorite(Priorite priorite);
    void setDeadline(const std::string& deadline);
    void setStatut(Statut statut);

    // Méthodes auxiliaires
    static std::string prioriteToString(Priorite priorite);
    static std::string statutToString(Statut statut);

    // Méthode pour afficher les informations de la tâche
    void afficher() const;
};

#endif
