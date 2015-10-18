/*
** list.h for zappy in /home/totote/PSU_2014_zappy/lib
**
** Made by Emeline Gaulard
** Login   <totote@epitech.net>
**
** Started on  Wed Jun 24 11:37:58 2015 Emeline Gaulard
** Last update Sun Jul  5 21:51:51 2015 Thibault Desplat
*/

#ifndef LIST_H_
# define LIST_H_

# include <stdlib.h>

# define TRUE	0
# define FALSE	1

typedef struct  s_list
{
  int		fd;
  ssize_t	ret;
  char		*msg;
  struct s_list	*next;
}               t_list;

/*
** list.c
*/
unsigned int	list_get_size(t_list *list);
int	        list_is_empty(t_list *list);
void		list_dump(t_list *list);
char		*list_get_elem(t_list *list, int fd);
void		add_ret(t_list *list, int fd, int ret);

/*
** add_list.c
*/
int		list_add_elem_at_front(t_list **front_ptr, char *msg, int fd);
int		list_add_elem_at_back(t_list **front_ptr, char *msg, int fd);
int		list_add_elem_at_position(t_list **front_ptr, char *msg, int fd,
					  unsigned int position);
void		list_update_elem(t_list *list, int fd, ssize_t ret);

/*
** del_list.c
*/
int		list_del_elem_at_front(t_list **front_ptr);
int		list_del_elem_at_back(t_list **front_ptr);
int		list_del_elem(t_list **front_ptr, int fd);

#endif /* !LIST_H_ */
