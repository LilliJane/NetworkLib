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
