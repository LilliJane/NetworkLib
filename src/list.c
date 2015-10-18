/*
** list.c for zappy in /home/totote/PSU_2014_zappy/lib
** 
** Made by Emeline Gaulard
** Login   <totote@epitech.net>
** 
** Started on  Wed Jun 24 11:38:09 2015 Emeline Gaulard
** Last update Sat Jul  4 15:09:25 2015 Emeline Gaulard
*/

#include <stdio.h>
#include "list.h"

unsigned int	list_get_size(t_list *list)
{
  unsigned int	size;
  t_list	*tmp;

  size = 0;
  tmp = list;
  if (tmp == NULL)
    return (0);
  while (tmp)
    {
      size++;
      tmp = tmp->next;
    }
  return (size);
}

int		list_is_empty(t_list *list)
{
  if (list == NULL)
    return (TRUE);
  return (FALSE);
}

void            list_dump(t_list *list)
{
  t_list	*tmp;

  tmp = list;
  while (tmp != NULL)
    {
      printf("fd = %d ret = %d msg = %s\n", tmp->fd, (int)tmp->ret, tmp->msg);
      tmp = tmp->next;
    }
}

/* Value Access */
char		*list_get_elem(t_list *list, int fd)
{
  t_list	*tmp;

  if (!list)
    return (NULL);
  tmp = list;
  while (tmp)
    {
      if (tmp->fd == fd)
	return (&(tmp->msg[tmp->ret]));
      tmp = tmp->next;
    }
  return (NULL);
}

void	add_ret(t_list *list, int fd, int ret)
{
  t_list	*tmp;

  if (!list)
    return ;
  tmp = list;
  while (tmp)
    {
      if (tmp->fd == fd)
	{
	  tmp->ret = ret;
	  return ;
	}
      tmp = tmp->next;
    }
}
