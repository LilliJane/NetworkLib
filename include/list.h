// The MIT License (MIT)
//
// Copyright (c) 2015 Emeline Gaulard
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

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
