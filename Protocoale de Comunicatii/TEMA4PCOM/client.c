#include <stdio.h>      /* printf, sprintf */
#include <stdlib.h>     /* exit, atoi, malloc, free */
#include <unistd.h>     /* read, write, close */
#include <string.h>     /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h>      /* struct hostent, gethostbyname */
#include <arpa/inet.h>
#include "helpers.h"
#include "requests.h"
#include "parson.h"

#define JSON_TYPE "application/json"
#define AUTH_STRING "Authorization: Bearer "
#define URL_REGISTER "/api/v1/tema/auth/register"
#define URL_LOGIN "/api/v1/tema/auth/login"
#define URL_ACCESS "/api/v1/tema/library/access"
#define URL_BOOKS_LIBRARY "/api/v1/tema/library/books"
#define URL_LOGOUT "/api/v1/tema/auth/logout"

char *reg_log_person()
{
    char *username = calloc(BUFLEN, sizeof(char));
    char *password = calloc(BUFLEN, sizeof(char));

    printf("username=");
    scanf("%s", username);
    printf("password=");
    scanf("%s", password);

    char *var = NULL;
    JSON_Value *root_value = json_value_init_object();
    JSON_Object *root_object = json_value_get_object(root_value);
    json_object_set_string(root_object, "username", username);
    json_object_set_string(root_object, "password", password);
    var = json_serialize_to_string(root_value);
    return var;
}

int main(int argc, char *argv[])
{
    char HOST_IP[16] = "34.254.242.81";
    int HOST_PORT = 8080;
    int socket = open_connection(HOST_IP, HOST_PORT, AF_INET, SOCK_STREAM, 0);
    char comanda[BUFLEN], token[BUFLEN];
    int conectat, ok, librarie;
    conectat = 0;
    ok = 0;
    librarie = 0;
    char *user[1], *cookies[1], cookie[100], *addbook[1];

    while (!ok)
    {
        // testam prima data daca comanda se introduce comanda de iesire
        fgets(comanda, BUFLEN, stdin);
        socket = open_connection(HOST_IP, HOST_PORT, AF_INET, SOCK_STREAM, 0);
        if (strncmp(comanda, "exit", 4) == 0)
        {
            break;
        }
        else
        {
            int socket = open_connection(HOST_IP, HOST_PORT, AF_INET, SOCK_STREAM, 0);
            if (strncmp(comanda, "register", 8) == 0)
            {
                user[0] = reg_log_person();

                // testam cazul in utilizatorul a mai fost sau nu inregistrat
                char *message = compute_post_request(HOST_IP, URL_REGISTER, "application/json", user, 1, NULL, 0, NULL);
                send_to_server(socket, message);
                char *response = receive_from_server(socket);

                if (strstr(response, "is taken") != NULL)
                {
                    printf("USERNAME FOLOSIT! Va rugam incercati un alt username!\n");
                }
                else
                {
                    printf("Acum esti inregistrat!\n");
                }

                free(message);
                free(response);
            }
            else if (strncmp(comanda, "login", 5) == 0)
            {
                conectat = 1;
                user[0] = reg_log_person();

                char *message = compute_post_request(HOST_IP, URL_LOGIN, "application/json", user, 1, NULL, 0, NULL);
                send_to_server(socket, message);
                char *response = receive_from_server(socket);

                char *cookie_ptr = strstr(response, "Set-Cookie: ");

                if (cookie_ptr == NULL)
                {
                    printf("ACCES NEREUSIT - PAROLA GRESITA!\n");
                    conectat = 0;
                    librarie = 0;
                    continue;
                }

                strtok(cookie_ptr, ";");
                cookie_ptr += 12;
                strcpy(cookie, cookie_ptr);
                cookies[0] = cookie_ptr;

                if (cookie != NULL)
                {
                    printf("TE-AI LOGAT CU SUCCES!\n");
                }

                conectat = 1;

                free(message);
                free(response);
            }
            else if (strncmp(comanda, "logout", 6) == 0)
            {
                if (conectat == 1)
                {
                    conectat = 0;
                    librarie = 0;

                    char *message = compute_get_request(HOST_IP, URL_LOGOUT, NULL, cookies, 1, token, "get");
                    send_to_server(socket, message);
                    char *response = receive_from_server(socket);

                    printf("Ai fost delogat cu succes!\n");

                    free(message);
                    free(response);
                }
                else
                {
                    error("Nu esti logat!\n");
                }
            }
            else if (strncmp(comanda, "enter_library", 13) == 0)
            {
                if (conectat && !librarie)
                {
                    // Dacă suntem logați și nu suntem în librarie, reținem tokenul pentru verificarea accesului

                    char *message = compute_get_request(HOST_IP, URL_ACCESS, NULL, cookies, 1, token, "get");
                    send_to_server(socket, message);

                    // Primim răspunsul de la server
                    char *response = receive_from_server(socket);

                    char *tok = strstr(response, "token");

                    if (tok == NULL)
                    {
                        error("NU AI ACCES IN LIBRARIE!\n");
                    }
                    else
                    {
                        tok += 8;
                        memset(token, 0, BUFLEN);
                        strncpy(token, tok, BUFLEN - 1);
                        token[strlen(token) - 2] = '\0';

                        librarie = 1;
                        printf("SUCCESS!\n");
                    }

                    // Eliberăm memoria alocată pentru răspuns
                    free(response);
                    free(message);
                }
                else if (!conectat)
                {
                    error("Nu esti logat.\n");
                }
                else
                {
                    printf("Esti deja in aceasta librarie\n");
                }
            }
            else if (strncmp(comanda, "get_books", 9) == 0)
            {
                if (librarie == 1)
                {
                    // Dacă suntem în librarie, se caută cărțile reținute
                    char *message = compute_get_request(HOST_IP, URL_BOOKS_LIBRARY, NULL, cookies, 1, token, "get");
                    send_to_server(socket, message);

                    // Primim răspunsul de la server
                    char *response = receive_from_server(socket);

                    printf("%s\n", strstr(response, "["));

                    // Eliberăm memoria alocată pentru răspuns
                    free(response);
                    free(message);
                }
                else
                {
                    error("Nu esti in librarie.\n");
                }
            }
            else if (strncmp(comanda, "get_book", 8) == 0)
            {
                if (librarie == 1)
                {
                    // Dacă suntem în librarie, se preia id-ul
                    char route[BUFLEN], bok[BUFLEN];
                    int book_id = 0;

                    printf("id=");
                    scanf("%s", bok);
                    book_id = atoi(bok);

                    sprintf(route, "%s/%d", URL_BOOKS_LIBRARY, book_id);

                    // Se construiește cererea GET pentru a obține detaliile cărții
                    char *message = compute_get_request(HOST_IP, route, NULL, cookies, 1, token, "get");
                    send_to_server(socket, message);

                    // Primim răspunsul de la server
                    char *response = receive_from_server(socket);

                    if (strstr(response, "Cartea nu a fost gasita!") != NULL)
                    {
                        error("CARTEA NU A FOST GASITA!\n");
                    }
                    else
                    {
                        printf("%s\n", strstr(response, "{"));
                    }

                    // Eliberăm memoria alocată pentru răspuns și cerere
                    free(response);
                    free(message);
                }
                else
                {
                    error("Nu esti in librarie!\n");
                }
            }
            else if (strncmp(comanda, "add_book", 8) == 0)
            {
                if (librarie == 1)
                {
                    // Daca suntem in librarie, se preiau informatiile despre carte

                    char title[BUFLEN], genre[BUFLEN], author[BUFLEN], publisher[BUFLEN], pg[BUFLEN];

                    printf("title=");
                    scanf("%s", title);
                    printf("author=");
                    scanf("%s", author);
                    printf("genre=");
                    scanf("%s", genre);
                    printf("publisher=");
                    scanf("%s", publisher);
                    printf("pages=");
                    scanf("%s", pg);

                    JSON_Value *value = json_value_init_object();
                    JSON_Object *object = json_value_get_object(value);
                    json_object_set_string(object, "title", title);
                    json_object_set_string(object, "author", author);
                    json_object_set_string(object, "genre", genre);
                    json_object_set_string(object, "page_count", pg);
                    json_object_set_string(object, "publisher", publisher);
                    addbook[0] = json_serialize_to_string(value);

                    // Construim cererea POST
                    char *var = compute_post_request(HOST_IP, URL_BOOKS_LIBRARY, "application/json", addbook, 1, NULL, 0, token);
                    send_to_server(socket, var);
                    receive_from_server(socket);

                    printf("Success!\n");
                }
                else
                    error("NU esti in librarie.\n");
            }
            else if (strncmp(comanda, "delete_book", 11) == 0)
            {
                if (librarie == 1)
                {
                    // Daca suntem in librarie, se preia id-ul

                    char route[BUFLEN], book[BUFLEN];
                    int book_id = 0;

                    printf("id=");
                    scanf("%s", book);
                    book_id = atoi(book);
                    sprintf(route, "%s/%d", URL_BOOKS_LIBRARY, book_id);

                    // Se construiește și se trimite cererea DELETE la server
                    char *request = compute_get_request(HOST_IP, route, NULL, cookies, 0, token, "delete");
                    send_to_server(socket, request);
                    free(request);

                    // Se primește răspunsul de la server
                    char *response = receive_from_server(socket);

                    // Se verifică dacă cartea a fost ștearsă sau nu
                    char *deleted = strstr(response, "Cartea nu a fost stearsa!");

                    if (deleted != NULL)
                        error("Cartea nu a fost gasita!\n");
                    else
                        printf("Succes!\n");

                    // Se eliberează memoria alocată pentru răspuns
                    free(response);
                }
                else
                    error("Nu esti in librarie\n");
            }

            close_connection(socket);
        }
    }
}