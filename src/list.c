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
