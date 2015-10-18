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
