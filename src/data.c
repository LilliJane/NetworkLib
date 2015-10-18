/*
** data.c for zappy in /home/totote/PSU_2014_zappy
** 
** Made by Emeline Gaulard
** Login   <totote@epitech.net>
** 
** Started on  Fri Jul  3 17:56:57 2015 Emeline Gaulard
** Last update Thu Jul 16 18:12:50 2015 Emeline Gaulard
*/

#include "network.h"

int	send_data(int fd, t_list **list)
{
  char		*tmp;
  ssize_t	ret;

  ret = 0;
  if ((tmp = list_get_elem(*list, fd)) == NULL)
    return (0);
  if ((ret = send(fd, &tmp[ret], strlen(&tmp[ret]), 0)) == ERROR)
    return (CLOSE_CONN);
  if (ret == (ssize_t)strlen(tmp))
    return (list_del_elem(list, fd));
  else
    list_update_elem(*list, fd, ret);
  return (SUCCESS);
}

int		receive_data(int fd, t_ringbuffer *client)
{
  char		buffer[512];
  int		ret;

  if ((ret = recv(fd, buffer, 514, 0)) > 0)
    {
      buffer[ret] = 0;
      add_item(client, buffer);
    }
  if (ret == 0)
    return (CLOSE_CONN);
  return (SUCCESS);
}
