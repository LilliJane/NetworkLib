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
#include "network.h"

int		disconnect_client(t_server *server, int idx)
{
  int		ret;

  ret = 0;
  while (ret == 0)
    ret = list_del_elem(&(server->to_send), server->clientfds[idx].fd);
  free_buffer(server->clientbuffer[idx]);
  if (close(server->clientfds[idx].fd))
    return (ERROR);
  server->clientfds[idx].fd = -1;
  order_fds(server);
  return (SUCCESS);
}

void		order_fds(t_server *server)
{
  int		i;
  int		j;

  for (i = 0; i < server->actual; ++i)
    {
      if (server->clientfds[i].fd == -1)
	{
	  for (j = i; j < server->actual - 1; ++j)
	    {
	      server->clientfds[j].fd = server->clientfds[j + 1].fd;
	      server->clientbuffer[j] = server->clientbuffer[j + 1];
	    }
	  server->clientfds[j].fd = -1;
	  server->clientbuffer[j] = init_buffer(10, 512);
	  i--;
	  server->actual--;
	}
    }
}

int		data_incoming(t_server *server, int i)
{
  if (server->clientfds[i].fd == server->clientfds[0].fd)
    {
      if ((server->clientfds[server->actual].fd =
	   to_accept(server->clientfds[0].fd)) == ERROR)
	return (ERROR);
      fill_slot(server);
    }
  if (receive_data(server->clientfds[i].fd, server->clientbuffer[i])
      == CLOSE_CONN)
    {
      if (disconnect_client(server, i) == ERROR)
	return (ERROR);
      printf("we are closing connection\n");
    }
  return (SUCCESS);
}

int		check_fd(t_server *server)
{
  int		i;

  for (i = 0; i <= server->actual; i++)
    {
      if (server->clientfds[i].revents & POLLOUT)
	if (send_data(server->clientfds[i].fd, &(server->to_send)) == CLOSE_CONN)
	  if (disconnect_client(server, i) == ERROR)
	    return (ERROR);
      if (server->clientfds[i].revents & POLLIN)
	data_incoming(server, i);
    }
  return (SUCCESS);
}

int		handle(t_server *server, int timeout)
{
  int		ret;

  server->clientfds[0].fd = server->network.fd;
  for (ret = 0; ret < server->actual; ++ret)
    {
      server->clientfds[ret].events = POLLIN | POLLOUT;
      server->clientfds[ret].revents = 0;
    }
  ret = 0;
  ret = poll(server->clientfds, server->max, timeout);
  if (ret == 0)
    return (SUCCESS);
  if (ret > 0)
    return (check_fd(server));
  return (SUCCESS);
}
