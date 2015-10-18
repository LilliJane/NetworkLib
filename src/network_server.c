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

int	init_bind(int fd, struct sockaddr_in *s_in)
{
  if (bind(fd, (const struct sockaddr *)s_in, sizeof(*s_in)) == SOCK_ERR)
    {
      if (close(fd) == CLOSE_ERR)
	return (error("close failed after bind failed"));
      return (ERROR);
    }
  return (SUCCESS);
}

int	to_listen(int fd, int nb)
{
  if (listen(fd, nb) == SOCK_ERR)
    {
      if (close(fd) == CLOSE_ERR)
	return (error("close failed after listen failed"));
      return (error("listen failed"));
    }
  return (SUCCESS);
}

int		to_accept(int fd)
{
  int			client_fd;
  struct sockaddr_in	sin;
  socklen_t		s_size;

  s_size = sizeof(sin);
  if ((client_fd = accept(fd, (struct sockaddr *)&sin, &s_size)) == ERROR)
    {
      if (close(fd) == CLOSE_ERR)
	return (error("close failed after accept failed"));
      return (error("accept failed"));
    }
  return (client_fd);
}

int	init_server(t_network *network, int port, int nb)
{
  int	opt;

  if ((network->pe = getprotobyname("TCP")) == NULL)
    return (error("getprotobyname failed"));
  if ((network->fd = socket(AF_INET, SOCK_STREAM,
			    network->pe->p_proto)) == SOCK_ERR)
    return (error("socket failed"));
  init_struct(&(network->s_in), port, NULL);
  opt = 1;
  if (setsockopt(network->fd, SOL_SOCKET, SO_REUSEADDR,
		 &opt, sizeof(opt)) == SOCK_ERR)
    {
      if (close(network->fd) == CLOSE_ERR)
	return (error("close failed after setsockopt failed"));
      return (error("setsockopt failed"));
    }
  if (init_bind(network->fd, &(network->s_in)) == ERROR)
    return (ERROR);
  if (to_listen(network->fd, nb) == ERROR)
    return (ERROR);
  return (SUCCESS);
}

int	init_ringbuffer(t_server *server, int nb)
{
  int	i;

  if ((server->clientbuffer = malloc(sizeof(t_ringbuffer *) * nb)) == NULL)
    return (ERROR);
  for (i = 0; i < nb; ++i)
    if ((server->clientbuffer[i] = init_buffer(10, 512)) == NULL)
      return (ERROR);
  return (SUCCESS);
}
