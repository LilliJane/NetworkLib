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

#ifndef NETWORK_H_
# define NETWORK_H_

# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <stdlib.h>
# include <unistd.h>
# include <poll.h>
# include <stropts.h>
# include <string.h>
# include "ringbuffer.h"
# include "list.h"

# define SUCCESS	0
# define ERROR		-1
# define CLOSE_ERR	-1
# define SOCK_ERR	-1
# define CLOSE_CONN	2

typedef struct		s_network
{
  struct protoent	*pe;
  struct sockaddr_in	s_in;
  int			fd;
}			t_network;

typedef struct		s_server
{
  t_network		network;
  struct pollfd		clientfds[1024];
  t_ringbuffer		**clientbuffer;
  t_list		*to_send;
  nfds_t		nfds;
  int			timeout;
  int			actual;
  int			max;
}			t_server;

typedef struct		s_client
{
  t_network		network;
  struct pollfd		server;
  t_ringbuffer		*buffer;
  t_list		*to_send;
  nfds_t		nfds;
  int			timeout;
  int			max;
}			t_client;

/*
** network.c
** This file contains the most important functions to auto start client/server
*/
void			init_struct(struct sockaddr_in *s_in, int port, char *ip);
int			error(char *str);
void			update_max(t_server *server, int nb);
t_server		*start_server(int port, int nb);
t_client		*start_client(int port, char *ip);

/*
** network_client.c
** init_client start a client
*/
int			init_client(t_client *client, int port, char *ip);

/*
** network_server.c
** Contains all functions to initialize connection of the server part
*/
int			init_bind(int fd, struct sockaddr_in *s_in);
int			init_server(t_network *network, int port, int nb);
int			to_listen(int fd, int nb);
int			to_accept(int fd);
int			init_ringbuffer(t_server *server, int nb);

/*
** utils.c
** This file contains the useful functions to :
** - set a new client
** - close client/server
** - find the index of the good ringbuffer corresponding to one fd
*/
int			check_slot(t_server *server);
int			fill_slot(t_server *server);
int			close_server(t_server *server);
int			close_client(t_client *client);
int			get_index(t_server *server, int fd);

/*
** handle_poll.c
** This file is about polling events and accepting new clients
*/
int			disconnect_client(t_server *server, int idx);
void			order_fds(t_server *server);
int			handle(t_server *server, int timeout);

/*
** data.c
** This file contains the functions about receiving and sending data
*/
int			send_data(int fd, t_list **list);
int			receive_data(int fd, t_ringbuffer *client);

#endif /* !NETWORK_H_ */
