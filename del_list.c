/*
** del_list.c for zappy in /home/totote/PSU_2014_zappy/lib
** 
** Made by Emeline Gaulard
** Login   <totote@epitech.net>
** 
** Started on  Wed Jun 24 11:48:19 2015 Emeline Gaulard
** Last update Sat Jul  4 19:51:02 2015 Emeline Gaulard
*/

#include "list.h"

int		list_del_elem_at_front(t_list **front_ptr)
{
  t_list	*tmp;
  t_list	*tmp2;

  if (front_ptr == NULL)
    return (FALSE);
  tmp = *front_ptr;
  tmp2 = (*front_ptr)->next;
  free(tmp);
  (*front_ptr) = tmp2;
  return (TRUE);
}

int		list_del_elem_at_back(t_list **front_ptr)
{
  t_list	*tmp;
  t_list	*tmp2;

  if (!front_ptr)
    return (FALSE);
  tmp = *front_ptr;
  tmp2 = (*front_ptr)->next;
  while (tmp2->next)
    {
      tmp = tmp->next;
      tmp2 = tmp2->next;
    }
  free(tmp2);
  tmp->next = NULL;
  return (TRUE);
}

int		list_del_elem(t_list **front_ptr, int fd)
{
  t_list	*tmp;
  t_list	*tmp2;

  if (front_ptr == NULL)
    return (FALSE);
  if (*front_ptr == NULL)
    return (FALSE);
  tmp = (*front_ptr)->next;
  tmp2 = *front_ptr;
  if (tmp2->fd == fd)
    return (list_del_elem_at_front(front_ptr));
  while (tmp)
    {
      if (tmp->fd == fd)
	{
	  tmp = tmp->next;
	  free(tmp2->next);
	  tmp2->next = tmp;
	  return (TRUE);
	}
      tmp = tmp->next;
      tmp2 = tmp2->next;
    }
  return (FALSE);
}
