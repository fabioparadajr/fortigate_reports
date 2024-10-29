#include <stdio.h>
#include <stdlib.h>
#include <libssh/libssh.h>
#include "file_handler.c"

#define HOST "10.64.10.1"
#define USER "admin"
#define PASS "sxxxx"
#define FL "comandos.txt"
#define OUT "saida.txt"

int main() {
    ssh_session session = ssh_new();
    if (!session) return -1;

    // Configurações da sessão
    ssh_options_set(session, SSH_OPTIONS_HOST, HOST); // IP do firewall
    int port = 22;
    ssh_options_set(session, SSH_OPTIONS_PORT, &port);

    // Conexão
    if (ssh_connect(session) != SSH_OK) {
        ssh_free(session);
        return -1;
    }

    // Autenticação
    if (ssh_userauth_password(session, USER, PASS) != SSH_AUTH_SUCCESS) {
        ssh_disconnect(session);
        ssh_free(session);
        return -1;
    }

    char *conteudo = ler_arquivo(FL);



    // Executar comando
    ssh_channel channel = ssh_channel_new(session);
    ssh_channel_open_session(channel);
    ssh_channel_request_exec(channel, conteudo); // Substitua "ls" pelo seu comando

    // Ler saída
    char buffer[1024];
    int nbytes;

        FILE *file = fopen(OUT,"w");

    //   fclose(file);


    while ((nbytes = ssh_channel_read(channel, buffer, sizeof(buffer), 0)) > 0) {
       fwrite(buffer, 1, nbytes, file);
       //escrever_arquivo(buffer);
    }

    fclose(file);
    // Limpeza
    ssh_channel_send_eof(channel);
    ssh_channel_close(channel);
    ssh_channel_free(channel);
    ssh_disconnect(session);
    ssh_free(session);
    free(conteudo);

    return 0;
}
