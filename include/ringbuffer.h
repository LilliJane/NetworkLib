/*
** ringbuffer.h for network in /home/totote/PSU_2014_zappy/lib
** 
** Made by Emeline Gaulard
** Login   <totote@epitech.net>
** 
** Started on  Wed Jun 17 14:23:33 2015 Emeline Gaulard
** Last update Tue Jun 30 16:45:29 2015 Emeline Gaulard
*/

#ifndef RINGBUFFER_H_
# define RINGBUFFER_H_

# include <stdlib.h>
# include <string.h>

# define EMPTY	2
# define FULL	1
# define OK	0
# define ERROR	-1

/*
** Ring buffer struct
** Contains:
** - a pointer on the actual buffer in memory
** - a pointer on the buffer end in memory
** - a pointer to the start of valid data
** - a pointer to the end of valid data
** - the number of actual items
*/
typedef struct	s_ringbuffer
{
  char		*buffer;
  unsigned int	start;
  unsigned int	end;
  size_t	count;
  size_t	max;
  size_t	cap;
}		t_ringbuffer;

t_ringbuffer	*init_buffer(size_t max, size_t size);
void		add_item(t_ringbuffer *buffer, char *item);
char		*get_item(t_ringbuffer *buffer, char delim);
void		free_buffer(t_ringbuffer *buf);
int		buffer_status(t_ringbuffer *buf);

#endif /* !RINGBUFFER_H_ */
