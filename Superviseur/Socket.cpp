#include <iostream>
#include <winsock2.h>
#include <Ws2tcpip.h>
#include <stdio.h>
#include <socketapi.h>
#pragma comment (lib, "ws2_32.lib")

using namespace std;

void _debuter() // Fonction _debuter()
{
    bool dllOK = false; // true = err= 10093 // false = err = 0
#ifdef WIN32
    if (!dllOK)
    {
        WSADATA wsaData;
        int err = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if (err == 0)
        {
            // confirmation que la dll ouverte supporte WinSock 2.2
            if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
            {
                /* Tell the user that we could not find a usable */
                /*WinSock DLL.*/
                printf("Could not find a usable version of Winsock.dll\n");
                WSACleanup();
                throw ERROR_DLL_NOT_FOUND;
            }
        }
        else
        {
            puts("WSAStartup failed !");
            WSACleanup();
            throw ERROR_DLL_NOT_FOUND;
        }
        dllOK = true;
        //cout << "err : " << err << " //// Si 'err = 0' tous va bien, Si 'err = supperieur a 0' ERREUR "<< endl;
    }
#endif
}

void _finir() // Fonction _finir()
{
#ifdef WIN32

    WSACleanup();

#endif
}

SOCKET num_socket;

void CSocket_init_connection(int type, int protocol, bool version)
{
    if (!version)
        num_socket = socket(AF_INET, type, protocol);
    else
        num_socket = socket(AF_INET6, type, protocol);
    if (num_socket == INVALID_SOCKET)
    {
        perror("socket()");
        //exit(errno);
        //socket = SOCKET_ERROR;
        throw SOCKET_ERROR;
    }
}

void CSocket_end_connection(void)
{
    cout << "Deconnexion..." << endl;
    if (num_socket != INVALID_SOCKET || num_socket != SOCKET_ERROR)
        closesocket(num_socket);
    cout << "Deconnexion terminer !" << endl;
}



SOCKADDR_IN serveur;
int MAX_CLIENT = 1;
void ERREUR_BIND() {
    int bind();
    cout << "== ERREUR DE LIAISON ==" << endl;
}

void ERREUR_LISTEN() {
    cout << "== ERREUR D'ECOUTE ==" << endl;
}

void ERREUR_SOCKET_CLIENT() {
    cout << "== ERREUR_SOCKET_CLIENT ==" << endl;
}

/// INICIALISATION DE LA CONNECTION

void Serveur_TCP_init_connection() // Fonction Serveur_TCP_init_connection().
{
    if (num_socket != INVALID_SOCKET)
    {
        serveur.sin_addr.s_addr = htonl(INADDR_ANY); // adresse local
        cout << "Choisir le port : ";
        int port;

        cin >> port;

        serveur.sin_port = htons(port); // mettre le port
        serveur.sin_family = AF_INET;
        int res = bind(num_socket, (sockaddr*)&serveur, sizeof serveur);
        if (res == SOCKET_ERROR)
        {
            perror("bind()");
            num_socket = SOCKET_ERROR;
            throw ERREUR_BIND;
        }
        else
        {
            int res = listen(num_socket, MAX_CLIENT);
            if (res == SOCKET_ERROR)
            {
                perror("listen()");
                num_socket = SOCKET_ERROR;
                throw ERREUR_LISTEN;
            }
            //cout << "res : " << res << " //// Si 'res = 0' tous va bien, Si 'res = supperieur a 0' ERREUR " << endl;
        }
    }
}

void Serveur_TCP_AttenteConnexion() // Fonction Serveur_TCP_AttenteConnexion()
{
    SOCKET clientSocket;
    struct sockaddr_in SenderAddr;

    int serveursize = sizeof SenderAddr;
    cout << endl << endl;
    cout << "En attente de la connection client ..." << endl;
    clientSocket = accept(num_socket, (SOCKADDR*)&SenderAddr, &serveursize); // en attente de la connection client
    cout << "Client connecter avec le ClientSocket numero " << clientSocket << endl;
    if (clientSocket == SOCKET_ERROR)
    {
        perror("accept()");
        throw ERREUR_SOCKET_CLIENT;
    }
}

/////////////////////////////////////////////////////////////////////// MAIN /////////////////////////////////////////////////////////////////////////////////

#define IPv4 false

int main(int argc, char* argv[]) // V0.03 // Main serveur
{
    _debuter(); // pour un système Windows

    CSocket_init_connection(SOCK_STREAM, IPPROTO_TCP, IPv4); // etablir une socket

    Serveur_TCP_init_connection(); // Inicialisation de la connection pour le client

    Serveur_TCP_AttenteConnexion(); // en pas à pas le programme attend qu'un client se connecte

    CSocket_end_connection();  // fermer la socket

    _finir(); // pour un système Windows

    //cout << "num_socket : " << num_socket << endl

    //system("PAUSE"); // pour eviter la fermeture de la console
}