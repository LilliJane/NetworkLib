/*
** utils.c for zappy in /home/totote/PSU_2014_zappy/lib
**
** Made by Emeline Gaulard
** Login   <totote@epitech.net>
**
** Started on  Fri May 15 17:03:46 2015 Emeline Gaulard
** Last update Sun Jul  5 22:40:25 2015 Emeline Gaulard
*/

#include "network.h"

int	check_slot(t_server *server)
{
  if (server->actual < server->max)
    return (SUCCESS);
  return (ERROR);
}

int	fill_slot(t_server *server)
{
  int	ret;

  ret = 0;
  if (check_slot(server) == ERROR)
    return (ERROR);
  server->clientfds[server->actual].events = POLLIN | POLLOUT;
  server->clientfds[server->actual].revents = 0;
  server->clientbuffer[server->actual] = init_buffer(10, 512);
  server->actual += 1;
  if ((ret = send(server->clientfds[server->actual - 1].fd, "BIENVENUE\n",
		  strlen("BIENVENUE\n"), 0)) == ERROR)
    return (error("send welcome message failed"));
  return (SUCCESS);
}

int	close_server(t_server *server)
{
  int	i;

  if (!server)
    return (ERROR);
  for (i = 0; i < server->max; ++i)
    {
      if (i < server->actual)
	{
	  if (close(server->clientfds[i].fd) == CLOSE_ERR)
	    return (error("Closing fd on close_server() failed"));
	}
      free_buffer(server->clientbuffer[i]);
    }
  free(server);
  return (SUCCESS);
}

int	close_client(t_client *client)
{
  if (!client)
    return (ERROR);
  if (close(client->server.fd) == CLOSE_ERR)
    return (error("Closing client fd failed"));
  free_buffer(client->buffer);
  while (list_is_empty(client->to_send) == FALSE)
    list_del_elem_at_back(&(client->to_send));
  if (client)
    free(client);
  return (SUCCESS);
}

int	get_index(t_server *server, int fd)
{
  int	i;

  for (i = 0; i <= server->actual; ++i)
    {
      if (server->clientfds[i].fd == fd)
	return (i);
    }
  return (-1);
}
