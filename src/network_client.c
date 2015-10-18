/*
** network_client.c for zappy in /home/gaular_e/PSU_2014_zappy/server
**
** Made by Emeline Gaulard
** Login   <gaular_e@epitech.net>
**
** Started on  Fri May  8 18:43:26 2015 Emeline Gaulard
** Last update Fri Jul  3 18:08:14 2015 Emeline Gaulard
*/

#include <stdio.h>
#include "network.h"

int	connect_client(int fd, struct sockaddr_in s_in)
{
  if (connect(fd, (struct sockaddr *)&s_in, sizeof(s_in)) == ERROR)
    {
      if (close(fd) == CLOSE_ERR)
	return (error("close failed after connect failed"));
      return (error("connect failed"));
    }
  return (SUCCESS);
}

t_client	*set_value(t_client *client)
{
  client->buffer = init_buffer(10, 1024);
  client->to_send = NULL;
  client->server.fd = client->network.fd;
  client->server.events = POLLIN | POLLOUT | POLLHUP;
  client->server.revents = 0;
  return (client);
}

int	init_client(t_client *client, int port, char *ip)
{
  struct hostent	*p;
  int			opt;

  if ((client->network.pe = getprotobyname("TCP")) == NULL)
    return (error("getprotobyname failed"));
  if ((client->network.fd = socket(AF_INET, SOCK_STREAM,
				   client->network.pe->p_proto)) == SOCK_ERR)
    return (error("socket failed"));
  opt = 1;
  if (setsockopt(client->network.fd, SOL_SOCKET, SO_REUSEADDR,
		 &opt, sizeof(opt)) == SOCK_ERR)
    {
      if (close(client->network.fd) == CLOSE_ERR)
	return (error("close failed after setsockopt failed"));
      return (error("setsockopt failed"));
    }
  if ((p = gethostbyname(ip)) == NULL)
    return (error("gethostbyname failed"));
  init_struct(&(client->network.s_in), port,
	      inet_ntoa(*((struct in_addr *)p->h_addr)));
  if (connect_client(client->network.fd, client->network.s_in) == ERROR)
    return (ERROR);
  client = set_value(client);
  return (SUCCESS);
}
