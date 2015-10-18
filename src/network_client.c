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

int	connect_client(int fd, struct sockaddr_in s_in)
{
  if (connect(fd, (struct sockaddr *)&s_in, sizeof(s_in)) == ERROR)
    {
      if (close(fd) == CLOSE_ERR)
	return (error("close failed after connect failed"));
      return (error("connect failed"));
    }
  return (SUCCESS);
}

t_client	*set_value(t_client *client)
{
  client->buffer = init_buffer(10, 1024);
  client->to_send = NULL;
  client->server.fd = client->network.fd;
  client->server.events = POLLIN | POLLOUT | POLLHUP;
  client->server.revents = 0;
  return (client);
}

int	init_client(t_client *client, int port, char *ip)
{
  struct hostent	*p;
  int			opt;

  if ((client->network.pe = getprotobyname("TCP")) == NULL)
    return (error("getprotobyname failed"));
  if ((client->network.fd = socket(AF_INET, SOCK_STREAM,
				   client->network.pe->p_proto)) == SOCK_ERR)
    return (error("socket failed"));
  opt = 1;
  if (setsockopt(client->network.fd, SOL_SOCKET, SO_REUSEADDR,
		 &opt, sizeof(opt)) == SOCK_ERR)
    {
      if (close(client->network.fd) == CLOSE_ERR)
	return (error("close failed after setsockopt failed"));
      return (error("setsockopt failed"));
    }
  if ((p = gethostbyname(ip)) == NULL)
    return (error("gethostbyname failed"));
  init_struct(&(client->network.s_in), port,
	      inet_ntoa(*((struct in_addr *)p->h_addr)));
  if (connect_client(client->network.fd, client->network.s_in) == ERROR)
    return (ERROR);
  client = set_value(client);
  return (SUCCESS);
}
