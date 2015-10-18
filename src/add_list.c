/*
** add_list.c for zappy in /home/totote/PSU_2014_zappy/lib
** 
** Made by Emeline Gaulard
** Login   <totote@epitech.net>
** 
** Started on  Wed Jun 24 11:48:55 2015 Emeline Gaulard
** Last update Mon Jun 29 11:06:58 2015 Emeline Gaulard
*/

#include "list.h"

int		list_add_elem_at_front(t_list **front_ptr, char *msg, int fd)
{
  t_list	*new;

  if ((new = malloc(sizeof(t_list))) == NULL)
    return (FALSE);
  if (*front_ptr == NULL)
    {
      if ((new = malloc(sizeof(t_list))) == NULL)
	return (FALSE);
      new->msg = msg;
      new->ret = 0;
      new->fd = fd;
      new->next = NULL;
      *front_ptr = new;
      return (TRUE);
    }
  new->msg = msg;
  new->ret = 0;
  new->fd = fd;
  new->next = *front_ptr;
  *front_ptr = new;
  return (TRUE);
}

int		list_add_elem_at_back(t_list **front_ptr, char *msg, int fd)
{
  t_list	*tmp;
  t_list	*new;

  if ((new = malloc(sizeof(t_list))) == NULL)
    return (FALSE);
  tmp = *front_ptr;
  if (tmp == NULL)
    {
      if ((tmp = malloc(sizeof(t_list))) == NULL)
	return (FALSE);
      tmp->msg = msg;
      tmp->fd = fd;
      tmp->ret = 0;
      tmp->next = NULL;
      *front_ptr = tmp;
      return (TRUE);
    }
  while (tmp->next)
    tmp = tmp->next;
  tmp->next = new;
  new->msg = msg;
  new->ret = 0;
  new->fd = fd;
  new->next = NULL;
  return (TRUE);
}

int	list_add_elem_at_position(t_list **front_ptr, char *msg, int fd,
				  unsigned int position)
{
  unsigned int	pos = 0;
  t_list	*tmp;
  t_list	*tmp2;
  t_list	*new;

  if ((new = malloc(sizeof(t_list))) == NULL)
    return (FALSE);
  if (position == 0)
    return (list_add_elem_at_front(front_ptr, msg, fd));
  tmp = *front_ptr;
  tmp2 = (*front_ptr)->next;
  while (pos != (position - 2) && tmp->next != NULL)
    {
      tmp = tmp->next;
      tmp2 = tmp2->next;
      pos++;
    }
  tmp->next = new;
  new->msg = msg;
  new->ret = 0;
  new->fd = fd;
  new->next = tmp2;
  return (TRUE);
}

void		list_update_elem(t_list *list, int fd, ssize_t ret)
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
  return ;
}
