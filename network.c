/*
** network.c for zappy in /home/gaular_e/PSU_2014_zappy/server
**
** Made by Emeline Gaulard
** Login   <gaular_e@epitech.net>
**
** Started on  Wed May  6 16:28:40 2015 Emeline Gaulard
** Last update Tue Jul  7 16:07:55 2015 Emeline Gaulard
*/

#include <stdio.h>
#include "network.h"

int	error(char *str)
{
  fprintf(stderr, "%s\n", str);
  return (-1);
}

void	init_struct(struct sockaddr_in *s_in, int port, char *ip)
{
  s_in->sin_family = AF_INET;
  s_in->sin_port = htons(port);
  if (!ip)
    s_in->sin_addr.s_addr = INADDR_ANY;
  else
    s_in->sin_addr.s_addr = inet_addr(ip);
}

void	update_max(t_server *server, int nb)
{
  server->max += nb;
  if (server->max > 256)
    server->max = 256;
}

/*
** This function handle a server by itself, just have to tell the port
** and the number of clients expected
*/
t_server	*start_server(int port, int nb)
{
  t_server	*server;

  if ((server = malloc(sizeof(t_server))) == NULL)
    {
      dprintf(2, "Malloc failed\n");
      return (NULL);
    }
  memset(server->clientfds, 0 , sizeof(server->clientfds));
  if (init_server(&(server->network), port, nb) == ERROR)
    return (NULL);
  if (init_ringbuffer(server, nb) == ERROR)
    return (NULL);
  server->to_send = NULL;
  server->clientfds[0].fd = server->network.fd;
  server->clientfds[0].events = POLLIN | POLLOUT;
  server->clientfds[0].revents = 0;
  server->actual = 1;
  server->max = nb;
  if (nb > 1014)
    server->max = 1014;
  return (server);
}

t_client	*start_client(int port, char *ip)
{
  t_client	*client;

  if ((client = malloc(sizeof(t_client))) == NULL)
    {
      dprintf(2, "Malloc failed\n");
      return (NULL);
    }
  if (init_client(client, port, ip) == ERROR)
    return (NULL);
  printf("socket client : [%d]\n", client->network.fd);
  return (client);
}
