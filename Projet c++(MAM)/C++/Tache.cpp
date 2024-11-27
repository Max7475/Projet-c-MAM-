#include "Tache.h"
#include <iostream> // Inclusion nécessaire pour std::cout

// Constructeur
Tache::Tache(const std::string& titre, const std::string& description, Priorite priorite, const std::string& deadline, Statut statut)
    : titre(titre), description(description), priorite(priorite), deadline(deadline), statut(statut) {}

// Getters
std::string Tache::getTitre() const {
    return titre;
}

std::string Tache::getDescription() const {
    return description;
}

Tache::Priorite Tache::getPriorite() const {
    return priorite;
}

std::string Tache::getDeadline() const {
    return deadline;
}

Tache::Statut Tache::getStatut() const {
    return statut;
}

// Setters
void Tache::setTitre(const std::string& titre) {
    this->titre = titre;
}

void Tache::setDescription(const std::string& description) {
    this->description = description;
}

void Tache::setPriorite(Priorite priorite) {
    this->priorite = priorite;
}

void Tache::setDeadline(const std::string& deadline) {
    this->deadline = deadline;
}

void Tache::setStatut(Statut statut) {
    this->statut = statut;
}

// Conversion enum -> string
std::string Tache::prioriteToString(Priorite priorite) {
    switch (priorite) {
        case BASSE: return "Basse";
        case MOYENNE: return "Moyenne";
        case ELEVEE: return "Élevée";
    }
    return "";
}

std::string Tache::statutToString(Statut statut) {
    switch (statut) {
        case EN_COURS: return "En cours";
        case EN_ATTENTE: return "En attente";
        case TERMINE: return "Terminé";
    }
    return "";
}

// Méthode afficher
void Tache::afficher() const {
    std::cout << "Titre       : " << titre << '\n'
              << "Description : " << description << '\n'
              << "Priorité    : " << prioriteToString(priorite) << '\n'
              << "Deadline    : " << deadline << '\n'
              << "Statut      : " << statutToString(statut) << '\n'
              << "------------------------------------\n";
}
