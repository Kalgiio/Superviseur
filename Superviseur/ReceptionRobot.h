#pragma once
#include <iostream>
using namespace std;

class ReceptionRobot
{
private:
	int surv; // Surveillance en cours // 0 : En attente // 1 : Surveillance en cours // 2 : Zone d'echaufement suspecte // 3 : Depart d'incendie potentiel // 4 : Depart d'incendie avéré // 5 : Retour au socle
	int batt; // Etat de la batterie // 100% Batterie plein --> 1% Demande de rechargement
	int interv; // Etat de l'intervention // 0 : En attente // 1 : Sur le chemein // 2 : Sur les lieu // 3 : Retour au socle
	int nivExtinc; // Etat de l'extincteur // 100% Extincteur plein --> 1% Extincteur vide
public:
	ReceptionRobot(int, int, int, int);
};

