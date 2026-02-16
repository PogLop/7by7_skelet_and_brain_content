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
    const char *ipa;
    struct sockaddr_in si;
    int scfd, port, silen = sizeof(si);

    port = f->port;
    ipa = f->ip;

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
    if(sendto(scfd, fdata, strlen(fdata), 0, (struct sockaddr *)&si, silen) == -1)
    {
        FOODISerrr("sendto :( fruck");
    }

    close(scfd);
}

void FOODISkonec(t_foodis *f)
{
    free(f);
}