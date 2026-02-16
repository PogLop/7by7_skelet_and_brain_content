#include "fudis.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

void FOODISerrr(const char *err)
{
    perror(err);
    exit(1);
}

t_foodis *FOODISprepstruct(const int fport, const char fip[])
{
    t_foodis *r = malloc(sizeof(t_foodis));

    r->port = fport;
    r->ip = fip;

    return r;
}

void FOODISmail(t_foodis *f, char fdata[], const char route[])
{
    struct sockaddr_in si;
    int scfd, silen = sizeof(si);
    char send[strlen(fdata) + strlen(route) + 1];

    if( (scfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        FOODISerrr("socket initialization failed :(");
    }

    memset((char *) &si, 0, silen);

    si.sin_family = AF_INET;
    si.sin_port = htons(f->port);

    if(!inet_aton(f->ip, &si.sin_addr))
    {
        FOODISerrr("inet_aton filed? :(");
    }

    //send!!!!
    //printf("posilam <%s> na port %d a ip %s", fdata, f->port, f->ip);

    snprintf(send, sizeof(send), "%s\x20%s", route, fdata);

    if(sendto(scfd, send, strlen(send), 0, (struct sockaddr *)&si, silen) == -1)
    {
        FOODISerrr("sendto failed");
    }

    close(scfd);
}

void FOODISkonec(t_foodis *f)
{
    free(f);
}